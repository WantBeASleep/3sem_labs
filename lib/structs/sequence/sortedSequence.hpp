#pragma once
#include "sequence.hpp"
#include "arraySequence.hpp"
#include "../../sort/binary_avl.hpp"
#include <iostream>

template <typename Type>
class SortedSequence
{
  private:
    Sequence<Type>* data;
    BinaryAVLSort<Type> sort;
    bool (*cmp)(Type val1, Type val2);

  public:
    SortedSequence() {data = new ArraySequence<Type>();}

    SortedSequence(Sequence<Type>* Seq) {data = sort.Sort(Seq, cmp);}

    SortedSequence(Type *items, int count)
    {
      data = new ArraySequence<Type>(items, count);
      Sequence<Type> *tmp = data;
      data = sort.Sort(data, cmp);
      delete tmp;
    }
    
    ~SortedSequence() {delete data;}

    int GetLength() const {return data->GetLength();}
    
    bool GetIsEmpty() const {return (bool)(data->GetLength());}
    
    Type& Get(int index) const {return data->Get(index);}

    Type& GetFirst() const {return data->GetFirst();}

    Type& GetLast() const {return data->GetLast();}

    int IndexOf(Type const &item) const {return data->IndexOf(item);}

    SortedSequence<Type> GetSubSequecne(int startIndex, int endIndex) const
    {
      Sequence<Type>* Seq = data->GetSubsequence(startIndex, endIndex);
      SortedSequence<Type> Res(Seq);
      delete Seq;
      return Res;
    }

    void Add(Type const &item)
    {
      data->Append(item);
      Sequence<Type>* tmp = data;
      data = sort.Sort(data, cmp);
      delete tmp;
    }

    SortedSequence& operator= (Sequence<Type>* Seq)
    {
      delete data;
      data = sort.Sort(Seq, cmp);
      return *this;
    }

};