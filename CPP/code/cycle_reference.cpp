#include <memory>
#include <iostream>

class B; // Forward declaration

class A {
public:
    std::shared_ptr<B> b_ptr;
    A() { std::cout << "A constructor\n"; }
    ~A() { std::cout << "A destructor\n"; }
};

class B {
public:
    std::shared_ptr<A> a_ptr;
    B() { std::cout << "B constructor\n"; }
    ~B() { std::cout << "B destructor\n"; }
};

int main() {
    std::shared_ptr<A> pa = std::make_shared<A>();
    std::shared_ptr<B> pb = std::make_shared<B>();

    pa->b_ptr = pb; // A holds a strong reference to B
    pb->a_ptr = pa; // B holds a strong reference to A

    // When pa and pb go out of scope, their reference counts for the objects
    // they manage will not drop to zero because of the circular dependency.
    // This results in a memory leak.
    return 0;
}

#include <memory>
#include <iostream>

class A; // Forward declaration

class B {
public:
    std::weak_ptr<A> a_weak_ptr; // Weak reference
    B() { std::cout << "B constructor\n"; }
    ~B() { std::cout << "B destructor\n"; }
};

class A {
public:
    std::shared_ptr<B> b_ptr;
    A() { std::cout << "A constructor\n"; }
    ~A() { std::cout << "A destructor\n"; }
};

int main() {
    std::shared_ptr<A> pa = std::make_shared<A>();
    std::shared_ptr<B> pb = std::make_shared<B>();

    pa->b_ptr = pb;
    pb->a_weak_ptr = pa; // Now B holds a weak reference to A

    // When pa and pb go out of scope, the objects will be correctly destroyed.
    return 0;
}