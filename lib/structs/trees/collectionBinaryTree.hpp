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
    Couple(TKey key) {this->key = key;}
    Couple(TKey key, TElement element) {this->key = key; this->element = element;}

    bool operator== (TKey key) {return this->key == key;}
    bool operator== (Couple<TKey, TElement> couple) {return this->key == couple.key;}
    bool operator> (TKey key) {return this->key > key;}
    bool operator> (Couple<TKey, TElement> couple) {return this->key > couple.key;}
    bool operator< (TKey key) {return this->key < key;}
    bool operator< (Couple<TKey, TElement> couple) {return this->key < couple.key;}
};

template <typename TKey, typename TElement>
class CollectionTree : public AVLTree<Couple<TKey, TElement>>
{
  using AVLTree<Couple<TKey, TElement>>::root;
  using AVLTree<Couple<TKey, TElement>>::Add;
  using AVLTree<Couple<TKey, TElement>>::Remove;
  // using AVLTree<Couple<TKey, TElement>>::size;
  // using AVLTree<Couple<TKey, TElement>>::GetHeight;
  // using AVLTree<Couple<TKey, TElement>>::GetBFactor;
  // using AVLTree<Couple<TKey, TElement>>::FixHeight;
  // using AVLTree<Couple<TKey, TElement>>::RotateRight;
  // using AVLTree<Couple<TKey, TElement>>::RotateLeft;
  // using AVLTree<Couple<TKey, TElement>>::Balance;
  // using AVLTree<Couple<TKey, TElement>>::Insert;
  // using AVLTree<Couple<TKey, TElement>>::FindMin;
  // using AVLTree<Couple<TKey, TElement>>::RemoveMin;
  // using AVLTree<Couple<TKey, TElement>>::Seq_LKP;
  // using AVLTree<Couple<TKey, TElement>>::GetCount;
  // using AVLTree<Couple<TKey, TElement>>::GetSequence;

  private:
    TElement REC_Get(Node<Couple<TKey, TElement>>* node, TKey key) const
    {
      if (node->key == key) return node->key.element;
      if (node->key > key) return REC_Get(node->left, key);
      else return REC_Get(node->right, key);
    }

  public:
    TElement Get(TKey key) const {return REC_Get(root, key);}

    void Add(TKey key, TElement element) {Add(Couple<TKey, TElement>(key, element));}

    void Remove(TKey key) {Remove(Couple<TKey, TElement>(key));}
};