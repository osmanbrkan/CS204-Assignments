#include <iostream>       
#include <iomanip>        // for put_time
#include <thread>        
#include <chrono>         // for chrono::system_clock
#include <ctime>          // for time_t, tm, localtime, mktime
using namespace std;

void count1m(int id, struct tm *ptm) 
{
  this_thread::sleep_until(chrono::system_clock::from_time_t(mktime(ptm)));  //ptm is the name of the parameter. The others chrono::system_clock::from_time_t(mktime(...)) are fixed code
  //Comment out sleep_until line to see the pattern of thread completion order is similar to the creating order.

  for (int i=0; i < 1000000; ++i) 
     {}
  cout << id;
}


int main () 
{
  time_t tt = chrono::system_clock::to_time_t (chrono::system_clock::now());  //gets the current time
  struct tm *ptm = new struct tm;  //creating the time struct to be used in thread
  localtime_s(ptm, &tt);  //converting the time structures
  //above two lines may not work for some platforms. instead you can replace these two lines with    struct tm *ptm = localtime(&tt);
  cout << "Time is now " << put_time(ptm,"%X") << endl;  //displaying the time  
  ptm->tm_min++; //new time is the next minute. If currently minute is 59, your program may crash or work unexpectedly
  ptm->tm_sec=0;
  
  //Comment out the above six lines and decomment the following block and update the values 
  //to see how to manipulate time without getting the current time
  
  /*struct tm *ptm = new struct tm;
  ptm->tm_year = 123;  //2023 - years since 1900
  ptm->tm_mon = 4;  // May - months since Jan. (0..11)
  ptm->tm_mday = 15;  //day of month (1 ..31)
  ptm->tm_hour = 10;  //hour (0 .. 23)
  ptm->tm_min = 10;  //minutes (0 .. 59)
  ptm->tm_sec = 55;   //second (0 .. 59)*/
  
  
  cout << "Race will start at " << put_time(ptm,"%X") << endl;
  thread threads[10];
  for (int i=0; i<10; i++)
	  threads[i] = thread(count1m, i, ptm);
  for (int i=0; i<10; i++)
	  threads[i].join();
  cout << endl;
  return 0;
}
