# `implicit_cast` 用法

## 1. `upcast`

that is, cast a pointer from type `Foo` to type `SuperclassOfFoo`.
`upcase` 总是成功的。但是使用 `implicit_cast<>` 是更好的，它可以检查类型是否正确。

## 2. `downcast`

that is, cast a pointer from type `Foo` to type `SubclassOfFoo`.
使用 `static_cast<>` 进行转换是不安全的，因为：

1. `Foo` 可能是空的；
2. `DifferentSubclassOfFoo；`

使用 `static_cast<>` 在 `downcast` 时不会报错。在 `debug` 模式下，可以使用 `dynamic_cast<>` 对 `downcast` 进行安全检查，但是在 `release` 模式下不会报错，这是因为 `static_cast<>` 不会进行运行时检查。

## 3. `implicit_cast`

使用 `implicit_cast` 作为 `static_cast` 和 `const_cast` 的安全版本，以便在层次关系中进行向上转换(`upcast`)。
>> `implicit_cast` 只能在 `upcast` 中使用。

在 `boost` 中，`implicit_cast` 的实现如下：

```cpp
// https://www.boost.org/doc/libs/1_82_0/boost/implicit_cast.hpp

template<class T> struct identity_ {
    typedef T type;
};

// The use of identity creates a non-deduced form, so that the
// explicit template argument must be supplied
template <typename T>
inline T implicit_cast (typename identity_<T>::type x) {
    return x;
}

```

```cpp
#include<boost/implicit_cast.hpp>
#include<iostream>

// 菱形继承
class Top {

};
class MiddleA : public Top {

};
class MiddleB : public Top {

};
class Bottom : public MiddleA, public MiddleB {

};


void Function(MiddleA& A) {
    std::cout<<"MiddleA Function &"<<std::endl;
}

void Function(MiddleB& B) {
    std::cout<<"MiddleB Function &"<<std::endl;
}

void Function(MiddleB* B) {
    std::cout<<"MiddleB Function *"<<std::endl;
}

int main() {
    
    // 1. upcast
    Bottom bottom;
    // Function(bottom);   // error: call of overloaded ‘Function(Bottom&)’ is ambiguous
    
    Function(static_cast<MiddleA&>(bottom));   // ok
    Function(boost::implicit_cast<MiddleA&>(bottom)); // better case

    // 2. downcast
    Top top;
    Function(static_cast<MiddleB&>(top));   // ok, 但不进行安全检查

    // Function(boost::implicit_cast<MiddleA&>(top)); // downcast 时编译会出错
    return 0;
}
```
