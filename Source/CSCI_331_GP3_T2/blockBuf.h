//BlockBuf.h
#pragma once

#ifndef BLOCKBUF
#define BLOCKBUF

#include <string>
#include "zip.h"
#include "recBuf.h"
#include <vector>
#include <iostream>

using namespace std;

const int SIZE = 512;


class blockNode {

	bool active;
	int recCount, currentSize;
	blockNode* prev, * next;
	vector<int> recordZip;
	
	void addRecord(int zip);
};

class blockBuf {
private:
	blockNode* firstActive;
	blockNode* firstAvail;

public:
	void read();
	void pack();
	void write();
	void unpack();
	void merge(blockNode *x, blockNode *y);
	void addBlock(int zip);
	void search(int target);
	void binSearch(int target, int l, int r);
	zip getZip(int target);

};
#endif
