index
- 计数DP
- 树形DP
- 

# 数位DP

数位：一个数字的每一位

问题特征：
- 计数
- 提供数字区间
- 上界大



```
给定两个整数 a 和 b，求 a 和 b 之间的所有数字中 0∼9 的出现次数。
```

思路：
统计某个数字在每一位上出现的次数。
例如：1 ~ n，n = abcdegf，统计第 4 位上数字 1 出现的次数
- 所求数字 xxx1yyy 应满足 1 <= xxx1yyy <= abcdefg
- 分类讨论
  1. xxx < abc, 即 xxx = 001 ~ abc - 1， 此时xxx1yyy一定小于abcdefg，故yyy可以取任意值，即 yyy = 000 ~ 999。总数为`abc*1000`
  2. xxx = abc
    - d < 1：abc1yyy一定大于abcdefg。总数为 0
    - d = 1：yyy = 000 ~ efg。总数为 `efg + 1`
    - d > 1：abc1yyy一定小于abcdefg。总数为1000。
  3. 边界条件：
    - 最高位为 1: 
    - 最高位为 0：

最后，要求一个区间的答案，只需拆成两部分相减：$ans_{[l,r]}=ans_{[0,r]}-ans_{[0,l-1]}$


