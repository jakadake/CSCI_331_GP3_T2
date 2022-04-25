

#include "blockFile.h"


blockFile::blockFile(string bFile){

	data.open(bFile);



}

blockFile::blockFile(string index = "IndexFile.index", string data = "DataFile.licsv") {



}

void blockFile::liToBlock() {



}

void blockFile::readHeader() {

	string temp;
	data.seekg(0);

	for (int i = 0; i < 512; i++) {
		temp.push_back(data.get());
	}



}


void blockFile::writeHeader() {



}