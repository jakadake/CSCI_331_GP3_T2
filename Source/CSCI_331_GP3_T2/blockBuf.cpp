/*
* BlockBuf.cpp
*/

#include "blockBuf.h"


void blockBuf::read(ifstream& inFile, int RBN) {
	
	int index = 0;
	inFile.seekg(RBN*BUFSIZE);
	while(!inFile.eof() && index != BUFSIZE) {
		blockText.push_back(inFile.get());
		index++;
	}
}

void blockBuf::pack(block &b){

	recBuf rec;
	vector<zip> records;

	// store block attributes as ascii
	blockText.append(to_string(b.getPrev()));
	blockText.append(to_string(b.getNext()));
	blockText.append(to_string(b.getRecCount()));
	blockText.append(to_string(b.getCurrentSize()));
	blockText.append(to_string(b.getHighestZip()));

	//Store records
	b.getRecords(records);
	for(int i = 0; i < records.size(); i++){
		rec.pack(records[i]);
		rec.write(blockText);
	}

}


void blockBuf::write(ofstream& outfile, int RBN){
	for (int i = 0; i < blockText.size(); i++) {
		outfile << blockText[i];
	}
	outfile.flush();
}


void blockBuf::unpack(block& b) {

	readHeader(b);

	zip tempZip;
	string temp;
	recBuf rec;
	int recSize;
	int count = 0;

	while (index != blockText.size()) {
		temp = blockText[index++];
		temp.push_back(blockText[index++]);
		recSize = stoi(temp);
		while (index != blockText.size() && count != recSize) {
			temp.push_back(blockText[index++]);
			count++;
		}
		rec.read(temp);
		rec.unpack(tempZip);

		b.addRecord(tempZip);

	}
}


void blockBuf::readHeader(block& b)
{
	index = 0;
	string temp;

	temp = blockText[index++];
	temp.push_back(blockText[index++]);

	b.setPrev(stoi(temp));

	temp = blockText[index++];
	temp.push_back(blockText[index++]);

	b.setNext(stoi(temp));

	temp = blockText[index++];
	temp.push_back(blockText[index++]);

	b.setRecCount(stoi(temp));

	temp = blockText[index++];
	temp.push_back(blockText[index++]);

	b.setCurrentSize(blockText[index++]);

	temp = blockText[index++];
	temp.push_back(blockText[index++]);

	b.setHighestZip(stoi(temp));
	
	index++;
}
