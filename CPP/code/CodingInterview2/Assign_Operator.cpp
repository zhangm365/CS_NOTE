

/*
    面试题1：赋值运算符函数
    题目：如下为类型CMyString的声明，请为该类型添加赋值运算符函数。

*/

#include <bits/stdc++.h>

using namespace std;


class CMyString
{
    public:
        CMyString(char *ptrData = nullptr);    //构造函数
        CMyString(const CMyString& temp);   //复制构造函数
        ~CMyString(void);

        //赋值运算符函数
        CMyString& operator = (const CMyString& str);

        void Print();

    private:
        char *m_pData;

    

};

//构造函数
CMyString::CMyString(char *ptrData)
{

    if(ptrData == nullptr)
    {
        m_pData = new char[1];
        m_pData[0] = '\0';

    }
    else
    {
        int len = strlen(ptrData);
        m_pData = new char[len+1];
        strcpy(m_pData, ptrData);

    }

}

CMyString::CMyString(const CMyString& str)
{

    int len = strlen(str.m_pData);
    m_pData = new char[len + 1];
    strcpy(m_pData, str.m_pData);


}

//析构函数
CMyString::~CMyString()
{

    delete [] m_pData;

}


CMyString& CMyString::operator=(const CMyString& str)
{

    if(this != &str)
    {
        CMyString Temp(str);    //创建临时实例
        char *Ptr = Temp.m_pData;
        Temp.m_pData = m_pData;
        m_pData = Ptr;

    }

    return *this;

}


void CMyString::Print()
{
    printf("%s", m_pData);

}

void test1()
{
    printf("Test1 begin:\n");
    char p[] = "hello world!";
    CMyString str1(p);
    CMyString str2;
    str2 = str1;
    CMyString str3(str1);

    printf("Class str1:");
    str1.Print();
    printf("\n");

    printf("Class str2:");
    str2.Print();
    printf("\n");
    
    printf("Class str3:");
    str3.Print();
    printf("\n");

}

//赋值给自己
void test2()
{
    printf("Test2 begin:\n");
    char p[] = "the first c++!";

    CMyString str1(p);
    str1 = str1;

    str1.Print();
    printf("\n");


}

//连续赋值
void test3()
{

    printf("Test3 begin:\n");
    char p[] = "zhangm365";

    CMyString str1(p);
    CMyString str2, str3;
    str3 = str2 = str1;

    printf("Class str1:");
    str1.Print();
    printf("\n");

    printf("Class str2:");
    str2.Print();
    printf("\n");

    printf("Class str3:");
    str3.Print();
    printf("\n");


}



int main()
{
    test1();
    test2();
    test3();
    return 0;
}