//
// main2.cpp
// CSE 100 Project 1
//
// Last modified by Heitor Schueroff on 01/10/2019
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>

#include "KDT.hpp"

using namespace std;

/*
 * IMPORTANT!! YOU MUST FORMAT PROMPTS AND OUTPUTS AS FOLLOWS: 
 *
 *      To output size of tree: 
 *          cout << "Size of tree: " << size << "\n"; 
 *
 *      To output height of tree: 
 *          cout << "Height of tree: " << height << "\n"; 
 *
 *      To prompt the user to enter a coordinate: 
 *          cout << "Enter coordinate (x y): " << "\n";
 *
 *      To output the result of the nearest neighbor search: 
 *          cout << "Nearest point in tree: " << nearestNeighbor << "\n"; 
 *
 *      To prompt the user to try again: 
 *          cout << "Search again? (y/n)" << "\n";
 *
 * Use cin to process user input.
 *
 * You MUST output size, then height, then prompt the user to search, as above.
 *
 * You MUST have the prompt for entering the name appear if and only if
 * the user input for trying again is "y" followed by the return key
 *
 * You MUST have the program exit (exiting the prompt loop) if and only if
 * the user input for trying again is "n" followed by the return key
 *
 * You should handle other inputs for the retry prompt,
 * but we will not be testing them.
 *
 * Note that size, height, and nearestNeighbor are local variables in main that
 * you should update accordingly.
 */

int main(int argc, char *argv[]) {
    // Check for Arguments
    if (argc != 2) {
        cout << "Invalid number of arguments.\n"
            << "Usage: ./main <input filename>.\n";
        return -1;
    }

    // Open file
    ifstream in;
    in.open(argv[1], ios::binary);

    // Check if input file was actually opened
    if (!in.is_open()) {
        cout << "Invalid input file. No file was opened. Please try again.\n";
        return -1;
    }

    // Check for empty file
    in.seekg(0, ios_base::end);
    unsigned int len = in.tellg();
    if (len == 0) {
        cout << "The file is empty. \n";
        return -1;
    }

    // Resets the stream to beginning of file
    // Initializes a new vector with Point type
    // creates string that will help us store whats read from txt file
    in.seekg(0, ios_base::beg);
    vector<Point> list;           
    std::string line;
    //std::string x , y , s  ;
    int size = 0;

     //inserting points to  vector,  a  little schetchy  IMO...
    while  (getline(in, line) ) {
	std::size_t s = line.find(" ");
	string xstr = line.substr(0,s);
	string ystr = line.substr(s);
	double x = stod(xstr);
	double y = stod(ystr);
	Point* n = new Point(x,y);
	list.push_back(*n);
	size = size + 1;
	}
    
    //valcout << "size of tree:  "   << list.size() <<  "\n";
    //
    //create  a  KDT
    //BST<Point> tree;
    //int treesize  =  tree.build(list);
	KDT tree;
	int treesize = tree.build(list);
	cout << "size of tree:  "  <<treesize   << "\n";

	cout << "Height of tree: " << tree.height() << "\n";

    string qpoint = "";
    char response = 'y';

    // Prompt user for an actor name
    while (response == 'y') {
        cout << "Enter coordinate (x y): " << "\n";
        getline(cin, qpoint);

	std::size_t s1 = qpoint.find(" ");
	string xstr1 = qpoint.substr(0,s1);
	string ystr1 = qpoint.substr(s1);
	double x1 = stod(xstr1);
	double y1 = stod(ystr1);
	Point* n1 = new Point(x1,y1);

        BST<Point>::iterator item = tree.findNearestNeighbor(*n1);
	//printout of the point provided
	//cout << "Point entered: " << n1->x << ", " << n1->y << "\n";
	//printout of the nearest node in tree
	cout << "Nearest point in the tree: "  << *item <<"\n";	

        cout << "Search again? (y/n)" << "\n";
        cin >> response;
        cin.ignore();

        if (response != 'n' && response != 'y') {
            cout << "Invalid response, exiting..." << endl;
            break;
        }
    }


    if (in.is_open()) {
        in.close();
    }

    return 0;
}
