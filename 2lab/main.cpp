#include <string>

#include "../lib/sequence.hpp"
#include "../lib/funcs.hpp"
#include "main/tasks.hpp"

using namespace std;

int main()
{
  string opt_values[3] = {"2.1 - Gistagramm", "2.2 - Discharged vector/matrix", 
    "2.4 - Alphabet indicator"};
  Sequence<string>* Options = new ArraySequence<string>(opt_values, 3);
  
  int res = ViewAnsMenu(Options);
  switch (res)
  {
    case 1:
    {
      Gistagramm_task();
      break;
    }
    case 2:
    {
      
      break;
    }
  }

  delete Options;
  return 0;
}