#ifndef INODE_H
#define INODE_H
#include <memory>
#include <vector>

namespace equation_generator {
  enum class NodeType {
    ValueNode,
    VarNode,
    AddNode,
    MultNode
  };

  class Node {
  public:
    virtual ~Node() = default;
    std::unique_ptr<Node> operator+(std::unique_ptr<Node> lhs, std::unique_ptr<Node> rhs) const
    {
      return lhs->add(std::move(lhs), std::move(rhs));
    }

    virtual std::unique_ptr<Node> add(std::unique_ptr<Node> self, std::unique_ptr<Node> other);
    virtual std::unique_ptr<Node> multiply(std::unique_ptr<Node> self, std::unique_ptr<Node> other);
    //virtual Node &complexify();

    NodeType type;

  protected:
    template<typename T>
    void insertNode(const NodeType type, std::vector<std::unique_ptr<Node>>& list, const std::unique_ptr<Node> node)
    {
      if (node->type != type) {
        list.push_back(node);
      }
      auto other_list = static_cast<T&>(*node).list;
      list.insert(list.end(),
        std::make_move_iterator(other_list.begin()),
        std::make_move_iterator(other_list.end()));
    }
  };
}

#endif
