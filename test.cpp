// thread example
#include <iostream>       // cout
#include <thread>         // thread

using namespace std;
 
void foo() 
{
  cout << "foo here\n" << endl;
}

void bar(int x)
{
  cout << "bar here\n" << x << endl;
}

int main() 
{
  thread first (&foo);     // spawn new thread that calls foo()
  thread second (&bar, 10);  // spawn new thread that calls bar(0)

  cout << "main, foo and bar now execute concurrently...\n";

  // synchronize threads:
  first.join();                // pauses until first finishes
  second.join();               // pauses until second finishes

  cout << "foo and bar completed.\n";

  return 0;
}