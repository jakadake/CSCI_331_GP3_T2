#pragma once


#include "blockBuf.h"
#include "recBuf.h"
#include "zip.h"

const int SIZE = 512;

class block {
public:

	void addRecord(zip newZip);

private:
	bool active;
	int recCount, currentSize, highestZip;
	block* prev, * next;
	vector<zip> records;

};

class BlockFile {

	blockBuf buf;
	vector<int> recordZip;
	
	
public:
	void addRecord(int zip);
}