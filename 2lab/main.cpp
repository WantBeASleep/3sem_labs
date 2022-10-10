#include <string>

#include "../lib/sequence.hpp"
#include "../lib/funcs.hpp"
#include "main/tasks.hpp"

using namespace std;

int main()
{
  Sequence<string>* Options = parse_seq("cfg/tasks.txt");
  
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