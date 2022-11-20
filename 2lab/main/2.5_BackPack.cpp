using namespace std;
#include <iostream>
#include <time.h>

#include "../../libv2/structs/trees/2.5lab2tree.hpp"
#include "../../libv2/libSequence.hpp"
#include "../../libv2/libSortSequence.hpp"

#define BACKPACK_VOL 5

class subject
{
  public:
    subject() {cost = 0; volume = 0;}
    subject(int cost, int volume) {this->cost = cost; this->volume = volume;}
    int cost;
    int volume;

    bool operator== (const subject& obj) {return (cost == obj.cost) && (volume == obj.volume);}
    subject& operator= (const subject& obj)
    {
      cost = obj.cost;
      volume = obj.volume;
      return *this;
    }
};

static bool comparator(const subject& obj1, const subject& obj2)
{
  if (obj1.cost < obj2.cost) return true;
  else if (obj1.cost == obj2.cost)
  {
    if (obj1.volume > obj2.volume) return true;
    else return false;
  } else return false;
}

ostream& operator<< (ostream &os, Sequence<subject>* seq)
{
  for (int i = 0; i < seq->GetLength(); i++)
  {
    cout << i+1 << " : ";
    cout << seq->Get(i).cost << " : ";
    cout << seq->Get(i).volume << endl;
  }
  return os;
}

ostream& operator<< (ostream &os, subject& sub)
{
  os << sub.cost << " : " << sub.volume;
  return os;
}

class solution
{
  public:
    int wayCost;
    simpleNode<subject>* leave;

  solution() {wayCost = 0; leave = nullptr;}

  void check(simpleNode<subject>* ptr)
  {
    if (ptr->wayCost > wayCost)
    {
      wayCost = ptr->wayCost;
      leave = ptr;
    }
  }
};



void doLeaves(simpleNode<subject>*, solution&);
void getway(simpleNode<subject>*);

void BackPack()
{
  Sequence<subject>* seq_data = new ArraySequence<subject>();
  // for (int i = 0; i < data.GetLength(); seq_data->Append(data.Get(i)), i++);
  for (int i = 0; i < 10; i++)
  {
    subject obj(rand()%10 + 1, 1);
    seq_data->Append(obj);
  }

  cout << seq_data;

  simpleTree<subject> tree;
  subject rootsub;
  simpleNode<subject> rootNode(rootsub, nullptr, 0, 0, seq_data);
  tree.root = &rootNode;

  simpleNode<subject>* ptr = tree.root;

  solution answer;

  // cout << "check" << endl;
  // cout << tree.root->options;
  doLeaves(tree.root, answer);

  // cout << "~!" << endl;
  // simpleNode<subject>* ptrOut = tree.root;
  // while (ptrOut->leaves->GetLength() != 0)
  // {
  //   cout << ptrOut->leaves->GetLength() << endl;
  //   cout << ptrOut->key << endl;
  //   ptrOut = ptrOut->leaves->Get(rand() % ptrOut->leaves->GetLength());
  // }

  // Sequence<subject>* res = answer.getSolution();

  // cout << "RESULT:" << endl << res;

  cout << "here!" << endl;

  getway(answer.leave);
}

void doLeaves(simpleNode<subject>* ptr, solution& answer)
{
  if (ptr->options->GetLength() == 0)
  {
    answer.check(ptr);
    return;
  }

  for (int i = 0; i < ptr->options->GetLength(); i++)
  {
    simpleNode<subject>* node = new simpleNode<subject>();
    node->key = ptr->options->Get(i);
    node->prev = ptr;
    node->wayCost = ptr->wayCost + node->key.cost;
    node->wayVolume = ptr->wayVolume + node->key.volume;

    Sequence<subject>* nodeOptions = new ArraySequence<subject>();
    for (int j = 0; j < ptr->options->GetLength(); j++)
    {
      if (node->wayVolume + ptr->options->Get(j).volume <= BACKPACK_VOL && j != i)
      {
        nodeOptions->Append(ptr->options->Get(j));
      }
    }
    node->options = nodeOptions;

    ptr->leaves->Append(node);
    doLeaves(ptr->leaves->GetLast(), answer);
  }
  return;
}

void getway(simpleNode<subject>* ptr)
{
  while (ptr->prev != nullptr)
  {
    cout << ptr->key << endl;
    ptr = ptr->prev;
  }
}