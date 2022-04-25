/*
*block.cpp
*/
#include "block.h"

block::block(){
	active = 0;
	recCount = 0;
	currentSize = 0; 
	highestZip = 0;
	prev = 0; 
	next = 0;
	records.clear();
}

block::block(const block& old){

	active = old.active;
	recCount = old.recCount;
	currentSize = old.currentSize;
	highestZip = old.highestZip;
	prev = old.prev;
	next = old.next;
	for (int i = 0; i < old.records.size(); i++)
		records[i] = old.records[i];

}

block::block(block& b1, block& b2) {

	if (b2.highestZip < b1.highestZip)
		swap(b1, b2);


	for (int i = 0; i < b1.records.size(); i++) {
		this->records[i] = b1.records[i];
	}
	int j = 0;
	for (int i = b1.records.size(); i < (b1.records.size() + b2.records.size()); i++) {
		this->records[i] = b2.records[j];
		j++;
	}

	active = true;
	this->recCount = b1.recCount + b2.recCount;
	this->currentSize = b1.currentSize + b2.currentSize;

}

bool block::addRecord(zip& newzip){

	int count = getSize(newzip);
	if (count + currentSize < 512) {
		currentSize += count;
		
		for(int i = 0; i < records.size(); i++){
			if (newzip.getNum() > records[i].getNum()) {
				records.insert(records.begin() + i, newzip);
			}
		}
		recCount++;
		findHighestZip();
		return true;
	}
	else
		return false;

}

bool block::delRecord(int zip){

	for(int i = 0; i < recCount; i++){
		if(records[i].getNum() == zip){
			records.erase(records.begin() + i);
			int count = getSize(records[i]);
			recCount--;
			currentSize -= count;
			findHighestZip();
			if (currentSize == 0)
				active = false;
			return true;
		}
	}

	return false;
}

int block::findHighestZip(){

	for (int i = 0; i < records.size(); i++) {
		if (highestZip < records[i].getNum())
			highestZip = records[i].getNum();
	}
}

int block::getSize(zip zipper){

	int count = 0;
	count += to_string(zipper.getNum()).size();
	count += (zipper.getCity()).size();
	count += (zipper.getStateCode()).size();
	count += (zipper.getCounty()).size();
	count += to_string(zipper.getLat()).size();
	count += to_string(zipper.getLon()).size();

	return count;
}

bool block::getZip(zip& rtn, int target){
	for(int i = 0; i < records.size(); i++){
		if(records[i].getNum() == target){
			rtn.setNum(records[i].getNum());
			rtn.setCity(records[i].getCity());
			rtn.setStateCode(records[i].getStateCode());
			rtn.setCounty(records[i].getCount());
			rtn.setLon(records[i].getLon());
			rtn.setLat(records[i].getLat());
			return true;
		}
	}
	return false;
}
