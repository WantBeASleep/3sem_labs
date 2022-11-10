#include <string>
#include <time.h>
#include <fstream>

#include "../../lib/sequence.hpp"
#include "../../lib/containers.hpp"
#include "../../lib/funcs.hpp"
#include "../../lib/libs.hpp"

using namespace std;

class Person
{
  public:
    string name;
    int age;

    Person() {}
    Person(string name, int age) {this->name = name; this->age = age;}
    ~Person() {}

    bool operator== (const Person &person) const {return (name == person.name) && (age == person.age);}
    bool operator> (const Person &person) const {return age > person.age;}
    bool operator< (const Person &person) const {return age < person.age;}
};

class Range
{
  public:
    int start;
    int end;

    Range() {}
    Range(int start, int end) {this->start = start; this->end = end;}
    ~Range() {}

    bool operator== (const Range &obj) const {return start == obj.start;}
    Range& operator= (const Range &obj) {start = obj.start; end = obj.end; return *this;}
    bool operator> (const Range &obj) const {return start > obj.start;}
    bool operator< (const Range &obj) const {return start < obj.start;}
};

ostream& operator<< (ostream& os, const Range &rng)
{
  string res;
  res = to_string(rng.start) + "-" + to_string(rng.end);
  return os << res;
}

class Split
{
  private:
    Sequence<Range>* data;

  public:
    Split(Sequence<int>* Borders)
    {
      data = new ArraySequence<Range>();

      int bottom = 0;
      for (int i = 0; i < Borders->GetLength(); i++)
      {
        Range rng(bottom, Borders->Get(i));
        data->Append(rng);
        bottom = Borders->Get(i) + 1;
      }
    }
    ~Split() {delete data;}

    int GetCount() const {return data->GetLength();}

    Range Get(int index) const {return data->Get(index);}
};

class Statistic
{
  private:
    Sequence<Person>* data;

  public:
    Statistic() {data = new ArraySequence<Person>();}

    Statistic(const Statistic &obj) {data = obj.data->Copy();}
    ~Statistic() {delete data;}  

    int GetCount() const {return data->GetLength();}

    Person Get(int index) const {return data->Get(index);}

    int GetAvgAge() const
    {
      int avg_age = 0;
      for (int i = 0; i < data->GetLength(); avg_age += data->Get(i).age, i++);
      avg_age /= data->GetLength();
      return avg_age;
    }

    void Add(Person const &obj) {data->Append(obj);}

    bool operator== (const Statistic &obj) {return data == obj.data;}
    Statistic& operator= (const Statistic &obj) {delete data; data = obj.data->Copy(); return *this;}

};

bool comparator(const PairKeyVal<Range, Statistic>& val1, const PairKeyVal<Range, Statistic>& val2)
{
  if (val1 < val2) return true;
  else return false;
}

class Gistagramm
{
  private:
    IMap<Range, Statistic>* map;

    bool IsInRange(Person const &person, Range const &range) const
    {
      if (person.age >= range.start && person.age <= range.end) return true;
      else return false;
    }

  public:
    Gistagramm(Sequence<Person>* Seq, Split const &Splt)
    {
      bool (*cmp)(const PairKeyVal<Range, Statistic>&, const PairKeyVal<Range, Statistic>&) = comparator;
      map = new AVLMap<Range, Statistic>(cmp);
      
      for (int i = 0; i < Splt.GetCount(); i++)
      {
        Statistic stat;
        map->Add(Splt.Get(i), stat);
      }
      
      for (int i = 0; i < Seq->GetLength(); i++)
      {
        for (int j = 0; j < Splt.GetCount(); j++)
        {
          if (IsInRange(Seq->Get(i), Splt.Get(j)))
          {
            map->Get(Splt.Get(j)).Add(Seq->Get(i));
            break;
          }
        }
      }
    }

    ~Gistagramm() {delete map;}

    void GetPlot()
    {
      GnuplotPipe Gp;
      Sequence<string>* Styles = parse_seq("plot/gistagramm/gnuplot_styles.txt");
      for (int i = 0; i < Styles->GetLength(); Gp.sendLine(Styles->Get(i)), i++);

      ofstream out;
      out.open("plot/gistagramm/gnuplot_data.gnu");
      Sequence<Range>* Keys = map->GetKeys();

      for (int i = 0; i < map->GetCount(); i++)
      {
        out << i << " " << Keys->Get(i) << " " << map->Get(Keys->Get(i)).GetCount() << endl;
      }
      out.close();
      
      Gp.sendLine("plot \"plot/gistagramm/gnuplot_data.gnu\" using 1:3:xtic(2) with boxes");
      
      delete Styles;
      delete Keys;
    }
};

void Gistagramm_task()
{
  srand(time(NULL));

  Sequence<string>* Names = parse_seq("base/name_base.txt");
  Sequence<Person>* Seq = new ArraySequence<Person>();

  for (int i = 0; i < 100; Seq->Append(Person(Names->Get(rand() % 100), rand() % 100)), i++);
  
  int borders[5] = {20, 40, 60, 80, 100};
  Sequence<int>* Bord_Seq = new ArraySequence<int>(borders, 5);

  Split Spl(Bord_Seq);
  Gistagramm Gista(Seq, Spl);

  Gista.GetPlot();

  delete Names;
  delete Seq;
  delete Bord_Seq;
}