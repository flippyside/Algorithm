#include "trie.h"
#include <string>
#include <string>
#include <memory>

/*
一个子节点的 map，键:下一个字母， 值:指向的子节点
TrieNode:  map<char, shared_ptr<const TrieNode>> children_;
*/
const int *Trie::Get(std::string key) const {
    // 你需要在字典树中寻找对应的键，如果不存在则返回 nullptr
    // 如果你找到了对应节点，你可以使用 `dynamic_cast` 尝试将其转化为 `const
    // TrieNodeWithValue<T> *`. 如果转化不成功，则其不存在值，返回
    // nullptr。否则可以通过转化后的指针访问 value.
    std::shared_ptr<TrieNode> cur = std::make_shared<TrieNode>(root_);
    for(char c : key){
        auto it = cur.get()->children_.find(c);
        if(it != cur.get()->children_.end()) // 元素存在
        {
            cur = std::const_pointer_cast<TrieNode>(it->second);
        }
        else{
            return nullptr;
        }

    }

    return nullptr;
}

Trie Trie::Put(std::string key, int value) const {
    // 如果对应 key 的节点已经存在，你需要新建（复制）节点
    // 你可以使用 make_shared<int> 来创建一个 value 对应的智能指针
    return {};
}

Trie Trie::Remove(std::string key) const {
    // 遍历节点并删除键对应的值
    // 删除值后你需要将节点转化为 `TrieNode`
    // 请删除既没有子节点也没有值的 TrieNode
    return {};
}
void BasicRemoveTest1() {
  auto trie = Trie();
  // Put something
  trie = trie.Put("test", 2333);
//   ASSERT_EQ(*trie.Get("test"), 2333);
//   trie = trie.Put("te", 23);
//   ASSERT_EQ(*trie.Get("te"), 23);
//   trie = trie.Put("tes", 233);
//   ASSERT_EQ(*trie.Get("tes"), 233);
//   // Delete something
//   trie = trie.Remove("test");
//   trie = trie.Remove("tes");
//   trie = trie.Remove("te");
//   ASSERT_EQ(trie.Get("te"), nullptr);
//   ASSERT_EQ(trie.Get("tes"), nullptr);
//   ASSERT_EQ(trie.Get("test"), nullptr);
}