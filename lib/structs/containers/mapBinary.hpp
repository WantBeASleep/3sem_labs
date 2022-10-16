#pragma once
#include "../sequence/sequence.hpp"
#include "../sequence/arraySequence.hpp"
#include "../trees/collectionBinaryTree.hpp"
#include "imap.hpp"

using namespace std;

template <typename TKey, typename TElement>
class AVLMap : public IMap<TKey, TElement>
{
  private:
    CollectionTree<TKey, TElement> data;

  public:
    
    //@ ПОЛУЧЕНИЕ 
    int GetCount() const override {return data.GetCount();}

    int GetCapacity() const override {return -1;}

    TElement& Get(TKey const &key) const override {return data.Get(key);}

    Sequence<TKey>* GetKeys() const override
    {
      Sequence<Couple<TKey, TElement>>* Couples = data.GetSequence();
    
      Sequence<TKey>* Keys = new ArraySequence<TKey>();
      for (int i = 0; i < Couples->GetLength(); Keys->Append(Couples->Get(i).key), i++);
      
      delete Couples;
      return Keys;
    }

    Sequence<TElement>* GetValues() const override
    {
      Sequence<Couple<TKey, TElement>>* Couples = data.GetSequence();

      Sequence<TElement>* Values = new ArraySequence<TElement>();
      for (int i = 0; i < Couples->GetLength(); Values->Append(Couples->Get(i).element), i++);

      delete Couples;
      return Values;
    }

    //@ INFO
    bool ContainsKey(TKey const &key) const override
    {
      Sequence<TKey>* Keys = GetKeys();
      bool res = Keys->Contains(key);
      delete Keys;
      return res;
    }

    //@ ОПЕРАЦИИ
    void Add(TKey const &key, TElement const &element) override {data.Add(key, element);}

    void Remove(TKey const &key) override {data.Remove(key);}
    
};