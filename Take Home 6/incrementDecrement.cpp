/* This program creates 4 threads, 2 of which increment a global variable by a random value between 1-5, the other 2 decrement it by some random numbers between 1-5. 
Each of the 4 threads is executed 5 times before it has completed its work. To make sure that the global variable is accessed and updated by exactly 1 thread at a time, we use a mutex.
*/
#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <random>
#include <time.h>

using namespace std;

// Global variables
mutex fMutex;
// Variable that will be decremented/incremented
int globalCount;
// Number of threads used for decrementing
const int DECREMENT_THREADS = 2;
// Number of threads used for incrementing
const int INCREMENT_THREADS = 2;

// Total number of iterations for each thread - i-th counter corresponds to i-th thread
int iterations[INCREMENT_THREADS + DECREMENT_THREADS] = {5, 5, 5, 5};

// Generate random numbers in a thread-safe manner in the range  (min, max).
int random_range(const int & min, const int & max) {
    static mt19937 generator(time(0));
    uniform_int_distribution<int> distribution(min,max);
    return distribution(generator);
}

// Increment global variable by random value between (and including) 1-5
void increment(int threadIdx)
{
    // Number of iterations performed by this thread so far
    int iteration = 0;
    while (iteration < (iterations[threadIdx]))
    {
        // Let thread sleep for 2s
        this_thread::sleep_for(chrono::milliseconds(100));

        // Critical region that can only be accessed by 1 thread at a time. That means 1 thread can only access the variable globalCount at a time.
        // If you comment out fMutex.Lock() and fMutex.unlock(), the output might be scrambled (and increment/decrement might yield incorrect results)
        fMutex.lock();
        int incremented = random_range(1, 5);
        globalCount += incremented;
        cout << "Increment thread " << threadIdx << ": variable was incremented by " << incremented << " updated value: " << globalCount << endl;
        iteration++;
        fMutex.unlock();
    }
}

// Decrement global variable by random value between (and including) 1-5
void decrement(int threadIdx)
{
    // Number of iterations performed by this thread so far
    int iteration = 0;
    while (iteration < (iterations[threadIdx]))
    {
        // Let thread sleep for 1s
        this_thread::sleep_for(chrono::milliseconds(100));

        // Critical region that can only be accessed by 1 thread at a time. That means 1 thread can only access the variable globalCount at a time.
        // If you comment out fMutex.Lock() and fMutex.unlock(), the output might be scrambled (and increment/decrement might yield incorrect results)
        fMutex.lock();
        int decremented = random_range(1, 5);
        globalCount -= decremented;
        cout << "Decrement thread " << threadIdx << ": variable was decremented by " << decremented << " updated value: " << globalCount << endl;
        iteration++;
        fMutex.unlock();
    }
}

int main ()
{
    // First come increment threads, then decrement threads, so we store [incrementThread1, incrementThread2, decrementThread1, decrementThread2]
    thread all[INCREMENT_THREADS + DECREMENT_THREADS];
    // Start all threads
    for (int i = 0; i < (INCREMENT_THREADS + DECREMENT_THREADS); i++)
    {
        // We deal with an increment thread if i < 2
        if (i < INCREMENT_THREADS)
        {
            all[i] = thread(&increment, i);
        }
        else
        {
            all[i] = thread(&decrement, i);
        }
    }
    // wait for all threads to finish before main exits
    for (int i = 0; i < (INCREMENT_THREADS + DECREMENT_THREADS); i++)
    {
        all[i].join();
    }

    return 0;
}