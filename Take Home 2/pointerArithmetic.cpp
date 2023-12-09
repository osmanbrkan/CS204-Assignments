/* 
   Author: Kamer Kaya
   Date: September, 2014
*/

#include <iostream>
using namespace std;

int main() {

  int myIntArray[100];
  int* arrPtr = myIntArray;
  int* pInt1 = &(myIntArray[5]);
  int* pInt2 = &(myIntArray[10]);

  //these are the addresses the pointer show
  cout << pInt2 << " " << pInt1 << endl;   //addresses of integer pointers

  //the difference should be 4 x 5 = 20 in decimal since each
  //integer is 4 bytes (32 bits). 

  //this is 5 in pointer arithmetic    //gives the integer difference
  cout << pInt2 - pInt1 << endl;
  cout << "------------------------------------" << endl;

    
  short myShortArray[100];  //max 65k characters can short holds
  short* pShort1 = &(myShortArray[5]);
  short* pShort2 = &(myShortArray[10]);

  //these are the addresses the pointer show
  cout << pShort2 << " " << pShort1 << endl;
  //the difference between the addresses is 2 x 5 = 10 since each
  //short is 2 bytes (16 bits). 

  //this is 5 in pointer arithmetic
  cout << pShort2 - pShort1 << endl;
  cout << "------------------------------------" << endl;  

  bool myBoolArray[100];   // 1byte, false or true
  bool* pBool1 = &(myBoolArray[5]);
  bool* pBool2 = &(myBoolArray[10]);

  //these are the addresses the pointer show
  cout << pBool2 << " " << pBool1 << endl;
  //the difference between the addresses is 1 x 5 = 5 since each
  //bool is 1 byte (8 bits; in fact 1 bit is sufficient but a 
  //byte is the smallest possible). 

  //this is 5 in pointer arithmetic
  cout << pBool2 - pBool1 << endl;
  cout << "------------------------------------" << endl;

  cin.get();
  cin.ignore();
  return 1;
}
