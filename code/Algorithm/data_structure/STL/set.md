
# 性质
- 底层实现：红黑树 O(logn)
- 元素有序(默认升序)
- 没有重复元素
- 不可修改元素，但可以删除

# 操作

- 插入元素：insert() ，返回`pair<set<int>::iterator, bool>`：第一项是x的迭代器，第二项是插入成功与否
- 删除元素：erase() 
  - `set.erase(iterator)`，删除定位器 iterator 指向的值
  - `set.erase(first,second)`，删除定位器 first 和 second 之间的值
  -` set.erase(key_value)`，删除键值 key_value 的值
- 查找元素：find() ，返回迭代器，若不存在，则返回end
- 大小：size() 返回集合中的元素个数。
- 清空：clear() 清空集合
- set.lower_bound(x) ：返回第一个大于等于 x 的位置，
- set.upper_bound(x) ：返回第一个大于 x 的位置，

```c++


```

# 应用

适合需要 唯一性 和 有序性 的场景，比如查找某个元素是否存在或者维护一组无重复且有序的值。
