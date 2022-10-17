#pragma once

#include "../containers/Couple.hpp"
#include "binaryTree.hpp"

using namespace std;



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