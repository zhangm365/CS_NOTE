

#include <bits/stdc++.h>

/**---------------------- 解题思路--------------------
lru的思路：删除最久未被使用的数据

**快速查找+数据存储的有序性**
快速查找O(1)完成，那么立即就要想到**哈希表**；
因为哈希表是无序的，所以为了保证数据的**有序性**，可以借助**链表**来实现，插入删除可以在常数时间O(1)内完成，从而标记最久未被使用的数据；
链表的表头为最久未被使用数据，尾部为最近使用数据。所以插入数据要插在链表尾部，删除数据则直接删除表头数据。
1. get方法访问缓存中的数据，并把当前访问的数据标记为最近使用；
2. put方法插入新的元素对；
- 如果已存在key, 则更新对应的val和链表中的位置；
- 若链表未满，则直接插入新数据；
- 若链表已慢，则删除最久未被使用的数据；

***************/



class LRUCache
{

    public:
        // default constructor
        LRUCache(){}
        // 构造函数, 以容量capacity构造初始化LRU缓存
        LRUCache( int capacity ) : cap(capacity){}

        // 若key在缓存中, 则返回key, 否则返回-1
        int get( int key ) ;

        // 若关键字key存在, 则变更其数值-> 若不存在, 则插入该组[关键字-值]
        void put( int key, int value );

        // 更新所有表的数据
        void update( int key );


    private:
        int cap;    // 缓存容量

        std::unordered_map<int, int> kVal;  // key ---> val
        // kIter store the position of the key in list: key ---> list iterator
        std::unordered_map<int, std::list<int>::iterator> kIter;
        // list
        std::list<int> kList;

};

void LRUCache::update( int key )
{

    // step1 : 删除旧数据
    kList.erase(kIter[key]);

    // step2 : 标记为最近使用
    // 插入链表尾部：最近使用数据
    kList.push_back(key);
    // 指向key对应链表中的位置
    kIter[key] = --kList.end();

}



int LRUCache::get( int key )
{
    if( !kVal.count(key) )
    {
        return -1;
    }

    update(key);
    return kVal[key];

}

void LRUCache::put( int key, int val )
{

    if( cap <= 0 ) return ;

    // 已存在
    if( kVal.count(key) )
    {
        // 更新数据
        kVal[key] = val;
        update(key);
        return;
    }

    // 链表已满，删除最久未使用的元素
    if( cap <= kVal.size() )
    {
        // 删除链表头结点
        kIter.erase(kList.front());
        kVal.erase(kList.front());
        kList.pop_front();
    }

    // 添加为最近使用的元素
    kVal[key] = val;
    kList.push_back(key);
    kIter[key] = --kList.end(); 

}
