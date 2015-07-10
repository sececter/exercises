#include <iostream>
#include <cassert>
#include <iostream>
#include <stdlib.h>
#include <cmath>

using namespace std;

bool isPrime (int num) {
  assert(num >= 2);
  if (num == 2) {
    return true;
  } else if (num % 2 == 0) {
    return false;
  } else {
    bool prime = true;
    int divisor = 3;
    int upperLimit = sqrt(num) + 1;
    while (divisor <= upperLimit) {
      if (num % divisor == 0) {
        prime = false;
      }
      divisor +=2;
    }
    return prime;
  }
}

int main(int argc, char** argv) {
  int ret = 0;
  if (argc < 2) {
    cerr << "error: need an integer on command line";
    return 1;
  }
  int theInt = atoi(argv[1]);
  if (isPrime(theInt)) {
    cout << theInt << " is a prime number!" << endl;
  } else {
    cout << theInt << "is composite" << endl;
  return ret;
}
}
