


#include <bits/stdc++.h>

using namespace std;


template <class T>
class Smart_Pointer
{
    public:
    
        Smart_Pointer(T *p = nullptr) : _ptr(p) 
        {

            if( _ptr )
            {
                _count = new size_t(1);
            }
            else
                _count = new size_t(0);

        }

        Smart_Pointer(const Smart_Pointer& pS)
        {
            if( this != &pS )
            {
                this->_ptr = pS._ptr;
                this->_count = pS._count;
                (*this->_count)++;
            }
        }

        Smart_Pointer& operator=(const Smart_Pointer& pS)
        {
            if(this->_ptr == pS._ptr) return *this;

            if(this->_ptr)
            {
                (*this->_count)--;
                if( (*this->_count) == 0 )
                {
                    delete _ptr;
                    delete _count;
                }
            }

            this->_ptr = pS._ptr;
            this->_count = pS._count;
            (*this->_count)++;

            return *this;

        }


        ~Smart_Pointer()
        {



        }



        T& operator*() const {
            return *_ptr;
        }

        T* operator->() const {

            return _ptr;
        }

        size_t use_count()
        {
            return *(this->_count);
        }
        

        
    private:
        T* _ptr;
        size_t* _count;
};





int main()
{
    
    Smart_Pointer<int> sp(new int(10));
    Smart_Pointer<int> s1(sp);
    Smart_Pointer<int> s2 = sp;

    cout << "sp = " << sp.use_count() << endl;    
    cout << "s1 = " << s1.use_count() << endl;

    Smart_Pointer<int> st(new int(20));
   
    s1 = st;


    cout << "sp = " << sp.use_count() << endl;
    cout << "st = " << st.use_count() << endl;

    return 0;
    
}