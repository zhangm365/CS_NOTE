



// https://leetcode-cn.com/problems/sliding-window-maximum/

# include<bits/stdc++.h>


// 单调队列的实现: 利用双链表结构实现
class MonotonicQueue
{
    public:
        // 双链表
        std::list<int> q;

        // 压入元素
        void push( int n );

        // 求队列中最大值
        int max();

        // 弹出值为n的元素
        void pop( int n );
};


void MonotonicQueue::push( int n )
{
    // 把比n小的元素全部出队：单调递减
    while( !q.empty() && n > q.back() )
        q.pop_back();

    // 将元素加入尾部：队头存储的最大元素
    q.push_back(n);

}

// 弹出值为n的元素
void MonotonicQueue::pop( int n )
{

    if ( n == q.front() )
        q.pop_front();

}


// 返回单调队列中的最大元素
int MonotonicQueue::max()
{

    return q.front();

}


class Solution 
{
    public:
        std::vector<int> maxSlidingWindow(std::vector<int>& nums, int k) ;
    
    private:
        MonotonicQueue MaxWindow;

};



std::vector<int> Solution::maxSlidingWindow( std::vector<int> &nums, int k )
{

    if( nums.empty() || k <= 0 ) return {};

    std::vector<int> res;

    for ( int i = 0 ; i < nums.size(); ++i )
    {
        
        // 先把k-1个元素放入窗口
        if( i < k - 1 )
        {
            MaxWindow.push(nums[i]);
        }
        else
        {
            // 窗口向前滑动
            MaxWindow.push(nums[i]);

            // 加入当前窗口的最大值
            res.push_back(MaxWindow.max());
            // 移除窗口旧数据
            MaxWindow.pop(nums[i-k+1]);
        }
    
    }

    return res;

}