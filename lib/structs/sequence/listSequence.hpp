#pragma once

#include "sequence.hpp"
#include "linkedList.hpp"

using namespace std;

template <typename T>
class LinkedListSequence : public Sequence<T>
{
  private:
    LinkedList<T>* list;
    
  public:
    LinkedListSequence() {list = new LinkedList<T>();}

    LinkedListSequence(T* items, int count) {list = new LinkedList<T>(items, count);}

    LinkedListSequence(const LinkedList<T>& _list) {list = new LinkedList<T>(_list);}

    LinkedListSequence(const LinkedListSequence<T>& _list) {list = new LinkedList<T>(*(_list.list));}

    ~LinkedListSequence() {delete list;}

    // получение
    T GetFirst() const override {return list->GetFirst();}

    T GetLast() const override {return list->GetLast();}

    T Get(int index) const override {return list->Get(index);}

    Sequence<T>* Copy() const override {return (Sequence<T>*)(new LinkedListSequence<T>(*this));}

    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override
    {
      return (Sequence<T>*)(new LinkedListSequence<T>(*(list->GetSubList(startIndex, endIndex))));
    }

    int GetLength() const override {return list->GetLength();}

    //@ INFO
    bool Contains(T item) const override {return false;}

    // Операции
    void Append(T item) override {list->Append(item);}

    void Prepend(T item) override {list->Prepend(item);}

    void InsertAt(int index, T item) override {list->InsertAt(index, item);}

    void Set(int index, T item) override {list->Set(index, item);}

    void Swap(int index1, int index2) override
    {
      T tmp = list->Get(index1);
      list->Set(index1, list->Get(index2));
      list->Set(index2, tmp);
    }

    void DoEmpty() override
    {
      delete list;
      list = new LinkedList<T>();
    }
    Sequence<T>* Concat(Sequence<T>* Seq) override
    {
      Sequence<T>* Res = new LinkedListSequence<T>(*this);
      for (int i = 0; i < Seq->GetLength(); Res->Append(Seq->Get(i)), i++);
      return Res;
    }
};