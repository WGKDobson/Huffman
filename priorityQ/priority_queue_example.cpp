/**************************
VGP310 Example code to implement a min priority queue
W. Dobson   1-19-2018

This queue structure automatically sorts the Csym elements
in ascending order (least first)
*************************/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Code symbol data structure (or node)
struct Csym{
    Csym(char a, unsigned int b):c(a), f(b)  {}

    char c;
    unsigned int f;
};

// Comparator boolean operator for use by the priority queue
struct compare_Csym{
    bool operator() (const Csym& a, const Csym& b) const
        { return a.f > b.f ; }  // Note the > forces ascending order
};



int main()
{
    cout << "Test Priority Queue" << endl;

    // Instantiation of priority queue object.
    // Note that the vector parameter is required along with the compare operator
    priority_queue<Csym*, vector<Csym>, compare_Csym> pq;

    // push some random data in the queue
    pq.push(Csym('a', 10));
    pq.push(Csym('b', 2));
    pq.push(Csym('c', 3));
    pq.push(Csym('e', 18));

    // Print out queue contents which should be in ascending order
    while(pq.size() > 0){
        cout<<"char: " << pq.top().c << " " << pq.top().f << endl;
        pq.pop();

    }

    return 0;
}
