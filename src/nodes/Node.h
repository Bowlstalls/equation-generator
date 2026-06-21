#ifndef INODE_H
#define INODE_H
#include <memory>
#include <vector>
#include "../generator.h"

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

    virtual std::unique_ptr<Node> add(std::unique_ptr<Node> self, std::unique_ptr<Node> other) = 0;
    virtual std::unique_ptr<Node> multiply(std::unique_ptr<Node> self, std::unique_ptr<Node> other) = 0;
    virtual std::unique_ptr<Node> mutate(std::unique_ptr<Node> self, GeneratorParams &params) = 0;
    virtual std::string toString() = 0;
    virtual std::unique_ptr<Node> clone() = 0;

    const NodeType type;
    const int priority;

  protected:
    explicit Node(const NodeType type, const int priority): type{type}, priority{priority} {}

    template<typename T>
    void insertNode(const NodeType type, std::vector<std::unique_ptr<Node>>& list, std::unique_ptr<Node> node)
    {
      if (node->type != type) {
        list.push_back(std::move(node));
        return;
      }
      auto& other_list = static_cast<T&>(*node).list;
      list.insert(list.end(),
        std::make_move_iterator(other_list.begin()),
        std::make_move_iterator(other_list.end()));
    }
    static std::string concatenate(const std::vector<std::unique_ptr<Node>>& list, const std::string& delimiter, int priority)
    {
      auto iterator = list.begin();
      if (iterator == list.end()) {
        return "";
      }
      std::string res;
      if ((*iterator)->priority < priority) {
        res += '(' + (*iterator)->toString() + ')';
      } else {
        res += (*iterator)->toString();
      }

      ++iterator;
      while (iterator < list.end()) {
        res += delimiter;
        if ((*iterator)->priority < priority) {
          res += '(' + (*iterator)->toString() + ')';
        } else {
          res += (*iterator)->toString();
        }
        ++iterator;
      }
      return res;
    }
    static std::vector<std::unique_ptr<Node>> cloneList(const std::vector<std::unique_ptr<Node>>& origin)
    {
      std::vector<std::unique_ptr<Node>> res;
      for (auto& i : origin) {
        res.push_back(i->clone());
      }
      return res;
    }
    static void mutateList(std::vector<std::unique_ptr<Node>>& list, GeneratorParams &params)
    {
      for (auto& term : list) {
        if (params.doMutate()) {
          term = term->mutate(std::move(term), params);
        }
      }
    }
  };
  inline std::unique_ptr<Node> operator+(std::unique_ptr<Node> lhs, std::unique_ptr<Node> rhs)
  {
    return lhs->add(std::move(lhs), std::move(rhs));
  }
  inline std::unique_ptr<Node> operator*(std::unique_ptr<Node> lhs, std::unique_ptr<Node> rhs)
  {
    return lhs->multiply(std::move(lhs), std::move(rhs));
  }
}

#endif
