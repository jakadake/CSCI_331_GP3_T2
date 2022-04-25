//BlockBuf.h
#pragma once

#ifndef BLOCKBUF
#define BLOCKBUF

#include <string>
#include "zip.h"
#include "recBuf.h"
#include "blockFile.h" 
#include "block.h"
#include <vector>
#include <iostream>

using namespace std;

const int SIZE = 512;


class blockBuf {
public:
	/*
	* @brief
	* @pre
	* @post
	*/
	blockBuf();


	/*
	* @brief
	* @pre
	* @post
	*/
	void read(fstream& infile, int RBN);

	/*
	* @brief translates block object into text
	* @pre
	* @post
	*/
	void pack(const block& b);

	/*
	* @brief writes blocktext to the file at the indicated RBN
	* @pre
	* @post
	*/
	void write(fstream& outfile, int RBN);

	/*
	* @brief translates text into a block object
	* @pre
	* @post
	*/
	void unpack(block& b);

private:


	string blockText;
	block obj;
	int index;

};
#endif
