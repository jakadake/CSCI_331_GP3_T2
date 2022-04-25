/**
* blockIndex.h 
* Class containing the block index for the highest zip in each block
* 
*/
#pragma once

#include <vector>
#include "block.h"

using namespace std;

struct indexElement {
	int zip;
	int RBN;
};

class blockIndex {
public:
	/*
	* @brief default constructor
	* @pre
	* @post
	*/
	blockIndex() { index.clear(); }


	/*
	* @brief search function
	* @pre Takes an integer ZIP to search through the index 
	* @post Returns the block number that would contain this zip
	*/
	int search(int zip); 

	/*
	* @brief add function
	* @pre adds the first parameter as a zip and second as a RBN onto the back of the index
	* @post returns void
	*/
	void add(int z, int r); 
	
	/*
	* @brief delete function
	* @pre takes a block number to delete from the index  
	* @post returns void 
	*/
	void del(int r); 

private:

	vector<indexElement> index;


};