

// sizeof的一些操作

# include <bits/stdc++.h>

// 空类
class A
{
    // brief : 空类占1个字节

};

class B
{

    // brief : 字节对齐来计算大小： 4+4+8
    public:
        char ch;
        int a;
        
        static int b;
        static int c;
        virtual void foo();     //含有虚函数，有且仅有一个虚指针，64位os中占用8个字节         
        virtual int fun(int x);

};

class VA
{

    public:
        virtual void f1()
        {
            std::cout << "VA: f1()" << std::endl;
        }
        
        virtual void f2()
        {
            std::cout << "VA: f2()" << std::endl;
        }

        virtual void f3()
        {
            std::cout << "VA: f3()" << std::endl;
        }

};



class VC : public VA
{
    // brief: 继承所有基类vptr指针大小
    public:
        virtual void f1()
        {
            std::cout << "VC: f1()" << std::endl;
        }

        virtual void f2()
        {
            std::cout << "VC: f2()" << std::endl;
        }
        
        virtual void f3()
        {
            std::cout << "VC: f3()" << std::endl;
        }


};

/**
 * @brief 函数指针
**/

typedef void (*Fun)();


Fun getAddr(void* obj, unsigned int offset)
{
    std::cout<<"======================="<< std::endl;
    void* vptr_addr = (void*)(std::uintptr_t)(*(unsigned long *)obj);  //64位操作系统，占8字节，通过*(unsigned long *)obj取出前8字节，即vptr指针
    printf("vptr_addr:%p\n",vptr_addr);

    /**
     * @brief 通过vptr指针访问virtual table，因为虚表中每个元素(虚函数指针)在64位编译器下是8个字节，因此通过*(unsigned long *)vptr_addr取出前8字节，
     * 后面加上偏移量就是每个函数的地址！
     */
    
    void* func_addr = (void *)(std::uintptr_t)*( (unsigned long *)vptr_addr + offset );
    printf("func_addr:%p\n",func_addr);
    return (Fun)func_addr;

}


int main()
{

    printf("A: %d\n", sizeof(A));
    // 字节对齐, vptr占用8字节大小
    printf("B: %d\n", sizeof(B));

    printf("VA = %d, VC: %d\n", sizeof(VA), sizeof(VC));

    VA *pa = new VC();
  
    Fun f1 = getAddr(pa, 0);
    (*f1)();

    // Fun f2 = getAddr(pa, 1);
    // (*f2)();

    VA *pt = new VA();

    Fun f3 = getAddr(pt, 0);
    (*f3)();

    delete pa;
    delete pt;

    return 0;


}