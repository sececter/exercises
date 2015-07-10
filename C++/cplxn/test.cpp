/* 
** Name:     test.cxx
** Author:   Leo Liberti
** Purpose:  testing the complex numbers class
** Source:   GNU C++
** History:  061019 work started
*/

#include <iostream>
#include <string>
#include "complex.cpp"

int main(int argc, char** argv) {
  using namespace std;
  if (argc < 4) {
    cerr << "need an operation on command line" << endl;
    cerr << "   e.g. ./test 4.3+3i - 2+3.1i" << endl;
    cerr << "   (no spaces within each complex number, use spaces to\n";
    cerr << "    separate the operands and the operator - use arithmetic\n";
    cerr << "    operators only)" << endl;
    return 1;
  }
  string complexString1 = argv[1];
  string complexString2 = argv[3];
  Complex complex1;
  complex1.fromString(complexString1);

  Complex complex2;
  complex2.fromString(complexString2);

  Complex complex3;
  if (argv[2][0] == '+') {
    complex3 = complex1 + complex2;
  } else if (argv[2][0] == '-') {
    complex3 = complex1 - complex2;
  } else if (argv[2][0] == '*' || argv[2][0] == '.') {
    argv[2][0] = '*';
    complex3 = complex1 * complex2;
  }
  cout << complex1 << " " << argv[2][0] << " (" << complex2 << ") = "
       << complex3 << endl;
  return 0;
}
