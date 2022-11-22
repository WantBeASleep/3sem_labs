#include <iostream>
using namespace std;

#define BACKPACK_VOL 5

#include "../../libv2/libSequence.hpp"
#include "../../libv2/structs/trees/solutionTree.hpp"

class backpack_item
{
  public:
    int cost;
    int volume;

    backpack_item() {cost = 0; volume = 0;}
    backpack_item(int cost, int volume) {this->cost = cost; this->volume = volume;}

    bool operator== (const backpack_item& item)
    {
      if (cost == item.cost && volume == item.volume) return true;
      else return false;
    }
};

class wayStats
{
  public:
    int cost;
    int volume;

    wayStats() {cost = 0; volume = 0;}
    wayStats(int cost, int volume) {this->cost = cost; this->volume = volume;}

    bool operator> (const wayStats& stat)
    {
      if (cost > stat.cost) return true;
      else if (cost < stat.cost) return false;
      else if (volume < stat.volume) return true;
      else return false;
    }

    wayStats& operator= (const wayStats& stat)
    {
      cost = stat.cost;
      volume = stat.volume;
      return *this;
    }
    
};

class limit
{
  public:
    int volume;

    limit() {volume = BACKPACK_VOL;}

    bool check(const wayStats& wayStat, const backpack_item& obj2)
    {
      if (wayStat.volume + obj2.volume <= volume) return true;
      else return false;
    }
};

ostream& operator<< (ostream& os, const backpack_item& item);
ostream& operator<< (ostream& os, Sequence<backpack_item>* Seq);
ostream& operator<< (ostream &os, const wayStats& stat);
wayStats func(const wayStats& stat, const backpack_item& obj);

void BackPack()
{
  wayStats (*_func)(const wayStats& stat, const backpack_item& obj) = func;
  Sequence<backpack_item>* items = new ArraySequence<backpack_item>();
  for (int i = 0; i < 10; i++)
  {
    backpack_item item(rand() % 10 + 1, 1);
    items->Append(item);
  }

  cout << items;

  limit lmt;

  solutionTree<backpack_item, wayStats, limit> tree(items, lmt, _func);
  
}

ostream& operator<< (ostream& os, const backpack_item& item)
{
  os << item.cost << " : " << item.volume << endl;
  return os;
}

ostream& operator<< (ostream& os, Sequence<backpack_item>* Seq)
{
  for (int i = 0; i < Seq->GetLength(); i++)
  {
    os << "id: " << i+1 << " : cost: " << Seq->Get(i).cost << " : volume: " << Seq->Get(i).volume << endl;
  }
  return os;
}

ostream& operator<< (ostream &os, const wayStats& stat)
{
  os << "Cost: " << stat.cost << " : Volume: " << stat.volume << endl;
  return os;
}

wayStats func(const wayStats& stat, const backpack_item& obj)
{
  wayStats newStat;
  newStat.cost = stat.cost + obj.cost;
  newStat.volume = stat.volume + obj.volume;
  return newStat;
}