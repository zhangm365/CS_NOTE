


//用两个栈实现一个队列
#include <bits/stdc++.h>

using namespace std;

template <typename T>
class CQueue
{
    public:
        
        void appendTail(const T& value);
        T deleteHead();

    private:
        stack<T> S1;
        stack<T> S2;

};

template <typename T>
void CQueue<T>::appendTail(const T& value)
{
    S1.push(value);
}

template <typename T>
T CQueue<T>::deleteHead()
{   
        
    if(S2.empty())
    {
        while(S1.size() > 0)
        {//将S1中元素依次出栈然后压入S2

            S2.push(S1.top());
            S1.pop();

        }

    }

    if(S2.size() == 0)  //栈为空
    {
        return -1;
    }
        
    T head = S2.top();
    S2.pop();

    return head;

}


int main()
{

    CQueue<char> queue;

    queue.appendTail('a');
    queue.appendTail('b');
    queue.appendTail('c');
    
    char head = queue.deleteHead();
    printf("%c\n", head);

    return 0;

}