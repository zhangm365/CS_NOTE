

// https://leetcode-cn.com/problems/implement-queue-using-stacks/
// 两个栈实现队列


#include <bits/stdc++.h>


class MyQueue
{
    public:
        MyQueue(){}
        // 入队
        void push( int x );
        // 出队
        int pop();
        // 返回队首元素
        int peek();
        // 是否为空
        bool empty();
        // 更新数据
        void update();

    private:
        std::stack<int> st1;
        std::stack<int> st2;

};

void MyQueue::update()
{
    while( !st1.empty() )
    {
        st2.push(st1.top());
        st1.pop();
    }

}


void MyQueue::push( int x )
{

    st1.push(x);

}

int MyQueue::pop()
{

    if( empty() ) return 0;

    // 更新两个栈中数据。st2为空, 那么就把st1的数据全部压入st2，否则直接返回st2的数据
    if( st2.empty() )
        update();

    int res = st2.top();
    st2.pop();

    return res;

}

bool MyQueue::empty()
{

    return ( st1.empty() && st2.empty() );

}

int MyQueue::peek()
{

    if( empty() ) return 0;
    if( st2.empty() )
        update();
    return st2.top();

}