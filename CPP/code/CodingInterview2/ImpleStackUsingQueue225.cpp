

// https://leetcode-cn.com/problems/implement-stack-using-queues/

// 使用队列实现栈


#include <bits/stdc++.h>


class MyStack {
    public:
    /** Initialize your data structure here. */
        MyStack() {

        }
        
        /** Push element x onto stack. */
        void push(int x);
        
        /** Removes the element on top of the stack and returns that element. */
        int pop();
        
        /** Get the top element. */
        int top() ;
        
        /** Returns whether the stack is empty. */
        bool empty() ;


    private:
        std::deque<int> Que;

};



bool MyStack::empty()
{
    return Que.empty();
}

void MyStack::push( int x )
{
    Que.push_back(x);

}



int MyStack::pop()
{
    
    if ( empty() ) return 0;

    int res = Que.back();
    Que.pop_back();

    return res;

}

int MyStack::top()
{

    return Que.back();

}