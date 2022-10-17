#pragma once
#include <iostream>
#include <string>
#include "../structs/sequence/sequence.hpp"
#include "../structs/trees/binaryTree.hpp"
#include "../structs/sort/isort.hpp"

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
      AVLTree<T> tree;
      for (int i = 0; i < _Seq->GetLength(); tree.Add(_Seq->Get(i)), i++);
      
      Sequence<T>* Res = tree.GetSequence();
      return Res;
    }
};