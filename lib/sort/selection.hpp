#pragma once

#include <string>
#include "../sorts.hpp"
#include "../sequence.hpp"

using namespace std;

template <class T>
class SelectionSort : public ISort<T>
{
  private:
    string name = "Selection Sort";

  public:
    string GetName() const override {return name;}

    Sequence<T>* Sort(Sequence<T>* _Seq, bool (*cmp)(T vol1, T vol2)) const override
    {
      Sequence<T>* Seq = _Seq->Copy();
      
      for (int i = Seq->GetLength() - 1; i > 0; i--)
      {
        int maximum = i;
        for (int j = 0; j <= i; j++)
        {
          if (cmp(Seq->Get(maximum), Seq->Get(j))) maximum = j;
        }
        Seq->Swap(maximum, i);
      }

      return Seq;
    }
};