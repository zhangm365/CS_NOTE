

#include <iostream>


#include <memory>

using namespace std;


int main()
{

    int ix = 1024, *pi = &ix;

    int *pi2 = new int(2048);

    typedef unique_ptr<int> IntUP;



    /**
     * @brief The code below can compile, but will cause error at run time.
     *        The reason is that when the unique_ptr p1 is out of scope, delete will be called
     *        to free th object. But the object is not allocate using new.Thus, an error
     *        would be thrown by operating system.
     *  @badcode
     */
    
    // IntUP u1(pi);   // 运行时错误：free(): invalid_pointer


    /**
     * @brief This code can compile, but cause a dangling pointer at run time.
     *        The reason is that the unique_ptr will free the object the raw pointer
     *        is pointing to.
     * @badcode
     */

    // {IntUP u2(pi2);} // pi2 之后称为悬空指针


    // IntUP u3(&ix);   // 运行时错误：free(): invalid_pointer


    /**
     *   @brief recommended
    
    */

    IntUP u4(new int(2048));   


     /**
     * @brief   error:   double free or corruption at run time
     *          two unique_ptr are pointing to the same object. Thus, when both are out of
     *          scope, Operating system will throw double free or corruption.
     * @badcode
     */

    // IntUP u2(pi2);
    // IntUP u5(u2.get());

    return 0;

}