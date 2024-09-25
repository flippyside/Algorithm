#pragma once

#include <algorithm>
#include <cstddef>
#include <map>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

// 一个字典树节点
class TrieNode {
  public:
    // 创建一个无儿子的节点
    TrieNode() = default;

    // 根据已有的子节点创建一个节点
    explicit TrieNode(std::map<char, std::shared_ptr<const TrieNode>> children)
        : children_(std::move(children)) {}
// 该构造函数不能用于隐式类型转换。只有在显式调用构造函数时，才能创建对象。

    virtual ~TrieNode() = default;// 编译器将会生成默认的虚析构函数实现

    // Clone 函数返回当前 TrieNode的一个拷贝，如果有值也会拷贝值。它会返回一个指向拷贝后内容unique_ptr
    // 由于拷贝构造函数无法判断当前类是否是子类型 TrieNodeWithValue,所以不能使用拷贝构造函数拷贝节点
    // 可以使用 `std::shared_ptr<T>(std::move(ptr))` 将 `unique_ptr` 转化为`shared_ptr`
    virtual std::unique_ptr<TrieNode> Clone() const {
        return std::make_unique<TrieNode>(children_);
    }

    // 一个子节点的 map，其中的 键 是下一个 字母， 值 是指向的子节点
    // 请不要修改这个定义，并使用这个结构保存子节点信息。我们会在一些测试中使用它
    std::map<char, std::shared_ptr<const TrieNode>> children_;

    // 判断节点是否含有值
    bool is_value_node_{false};

    // 你可以添加任何你需要的内容
};

//
class TrieNodeWithValue : public TrieNode {
  public:
    // 创建一个有值无子节点的 节点
    explicit TrieNodeWithValue(std::shared_ptr<int> value)
        : value_(std::move(value)) {
        this->is_value_node_ = true;
    }

    // 根据已有的子节点和值创建节点
    TrieNodeWithValue(std::map<char, std::shared_ptr<const TrieNode>> children,
                      std::shared_ptr<int> value)
        : TrieNode(std::move(children)), value_(std::move(value)) {
        this->is_value_node_ = true;
    }

    // 重写 Clone 函数
    std::unique_ptr<TrieNode> Clone() const override {
        return std::make_unique<TrieNodeWithValue>(children_, value_);
    }
    
    std::shared_ptr<int> value_;// 指向value值的指针。 通过 make_shared<int> 来构造它
};

// 从总体上来说，字典树是一个从 string 到 int * 的映射
// 在实现 Trie 的接口时，你需要尽可能地重用已有的 TrieNode, 并在必要时创建新的节点
// 不要删除 const 或添加 mutable 修饰符
class Trie {
  private:
    std::shared_ptr<const TrieNode> root_{nullptr};// 指向字典树的子节点

    explicit Trie(std::shared_ptr<const TrieNode> root)// 根据当前子节点创建新的 Trie
        : root_(std::move(root)) {} //将 root 的所有权从传入的智能指针转移到了 Trie 对象内部的成员变量上

  public:
    Trie() = default;// 创建空字典树

    // 查找 key 对应的 value. 如果不存在返回 nullptr，否则返回对应指针
    // 你可以调用 get 接口从智能指针中获取
    const int *Get(std::string key) const;

    // 在字典树中插入一个新的键值对。如果已经存在对应键，复写原有键值对
    // 返回新的字典树
    Trie Put(std::string key, int value) const;

    // 删除某个键值对。如果对应键不存在，返回原字典树，否则返回新的字典树
    Trie Remove(std::string key) const;

    // 获取字典树的根。我们会在测试中调用这个函数
    std::shared_ptr<const TrieNode> GetRoot() const { return root_; }
};
