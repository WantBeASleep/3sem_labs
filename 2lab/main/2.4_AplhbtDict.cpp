#include <string>
#include <iostream>
#include <fstream>
#include "../../lib/sequence.hpp"
#include "../../lib/containers.hpp"
#include "../../lib/funcs.hpp"

class Book
{
  private:
    SortedSequence<Couple<string, Sequence<int>*>> data;
    string text;
    int pagesize;

    int PageSize(int number) const
    {
      if (number == 1) return pagesize/2;
      if (!(number % 10)) return pagesize/4 * 3;
      return pagesize;
    }

  public:
    Book(string text, int size)
    {
      this->text = text;
      pagesize = size;

      Sequence<Couple<string, Sequence<int>*>>* Res = new ArraySequence<Couple<string, Sequence<int>*>>();

      int curPage = 1, symbCounter = -1;// pagesize
      int strIdx = 0, endIdx = 0, ptr = 0; // word vars
      while(text[ptr])
      {
        if (text[ptr] == ' ')
        {
          endIdx = ptr - 1;
          string word = text.substr(strIdx, endIdx - strIdx + 1);

          symbCounter += word.length() + 1;
          if (symbCounter >= PageSize(curPage))
          {
            symbCounter = -1;
            curPage++;
          }

          Couple<string, Sequence<int>*> cpl(word);
          if (!Res->Contains(cpl))
          {
            cpl.element = new ArraySequence<int>();
            cpl.element->Append(curPage);
            Res->Append(cpl);
          } else {
            Res->Get(Res->IndexOf(cpl)).element->Append(curPage);
          }

          strIdx = ptr + 1;
        }

        if (text[ptr] == '\n') // СЧИТАЮ ЧТО У МЕНЯ ВСЕГДА 20 СТРОК, СИМВОЛОВ В СТРОКЕ = PAGESIZE / 20;
        {
          int line = (symbCounter / (pagesize/20)) + 1;
          symbCounter = line * (pagesize/20);
          if (symbCounter >= PageSize(curPage))
          {
            symbCounter = -1;
            curPage++;
          }

          strIdx = ptr + 1;
        }

        ptr++;
      }

      data = Res;
      delete Res;
    }

    friend ostream& operator<< (ostream &os, Book const &book);

};

ostream& operator<< (ostream &os, Book const &book)
{
  for (int i = 0; i < book.data.GetLength(); i++)
  {
    os << book.data.Get(i).key << ":";
    PrintSeqAsList<ostream, int>(os, book.data.Get(i).element);
    os << endl;
  }
  return os;
}

void Aplhabet_dictionary()
{
  string text, line;
  ifstream in("base/text.txt");
  while (getline(in, line))
  {
    text.append(line + '\n');
  }
  in.close();
  text.erase(text.size() - 1);

  Book book(text, 100);
  // cout << book << endl;
}