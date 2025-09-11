
#include <bits/stdc++.h>
#include <ext/pool_allocator.h>

using namespace std;

template<typename Alloc>
void cookie_test(Alloc alloc, size_t n)
{
    typename Alloc::value_type *p1, *p2, *p3;
    p1 = alloc.allocate(n);
    p2 = alloc.allocate(n);
    p3 = alloc.allocate(n);



    cout << "p1 = " << p1 << '\t' << "p2 = " << p2 << '\t' << "p3 = " << p3 << endl;

    alloc.deallocate(p1, sizeof(typename Alloc::value_type));
    alloc.deallocate(p2, sizeof(typename Alloc::value_type));
    alloc.deallocate(p3, sizeof(typename Alloc::value_type));


}

int main()
{

    cout << sizeof(__gnu_cxx::__pool_alloc<int>) << endl;    // 1
    
    cookie_test(__gnu_cxx::__pool_alloc<int>(), 1);    // p1 = 0x721ac0   p2 = 0x721ac8   p3 = 0x721ad0. 每个地址相差 08h, 表示不带 cookie
    cookie_test(std::allocator<int>(), 1);    // p1 = 0xf81c10   p2 = 0xf81c30   p3 = 0xf81c50. 每个地址相差 20h, 标准库分配器每次分配带有 cookie

   
    return 0;

}

