#pragma once


#include "blockBuf.h"
#include "recBuf.h"
#include "zip.h"
#include "block.h"
#include "blockIndex.h"

const int SIZE = 512;

class blockFile {
public:

	/*
	* @brief specified constructor
	* @pre takes a string as parameter
	* @post opens file specified by parameter
	*/
	blockFile(string bFile);
	
	blockFile(string index = "IndexFile.index", string data = "DataFile.licsv");

	/*
	* @brief length indicated to block function
	* @pre
	* @post
	*/
	void liToBlock();


	/**
	* @brief opens the file indicated by filename
	* @pre
	* @post
	*/
	void open(string filename) { data.open(filename); };

	/**
	* @brief
	* @pre
	* @post
	*/
	void close() { data.close(); };

	/*
	* @brief read header function
	* @pre
	* @post
	*/
	void readHeader();

	/*
	* @brief write header function
	* @pre 
	* @post
	*/
	void writeHeader();

private:


	int first, avail, numBlocks, recCount;

	fstream data;
	blockBuf buf;
	blockIndex index;

};