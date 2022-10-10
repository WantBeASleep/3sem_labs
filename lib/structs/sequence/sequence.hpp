#pragma once

using namespace std;

template <class T>
class Sequence
{
  public:
    virtual ~Sequence() {}

    // получение
    virtual T GetFirst() const = 0;
    virtual T GetLast() const = 0;
    virtual T Get(int index) const = 0;
    virtual Sequence<T>* Copy() const = 0;
    virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) const = 0;
    virtual int GetLength() const = 0;

    //@ INFO
    virtual bool Contains(T item) const = 0;
    
    //Операции
    virtual void Append(T item) = 0;
    virtual void Prepend(T item) = 0;
    virtual void InsertAt(int index, T item) = 0;
    virtual void Set(int index, T item) = 0;
    virtual void Swap(int index1, int index2) = 0;
    virtual void DoEmpty() = 0;
    virtual Sequence<T>* Concat(Sequence<T>* seq) = 0;
};