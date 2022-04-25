#pragma once


#include "zip.h"
#include <string>
#include <vector>
using namespace std;


#ifndef BLOCK
#define BLOCK



class block {
public:
	/*
	* @brief Default, copy and merge constructors for the block. 
	* @pre Requires instances of the block class to be copied or merged. 
	* @post Creates a new block.
	*/
	block();
	block(const block& old);
	block(block&, block&);

	/*
	* @brief adds a new record onto the existing block.
	* @pre Requires that the block not be over bytes. 
	* @post A record is added onto an existing block. Returns true if deleted or false if it failed. 
	*/
	bool addRecord(zip& newZip);

	/*
	* @brief Deletes a record from the block. 
	* @pre Requires a valid zip code to be removed from the block.  
	* @post Removes a record from the block and decreases the block size. Returns true if deleted or false if it failsed. 
	*/
	bool delRecord(int zip);

	/*
	* @brief Gives the next block in the list. 
	* @post Returns the next block index.
	*/
	int getNext() { return next; };

	/*
	* @brief Gives the previous block in the list. 
	* @post Returns the previous block index.
	*/
	int getPrev() { return prev; };

	/*
	* @brief searches the block for a zip and returns the record
	* @pre
	* @post
	*/
	bool getZip(zip& rtn, int target);

	void setNext(int next) { this->next = next; };

	void setPrev(int prev) { this->prev = prev; };

	void setRecCount(int recCount) { this->recCount = recCount; };

	void setCurrentSize(int currentSize) { this->currentSize = currentSize; };

	void setHighestZip(int next) { this->highestZip = highestZip; };


private:

	/*
	* @brief Sets the highest zip for a block.
	* @pre Requires that the block is not empty. 
	*/
	int findHighestZip();

	/*
	* @brief Gives the size of a zip record.  
	* @pre Takes in a zip.
	* @post Returns the size of the zip object.
	*/
	int getSize(zip zipper);

	bool active;
	int recCount, currentSize, highestZip;
	int prev, next;
	
	vector<zip> records;
};

#endif