#include <iostream>
#include <sstream>
#include <thread>
#include <string>

using namespace std;

int maximum = 7;

void function1(string name)
{
    for(int i = 0; i < maximum; i++)
    {
        ostringstream output;
        output << name <<" thread, thread id: "<<this_thread::get_id() << " is working with i="<< i <<endl;
        cout << output.str();
    }
}

int main()
{
    thread thr1(function1, "First");
    thread thr2(function1, "Second");

    thr1.join();
    thr2.join();
    return 0;
}