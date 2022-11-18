#pragma once

using namespace std;

template <typename TKey, typename TElement>
class PairKeyVal
{
  public:
    TKey key;
    TElement element;

    PairKeyVal() {}
    PairKeyVal(TKey const &key) {this->key = key;}
    PairKeyVal(TKey const &key, TElement const &element) {this->key = key; this->element = element;}
    PairKeyVal(const PairKeyVal &obj) {key = obj.key; element = obj.element;}
    ~PairKeyVal() {}

    bool operator== (const PairKeyVal<TKey, TElement> &obj) const {return this->key == obj.key;}
    PairKeyVal& operator= (const PairKeyVal<TKey, TElement> &obj) {key = obj.key; element = obj.element; return *this;}
    bool operator> (const PairKeyVal<TKey, TElement> &obj) const {return this->key > obj.key;}
    bool operator< (const PairKeyVal<TKey, TElement> &obj) const {return this->key < obj.key;}
};
