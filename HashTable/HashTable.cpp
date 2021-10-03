//============================================================================
// Name        : HashTable.cpp
// Author      : John Watson
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <algorithm>
#include <climits>
#include <iostream>
#include <string> // atoi
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

const unsigned int DEFAULT_SIZE = 179;

// forward declarations
double strToDouble(string str, char ch);
void displayBid(Bid bid);
// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

//============================================================================
// Hash Table class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a hash table with chaining.
 */
class HashTable {

private:
   
    // Define structures to hold bids
    struct Node {
        Bid bid;
        unsigned int key;
        Node* next;

        // default constructor
        Node() {
            key = UINT_MAX;
            next = nullptr;
        }

        // initialize with a bid
        Node(Bid aBid) : Node() {
            bid = aBid;
        }

        // initialize with a bid and a key
        Node(Bid aBid, unsigned int aKey) : Node(aBid) {
            key = aKey;
        }
    };

    vector<Node> nodes;

    unsigned int tableSize = DEFAULT_SIZE;

    unsigned int hash(int key);

public:
    //static void displayBid(Bid bid);
    HashTable();
    HashTable(unsigned int);
    //void displayBid(Bid bid);
    virtual ~HashTable();
    void Insert(Bid bid);
    void PrintAll();
    void Remove(string bidId);
    Bid Search(string bidId);
};

/**
 * Default constructor
 */
HashTable::HashTable() {
    // FIXME (1): Initialize the structures used to hold bids

    // Initalize node structure by resizing tableSize
    nodes.resize(tableSize);
}

/**
 * Constructor for specifying size of the table
 * Use to improve efficiency of hashing algorithm
 * by reducing collisions without wasting memory.
 */
HashTable::HashTable(unsigned int size) {
    // invoke local tableSize to size with this->
    // resize nodes size
    nodes.resize(size);
}


/**
 * Destructor
 */
HashTable::~HashTable() {
    // FIXME (2): Implement logic to free storage when class is destroyed

    // erase nodes beginning
    nodes.erase(nodes.begin());
}

/**
 * Calculate the hash value of a given key.
 * Note that key is specifically defined as
 * unsigned int to prevent undefined results
 * of a negative list index.
 *
 * @param key The key to hash
 * @return The calculated hash
 */
unsigned int HashTable::hash(int key) {
    // FIXME (3): Implement logic to calculate a hash value
    // return key tableSize
    return key % tableSize;
}

/**
 * Insert a bid
 *
 * @param bid The bid to insert
 */
void HashTable::Insert(Bid bid) {
    // FIXME (5): Implement logic to insert a bid
    // create the key for the given bid
    // retrieve node using key
    // if no entry found for the key
        // assign this node to the key position
    // else if node is not used
         // assing old node key to UNIT_MAX, set to key, set old node to bid and old node next to null pointer
    // else find the next open node
            // add new newNode to end
   // FIXME (5): Implement logic to insert a bid

    unsigned key = hash(atoi(bid.bidId.c_str()));

    //get the particular node for search

    Node* previous = &(nodes.at(key));

    //check previous is nullptr then

    if (previous == nullptr)

    {

        //Create an object for HashNode class

        Node* next = new Node(bid, key);

        //call insert function through nodeObject

        nodes.insert(nodes.begin() + key, (*next));

    }

    //check previous is not equal to nullptr then

    else if (previous != nullptr)

    {

        // check previous->key is equal to

        // UINT_MAX

        if (previous->key == UINT_MAX)

        {

            //assign key to previous->key

            previous->key = key;

            //assign bid to previous->bidObject

            previous->bid = bid;

            //assign nullptr to previous->nextPtr

            previous->next = nullptr;

        }

        // check previous->key is NOT equal to

        // UINT_MAX

        else if (previous->key != UINT_MAX)

        {

            //Iterate the loop

            while (previous->next != nullptr)

            {

                //assign previous->nextPtr to previous

                previous = previous->next;

            }

        }

    }


}

/**
 * Print all bids
 */
void HashTable::PrintAll() {
    // FIXME (6): Implement logic to print all bids
    // for node begin to end iterate
    //   if key not equal to UINT_MAx
            // output key, bidID, title, amount and fund
            // node is equal to next iter
            // while node not equal to nullptr
               // output key, bidID, title, amount and fund
               // node is equal to next node
    unsigned int k = 0;

    //Iterate the loop

    while (k < nodes.size())

    {

        //call displayBid function

        displayBid(nodes[k].bid);

        //increment k by 1

        ++k;

    }

}

/**
 * Remove a bid
 *
 * @param bidId The bid id to search for
 */
void HashTable::Remove(string bidId) {
    // FIXME (7): Implement logic to remove a bid
    // set key equal to hash atoi bidID cstring
    // erase node begin and key
    unsigned keytoRemove = hash(atoi(bidId.c_str()));

    //call erase function with nodeObject

    nodes.erase(nodes.begin() + keytoRemove);
}


/**
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */
Bid HashTable::Search(string bidId) {

    // FIXME (8): Implement logic to search for and return a bid

    // create the key for the given bid
    // if entry found for the key
         //return node bid

    // if no entry found for the key
      // return bid
    // while node not equal to nullptr
        // if the current node matches, return it
        //node is equal to next node
    Bid bid;

    unsigned key = hash(atoi(bidId.c_str()));

    Node* hasObject = &(nodes.at(key));

    //check hasObject->bidObject.bidId.compare(bidId) is equal to 0

    //and hasObject->key != UINT_MAX and hasObject != nullptr

    if (hasObject->key != UINT_MAX && hasObject != nullptr

        && hasObject->bid.bidId.compare(bidId) == 0)

    {

        //return hasObject->bidObject

        return hasObject->bid;

    }

    //check hasObject is equal to nullptr or hasObject->key

    //is equal to UINT_MAX

    if (hasObject == nullptr || hasObject->key == UINT_MAX)

    {

        //return bidObject

        return bid;

    }

    //Iterate the loop

    while (hasObject != nullptr)

    {

        //check hasObject->bidObject.bidId.compare(bidId) is equal to 0 and

        //hasObject->key is not equal to UINT_MAX

        if (hasObject->bid.bidId.compare(bidId) == 0 && hasObject->key != UINT_MAX)

        {

            return hasObject->bid;

        }

        //assign hasObject->nextPtr to hasObject

        hasObject = hasObject->next;

    }

    //return bidObject



    return bid;
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
        << bid.fund << endl;
    return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, HashTable* hashTable) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            hashTable->Insert(bid);
        }
    }
    catch (csv::Error& e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98109";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
        bidKey = "98109";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a hash table to hold all the bids
    HashTable* bidTable{};

    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            bidTable = new HashTable();

            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bidTable);

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            
            bidTable->PrintAll();
            break;

        case 3:
            ticks = clock();

            bid = bidTable->Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            }
            else {
                cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 4:
            bidTable->Remove(bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}