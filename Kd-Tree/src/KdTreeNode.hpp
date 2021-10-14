#include <cmath>
#include <iostream>
#include <set>
#include <stdexcept>
#include <utility>
#include <vector>
#include "Point.hpp"
template <size_t N, typename ElemType>
class KDTreeNode {
  public:
    typedef std::pair<Point<N>, ElemType> value_type;
    KDTreeNode *leftchild;
    KDTreeNode *rightchild;
    ElemType value;
    Point<N> p;
    KDTreeNode();
    KDTreeNode(value_type &value);
};
template <size_t N, typename ElemType>
KDTreeNode<N, ElemType>::KDTreeNode() {
  this->leftchild=nullptr;
  this->rightchild=nullptr;
}
template <size_t N, typename ElemType>
KDTreeNode<N, ElemType>::KDTreeNode(value_type &value){
  this->leftchild=nullptr;
  this->rightchild=nullptr;
  this->value=value.second;
  this->p=value.first;
}