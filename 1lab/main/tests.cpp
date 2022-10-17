#include <time.h>
#include <iostream>

#include "../../lib/sequence.hpp"
#include "../../lib/sorts.hpp"
#include "../../lib/funcs.hpp"

using namespace std;

static bool comparator(int val1, int val2);

//EXTERN не работает
static ostream& operator<< (ostream& os, const ISort<int>* Sort)
{
  return os << Sort->GetName();
}

void Test()
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
  Sorts->Append(new BinaryAVLSort<int>());
  // Sorts->Append(new BinaryInsertSort<int>()); // 19 bytes heap? delete???? delete Isort = Bin..

  // МАССИВ КОТОРЫЙ БУДЕМ СОРТИРОВАТЬ
  for (int i = 0; i < 20; Seq->Append(rand() % 1000), i++);

  // ВЫВОДИМ ОРИГИНАЛ
  cout << "Original: ";
  PrintSeqAsList<ostream, int>(cout, Seq);
  cout << endl;

  // ВЫВОДИМ СОРТИРОВКИ
  for (int i = 0; i < Sorts->GetLength(); i++)
  {
    cout << Sorts->Get(i) << ": ";
    Sequence<int>* Res = Sorts->Get(i)->Sort(Seq, comparator);
    PrintSeqAsList<ostream, int>(cout, Res);
    cout << endl;
    delete Res;
  }

  delete types;
  delete Seq;
  for (int i = 0; i < Sorts->GetLength(); delete Sorts->Get(i), i++);
  delete Sorts;
}

// КОМПАРАТОР
static bool comparator(int val1, int val2)
{
  if (val1 < val2) return true;
  else return false;
}