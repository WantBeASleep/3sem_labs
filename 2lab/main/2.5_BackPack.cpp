//* ПРОЧТИ ОПИСАНИЕ В solutionTree.hpp !! 

#include <iostream>
using namespace std;


//? ОГРАНИЧЕНИЯ
#define VOL_LIMIT 5


#include "../../libv2/libSequence.hpp"
#include "../../libv2/structs/trees/solutionTree.hpp"

class item
{
  public:
    int cost;
    int volume;

    item() {cost = 0; volume = 0;}
    item(int cost, int volume) {this->cost = cost; this->volume = volume;}

    bool operator== (const item& item)
    {
      if (cost == item.cost && volume == item.volume) return true;
      else return false;
    }

    bool Better(const item& _item)
    {
      if (_item.cost > cost) return true;
      else if (_item.cost < cost) return false;
      else if (_item.volume < volume) return true;
      else return false;
    }

    item GetWayStat(const item& _item)
    {
      item newItem(cost + _item.cost, volume + _item.volume);
      return newItem;
    }

    bool InLimit(const item& _item)
    {
      if (volume + _item.volume <= VOL_LIMIT) return true;
      else return false;
    }
};

ostream& operator<< (ostream& os, const item& item);

void BackPack()
{
  Sequence<item>* items = new ArraySequence<item>();
  cout << "data:" << endl;
  for (int i = 0; i < 10; i++)
  {
    item newItem(rand() % 10 + 1, rand() % 10 + 1);
    items->Append(newItem);
    cout << newItem << endl;
  }

  solutionTree<item> tree(items);
  
}

ostream& operator<< (ostream& os, const item& item)
{
  os << "item// " << item.cost << " : " << item.volume;
  return os;
}
