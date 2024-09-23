介绍<string>头文件里的函数及其用法。


切割字符串：
```cpp
string s;
s.substr(idx, k);
```
- 从下标idx开始，连续截取k个字符，返回字符串。s不变。
- 如果order+k超过了s.size()-1，函数会自动只截取到s的末尾。
- 如果不传入k，那么默认截取到末尾。

```cpp
s.find(c);
//在字符串s中查找第一个字符c的位置，返回下标，如果没有返回string::npos

s.erase(it);
//在字符串中删除指针it所指向的字符

s.begin();
//返回s的首字符的指针（迭代器）
```


