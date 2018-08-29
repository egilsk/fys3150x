#include <cstdlib>
#include <iostream>
#include <cmath>
#include <iomanip> 
#include "time.h"   // Not the use time.h

using namespace std; // note use of namespace                                       
int main (int argc, char* argv[])
{
  int i = atoi(argv[1]); 
  double *a, *b, *c;
  a = new double[i]; 
  b = new double[i]; 
  c = new double[i]; 

  clock_t start, finish;
  start = clock();
  for (int j = 0; j < i; j++) {
    a[j] = cos(j*1.0);
    b[j] = sin(j+3.0);
    c[j] = 0.0;
  }
  for (int j = 0; j < i; j++) {
    c[j] = a[j]+b[j];
  }
  finish = clock();
  double timeused = (double) (finish - start)/(CLOCKS_PER_SEC );
  cout << setiosflags(ios::showpoint | ios::uppercase);
  cout << setprecision(10) << setw(20) << "Time used  for vector addition=" << timeused  << endl;
  delete [] a;
  delete [] b;
  delete [] c;
  return 0;           /* success execution of the program */
}
