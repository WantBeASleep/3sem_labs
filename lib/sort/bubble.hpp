#pragma once

#include <string>
#include "../sorts.hpp"
#include "../sequence.hpp"

using namespace std;

template <class T>
class BubbleSort : public ISort<T>
{
  private:
    string name = "Bubble Sort";

  public:
    string GetName() const override {return name;}

    Sequence<T>* Sort(Sequence<T>* _Seq, bool (*cmp)(T val1, T val2)) const override
    {
      Sequence<T>* Seq = _Seq->Copy();

      for (int i = 0; i < Seq->GetLength() - 1; i++)
      {
        for (int j = 0; j < Seq->GetLength() - i - 1; j++)
        {
          if (!cmp(Seq->Get(j), Seq->Get(j+1))) Seq->Swap(j, j+1);
        }
      }

      return Seq;
    }
};
