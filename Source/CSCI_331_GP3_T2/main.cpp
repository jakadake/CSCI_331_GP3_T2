/**
Main program 
@brief reads zip codes in from a csv file, then prints a table organized by state with most east, west, north, and south zips
@author Jake Haapoja, Ken Stearns, Nathan O'Connor, Zach Sawicki
*/



#include "primaryindex.h"
#include "delimBuffer.h"
#include "LIBuffer.h"
#include "zip.h"
#include <vector>
#include <iostream>
using namespace std;



const string manual =
"sample input: programname -r filename.csv\noptions: \n-r <filename.csv>\n-z <zip code> \nprogram must be run once with a csv file to generate the datafile and index";


/*
* @brief main function that takes command line arguments
* @param argument count, string of arguments
*/

int main(int argc, char* argv[]) {
	
	fstream iFile, dFile;
	ifstream inFile;	// filestream objects
	string filename;
	int queryZip;
	unsigned long offset = 0;
	LIBuffer indicated;
	string arg1, arg2;

	for (int i = 0; i < argc; i++) {
		cout << argv[i] << ' ';
	}

	if (argc != 3) {
		cout << "Invalid Input" << endl << manual;
		return -1;
	}

	arg1 = argv[1];
	arg2 = argv[2];


	if (arg1 == "-r") {	// read file into memory

		char response;
		int zipResponse;

		filename = argv[2];
		inFile.open(filename); // access the data file and associate to filestream object

		primaryIndex indexList(inFile);

		iFile.open("IndexFile.index");
		dFile.open("DataFile.licsv");

		cout << "file imported successfully\n";
		cout << "do you want to search the database? (Y/N): ";
		cin >> response;
		if (tolower(response) == 'y') {
			cout << "\nPlease enter a valid zip: ";
			cin >> zipResponse;

			offset = indexList.search(zipResponse);
			if (offset == 0) { cout << "Sorry! We can't seem to find that one."; return -2; }
			indicated.read(dFile, offset);
			for (int i = 0; i < 6; i++) {
				string temp = "";
				switch(i) {
				case 0:
					cout << "\nZip Code: ";
					indicated.unpack(temp);
					cout << temp;
					break;
				case 1: 
					cout << " Place Name: ";
					indicated.unpack(temp);
					cout << temp;
					break;
				case 2:
					cout << " State: ";
					indicated.unpack(temp);
					cout << temp;
					break;
				case 3:
					cout << " County: ";
					indicated.unpack(temp);
					cout << temp;
					break;
				case 4:
					cout << " Lat: ";
					indicated.unpack(temp);
					cout << temp;
					break;
				default:
					cout << " Long: ";
					indicated.unpack(temp);
					cout << temp;
					break;
				}
			}
		}

		return 1;
	}
	else if (arg1 == "-z") {	// search for zip
	
		
		primaryIndex indexList("IndexFile.index", "DataFile.licsv");
		queryZip = stoi(arg2);
		offset = indexList.search(queryZip);
		if (offset == 0) { cout << "Sorry! We can't seem to find that one.\n"; return -2; }

		dFile.open("DataFile.licsv");
		indicated.read(dFile, offset);
		dFile.close();

		for (int i = 0; i < 6; i++) {
			string temp = "";
			switch(i) {
			case 0:
				cout << "Zip Code: ";
				indicated.unpack(temp);
				cout << temp;
				break;
			case 1: 
				cout << " Place Name: ";
				indicated.unpack(temp);
				cout << temp;
				break;
			case 2:
				cout << " State: ";
				indicated.unpack(temp);
				cout << temp;
				break;
			case 3:
				cout << " County: ";
				indicated.unpack(temp);
				cout << temp;
				break;
			case 4:
				cout << " Lat: ";
				indicated.unpack(temp);
				cout << temp;
				break;
			default:
				cout << " Long: ";
				indicated.unpack(temp);
				cout << temp;
				break;
			}
		}
	}
	else {	// invalid arguments 

		cout << "invalid arguments";
		return -1;
	}
	

	cout << endl << "Hello World!" << endl;

	dFile.close();  // definitely nothing to see here
	iFile.close();
	inFile.close();

	return 1;
}
