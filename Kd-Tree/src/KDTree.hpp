// Copyright
#ifndef SRC_KDTREE_HPP_
#define SRC_KDTREE_HPP_
#include <cmath>
#include <iostream>
#include <set>
#include <stdexcept>
#include <utility>
#include <queue>
#include <list>
#include <vector>
#include "KdTreeNode.hpp"
#include "Point.hpp"
using namespace std;
template <size_t N, typename ElemType>
class KDTree {
  public:
    typedef std::pair<Point<N>, ElemType> value_type;
    KDTreeNode<N,ElemType> *root;
    KDTree();
    ~KDTree();
    KDTree(const KDTree &rhs);
    KDTree &operator=(const KDTree &rhs);
    size_t dimension() const;
    size_t size() const;
    bool empty() const;
    bool contains(const Point<N> &pt) const;
    void insert(const Point<N> &pt, const ElemType &value);
    ElemType &operator[](const Point<N> &pt);
    ElemType &at(const Point<N> &pt);
    const ElemType &at(const Point<N> &pt) const;
    ElemType knn_value(const Point<N> &key, size_t k) const;
    void knn_query(KDTreeNode<N,ElemType> *t,const Point<N> &key, size_t k, vector<pair<double, KDTreeNode<N,ElemType>*>>& pQueue,size_t depth) const;
    void print() const;
    vector<KDTreeNode<N,ElemType>*> nodes;
  private:
    size_t dimension_;
    size_t size_;
    bool find(const Point<N> &pt,KDTreeNode<N,ElemType> **t) const;
};

template <size_t N, typename ElemType>
KDTree<N, ElemType>::KDTree() {
  this->dimension_ = N;
  this->size_ = 0;
  this->root= nullptr;
}

template <size_t N, typename ElemType>
KDTree<N, ElemType>::~KDTree() {
/*  for(auto i=nodes.size()-1;i>=0;i--){
    delete nodes[i];
  }
  delete root;*/
}

template <size_t N, typename ElemType>
KDTree<N, ElemType>::KDTree(const KDTree &rhs) {
  this->dimension_ = rhs.dimension();
  this->size_ = rhs.size();
  this->root=rhs.root;
  this->nodes.clear();
  this->nodes=rhs.nodes;
}

template <size_t N, typename ElemType>
KDTree<N, ElemType> &KDTree<N, ElemType>::operator=(const KDTree &rhs) {
  this->dimension_ = rhs.dimension();
  this->size_ = rhs.size();
  this->root=rhs.root;
  this->nodes.clear();
  this->nodes=rhs.nodes;
  return *this;
}

template <size_t N, typename ElemType>
size_t KDTree<N, ElemType>::dimension() const {
  return this->dimension_;
}

template <size_t N, typename ElemType>
size_t KDTree<N, ElemType>::size() const {
  return this->size_;  
}

template <size_t N, typename ElemType>
bool KDTree<N, ElemType>::empty() const {
  if(this->size_== 0)
    return true;

  return false;
}

template <size_t N, typename ElemType>
void KDTree<N, ElemType>::print()const{
  cout<<"{ ";
  for(auto i=0;i<nodes.size();i++){
    cout<<nodes[i]->p<< " "<< nodes[i]->value<<",";
  }
  cout<< " }"<<endl;
}

template <size_t N, typename ElemType>
bool KDTree<N, ElemType>::find(const Point<N> &pt,KDTreeNode<N,ElemType> **t)const{
  *t=root;
  for(auto i=0;i<nodes.size();i++){
    if(nodes[i]->p==pt){
      *t=nodes[i];
      return true;
    } 
  }
  return false;
}
template <size_t N, typename ElemType>
bool KDTree<N, ElemType>::contains(const Point<N> &pt) const {
  KDTreeNode<N,ElemType> *t;
  return find(pt,&t);
}

template <size_t N, typename ElemType>
void KDTree<N, ElemType>::insert(const Point<N> &pt, const ElemType &value) {
  int i=0;
  KDTreeNode<N,ElemType> *t=root;
  if(!root){
    pair<Point<N>, ElemType> ar(pt,value);
    KDTreeNode<N,ElemType> *a = new KDTreeNode<N,ElemType>(ar);
    root=a;
    size_+=1;
    nodes.push_back(a);
    return;
  }
  if(find(pt,&t)){
    t->value;
  }
  while(t){
    if(t->p[i%N] > pt[i%N]){
      if(t->leftchild)
        t=t->leftchild;
      else break;
    }
    if(t->p[i%N] < pt[i%N]){
      if(t->rightchild)
        t=t->rightchild;
      else break;
    }
    else {
      if(t->p == pt){
      t->value = value;
      return;
      } 
    }
    i++;
    
  }
  if(t->p == pt){
    t->value = value;
    return;
  } 
  pair<Point<N>, ElemType> ar(pt,value);
  KDTreeNode<N,ElemType> *a = new KDTreeNode<N,ElemType>(ar);
  if(t->p[i%N] >= pt[i%N]){
    t->leftchild=a;
  } 
  else{
    t->rightchild=a;
  }
  size_+=1;
  nodes.push_back(a);
}

template <size_t N, typename ElemType>
ElemType &KDTree<N, ElemType>::operator[](const Point<N> &pt) {
  int i=0;
  KDTreeNode<N,ElemType> *t;
  if(!root){
    pair<Point<N>, ElemType> ar(pt,NULL);
    KDTreeNode<N,ElemType> *a = new KDTreeNode<N,ElemType>(ar);
    root=a;
    size_+=1;
    nodes.push_back(a);
    return a->value;
  }
  if(find(pt,&t)){
    return t->value;
  }
  t=root;
  while(t){
    if(t->p[i%N] > pt[i%N]){
      if(t->leftchild)
        t=t->leftchild;
      else break;
    }
    if(t->p[i%N] < pt[i%N]){
      if(t->rightchild)
        t=t->rightchild;
      else break;
    }
    else {
      if(t->p == pt){
      return t->value;
      } 
    }
    i++;
  }
  if(t->p == pt){
    return t->value;
  } 
  pair<Point<N>, ElemType> ar(pt,NULL);
  KDTreeNode<N,ElemType> *a = new KDTreeNode<N,ElemType>(ar);
  if(t->p[i%N] >= pt[i%N]){
    t->leftchild=a;
  } 
  else{
    t->rightchild=a;
  }
  size_+=1;
  nodes.push_back(a);
  return a->value;
}

template <size_t N, typename ElemType>
ElemType &KDTree<N, ElemType>::at(const Point<N> &pt) {
  KDTreeNode<N,ElemType> *t;
  if(!root){
    throw std::out_of_range("Nonexistent elements aren't in the tree.");
  }
  if(find(pt,&t)){
    return t->value;
  } 
  throw std::out_of_range("Fuera de rango");
}

template <size_t N, typename ElemType>
const ElemType &KDTree<N, ElemType>::at(const Point<N> &pt) const {
  KDTreeNode<N,ElemType> *t;
  if(!root){
    throw std::out_of_range("Nonexistent elements aren't in the tree.");
  }
  if(find(pt,&t)){
    return t->value;
  } 
  throw std::out_of_range("Fuera de rango");
}

template <size_t N, typename ElemType>
ElemType KDTree<N, ElemType>::knn_value(const Point<N> &key, size_t k) const {
  KDTreeNode<N,ElemType> *t=root;
  vector<pair<double,KDTreeNode<N,ElemType>*>> pQueue;
  knn_query(t,key,k, pQueue,0);
  sort(pQueue.begin(),pQueue.end());
  vector<ElemType> knn_values;
  for(long long i=0;i<k && i<pQueue.size();i++){
    pair<double,KDTreeNode<N,ElemType>*> t=pQueue[i];
    KDTreeNode<N,ElemType>* a=t.second;
    knn_values.push_back(a->value);
  }
  size_t max=0;
  ElemType m=knn_values[0];
  for(long long i=0;i<knn_values.size();i++){
    size_t cont=0;
    for(long long j=i;j<knn_values.size();j++){
      if(knn_values[i]==knn_values[j]) cont+=1;
    }
    if(cont>=max){
      max=cont;
      m=knn_values[i];
    } 
  }
  pQueue.clear();
  return m;
}


template <size_t N, typename ElemType>
void KDTree<N, ElemType>::knn_query(KDTreeNode<N,ElemType> *t,const Point<N> &key,size_t k, vector<pair<double,KDTreeNode<N,ElemType>*>>& pQueue,size_t depth) const {
  if (t == NULL) return; 
  pair<double,KDTreeNode<N,ElemType>*> w(distance(key,t->p),t);
  pQueue.push_back(w); 
  sort(pQueue.begin(),pQueue.end());
  int axis=depth%N;
  bool rigth=false;
  if(key[axis]< t->p[axis]){
    bool rigth=false;
    knn_query(t->leftchild,key,k,pQueue,++depth);
  }
  else{
    bool rigth=true;
    knn_query(t->rightchild,key,k,pQueue,++depth);
  }
pair<double,KDTreeNode<N,ElemType>*> a=pQueue.back();
KDTreeNode<N,ElemType> *r=a.second;
  if(pQueue.size() < k|| (fabs(t->p[axis])-key[axis])< r->p[axis]){
    if(right){
      knn_query(t->leftchild,key,k,pQueue,++depth);
    }
    else{
      knn_query(t->rightchild,key,k,pQueue,++depth);
    }
  }
}

#endif  // SRC_KDTREE_HPP_
