#pragma once

#include <string>
#include "../structs/sequence/sequence.hpp"
#include "../structs/sort/isort.hpp"

using namespace std;

template <class T>
class InsertionSort : public ISort<T>
{
private:
  string name = "Insertion Sort";

public:
  string GetName() const override {return name;}

  Sequence<T>* Sort(Sequence<T> *_Seq, bool (*cmp)(T vol1, T vol2)) const override
  {
    Sequence<T>* Seq = _Seq->Copy();

    for (int i = 0; i < Seq->GetLength(); i++)
    {
      int j = i;
      while (j > 0 && !cmp(Seq->Get(j - 1), Seq->Get(j)))
      {
        Seq->Swap(j - 1, j);
        j--;
      }
    }

    return Seq;
  }
};