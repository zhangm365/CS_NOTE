CC     := clang
CFLAGS := -Wall -Werror -I../include -pthread

OS     := $(shell uname -s)
LIBS   :=
ifeq ($(OS),Linux)
	LIBS += -pthread
endif

SRCS        := condition_variable.c
OBJS        := ${SRCS:.c=.o}

# 保留中间产物 .o：避免 make 把作为中间文件的 .o 在构建结束时删除
.SECONDARY: $(OBJS)

BIN_DIR     := bin
PROG_NAMES  := ${SRCS:.c=}
PROGS       := $(addprefix $(BIN_DIR)/, $(PROG_NAMES))

.PHONY: all clean
all: ${PROGS}

# 链接到 bin 目录，确保 bin 目录存在
$(BIN_DIR)/%: %.o Makefile | $(BIN_DIR)
	${CC} $< -o $@ ${LIBS}

# 生成 bin 目录（注意：下面一行前面是 TAB 不是空格）
$(BIN_DIR):
	mkdir -p $@

clean:
	rm -f ${PROGS} ${OBJS}

%.o: %.c Makefile
	${CC} ${CFLAGS} -c $<