#include <iostream>
#include <vector>

using namespace std::cout;
using namespace std::endl;

enum class Color
{
  RED,
  BLACK
};

struct Node
{
  Node(int value);

  // 左旋
  void rot_left(Node* node);

  // 右旋
  void rot_right(Node* node);

  // 颜色翻转
  void clip_color(Node* node);

  // 插入
  Node* insert(Node* node, int value);

private:

  int value;
  Node* left;
  Node* right;
  Node* parent;
  Color color;
};

Node::Node(int value)
{
  value = value;
  left =nullptr;
  right = nullptr;
  parant = nullptr;
  color = Color.RED;
}

void Node::rot_left(Node* node)
{
  Node* tmp_node = node->right;
  node->right = tmp_node->left;
  tmp_node->left = node;

  Color tmp_color = tmp->color;
  tmp->color = node->color;
  node->color = tmp_color;
}

void Node::rot_right(Node* node)
{
  Node* tmp_node = node->left;
  node->left = tmp_node->right;
  tmp_node->right = node;

  Color tmp_color = tmp->color;
  tmp->color = node->color;
  node->color = tmp->color;
}

void Node::flip_color()
{
  color = Color.RED;
  left->color = Color.BLACK;
  right->color = Color.BLACK;
}

Node* Node::insert(Node* node, int value)
{
  if (node == nullptr)
    return new Node(value);

  Node* parent = node->parent;
  if (parent->left->color == Color.RED && parent->right->color == Color.RED)
    parent->clip_color();

  if ()
}

int main()
{
  std::vector<int> vec1 = { 41, 38, 31, 12, 19, 8 };  

  return 0;
}
