/*
*block.cpp
*/
#include "block.h"
#include "blockBuf.h"

block::block(){
	active = 0;
	recCount = 0;
	currentSize = 20; 
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
	this->prev = b1.prev;
	this->next = b2.next;
}

bool block::addRecord(zip& newzip){

	int count = getSize(newzip);
	if (count + currentSize + 2 < 512) {
		currentSize += (count + 2);
		
		for(int i = 0; i <= records.size(); i++){
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

void block::split(block& newBlock){
	
	int change = 0;
	int start = (records.size() / 2);

	for(int i = start; i < records.size(); i++){
		newBlock.addRecord(records(i));
		change++;
	}

	for(int j = 0; j < change; j++){
		delRecord(records(start).getNum());
	}

	findHighestZip();
	newBlock.findHighestZip();
}

bool block::delRecord(int zip){

	for(int i = 0; i < recCount; i++){
		if(records[i].getNum() == zip){
			records.erase(records.begin() + i);
			int count = getSize(records[i]);
			recCount--;
			currentSize -= (count + 2);
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

void block::getRecords(vector<zip>& rtn){
	for (int i = 0; i < records.size(); i++) {
		rtn[i] = records[i];
	}
}

bool block::getZip(zip& rtn, int target){
	for(int i = 0; i < records.size(); i++){
		if(records[i].getNum() == target){
			rtn.setNum(records[i].getNum());
			rtn.setCity(records[i].getCity());
			rtn.setStateCode(records[i].getStateCode());
			rtn.setCounty(records[i].getCounty());
			rtn.setLon(records[i].getLon());
			rtn.setLat(records[i].getLat());
			return true;
		}
	}
	return false;
}

string block::ldump() {

	recBuf rec;
	string temp = "", rtn = "";

	rtn.append("active? ");
	if (active)
		rtn.append("TRUE\n");
	else
		rtn.append("FALSE\n");

	rtn.append("Previous Block Number: ");
	rtn.append(to_string(prev));
	rtn.push_back('\n');

	rtn.append("Next Block Number: ");
	rtn.append(to_string(next));
	rtn.push_back('\n');

	rtn.append("Highest Zip: ");
	rtn.append(to_string(highestZip));
	rtn.push_back('\n');

	rtn.append("Record Count: ");
	rtn.append(to_string(recCount));
	rtn.push_back('\n');

	rtn.append("Current Size: ");
	rtn.append(to_string(currentSize));
	rtn.push_back('\n');

	for (int i = 0; i < records.size(); i++) {
		rec.pack(records[i]);
		rec.write(temp);
		rtn.append(temp);
		rec.clear();
		temp = "";
	}
	return rtn;
}

string block::pdump() {blockBuf b; b.pack(*this); return b.getText();}