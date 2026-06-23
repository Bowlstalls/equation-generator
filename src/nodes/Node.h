#ifndef INODE_H
#define INODE_H
#include <functional>
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
    const NodeType type;
    const int priority;

    virtual ~Node() = default;

    virtual std::unique_ptr<Node> add(std::unique_ptr<Node> self, std::unique_ptr<Node> other) = 0;
    virtual std::unique_ptr<Node> multiply(std::unique_ptr<Node> self, std::unique_ptr<Node> other) = 0;
    virtual std::unique_ptr<Node> negate(std::unique_ptr<Node> self) = 0;
    virtual std::unique_ptr<Node> mutate(std::unique_ptr<Node> self, GeneratorParams &params) = 0;

    virtual std::string toString() const = 0;
    virtual std::unique_ptr<Node> clone() const = 0;

  protected:
    explicit Node(const NodeType type, const int priority): type{type}, priority{priority} {}

    template<typename T>
    static void insertNode(T& self, std::unique_ptr<Node> node)
    {
      if (node->type != self.type) {
        self.list.push_back(std::move(node));
        return;
      }
      auto& other_list = static_cast<T&>(*node).list;
      self.list.insert(self.list.end(),
        std::make_move_iterator(other_list.begin()),
        std::make_move_iterator(other_list.end()));
    }
    template<typename T>
    static void map(T& self, const std::function<std::unique_ptr<Node>(std::unique_ptr<Node>)> function)
    {
      auto& list = self.list;
      const size_t size = list.size();
      for (auto i = 0; i < size; i++) {
        insertNode<T>(self, function(std::move(list[i])));
      }
      list.erase(list.begin(), list.begin() + size);
    }
    template<typename T>
    static void mutateList(T& self, GeneratorParams& params)
    {
      auto lambda = [&params](std::unique_ptr<Node> node) -> std::unique_ptr<Node> {
        return node->mutate(std::move(node), params);
      };
      map<T>(self, lambda);
    }
    static std::string concatenate(const std::vector<std::unique_ptr<Node>>& list, const std::string& delimiter, const int priority)
    {
      auto iterator = list.begin();
      if (iterator == list.end()) {
        return "";
      }
      std::string res = getNext(iterator, priority);

      while (iterator < list.end()) {
        res += delimiter + getNext(iterator, priority);
      }
      return res;
    }
    static std::string getNext(std::vector<std::unique_ptr<Node>>::const_iterator& iterator, const int priority)
    {
      std::string res = (*iterator)->toString();
      if ((*iterator)->priority < priority) {
        res = '(' + res + ')';
      }
      ++iterator;
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
  };
  inline std::unique_ptr<Node> operator+(std::unique_ptr<Node> lhs, std::unique_ptr<Node> rhs)
  {
    return lhs->add(std::move(lhs), std::move(rhs));
  }
  inline std::unique_ptr<Node> operator*(std::unique_ptr<Node> lhs, std::unique_ptr<Node> rhs)
  {
    return lhs->multiply(std::move(lhs), std::move(rhs));
  }
  inline std::unique_ptr<Node> operator-(std::unique_ptr<Node> self)
  {
    return self->negate(std::move(self));
  }
}

#endif
