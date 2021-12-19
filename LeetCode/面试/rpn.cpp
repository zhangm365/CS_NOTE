#include <bits/stdc++.h>

using namespace std;
vector<string> dst;
stack<int> nums;

// 中缀表达式转为后缀表达式

bool isOperator( char c )
{
    if( c == '+' || c == '-' || c == '*' || c == '/' )
        return true;
    
    return false;
}

int getPrior(char c)
{
    int level = 0;
    
    switch(c)
    {
        case '(':
            level = 1;
            break;
        case '+':
        case '-':
            level = 2;
            break;
        case '*':
        case '/':
            level = 3;
            break;
        case ')':
            level = 4;
            break;
        default:
            break;
    }
    
    return level;
}

void inToRPN(const string &src )
{
    
    int len = src.size();
    int num = 0;
    int i = 0;
    stack<char> op;
    
    while( i < len )
    {
        if(isdigit(src[i]))    // 数字
        {
            num = 0;
            do{
                num = num*10 + (src[i] - '0');
                i++;
            }while(i < len && isdigit(src[i]));
            
            dst.push_back(to_string(num));
            
        }
        else if(src[i] == '(')
        {
            op.push(src[i]);
            i++;
        }
        else if(isOperator(src[i]))
        {
            if(op.empty())
            {
                op.push(src[i]);
                i++;
            }
            else
            {
                while(!op.empty())
                {
                    char c = op.top();
                    if(getPrior(c) >= getPrior(src[i]))
                    {
                        string tmp = " ";
                        tmp[0] = c;
                        dst.push_back(tmp);
                        op.pop();
                    }
                    else
                    {
                        break;
                    }
                }
                op.push(src[i]);
                i++;
            }
        }
        else if(src[i] == ')')
        {
            while( op.top() != '(' )
            {
                string tmp = " ";
                tmp[0] = op.top();
                dst.push_back(tmp);
                op.pop();
            }
            op.pop();
            i++;
        }
        else
        {
            i++;
        }
        
    }
    
    while(!op.empty())
    {
        string tmp = " ";
        tmp[0] = op.top();
        dst.push_back(tmp);
        op.pop();
    }
        
}

void helper( const string &str )
{
    int second = nums.top();
    nums.pop();
    int first = nums.top();
    nums.pop();
    
    int res;
    
    if(str == "+")
        res = first + second;
    else if(str == "-")
        res = first - second;
    else if(str == "*")
        res = first * second;
    else if(str == "/")
        res = first/second;
   
    nums.push(res);
}

int main()
{
    
    string src;
    cin >> src;
    inToRPN(src);
    
    
    for( const auto &s : dst )
    {
        if( s == "+" || s == "-" || s == "*" || s == "/" )
            helper(s);
        else
            nums.push(atoi(s.c_str()));
    }
    
    printf("%d\n", nums.top());
    
    return 0;
    
}