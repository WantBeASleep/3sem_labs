#pragma once

#include "../sequence/sequence.hpp"

using namespace std;

template <typename TKey, typename TElement>
class IMap
{
  public:
    virtual ~IMap() {}

    //@ ПОЛУЧЕНИЕ
    virtual int GetCount() const = 0;
    virtual int GetCapacity() const = 0;
    virtual TElement Get(TKey key) const = 0;
    virtual Sequence<TKey>* GetKeys() const = 0;
    virtual Sequence<TElement>* GetValues() const = 0;
    
    //@ INFO
    virtual bool ContainsKey(TKey key) const = 0;

    //@ ОПЕРАЦИИ
    virtual void Add(TKey key, TElement element) = 0;
    virtual void Remove(TKey key) = 0;

};