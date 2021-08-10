/**************************
VGP310 Example code to count character frequencies in a string and create
a min priority queue of the code symbols with character and freq.
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

/******************
 Function to scan a string counting frequency of characters then putting them
 into a priority queue.  Returns the number of codesymbols discovered.
*******************/
unsigned int freqcount(string& str, priority_queue<Csym*, vector<Csym>, compare_Csym>& pq){
    unsigned int symcnt = 0;
    vector<unsigned int> freq(256, 0);

    // Loop scan the input string incrementing the count using the ASCII code
    // for the character as an address for the counter value.
    for(unsigned int i = 0; i < str.size(); i++){
        ++freq[(unsigned int)str[i]];
    }

    // Loop scans the vector of freq counts and pushes any non zero
    // into a priority queue using the ASCII char equal to the index.
    for(unsigned int i = 0; i < 255; i++){
        if(freq[i]>0){
            pq.push(Csym((char)i, freq[i]));
            ++symcnt;
        }
    }

    return symcnt;
}

/************
Main program body
*************/
int main()
{
    cout << "Test Frequncy Counting" << endl;

    // Instantiation of priority queue object.
    // Note that the vector parameter is required along with the compare operator
    priority_queue<Csym*, vector<Csym>, compare_Csym> pq;
    string str;
 //   vector<unsigned int> freq(256, 0);
    int symcnt = 0;

    cout << "Enter a string : ";
    cin >> str;

    cout << "String length = " << str.size() << endl;

    // Call function to scan string and create freq list in priority queue
    symcnt = freqcount(str, pq);

    cout << "Symbol count = " << symcnt << endl;
    // Print out queue contents which should be in ascending order
    while(pq.size() > 0){
        cout<<"char: " << pq.top().c << "    freq: " << pq.top().f << endl;
        pq.pop();
    }

    return 0;
}
