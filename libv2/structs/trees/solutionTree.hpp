#pragma once
#include <iostream>
using namespace std;

#include "../sequence/sequence.hpp"
#include "../sequence/arraySequence.hpp"


template <typename EType, typename Stats>
class solutionNode
{
  public:
    EType key;
    solutionNode<EType, Stats>* prev;
    Sequence<solutionNode<EType, Stats>*>* leaves;
    
    Stats wayStats;

    solutionNode()
    {
      leaves = new ArraySequence<solutionNode<EType, Stats>*>();
    }

    solutionNode(const EType& key, solutionNode<EType, Stats>* prev, const Stats& wayStats) :  key(key), wayStats(wayStats)
    {
      leaves = new ArraySequence<solutionNode<EType, Stats>*>();
      this->prev = prev;
    }

    ~solutionNode()
    {
      delete leaves;
    }
};

template <typename EType, typename Stats>
class solution
{
  public:
    Stats cfg;
    solutionNode<EType, Stats>* ptr;

    void checkWay(solutionNode<EType, Stats>* ptr)
    {
      if (ptr->wayStats > cfg)
      {
        cfg = ptr->wayStats;
        this->ptr = ptr;
      }
    }  

    void getAnswer()
    {
      cout << cfg;

      solutionNode<EType, Stats>* ptr2 = ptr;

      while (ptr2->prev)
      {
        cout << ptr2->key;
        ptr2 = ptr2->prev;
      }
    }

};

template <typename EType, typename Stats, typename limit>
class solutionTree
{
  private:
    solutionNode<EType, Stats>* root;
    solution<EType, Stats> answer;
    Sequence<EType>* data;
    limit lmt;
    Stats (*func)(const Stats& stat, const EType& obj);


    void addLeaves(solutionNode<EType, Stats>* ptr, Sequence<EType>* options)
    {
      if (!options->GetLength())
      {
        answer.checkWay(ptr);
        return;
      }

      for (int i = 0; i < options->GetLength(); i++)
      {
        Stats node_stat = func(ptr->wayStats, options->Get(i));

        solutionNode<EType, Stats>* node = new solutionNode<EType, Stats>(options->Get(i), ptr, node_stat);

        Sequence<EType>* node_opt = new ArraySequence<EType>();
        for (int j = 0; j < options->GetLength(); j++)
        {
          if (i != j && lmt.check(ptr->wayStats, options->Get(j)))
          {
            node_opt->Append(options->Get(j));
          }
        }

        ptr->leaves->Append(node);

        addLeaves(ptr->leaves->GetLast(), node_opt);

        delete node_opt;
      }
      return;
    }

  public:

    solutionTree(Sequence<EType>* data, limit lmt, Stats (*func)(const Stats&, const EType&))
    {
      root = new solutionNode<EType, Stats>();
      this->data = data->Copy();
      this->lmt = lmt;
      this->func = func;

      addLeaves(root, data);

      answer.getAnswer();
    }

    ~solutionTree()
    {
      // delete root;
      // delete data;
    }
    
};