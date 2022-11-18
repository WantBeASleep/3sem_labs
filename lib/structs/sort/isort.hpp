#pragma once

#include "../sequence/sequence.hpp"

using namespace std;

template <class T>
class ISort
{
  public:
    virtual string GetName() const = 0;
    virtual Sequence<T>* Sort(Sequence<T>* seq, bool (*cmp)(const T&, const T&)) const = 0;
};