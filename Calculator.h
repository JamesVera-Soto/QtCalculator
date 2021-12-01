#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include <stack>
#include <vector>
#include <math.h>
#include <stdexcept>
using namespace std;

class Calculator{
  private:

  public:

    string reformat(string s);

    string removeTrailingZeros(string &s);

    int findClosingP(string &s, int l, int r);

    double getNextNum(vector<string> v, int &i);

    string calculate(string s);
};

#endif // CALCULATOR_H
