#pragma once


#include "blockBuf.h"
#include "recBuf.h"
#include "zip.h"
#include "block.h"
#include "blockIndex.h"
#include "LIBuffer.h"
#include "primaryindex.h"

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
	void liToBlock(string index, string lidata);


	/**
	* @brief opens the file indicated by filename
	* @pre
	* @post
	*/
	void open(string filename) { iData.open(filename); oData.open(filename);};

	/**
	* @brief
	* @pre
	* @post
	*/
	void close() { iData.close(); oData.close(); };

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

	/**
	* @brief physical dump function
	* @pre
	* @post
	*/
	void dump();

	/**
	* @brief
	* @pre
	* @post
	*/
	bool split(block& b);

	/**
	* @brief
	* @pre
	* @post
	*/
	void addRecord(zip& z, blockBuf &b);

private:


	int first, avail, numBlocks, recCount;

	//istream in;
	ofstream oData;
	ifstream iData;
	blockBuf buf;
	blockIndex index;
};