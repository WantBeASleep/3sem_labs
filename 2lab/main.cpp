#include <string>

#include "../libv2/libSequence.hpp"
#include "../libv2/libFuncs.hpp"
#include "main/tasks.hpp"

using namespace std;

int main()
{
  string opt_values[3] = {"2.1 - Gistagramm", "2.4 - Alphabet Dictionary"};
  Sequence<string>* Options = new ArraySequence<string>(opt_values, 2);
  
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
      Aplhabet_dictionary();
      break;
    }
  }

  delete Options;
  return 0;
}