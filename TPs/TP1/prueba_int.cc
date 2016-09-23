#include <iostream>
#include <cmath>
using namespace std;

int main()
{
  if (log2(4) - (int)log2(4))
    return(1);

  cout << log2(7) << endl;
  cout << log2(8) << endl;
  cout << log2(7) - (int) log2(7) << endl;
  
  cout << ((log2(7) - (int) log2(7)) == 0) << endl;
  cout << ((log2(8) - (int) log2(8)) == 0) << endl;

  return 0;
}
