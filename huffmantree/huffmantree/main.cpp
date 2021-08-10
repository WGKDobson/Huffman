/**************************
VGP310 Example code to build a Huffman tree from character frequencies
in min priority queue of the code symbols with character and freq.
W. Dobson   1-20-2018

This queue structure automatically sorts the Csym elements
in ascending order (least first)
*************************/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Code symbol data structure (or node)
struct Csym{
//    Csym(char a, unsigned int b):c(a), f(b)  {}

    char c;
    unsigned int f;
    Csym *left, *right;

    // overloaded initialize function for this structure
    Csym(char c, unsigned f){
        left = NULL;
        right = NULL;
        this->c = c;
        this->f = f;
    }
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
unsigned freqcount(string& str, priority_queue<Csym*, vector<Csym>, compare_Csym>& pq){
    unsigned symcnt = 0;
    vector<unsigned> freq(256, 0);

    // Loop scan the input string incrementing the count using the ASCII code
    // for the character as an address for the counter value.
    for(unsigned i = 0; i < str.size(); i++){
        ++freq[(unsigned)str[i]];
    }

    // Loop scans the vector of freq counts and pushes any non zero
    // into a priority queue using the ASCII char equal to the index.
    for(unsigned i = 0; i < 255; i++){
        if(freq[i]>0){
            pq.push(Csym((char)i, freq[i]));
            ++symcnt;
        }
    }

    return symcnt;
}

/************
Function to build a Huffman coding tree
*************/
Csym *huffmantree(priority_queue<Csym*, vector<Csym>, compare_Csym>& pq){
    Csym *left, *right, *top;

    while(pq.size()>1){
        left = new Csym(0xff, 0);
        right = new Csym(0xff, 0);

        *left = pq.top();  // grab next two lowest freq nodes
        pq.pop();
        *right = pq.top();
        pq.pop();

        // Create new parent node with freq being the sum
        // of the two child node freqs. We use the hex 0xff
        // for all non leaf nodes.
        top = new Csym((char)255, left->f+right->f);
        top->left = left;
        top->right = right;
        //cout<<"debug:"<< top->left << " " << top->right << " f=" << top->f << "  c=0xff" << endl;
        // Push the new node into the queue and the process repeats
        // with one fewer nodes in the queue each time.
        pq.push(*top);
    }

    return top;  // returns last top node which is the root of the tree
}

void printtree(Csym *root, string str){
    if(!root)
        return;
    //cout << hex << (short)root->c <<endl;
    if((unsigned)root->c < 255){
        cout << root->c << ": " << str << endl;
    }

    printtree(root->left, str+"0");
    printtree(root->right, str+"1");
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
    priority_queue<Csym*, vector<Csym>, compare_Csym> pq2;
    Csym *root;
    Csym temp(0, 0);
    string str, bstr;
    unsigned symcnt = 0;

    cout << "Enter a string : ";
    cin >> str;

    cout << "String length = " << str.size() << endl;

    // Call function to scan string and create freq list in priority queue
    symcnt = freqcount(str, pq);

    cout << "Symbol count = " << symcnt << endl;
    // Print out queue contents which should be in ascending order
    while(pq.size() > 0){
        cout<<"char: " << pq.top().c << "    freq: " << pq.top().f << endl;
        temp = pq.top();
        pq.pop();
        pq2.push(temp);
    }

cout<<"huffmantree"<<endl;
    root = huffmantree(pq2);
cout<<"printtree cnt = "<<root->f <<endl;
    printtree(root, bstr);

    return 0;
}
