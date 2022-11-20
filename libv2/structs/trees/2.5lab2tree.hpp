#pragma once
using namespace std;

#include "../sequence/sequence.hpp"
#include "../sequence/arraySequence.hpp"

template <typename T>
class simpleNode
{
  public:
    T key;
    simpleNode<T>* prev;
    Sequence<simpleNode<T>*>* leaves;

    int wayCost;
    int wayVolume;
    Sequence<T>* options;

    simpleNode() 
    {
      leaves = new ArraySequence<simpleNode<T>*>();
      options = new ArraySequence<T>();
    }

    simpleNode(const T& key, int wayCost, int wayVolume) : simpleNode()
    {
      this->key = key;
      this->wayCost = wayCost;
      this->wayVolume = wayVolume;
    }

    simpleNode(const T& key, simpleNode<T>* prev, int wayCost, int wayVolume, Sequence<T>* options) : simpleNode(key, wayCost, wayVolume)
    {
      this->prev = prev;
      this->options = options;
    }

};

template <typename T>
class simpleTree
{
  public:
    simpleNode<T>* root;
    int size;
    
    void nodeAdd(simpleNode<T>* currentNode, simpleNode<T>* newNode)
    {
      size++;
      currentNode->leaves->Append(newNode);
    }
    
};