#include <string>

#include "../lib/sequence.hpp"
#include "../lib/funcs.hpp"
#include "main/tasks.hpp"

using namespace std;

int main()
{
  string opt_values[2] = {"Plot", "Tests"};
  Sequence<string>* Options = new ArraySequence<string>(opt_values, 2);

  int res = ViewAnsMenu(Options);
  switch (res)
  {
    case 1:
    {
      Plot();
      break;
    }
    case 2:
    {
      Test();
      break;
    }
  }

  delete Options;
  return 0;
}