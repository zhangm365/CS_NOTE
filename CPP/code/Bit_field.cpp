

// 位段操作

# include <bits/stdc++.h>


struct Bit_field 
{
    unsigned char a : 2;

    unsigned char b : 6;


};


int main()
{

    struct Bit_field Bf = {1, 2};
    
    //std::cout << "Bf.a = " << Bf.a << " Bf.b = " << Bf.b << " sizeof = " << sizeof(Bf) << std::endl;
    std::cout << sizeof(Bf) << std::endl; 

    return 0;

}


