/*
blockIndex.cpp
*/
#include "blockIndex.h"

using namespace std;


int blockIndex::search(int zip){
	
	int tempRBN;
	bool found = false;
	if (index.size() == 0)
		return -1;
	int tempZip;

	for (int i = 0; i < index.size(); i++) {
		if(found){
			if (index[i].zip >= zip && index[i].zip < tempZip) {
				tempRBN = index[i].RBN;
				tempZip = index[i].zip;
			}
		}

		else
			if (index[i].zip > zip){
				tempRBN = index[i].RBN;
				tempZip = index[i].zip;
				found = true;
			}
	}

	return tempRBN;
}



void blockIndex::add(int z, int r){
	indexElement temp;
	temp.zip = z;
	temp.RBN = r;

	index.push_back(temp);
}


void blockIndex::del(int r){
	for(int i = 0; i < index.size(); i++){
		if(index[i].RBN == r){
			index.erase(index.begin() + i);
			break;
		}
	}
}