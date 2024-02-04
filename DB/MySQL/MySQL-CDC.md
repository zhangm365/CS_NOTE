
# MySQL-CDC

- [MySQL-CDC](#mysql-cdc)
  - [1. 代码结构](#1-代码结构)
    - [1.1. `MySqlSchema`](#11-mysqlschema)
      - [1. `MySqlSchema`](#1-mysqlschema)
      - [2. `MySqlDatabaseSchema`](#2-mysqldatabaseschema)
      - [3. `DdlParser`](#3-ddlparser)
      - [4. `DdlChanges`](#4-ddlchanges)
      - [5. `MySqlOffsetContext`](#5-mysqloffsetcontext)
    - [1.2. `binlog`](#12-binlog)
    - [1.3. `MySqlConnectionUtils`](#13-mysqlconnectionutils)
    - [1.4 `snapshot`](#14-snapshot)

基于 `Debezium` 分布式框架实现 `MySQL CDC` 的功能接口。
`Debezium` 通过读取 `MySQL` 的 `binlog` 日志，将数据变更事件转换成 `Kafka` 消息，然后通过 `Kafka Connect` 将消息写入到 `Kafka topic` 集群中。

[`Debezium`](https://github.com/debezium/debezium) 提供了 `MySQL` 的 `Connector` 实现接口，源码目录是[Debezium-connector-MySQL](https://github.com/debezium/debezium/tree/main/debezium-connector-mysql)。

## 1. 代码结构

本文基于开源项目 `Apache SeaTunnel` 实现的 [`MySQL CDC Connector`](https://github.com/apache/seatunnel/tree/dev/seatunnel-connectors-v2/connector-cdc/connector-cdc-mysql)
代码结构，主要包括以下几个组件：`schema`、`kafka connect`等。

### 1.1. `MySqlSchema`

梳理获取 `MySQL` 中 `table schema` 的定义实现。有如下接口功能：

1. 根据 `MySqlConnectionUtils` 连接属性创建 `MySqlDatabaseSchema` 对象，来监听 `SchemaChangeEvent` 事件；
2. 调用 `getTableSchema` 方法，开始解析 `DDL` 语句；

#### 1. `MySqlSchema`

如何获取表的 `schema` 信息？

代码路径：`seatunnel/seatunnel-connectors-v2/connector-cdc/connector-cdc-mysql/src/main/java/org/apache/seatunnel/connectors/seatunnel/cdc/mysql/utils/MySqlSchema.java`

通过函数 `readTableSchema` 获取表的 `schema` 信息，从连接实例的当前纪元解析 `snapshot` 中的 `DDL` 语句，并根据 `databaseName` 进行分流并发送 `SchemaChangeEvent` 事件。

```java
//@start 
public class MySqlSchema {
    
    private static final String SHOW_CREATE_TABLE = "SHOW CREATE TABLE ";

    private final MySqlConnectorConfig connectorConfig;
    /* MySQL database schema 类, 在 debezium 中定义 */。
    private final MySqlDatabaseSchema databaseSchema;

    public MySqlSchema(
            MySqlSourceConfig sourceConfig,
            boolean isTableIdCaseSensitive,
            Map<TableId, CatalogTable> tableMap) {
        this.connectorConfig = sourceConfig.getDbzConnectorConfig();
        this.databaseSchema =
                MySqlConnectionUtils.createMySqlDatabaseSchema(
                        connectorConfig, isTableIdCaseSensitive);
        this.schemasByTableId = new HashMap<>();
        this.tableMap = tableMap;
    }

    /* 获取表的 schema，执行命令 "show create table" */
    public TableChange getTableSchema(JdbcConnection jdbc, TableId tableId) {
        TableChange schema = readTableSchema(jdbc, tableId);
        return schema;
    }

    /* 读取 TableSchema by jdbc connection and tableId. */
    private TableChange readTableSchema(JdbcConnection jdbc, TableId tableId) {
        
        final String sql = SHOW_CREATE_TABLE + MySqlUtils.quote(tableId);
        try {
            jdbc.query(
                sql,
                rs -> {
                    if (rs.next()) {
                        /* 从索引 2 （索引从 1 开始计算）读取 ddl 语句。*/
                        final String ddl = rs.getString(2);
                        /* 初始化 binlog 当前的偏移量。*/
                        final MySqlOffsetContext offsetContext =
                                MySqlOffsetContext.initial(connectorConfig);
                        /** 
                         * 从连接实例的当前时间纪元开始解析 snapshot 中的 DDL 语句
                         * @return List<SchemaChangeEvent>
                         *  
                         **/
                        List<SchemaChangeEvent> schemaChangeEvents =
                                databaseSchema.parseSnapshotDdl(
                                        ddl, tableId.catalog(), offsetContext, Instant.now());
                        /* 根据 TableID 记录 TableChange 事件 */
                        for (SchemaChangeEvent schemaChangeEvent : schemaChangeEvents) {
                            for (TableChange tableChange :
                                    schemaChangeEvent.getTableChanges()) {
                                Table table =
                                        CatalogTableUtils.mergeCatalogTableConfig(
                                                tableChange.getTable(), tableMap.get(tableId));
                                TableChange newTableChange =
                                        new TableChange(
                                                TableChanges.TableChangeType.CREATE, table);
                                tableChangeMap.put(tableId, newTableChange);
                            }
                         }
                    }
                }
            );
        }                    
    }

}  // @end MySqlSchema


/**
 * seatunnel/seatunnel-connectors-v2/connector-cdc/connector-cdc-mysql/src/main/java/org/apache/seatunnel/connectors/seatunnel/cdc/mysql/utils/MySqlConnectionUtils.java
 * 
 * Creates a new {@link MySqlDatabaseSchema} to monitor the latest MySql database schemas. 
 *
 * @topicSelector: topic name: topic_prefix + "." + databaseName + "." + tableName;
 * @schemaNameAdjuster: schema name adjuster for Avro format (serialize and deserializer); 
 *
 **/
public static MySqlDatabaseSchema createMySqlDatabaseSchema(
        MySqlConnectorConfig dbzMySqlConfig, boolean isTableIdCaseSensitive) {
    TopicSelector<TableId> topicSelector = MySqlTopicSelector.defaultSelector(dbzMySqlConfig);
    SchemaNameAdjuster schemaNameAdjuster = SchemaNameAdjuster.create();
    MySqlValueConverters valueConverters = getValueConverters(dbzMySqlConfig);
    return new MySqlDatabaseSchema(
            dbzMySqlConfig,
            valueConverters,
            topicSelector,
            schemaNameAdjuster,
            isTableIdCaseSensitive);
}


/* Schema Change Event */
public class SchemaChangeEvent {
    private TableChanges tableChanges = new TableChanges();

}

/* Table Changes */
public class TableChanges implements Iterable<TableChange> {
   private final List<TableChange> changes;

}

```

#### 2. `MySqlDatabaseSchema`

从 `MySQL Server` 中读取 `schema` 信息。

代码路径：`debezium/debezium-connector-mysql/src/main/java/io/debezium/connector/mysql/MySqlDatabaseSchema.java`

```java
/**
 * 记录 MySQL database Schema 信息。包括：
 * 1. table DDL;
 * 2. Kafka Connects for each table;
 * 
 * **/
public class MySqlDatabaseSchema extends HistorizedRelationalDatabaseSchema {
    // ddl parser based on antlr
    private final DdlParser ddlParser;
    private final RelationalTableFilters filters;
    // 
    private final DdlChanges ddlChanges;
    private final MySqlConnectorConfig connectorConfig;    

    /*
    * :解析 Snapshot DDL 语句，生成 SchemaChangeEvent 事件。
    * @
    */
    public List<SchemaChangeEvent> parseSnapshotDdl(String ddlStatements, String databaseName, MySqlOffsetContext offset, Instant sourceTime) {
        LOGGER.debug("Processing snapshot DDL '{}' for database '{}'", ddlStatements, databaseName);
        return parseDdl(ddlStatements, databaseName, offset, sourceTime, true);
    }
    
    private List<SchemaChangeEvent> parseDdl(String ddlStatements, String databaseName, MySqlOffsetContext offset, Instant sourceTime, boolean snapshot) {
        /*
         * 解析 DDL 语句，生成解析树，并监听解析树的更改事件 {ParseTreeWalker | antlrDdlParserListener}。
        */
        this.ddlParser.parse(ddlStatements, tables()); 
    }       
}

```

#### 3. `DdlParser`

`DDL` 解析器的实现原理。通过 [`ANTLR`](https://github.com/antlr/antlr4) 解析器解析 `MySQL` 的 `DDL` 语句，使用 `Lexer` 和 `Parser` 两个类接口，其中 `Lexer` 是词法分析器，读取 `CodePointCharStream` 字符流结构（Unicode Code Point）， `Parser` 是语法分析器，读取 `Lexer` 生成的 `token` 流，然后作为方法 `parseTree` 的输入对象，生成解析树。

```java
public class MySqlAntlrDdlParser extends AntlrDdlParser<MySqlLexer, MySqlParser> {
    /* 
     * 解析树，调用 `MySqlParser` 的 `root()` 方法，生成解析树。
     */
    @Override
    protected ParseTree parseTree(MySqlParser parser) {
        return parser.root();
    }
}

```

#### 4. `DdlChanges`

监听 `DDL` 变更事件，包括 `EventType` 等事件。

```java
enum EventType {
    CREATE_TABLE,
    ALTER_TABLE,
    DROP_TABLE,
    TRUNCATE_TABLE,
    CREATE_INDEX,
    DROP_INDEX,
    CREATE_DATABASE,
    ALTER_DATABASE,
    DROP_DATABASE,
    USE_DATABASE,
    SET_VARIABLE,
}
```

`debezium/debezium-core/src/main/java/io/debezium/relational/ddl/DdlChanges.java`

```java
public class DdlChanges implements DdlParserListener {
    /* 累积事件流，后续根据不同的 dbName 将 events 进行分流. */
    protected final List<Event> events = new ArrayList<>();
    /* 保存 DDL 涉及的 dbNames. */
    private final Set<String> databaseNames = new HashSet<>();

}
```

#### 5. `MySqlOffsetContext`

跟踪 `change stream` 当前上下文的偏移量。基于 `snapshot` 获取 `incremental event`，并初始化 `binlog` 的偏移量。

```java
/***
 * 计算 MySQL 中 binlog 的上下文 Context 信息。
 ***/
public class MySqlOffsetContext implements OffsetContext {

    private final TransactionContext transactionContext;
    /* 
     * 记录增量快照的上下文信息。
    */
    private final IncrementalSnapshotContext<TableId> incrementalSnapshotContext;
    
    public MySqlOffsetContext(MySqlConnectorConfig connectorConfig, boolean snapshot, boolean snapshotCompleted,
                              TransactionContext transactionContext, IncrementalSnapshotContext<TableId> incrementalSnapshotContext,
                              SourceInfo sourceInfo) {
        partition = Collections.singletonMap(SERVER_PARTITION_KEY, connectorConfig.getLogicalName());
        this.sourceInfo = sourceInfo;
        sourceInfoSchema = sourceInfo.schema();

        this.snapshotCompleted = snapshotCompleted;
        if (this.snapshotCompleted) {
            postSnapshotCompletion();
        }
        else {
            sourceInfo.setSnapshot(snapshot ? SnapshotRecord.TRUE : SnapshotRecord.FALSE);
        }
        this.transactionContext = transactionContext;
        this.incrementalSnapshotContext = incrementalSnapshotContext;
    }

    public MySqlOffsetContext(MySqlConnectorConfig connectorConfig, boolean snapshot, boolean snapshotCompleted, SourceInfo sourceInfo) {
        this(connectorConfig, snapshot, snapshotCompleted, new TransactionContext(), new IncrementalSnapshotContext<>(),
                sourceInfo);
    }


    /**
     * @param config of @link{MySqlConnectorConfig}
     * 
     **/
    public static MySqlOffsetContext initial(MySqlConnectorConfig config) {
        final MySqlOffsetContext offset = new MySqlOffsetContext(config, false, false, new SourceInfo(config));
        offset.setBinlogStartPoint("", 0L); // start from the beginning of the binlog
        return offset;
    }

    /**
     * Set the position in the MySQL binlog where we will start reading.
     * setOffsetContextBinlogPositionAndGtidDetailsForSnapshot
     * @param binlogFilename the name of the binary log file; may not be null
     * @param positionOfFirstEvent the position in the binary log file to begin processing
     */
    public void setBinlogStartPoint(String binlogFilename, long positionOfFirstEvent) {
        assert positionOfFirstEvent >= 0;
        if (binlogFilename != null) {
            sourceInfo.setBinlogPosition(binlogFilename, positionOfFirstEvent);
            this.restartBinlogFilename = binlogFilename;
        }
        else { /* 当前获取的 BinlogFilename ---> SHOW MASTER STATUS; */
            sourceInfo.setBinlogPosition(sourceInfo.getCurrentBinlogFilename(), positionOfFirstEvent);
        }
        this.restartBinlogPosition = positionOfFirstEvent;
        this.restartRowsToSkip = 0;
        this.restartEventsToSkip = 0;
    }

}
```

### 1.2. `binlog`

如何获取 `MySQL` 的 `binlog` 日志的文件名和初始位置？
如何解析 `binlog` 日志的信息？
如何监听 `binlog` 日志的变更事件？

```java
/*** 
 * seatunnel/seatunnel-connectors-v2/connector-cdc/connector-cdc-mysql/src/main/java/org/apache/seatunnel/connectors/seatunnel/cdc/mysql/source/reader/fetch/binlog/MySqlBinlogFetchTask.java
 ***/
public class MySqlBinlogFetchTask implements FetchTask<SourceSplitBase> {
    /* 记录增量分片中捕获的 TableID 集合。 */
    private final IncrementalSplit split;
    private volatile boolean taskRunning = false;

    /***
     * 执行 binlog Fetch 任务。
     * 
     ***/
    public void execute(FetchTask.Context context) throws Exception {

        /***
         * 1. 创建两个实例
         *    a. 连接实例 ---> createMySqlConnection()，记录 hostname, port 等；
         *    b. binlog 客户端实例---> createBinaryClient().
         ***/
        MySqlSourceFetchTaskContext sourceFetchContext = (MySqlSourceFetchTaskContext) context;
        
        /**
         * 2. 根据第 1 步的配置从 Clock.SYSTEM 时刻监听 StreamingChangeEventSource；
         *  2.1 获取 BinaryLogClient 并设置对应的解码器；
         *  2.2 MySqlStreamingChangeEventSourceMetrics 
         *    a. 注册 BinaryLogClient 的 listener：EventListener and LifecycleListener;
         *    b. getSchema() ---> MySqlDatabaseSchema
         */
        MySqlStreamingChangeEventSource mySqlStreamingChangeEventSource =
                new MySqlStreamingChangeEventSource(
                        sourceFetchContext.getDbzConnectorConfig(),
                        sourceFetchContext.getConnection(),
                        sourceFetchContext.getDispatcher(),
                        sourceFetchContext.getErrorHandler(),
                        Clock.SYSTEM, /* 当前时钟 */
                        sourceFetchContext.getTaskContext(),
                        /* new BinaryLogClientStatistics(client); 注册监听器 */
                        sourceFetchContext.getStreamingChangeEventSourceMetrics());
        
        /**
         * 2.1 MySqlStreamingChangeEventSource 构造函数
         *  设置 BinaryLogClient 的解码器
         */
        public MySqlStreamingChangeEventSource(...) {
            // Set up the log reader ...
            BinaryLogClient client = taskContext.getBinaryLogClient();
            // ...
            // binlog 解码器，根据 tableId 处理 tableEvent
            EventDeserializer eventDeserializer = new EventDeserializer();
            client.setEventDeserializer(eventDeserializer);

        }

        /**
         * 3. start the log reader 
         */
        BinlogSplitChangeEventSourceContext changeEventSourceContext =
                new BinlogSplitChangeEventSourceContext();

        mySqlStreamingChangeEventSource.execute(
                changeEventSourceContext, sourceFetchContext.getOffsetContext());
    }        
    
    public class MySqlStreamingChangeEventSource implements StreamingChangeEventSource<MySqlOffsetContext> {
        //...

        // 实现：执行 binlog 日志的读取
        @Override
        public void execute(ChangeEventSourceContext context, MySqlOffsetContext offsetContext) throws InterruptedException {
            // 
            if (!connectorConfig.getSnapshotMode().shouldStream()) {
                LOGGER.info("Streaming is disabled for snapshot mode {}", connectorConfig.getSnapshotMode());
                return;
            }
            taskContext.getSchema().assureNonEmptySchema();
            final Set<Operation> skippedOperations = connectorConfig.getSkippedOperations();

            /**
             * 根据获取的 binlog filename 和 position 调用 MySqlOffsetContext.initial() 方法初始化 binlog 的偏移量。
             **/
            final MySqlOffsetContext effectiveOffsetContext = offsetContext != null
                    ? offsetContext
                    : MySqlOffsetContext.initial(connectorConfig);    
        
            /// ...

            /** 读取 binlog ---> client.connect(timeout); **/
            try {
                // Start the log reader, which starts background threads ...
                if (context.isRunning()) { // binlogSplitChangeEventSourceContext.
                    long timeout = connectorConfig.getConnectionTimeout().toMillis();
                    long started = clock.currentTimeInMillis();
                    try {
                        LOGGER.debug("Attempting to establish binlog reader connection with timeout of {} ms", timeout);
                        client.connect(timeout);
                    }
                 }
            }
        }

    } // @end MySqlStreamingChangeEventSource

    /*
     * 在一个单独的线程中连接到复制流。 
     */
    public void connect(final long timeout) throws IOException, TimeoutException {
        final CountDownLatch countDownLatch = new CountDownLatch(1);    
        // ...

        // 创建线程，执行 client.connect() 方法
        Runnable runnable = new Runnable() {

            @Override
            public void run() {
                try {
                    setConnectTimeout(timeout);
                    connect(); // 执行连接
                } catch (IOException e) {
                    exceptionReference.set(e);
                    countDownLatch.countDown(); // making sure we don't end up waiting whole "timeout"
                } catch (Exception e) {
                    exceptionReference.set(new IOException(e)); // method is asynchronous, catch all exceptions so that they are not lost
                    countDownLatch.countDown(); // making sure we don't end up waiting whole "timeout"
                }
            }
        };         
    } // @end connect(timeout)


    /**
     * Connect to the replication stream.
     * 1. 加锁: connectLock.tryLock()
     * 2. 创建 socket 管道: openChannel()
     * 3. 获取 binlog filename and position: fetchBinlogFilenameAndPosition()
     * 4. 建立连接: setupConnection()
     * 5. 请求 binlog 日志流: requestBinaryLogStream()
     * 6. 监听事件包: listenForEventPackets()
     * 
     */
    public void connect() throws IOException, IllegalStateException {
        if (!connectLock.tryLock()) { // 加锁
            throw new IllegalStateException("BinaryLogClient is already connected");
        }
        boolean notifyWhenDisconnected = false;
        try {
                Callable cancelDisconnect = null;
                try {
                    try {
                        long start = System.currentTimeMillis();

                        // 创建 socket 管道
                        channel = openChannel();
                    }

                    // 获取 binlog filename and position
                    if (binlogFilename == null) {
                        fetchBinlogFilenameAndPosition();
                    }

                    // 建立连接
                    setupConnection();
                    gtid = null;
                    tx = false;
                    // 请求 binlog 日志流
                    requestBinaryLogStream();

                    // 设置事件包的解码器
                    ensureEventDataDeserializer(EventType.ROTATE, RotateEventDataDeserializer.class);
                    synchronized (gtidSetAccessLock) {
                        if (gtidSet != null) {
                            ensureEventDataDeserializer(EventType.GTID, GtidEventDataDeserializer.class);
                            ensureEventDataDeserializer(EventType.QUERY, QueryEventDataDeserializer.class);
                        }
                    }
                    // 读取事件包，并解析
                    listenForEventPackets();
                    
                }  
        }
        finally {
            connectLock.unlock(); // 解锁
        }

    } // @end connect()

```

### 1.3. `MySqlConnectionUtils`

代码路径 `seatunnel/seatunnel-connectors-v2/connector-cdc/connector-cdc-mysql/src/main/java/org/apache/seatunnel/connectors/seatunnel/cdc/mysql/utils/MySqlConnectionUtils.java`。

模块的主要功能：

1. 创建 `MySqlConnection` 连接实例；
2. 创建 `BinaryClient` 实例，用于消费 `MySQL binlog`；
3. 创建 `MySqlDatabaseSchema` 实例，记录 `Schema History for databases hosted by mysqld`；

```java
/** MySQL connection Utilities. */
public class MySqlConnectionUtils {

    /** Creates a new {@link BinaryLogClient} for consuming mysql binlog. 
     * 调用方法 fetchBinlogFilenameAndPosition() ---> SHOW MASTER STATUS 获取当前 binlog filename 和 position;
    */
    public static BinaryLogClient createBinaryClient(Configuration dbzConfiguration) {
        final MySqlConnectorConfig connectorConfig = new MySqlConnectorConfig(dbzConfiguration);
        return new BinaryLogClient(
                connectorConfig.hostname(),
                connectorConfig.port(),
                connectorConfig.username(),
                connectorConfig.password());
    }
}
```

### 1.4 `snapshot`

如何获取 `snapshot` ？

快照格式：
`[low watermark event][snapshot events][high watermark event]`

通过 `MySqlSnapshotFetchTask` 实现 `snapshot` 的获取。

```java
/***
 * seatunnel/seatunnel-connectors-v2/connector-cdc/connector-cdc-mysql/src/main/java/org/apache/seatunnel/connectors/seatunnel/cdc/mysql/source/reader/fetch/scan/MySqlSnapshotFetchTask.java
 * 
 * 
 ***/
@Slf4j
public class MySqlSnapshotFetchTask implements FetchTask<SourceSplitBase> {

    /* 快照分片标识符 */
    private final SnapshotSplit split;

    private volatile boolean taskRunning = false;

    /* snapshot split 读取任务 */
    private MySqlSnapshotSplitReadTask snapshotSplitReadTask;

    public MySqlSnapshotFetchTask(SnapshotSplit split) {
        this.split = split;
    }


    /***
     * 执行快照任务
     * 
     * @param context
     * @throws Exception
     */

    @Override
    public void execute(FetchTask.Context context) throws Exception {
        MySqlSourceFetchTaskContext sourceFetchContext = (MySqlSourceFetchTaskContext) context;
        taskRunning = true;
        

        /**
         * 1. 创建分片读取任务的实例
         *  从 Clock.SYSTEM 开启
         */
        snapshotSplitReadTask =
                new MySqlSnapshotSplitReadTask(
                        sourceFetchContext.getDbzConnectorConfig(),
                        sourceFetchContext.getOffsetContext(),
                        sourceFetchContext.getSnapshotChangeEventSourceMetrics(),
                        sourceFetchContext.getDatabaseSchema(),
                        sourceFetchContext.getConnection(),
                        sourceFetchContext.getDispatcher(),
                        split);

        // 2. 执行分片读取任务
        SnapshotSplitChangeEventSourceContext changeEventSourceContext =
                new SnapshotSplitChangeEventSourceContext();
        SnapshotResult snapshotResult =
                snapshotSplitReadTask.execute(
                        changeEventSourceContext, sourceFetchContext.getOffsetContext());
        if (!snapshotResult.isCompletedOrSkipped()) {
            taskRunning = false;
            throw new IllegalStateException(
                    String.format("Read snapshot for split %s fail", split));
        }

        boolean changed =
                changeEventSourceContext
                        .getHighWatermark()
                        .isAfter(changeEventSourceContext.getLowWatermark());
        if (!context.isExactlyOnce()) {
            taskRunning = false;
            if (changed) {
                log.debug("Skip merge changelog(exactly-once) for snapshot split {}", split);
            }
            return;
        }

        final IncrementalSplit backfillSplit = createBackfillBinlogSplit(changeEventSourceContext);
        // optimization that skip the binlog read when the low watermark equals high
        // watermark
        if (!changed) {
            dispatchBinlogEndEvent(
                    backfillSplit,
                    ((MySqlSourceFetchTaskContext) context).getOffsetContext().getPartition(),
                    ((MySqlSourceFetchTaskContext) context).getDispatcher());
            taskRunning = false;
            return;
        }

        final MySqlBinlogFetchTask.MySqlBinlogSplitReadTask backfillReadTask =
                createBackfillBinlogReadTask(backfillSplit, sourceFetchContext);
        log.info(
                "start execute backfillReadTask, start offset : {}, stop offset : {}",
                backfillSplit.getStartupOffset(),
                backfillSplit.getStopOffset());
        backfillReadTask.execute(
                new SnapshotBinlogSplitChangeEventSourceContext(),
                sourceFetchContext.getOffsetContext());
        log.info("backfillReadTask execute end");

        taskRunning = false;
    } // @end execute((FetchTask.Context context)

} // @end MySqlSnapshotFetchTask


/* 快照分片读取任务的构造函数 */
public class MySqlSnapshotSplitReadTask extends AbstractSnapshotChangeEventSource {

    private static final Logger LOG = LoggerFactory.getLogger(MySqlSnapshotSplitReadTask.class);

    /** Interval for showing a log statement with the progress while scanning a single table. */
    private static final Duration LOG_INTERVAL = Duration.ofMillis(10_000);

    // ...

    // Decode text protocol value for MySQL
    private final MysqlTextProtocolFieldReader mysqlTextProtocolFieldReader =
            new MysqlTextProtocolFieldReader();

    public MySqlSnapshotSplitReadTask(
            MySqlConnectorConfig connectorConfig,
            MySqlOffsetContext previousOffset,
            SnapshotProgressListener snapshotProgressListener,
            MySqlDatabaseSchema databaseSchema,
            MySqlConnection jdbcConnection,
            JdbcSourceEventDispatcher dispatcher,
            SnapshotSplit snapshotSplit) {
        super(connectorConfig, snapshotProgressListener);
        this.offsetContext = previousOffset;
        this.connectorConfig = connectorConfig;
        this.databaseSchema = databaseSchema;
        this.jdbcConnection = jdbcConnection;
        this.dispatcher = dispatcher;
        this.clock = Clock.SYSTEM; // 当前时钟
        this.snapshotSplit = snapshotSplit;
        this.snapshotProgressListener = snapshotProgressListener;
    }

    @Override
    public SnapshotResult execute(
            ChangeEventSource.ChangeEventSourceContext context, OffsetContext previousOffset)
            throws InterruptedException {
        SnapshottingTask snapshottingTask = getSnapshottingTask(previousOffset);
        final SnapshotContext ctx;
        try {
            ctx = prepare(context);
        }
        try {
            return doExecute(context, previousOffset, ctx, snapshottingTask);
       
        }
    } // @end execute(context, offset)


    /**
     * 执行生成快照的任务。
     * [low watermark event][snapshot events][high watermark event] 
     * lowWatermark: 第一次读取 binlog 的偏移量，低水位；
     * createDataEvents：创建数据事件，读取当前的表数据；
     * highWatermark: 获取表数据后再次记录 binlog 的偏移量，高水位；
     */
    @Override
    protected SnapshotResult doExecute(
            ChangeEventSource.ChangeEventSourceContext context,
            OffsetContext previousOffset,
            AbstractSnapshotChangeEventSource.SnapshotContext snapshotContext,
            AbstractSnapshotChangeEventSource.SnapshottingTask snapshottingTask)
            throws Exception {
        final RelationalSnapshotChangeEventSource.RelationalSnapshotContext ctx =
                (RelationalSnapshotChangeEventSource.RelationalSnapshotContext) snapshotContext;
        ctx.offset = offsetContext;

        final BinlogOffset lowWatermark = currentBinlogOffset(jdbcConnection);
        LOG.info(
                "Snapshot step 1 - Determining low watermark {} for split {}",
                lowWatermark,
                snapshotSplit);
        ((SnapshotSplitChangeEventSourceContext) context).setLowWatermark(lowWatermark);
        dispatcher.dispatchWatermarkEvent(
                offsetContext.getPartition(), snapshotSplit, lowWatermark, WatermarkKind.LOW);

        LOG.info("Snapshot step 2 - Snapshotting data");
        createDataEvents(ctx, snapshotSplit.getTableId());

        final BinlogOffset highWatermark = currentBinlogOffset(jdbcConnection);
        LOG.info(
                "Snapshot step 3 - Determining high watermark {} for split {}",
                highWatermark,
                snapshotSplit);
        ((SnapshotSplitChangeEventSourceContext) context).setHighWatermark(highWatermark);
        dispatcher.dispatchWatermarkEvent(
                offsetContext.getPartition(), snapshotSplit, highWatermark, WatermarkKind.HIGH);
        return SnapshotResult.completed(ctx.offset);
    } // @end doExecute
    
} // @end MySqlSnapshotSplitReadTask

```
