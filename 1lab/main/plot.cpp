#include <time.h>
#include <fstream>

#include "../../lib/sequence.hpp"
#include "../../lib/sorts.hpp"
#include "../../lib/funcs.hpp"
#include "../../lib/libs.hpp"

using namespace std;

static bool comparator(int val1, int val2);

static ostream& operator<< (ostream& os, const ISort<int>* Sort)
{
  return os << Sort->GetName();
}

void Plot()
{
  srand(time(NULL));
  
  // ОПРЕДЕЛЯЕМ ARRAY/LIST
  string opt_string[2] = {"Array base", "Lists base"};
  Sequence<string>* types = new ArraySequence<string>(opt_string, 2);
  int res_type = ViewAnsMenu(types);

  Sequence<int>* Seq =
    res_type == 1
      ? (Sequence<int>*)(new ArraySequence<int>())
      : (Sequence<int>*)(new LinkedListSequence<int>());

  // ФОРМИРУЕМ СИКВЕНС СОРТИРОВОК
  Sequence<ISort<int>*>* Sorts = new ArraySequence<ISort<int>*>();

  Sorts->Append(new BubbleSort<int>());
  Sorts->Append(new InsertionSort<int>());
  Sorts->Append(new SelectionSort<int>());
  Sorts->Append(new ShakerSort<int>());
  // Sorts->Append(new BinaryInsertSort<int>()); // 19 bytes heap? delete???? delete Isort = Bin..
  // Sorts->Append(new BinaryAVLSort<int>()); // 16 bytes with todo...

  // ВСТУПЛЕНИЕ В ФАЙЛ С ДАННЫМИ(ВРЕМЯ СОРТРОВКИ)
  ofstream out;
  out.open("plot/plot_data.gnu");
  out << "#\t\t\tGRAPH DATA FOR GNUPLOT" << endl;
  out << "#\t\t\tFROM plot.cpp" << endl;
  out << "#ROWS: " << endl << "Count ";
  PrintSeqAsList<ofstream, ISort<int>*>(out, Sorts);
  out << endl;

  // СОРТИРУЕМ С ШАГОМ В 100 ЭЛЕМЕНТОВ
  for (int count = 100; count <= 1000; count+= 100)
  {
    out << count << " ";
    for (int i = 0; i < Sorts->GetLength(); i++)
    {
      Seq->DoEmpty();
      for (int j = 0; j < count; Seq->Append(rand() % count), j++);

      clock_t start = clock();
      Sequence<int>* Res = Sorts->Get(i)->Sort(Seq, comparator);
      clock_t end = clock();

      double SortTime = (double)(end - start) / CLOCKS_PER_SEC;
      out << SortTime << " ";
      
      delete Res;
    }
    out << endl;
  }
  out.close();

  // ФОРМИРУЕМ ОБЪЕКТ ГРАФИКА
  GnuplotPipe Gp;
  Sequence<string>* GnuplotStyles = parse_seq("plot/gnuplotStyles.gnu");
  for (int i = 0; i < GnuplotStyles->GetLength(); Gp.sendLine(GnuplotStyles->Get(i)), i++);
  string PlotCfg = "plot ";
  for (int i = 0; i < Sorts->GetLength(); i++)
  {
    PlotCfg.append("\'plot/plot_data.gnu\' using 1:" + to_string(i+2)
    + " title \"" + Sorts->Get(i)->GetName() + "\" w l lw 2");
    if (!(i == Sorts->GetLength() - 1)) PlotCfg.append(", ");
  }
  Gp.sendLine(PlotCfg);

  delete types;
  delete Seq;
  for (int i = 0; i < Sorts->GetLength(); delete Sorts->Get(i), i++);
  delete Sorts;
  delete GnuplotStyles;
}

// КОМПАРАТОР
static bool comparator(int val1, int val2)
{
  if (val1 < val2) return true;
  else return false;
}