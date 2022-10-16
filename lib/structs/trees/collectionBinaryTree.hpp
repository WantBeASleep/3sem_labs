#pragma once

#include "binaryTree.hpp"

using namespace std;

template <typename TKey, typename TElement>
class Couple
{
  public:
    TKey key;
    TElement element;

    Couple() {}
    Couple(TKey const &key) {this->key = key;}
    Couple(TKey const &key, TElement const &element) {this->key = key; this->element = element;}
    Couple(const Couple &obj) {key = obj.key; element = obj.element;}
    ~Couple() {}

    bool operator== (const Couple<TKey, TElement> &obj) const {return this->key == obj.key;}
    Couple& operator= (const Couple<TKey, TElement> &obj) {key = obj.key; element = obj.element; return *this;}
    bool operator> (const Couple<TKey, TElement> &obj) const {return this->key > obj.key;}
    bool operator< (const Couple<TKey, TElement> &obj) const {return this->key < obj.key;}
};


template <typename TKey, typename TElement>
class CollectionTree : public AVLTree<Couple<TKey, TElement>>
{
  using AVLTree<Couple<TKey, TElement>>::root;
  using AVLTree<Couple<TKey, TElement>>::Add;
  using AVLTree<Couple<TKey, TElement>>::Remove;
  
  private:
    TElement& REC_Get(Node<Couple<TKey, TElement>>* node, TKey const &key) const
    {
      if (node->key == key) return node->key.element;
      if (node->key > key) return REC_Get(node->left, key);
      else return REC_Get(node->right, key);
    }

  public:
    TElement& Get(TKey const &key) const 
    {
      return REC_Get(root, key);
    }

    void Add(TKey const &key, TElement const &element) 
    {
      Couple<TKey, TElement> cpl(key, element);
      Add(cpl);
    }

    void Remove(TKey const &key) 
    {
      Couple<TKey, TElement> cpl(key);
      Remove(cpl);
    }
};