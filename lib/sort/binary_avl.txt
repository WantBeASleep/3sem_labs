#pragma once

#include <string>

#include "../sorts.hpp"
#include "../sequence.hpp"
#include "../structs/trees/binaryTree.hpp"

using namespace std;

template <class T>
class BinaryAVLSort : public ISort<T>
{
  private:
    string name = "Binary AVL Sort";

  public:
    string GetName() const override {return name;}

    Sequence<T>* Sort(Sequence<T>* _Seq, bool (*cmp)(T vol1, T vol2)) const override
    {
      BinaryTree<T>* avl_tree = new BinaryTree<T>();
      for (int i = 0; i < _Seq->GetLength(); avl_tree->add_key(_Seq->Get(i)), i++);

      Sequence<T>* Seq = avl_tree->GetSeq("LKP");

      delete avl_tree;
      return Seq;
    }
};