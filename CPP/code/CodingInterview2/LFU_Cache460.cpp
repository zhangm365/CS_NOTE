

// https://leetcode-cn.com/problems/lfu-cache/

// LFU缓存：删除使用频次最少的数据

#include <bits/stdc++.h>


class LFUCache
{

    public:
        // default
        LFUCache(){}

        LFUCache( int capacity ) : cap(capacity), minFreq(0) {};
        
        // 获取val
        int get( int key );
        // 添加元素对
        void put( int key, int val );

        // 更新所有表的信息
        void update( int key );

    private:
        std::unordered_map<int, std::pair<int, int>> kVF;  // key->{val, freq}映射

        // store the key position in the linkedlist
        std::unordered_map<int, std::list<int>::iterator> kIter; // key->list iterator

        // 相同的频次freq对应一个双链表
        std::unordered_map<int, std::list<int>> fList; // freq->key list

        int cap;    // 记录缓存容量
        int minFreq;    // 记录最小频次
        
};

void LFUCache::update( int key )
{
    /******* 更新freq ********/

    // step1 : 删除fList中旧的freq节点
    fList[kVF[key].second].erase(kIter[key]);

    // 维护kVF表的freq++
    kVF[key].second++;

    // step2 : 更新fList表freq的信息，kIter的信息
    fList[kVF[key].second].push_back(key);  // 链表尾部添加元素key
    kIter[key] = --fList[kVF[key].second].end();    // kIter指向key在list中的对应位置

    //若当前最小的minFreq对应的链表为空, 则minFreq递加，否则会有空指针
    if( fList[minFreq].empty() )
        minFreq++;


}




int LFUCache::get( int key )
{

    if( !kVF.count(key) ) return -1;
    
    // 更新数据
    update(key);

    return kVF[key].first;  //返回key对应的value


}

// 添加元素
void LFUCache::put( int key, int val )
{

    if( cap <= 0 ) return ;

    // key已存在
    if( kVF.count(key) )
    {
        kVF[key].first = val;
        update(key);
        return;

    }

    // key存在且缓存已满，需要删除freq最小的对应key
    if( kVF.size() >= cap )
    {
        // 更新kVF
        kVF.erase(fList[minFreq].front());
        // 更新kIter
        kIter.erase(fList[minFreq].front());
        // 将最小freq对应的key从链表中删除
        fList[minFreq].pop_front();

    }

    // 新插入元素
    kVF[key] = {val, 1};
    fList[1].push_back(key);
    kIter[key] = --fList[1].end();
    minFreq = 1;
    
}
