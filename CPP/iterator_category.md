[toc]

# 迭代器分类

-----------------

迭代器 `iterator` 一共分为 `5` 类：

```cpp
struct input_iterator_tag {};

struct output_iterator_tag {};

struct forward_iterator_tag : input_iterator_tag {};

struct bidirectional_iterator_tag : forward_iterator_tag {};

struct random_access_iterator_tag : bidirectional_iterator_tag {};

```

