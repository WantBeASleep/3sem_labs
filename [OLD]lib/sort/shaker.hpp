#pragma once

#include <string>
#include "../structs/sequence/sequence.hpp"
#include "../structs/sort/isort.hpp"

using namespace std;

template <class T>
class ShakerSort : public ISort<T>
{
  private:
    string name = "Shaker Sort";

  public:
    string GetName() const override {return name;}

    Sequence<T>* Sort(Sequence<T>* _Seq, bool (*cmp)(T vol1, T vol2)) const override
    {
      Sequence<T>* Seq = _Seq->Copy();

      int left = 0;
      int right = Seq->GetLength() - 1;
      int control = Seq->GetLength() - 1;
      do
      {
        for (int i = left; i < right; i++)
        {
          if (!cmp(Seq->Get(i), Seq->Get(i+1)))
          {
            Seq->Swap(i, i+1);
            control = i;
          }
        }
        right = control;
        for (int i = right; i > left; i--)
        {
          if (!cmp(Seq->Get(i-1), Seq->Get(i)))
          {
            Seq->Swap(i-1, i);
            control = i;
          }
        }
        left = control;
      } while (left < right);

      return Seq;
    }
};