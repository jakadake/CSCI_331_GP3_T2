/*
* BlockBuf.cpp
*/

#include "blockBuf.h"
#include "recBuf.h"


void blockBuf::read(fstream& inFile, int RBN) {
	
	int index = 0;
	inFile.seekg(RBN*512);
	while(!inFile.eof() && index != 512){
		blockText.push_back(inFile.get());
		index++;
	}
}

void blockBuf::pack(const block &b ){

}


void blockBuf::write(fstream& outfile, int RBN){
	for (int i = 0; i < blockText.size(); i++) {
		outfile << blockText[i];
	}
}


void blockBuf::unpack(block& b) {
	recBuf rec;
	int prev, next, recCount, currentSize, highestZip;

	
}