#pragma once

#include "../containers/PairKeyVal.hpp"
#include "binaryTree.hpp"

using namespace std;

template <typename TKey, typename TElement>
class CollectionTree : public AVLTree<PairKeyVal<TKey, TElement>>
{
  using AVLTree<PairKeyVal<TKey, TElement>>::root;
  using AVLTree<PairKeyVal<TKey, TElement>>::Add;
  using AVLTree<PairKeyVal<TKey, TElement>>::Remove;
  
  private:
    TElement& REC_Get(Node<PairKeyVal<TKey, TElement>>* node, TKey const &key) const
    {
      if (node->key == key) return node->key.element;
      if (node->key > key) return REC_Get(node->left, key);
      else return REC_Get(node->right, key);
    }

  public:
    CollectionTree(bool (*cmp)(const PairKeyVal<TKey, TElement>&, const PairKeyVal<TKey, TElement>&)) : AVLTree<PairKeyVal<TKey, TElement>>(cmp) {}

    TElement& Get(TKey const &key) const 
    {
      return REC_Get(root, key);
    }

    void Add(TKey const &key, TElement const &element) 
    {
      PairKeyVal<TKey, TElement> cpl(key, element);
      Add(cpl);
    }

    void Remove(TKey const &key) 
    {
      PairKeyVal<TKey, TElement> cpl(key);
      Remove(cpl);
    }
};