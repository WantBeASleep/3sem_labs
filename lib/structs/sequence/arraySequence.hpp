#pragma once

#include "sequence.hpp"
#include "dynamicArray.hpp"

using namespace std;

template <class T>
class ArraySequence : public Sequence<T>
{
  private:
    DynamicArray<T>* array;

  public:
    ArraySequence() {array = new DynamicArray<T>();}

    ArraySequence(T* items, int count) {array = new DynamicArray<T>(items, count);}

    ArraySequence(const DynamicArray<T>& _array) {array = new DynamicArray<T>(_array);}

    ArraySequence(const ArraySequence<T>& _array) {array = new DynamicArray<T>(*(_array.array));}

    ~ArraySequence() {delete array;}

    // получение
    T GetFirst() const override {return array->Get(0);}

    T GetLast() const override {return array->Get(array->GetSize() - 1);}

    T Get(int index) const override {return array->Get(index);}

    Sequence<T>* Copy() const override {return (Sequence<T>*)(new ArraySequence<T>(*this));}

    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override
    {
      Sequence<T>* seq = new ArraySequence<T>();
      for (int i = startIndex; i <= endIndex; seq->Append(array->Get(i)), i++);
      return seq;
    }

    int GetLength() const override {return array->GetSize();}

    //@ INFO
    bool Contains(T item) const override
    {
      for (int i = 0; i < array->GetSize(); i++)
      {
        if (array->Get(i) == item) return true;
      }
      return false;
    }
    
    //Операции
    void Append(T item) override
    {
      array->Resize(array->GetSize() + 1);
      array->Set(array->GetSize() - 1, item);
    }

    void Prepend(T item) override
    {
      array->Resize(array->GetSize() + 1);
      for (int i = array->GetSize() - 1; i > 0 ; array->Set(i, array->Get(i - 1)), i--);
      array->Set(0, item);
    }

    void InsertAt(int index, T item) override
    {
      array->Resize(array->GetSize() + 1);
      for (int i = array->GetSize() - 1; i > index; array->Set(i, array->Get(i - 1)), i--);
      array->Set(index, item);
    }

    void Set(int index, T item) override {array->Set(index, item);}

    void Swap(int index1, int index2) override
    {
      T tmp = array->Get(index1);
      array->Set(index1, array->Get(index2));
      array->Set(index2, tmp);
    }

    void DoEmpty() override
    {
      if (array) delete array;
      array = new DynamicArray<T>();
    }

    Sequence<T>* Concat(Sequence<T>* _array) override
    {
      Sequence<T>* seq = new ArraySequence<T>(*array);
      for (int i = 0; i < _array->GetLength(); seq->Append(_array->Get(i)), i++);
      return seq;
    }
};