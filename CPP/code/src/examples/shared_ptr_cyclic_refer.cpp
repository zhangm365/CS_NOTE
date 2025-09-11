
/*
//  1. 两个 shared_ptr 循环引用
#include <memory>
#include <iostream>

struct B;
struct A {
  std::shared_ptr<B> pb;  
  ~A() { std::cout << "~A()\n"; }
};

struct B {
  // std::shared_ptr<A> pa;
  std::weak_ptr<A> pa;  // 改进方式是使用 weak_ptr
  ~B() { std::cout << "~B()\n"; }  
};

void useAnB() {
  auto ptr_A = std::make_shared<A>();
  auto ptr_B = std::make_shared<B>();
  ptr_A->pb = ptr_B;  // 相互引用
  ptr_B->pa = ptr_A;
}

int main() {
   useAnB();
   std::cout << "Finished using A and B\n";
}
*/


// 2. 对象自引用
#include <iostream>
#include <memory> // for std::shared_ptr

class Resource {
public:
	std::shared_ptr<Resource> m_ptr; // shared_ptr
  // std::weak_ptr<Resource> m_ptr;
	Resource() { std::cout << "Resource acquired\n"; }
	~Resource() { std::cout << "Resource destroyed\n"; }
};

int main() {
	auto ptr1 = std::make_shared<Resource>();

	ptr1->m_ptr = ptr1; // m_ptr is now sharing the Resource that contains it
  // 没有调用析构函数，造成内存泄露
	return 0;
}

