#pragma once

#include <string>
#include "../sorts.hpp"
#include "../sequence.hpp"

using namespace std;

template <class T>
class BinaryInsertSort : public ISort<T>
{
  private:
    string name = "Binary Insert Sort";

  public:
    string GetName() const override {return name;}

    Sequence<T>* Sort(Sequence<T>* _Seq, bool (*cmp)(T vol1, T vol2)) const override
    {
      Sequence<T>* Seq = _Seq->Copy();
      
      for (int i = 1; i < Seq->GetLength(); i++)
      {
        int left = 0;
        int right = i - 1;

        if (i == 1)
        {
          if (!cmp(Seq->Get(0), Seq->Get(1))) Seq->Swap(0,1);
          continue;
        }

        if (cmp(Seq->Get(right), Seq->Get(i)))
        {
          continue;
        }

        while (left < right)
        {
          int mid = left + (right - left) / 2;
          if (!cmp(Seq->Get(mid), Seq->Get(i))) right = mid;
          else left = mid + 1;
        }
        for (int j = i; j > left; j--)
        {
          Seq->Swap(j-1, j);
        }
      }

      return Seq;
    }
};