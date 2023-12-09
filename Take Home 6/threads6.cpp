#include <thread>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

void hello(int order)
{
  //uncomment the following code and comment out the long cout to see a tidy output on screen
  /*ostringstream os;
  os << order << " " << this_thread::get_id() << endl;
  cout << os.str();*/

  cout << order << " " << this_thread::get_id() << endl;
}

int main()
{
  int i;
  thread threads[5];
  for (i=0; i < 5; i++)
  {
      threads[i] = (thread(&hello, i));
  }

  for (i=0; i < 5; i++)
  {
      threads[i].join();
  }
  cout << endl << "Main Thread id:" << this_thread::get_id() << endl;

  return 0;
}
