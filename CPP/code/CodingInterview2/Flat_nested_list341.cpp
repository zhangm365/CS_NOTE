

// https://leetcode-cn.com/problems/flatten-nested-list-iterator/
// 扁平化嵌套列表迭代器

#include <bits/stdc++.h>


/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 *  
 * */


class NestedInteger 
{
    public:
    // Return true if this NestedInteger holds a single integer, rather than a nested list.
    bool isInteger() const;

    // Return the single integer that this NestedInteger holds, if it holds a single integer
    // The result is undefined if this NestedInteger holds a nested list
    int getInteger() const;

    // Return the nested list that this NestedInteger holds, if it holds a nested list
    // The result is undefined if this NestedInteger holds a single integer
    const std::vector<NestedInteger> &getList() const;

};


class NestedIterator {
public:
    NestedIterator(std::vector<NestedInteger> &nestedList) {
        traverse(nestedList);
    }

    void traverse(const std::vector<NestedInteger> &nestedList)
    {

        for( int i = 0; i < nestedList.size(); ++i)
        {
            // 整数则直接加入res
            if(nestedList[i].isInteger())
            {
                res.push_back(nestedList[i].getInteger());
            }
            else    // 遍历N叉树
                traverse(nestedList[i].getList());  

        }

    }


    int next() {
        return res[i++];
    }
    
    bool hasNext() {
        return i < res.size();
    }

    private:
        std::vector<int> res;
        int i = 0;

};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */