


#include <iostream>
#include <string>
#include "IntQueueHW6.h"
#include <mutex>
#include <chrono>
#include <ctime>
#include <thread>
#include <iomanip>
#include <vector>

using namespace std;


//globals

IntQueueHW6 myQueue(0);     // like chairs  // First I initialize it with size 0 and then change in playGame function, because otherwise its size is become negative initially and it gives error
mutex mtx, coutMutex;      // mutexes also must be global for using in all functions to synchronization of threads
vector<int> captured;   //players who captured (it resets every round)  I will use it in two functions


void playerThread(int playerID, struct tm*ptm) {


    this_thread::sleep_until(chrono::system_clock::from_time_t(mktime(ptm))); // 2 seconds sleep

    mtx.lock();
    if (!myQueue.isEmpty()) {
        int dequeueID;
        myQueue.dequeue(dequeueID);


        coutMutex.lock();
        cout << "Player " << playerID << " captured a chair at " << put_time(ptm, "%X") << "." << endl;
        coutMutex.unlock();
        captured.push_back(playerID);


    }
    else {

        coutMutex.lock();
        cout << "Player " << playerID << " couldn't capture a chair." << endl;
        coutMutex.unlock();


    }
    mtx.unlock();

}

void playGame(int numPlayers)
{

    thread playerThreads[numPlayers];
    vector<int>remainingPlayers; // remaining players to store playerIDs correctly to the next round.

    for (int i = 0; i < numPlayers; i++) { //playerID's starts from 0 to numberofplayers-1
        remainingPlayers.push_back(i);

    }  // first I pushed all players into vector

    mtx.lock();
    while (numPlayers > 1) {

        myQueue = IntQueueHW6(numPlayers-1);  // size with number of players-1

        for(int i=0; i<numPlayers-1; i++){
            if(!myQueue.isFull()){
                myQueue.enqueue(remainingPlayers[i]);    //players try to get a chair in the Queue
                mtx.unlock();
            }

        }

        time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
        struct tm *ptm = localtime(&tt);
        coutMutex.lock();
        cout << "Time is now " << put_time(ptm, "%X") << endl;
        coutMutex.unlock();

        ptm->tm_sec+=2;  // 2 sec later

        for (int i = 0 ; i < numPlayers; i++) {  //create the threads

            playerThreads[i] = thread(playerThread, remainingPlayers[i],ptm);

        }


        for (int i = 0; i < numPlayers; i++) { // join the threads

            playerThreads[i].join();

        }

        numPlayers--;  // after every round one player eliminated

        cout << "Remaining players are as follows: ";
        for(int i=0; i<captured.size(); i++){
            coutMutex.lock();
            cout << captured[i] << " ";

            coutMutex.unlock();
        }
        remainingPlayers.clear();  // should reset here to take new remaining players from captured vector

        for(int j=0; j<captured.size(); j++) {
            remainingPlayers.push_back(captured[j]);  //remaining players became a players who captured chair in this round with that order
        }

        cout << endl << endl;

        if(numPlayers == 1){  // when there is 1 player left, game ends and there is a winner.
            cout << "Game over!" << endl;
            cout << "Winner is Player " << captured[0] << "!";  // only 1 player capture in the last round at it's the winner.
        }

        captured.clear();  // should reset after all rounds

    }

}


int main() {
    int number_of_players;
    cout << "Welcome to Musical Chairs game!" << endl;
    cout <<  "Enter the number of players in the game:" << endl;
    cin >> number_of_players;  // >= 2
    cout <<  "Game Start!" << endl << endl;
    playGame(number_of_players);


    return 0;
}