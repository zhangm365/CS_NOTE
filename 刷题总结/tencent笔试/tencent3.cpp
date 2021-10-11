
/*
    计算表达式的值

    运算符： @ > x > +
        @ ：优先级最高
        x : 代表乘法

*/

#include <bits/stdc++.h>

using namespace std;

bool isNum(char c)  // 判断一个字符是否为 [0, 9]
{

    return (c >= '0' && c <= '9');

}


// 计算两个数的值
long TwoOp( long a, long b, char op )
{

    if ( op == '+')
    {
        return a+b;
    }
    
    if ( op == 'x' )
    {
        return a*b;
    }
    
    return a | (a+b);
    
}



int main()
{

    string str;
    cin >> str;

    stack<long> st;    // 操作数栈
    stack<char> op;    // 运算符栈

    int curnum = 0;
    for( const auto& c : str )
    {

        if( isNum(c) )
        {
            curnum = curnum * 10 + c - '0';
            continue;
        }

        st.push(curnum);

        if ( c == '+' )
        {
            while( !op.empty() )
            {
                long b = st.top();
                st.pop();
                long a = st.top();
                st.pop();

                char cop = op.top();
                op.pop();

                long ans = TwoOp(a, b, cop);
                st.push(ans);
            }
        }
        else if( c == 'x' )
        {
            while( !op.empty() )
            {
                if( op.top() == '+' ) break;

                long b = st.top();
                st.pop();
                long a = st.top();
                st.pop();

                char cop = op.top();
                op.pop();

                long ans = TwoOp(a, b, cop);

                st.push(ans);
            }
        }
        else if( c == '@' )
        {
            while(!op.empty())
            {
                if( op.top() == '+' || op.top() == 'x' ) break;

                long b = st.top();
                st.pop();
                long a = st.top();
                st.pop();

                char cop = op.top();
                op.pop();

                long ans = TwoOp(a, b, cop);

                st.push(ans);

            }
        }

        op.push(c);

        curnum = 0;

    }

    st.push(curnum);    // 最后一个一定是数字

    while(!op.empty())
    {
    
        long b = st.top();
        st.pop();
        long a = st.top();
        st.pop();

        char cop = op.top();
        op.pop();

        long ans = TwoOp(a, b, cop);

        st.push(ans);

    }

    cout << st.top() << endl;
    
    return 0;

}