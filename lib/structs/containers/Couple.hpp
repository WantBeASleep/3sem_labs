#pragma once

using namespace std;

template <typename TKey, typename TElement>
class Couple
{
  public:
    TKey key;
    TElement element;

    Couple() {}
    Couple(TKey const &key) {this->key = key;}
    Couple(TKey const &key, TElement const &element) {this->key = key; this->element = element;}
    Couple(const Couple &obj) {key = obj.key; element = obj.element;}
    ~Couple() {}

    bool operator== (const Couple<TKey, TElement> &obj) const {return this->key == obj.key;}
    Couple& operator= (const Couple<TKey, TElement> &obj) {key = obj.key; element = obj.element; return *this;}
    bool operator> (const Couple<TKey, TElement> &obj) const {return this->key > obj.key;}
    bool operator< (const Couple<TKey, TElement> &obj) const {return this->key < obj.key;}
};
