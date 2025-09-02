

# `STL`迭代器分类

迭代器 `iterator` 一共分为 `5` 类：

```cpp
template<typename IterT>        //template，用来处理迭代器分类的相关信息
struct iterator_traits 
{
    typedef typename IterT::iterator_category iterator_category    //
};         

struct input_iterator_tag {};

struct output_iterator_tag {};

struct forward_iterator_tag : public input_iterator_tag {};

struct bidirectional_iterator_tag : public forward_iterator_tag {};

struct random_access_iterator_tag : public bidirectional_iterator_tag {};

```

`input`：这类只能向前移动，一次一步，只可读取所指的内容，而且只能读取一次。它们模仿指向输入文件的阅读指针，`istream_iterator` 是这一分类的代表。

`output`：这类只能向前移动，一次一步，只可涂写所指的内容，而且只能涂写一次。它们模仿指向输出文件的涂写指针，`ostream_iterator` 是这一分类的代表。

上述两类都只能向前移动，而且只能读取或涂写其所指物最多一次。所以它们只适合 "一次性操作算法"。

`forward`：只能向前移动，但可以读取或涂写所指物多次。可以施行于多次性操作算法。`forward_list`的迭代器就是这一分类。

`bidirectional`：可以向前或向后移动，`list`的迭代器就是这一分类，` set, multiset, map和multimap`的迭代器也都是这一分类。

`random`：随机迭代器，可以在 `O(1)` 的复杂度内向前或向后跳跃任何距离。`vector, deque和string`提供的迭代器都是这一分类。

