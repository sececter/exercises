#include <iostream>
//global variable
int g_One=1;
//function prototype

void func(int** pInt);

int main()
{
  int nvar=2;
  int* pvar=&nvar;
  func(&pvar);
  std::cout<<*pvar<<std::endl;//Will still show 2

  return 0;
}

void func(int** pInt)
{
  *pInt=&g_One;
}

