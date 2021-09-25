# `stack & queue` 容器结构

## 1. `stack` 数据结构

`stack` 是一种容器适配器，底层容器使用的是 `deque` 数据结构。

```cpp
template<class T, class Sequence = deque<T>>
class stack{
...
public:
    typedef typename Sequence::value_type value_type;
    typedef typename Sequence::size_type size_type;
    typedef typename Sequence::reference reference;
    typedef typename Sequence::const_reference const_reference;
    
protected:
    Sequence c;	// 底层容器

public:
	bool empty() const { return c.empty(); }
    size_type size() const { return c.size(); }
    reference top() const { return c.back(); }
	const_reference top() const { return c.back(); }
    void push( const value_type &x ) { c.push_back(x); }
    void pop() { c.pop_back(); }
};
```

## 2. `queue` 数据结构

```c++
template<class T, class Sequence = deque<T>>
class queue{
...
public:
    typedef typename Sequence::value_type value_type;
    typedef typename Sequence::size_type size_type;
    typedef typename Sequence::reference reference;
    typedef typename Sequence::const_reference const_reference;
    
protected:
    Sequence c;	// 底层容器

public:
	bool empty() const { return c.empty(); }
    size_type size() const { return c.size(); }
    reference front() const { return c.front(); }
    const_reference front() const { return c.front(); }
    reference back() const { return c.back(); }
    const_reference back() const { return c.back(); }
    void push( const value_type &x ) { c.push_back(x); }
    void pop() { c.pop_front(); }
};
```

