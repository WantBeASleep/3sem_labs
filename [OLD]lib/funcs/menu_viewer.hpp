#pragma once

#include <string>
#include <iostream>

#include "../structs/sequence/sequence.hpp"

using namespace std;

static void ViewMenu(Sequence<string>* Seq)
{
  for (int i = 0; i < 5; cout << "~~ ", i++);
  cout << "menu viewer";
  for (int i = 0; i < 5; cout << " ~~", i++);
  cout << endl;

  cout << "0. Return" << endl;
  for (int i = 0; i < Seq->GetLength(); i++)
  {
    cout << i + 1 << ". " << Seq->Get(i) << endl;
  }
}

static int ViewAnsMenu(Sequence<string>* Seq)
{
  ViewMenu(Seq);

  cout << "Option?: ";
  int ans;
  cin >> ans;
  return ans;
}