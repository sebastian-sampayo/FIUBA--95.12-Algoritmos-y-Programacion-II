#include <iostream>
#include "vector.h"

using namespace std;

void print(Vector<int> &v)
{
  for(int i=0; i<v.size(); i++)
    cout << v[i] << endl;
}


int
main ()
{
  Vector<int> v;
  Vector<int> v2 = v;
  Vector<int> v3(3);
  Vector<int> v4(4);
  
  for (int i=0; i<v3.size(); i++)
    v3[i] = i;
  for (int i=0; i<v4.size(); i++)
    v4[i] = -i;

  cout << "Size v: " << v.size() << endl;
  print(v);
  cout << "Size v2: " << v2.size() << endl;
  print(v2);
  cout << "Size v3: " << v3.size() << endl;
  print(v3);
  cout << "Size v4: " << v4.size() << endl;
  print(v4);

  v4 = v3;
  v4.push_back(100);
  cout << "Size v4: " << v4.size() << endl;
  print(v4);

  v4.pop_back();
  cout << "Size v4: " << v4.size() << endl;
  print(v4);

  return 0;
}
