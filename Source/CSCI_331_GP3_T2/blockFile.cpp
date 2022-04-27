

#include "blockFile.h"

blockFile::blockFile(string index = "IndexFile.index", string data = "DataFile.licsv") {
	liToBlock(index, data); // dtatata


}

void blockFile::liToBlock(string index, string liData) {

	recBuf recParser; // parse LI records onto zip object 
	zip z;
	blockBuf b;
	ifstream ind; 
	ind.open(index);
	ifstream lid;
	lid.open(liData);


	oData.open("DataFile.bli");

	int size;
	string s;
	char character;
	for (int i = 0; i < 3; ++i) {
		getline(lid, s); // skipping header. How many lines? ..
	}
	s = "";

	while(!lid.eof()) {
		size = atoi(get(lid)) * 10;
		size += atoi(get(lid));
		for (int i = 0; i < size; ++i) {
			lid >> character;
			s.push_back(character);
		}
		recParser.read(s);
		recParser.unpack(z);
		++recCount;
		addRecord(z, b);

		s = "";
	} 

}

void blockFile::addRecord(zip& z, blockBuf &b) {
	int rbn = index.search(z.getNum())
	if (rbn == 0) {
		rbn = index.findHighest();
		if (rbn == 0) {
			block first;
			first.addRecord(z);
			first.prev = 0;
			first.next = 0;
			index.add(first, 1);
		}
		else{

		}
	}
	else {
		
	}
}
///asdfasdfasdfasdfakljnsdfasdjf; fsadfasdfasfdasdfasdfasdfasdfasdfoja; asodfi; lfija; sodfjia; sldfij; akls j  as; dfj; djf; alskdjf; alksjdf;/ alksjdfsaodsd ofij   oas dj


void blockFile::readHeader() {

	string temp;
	data.seekg(0);

	for (int i = 0; i < 512; i++) {
		temp.push_back(data.get());
	}



}


void blockFile::writeHeader() {

	string header;

	//File Structure Type
	header.append("File Structure Type: Blocked sequence set with comma separated fields, and length-indicated records\n");

	//File Version
	header.append("Version: 1.0\n");

	//header record size
	header.append("Header Size: 512 bytes\n");

	//Size Format
	header.append("Format: ASCII\n");

	//Block size
	header.append("Block Size: 512 bytes\n");

	//Minimum block capacity
	header.append("Min Block Capacity: 256 bytes\n");

	//Index File Name
	header.append("Index File: TBD\n");

	//Index File Schema
	header.append("File Schema: Highest zip code and RBN\n");

	//record count
	header.append("Record Count: ");
	header.append(recCount);
	header.push_back("\n");

	//block count
	header.append("Block Count: ");
	header.append(numBlock);
	header.push_back("\n");

	//Fields per record
	header.append("Fields: 6\n");

	//Fields
	header.append("ZipCode, Place Name, State, County, Lat, Long\n")
	
	//Type Schema
	header.append("Type Schema: Zip Code is an integer. Lon and Lat are floating point decimals. County, State Code, and City are strings.\n");

	//Primary key
	header.append("Zip code is the first key\n");

	//RBN link to avail list

	//RBN link to active list

	//Stale flag

}

void blockFile::dump()
{
	

}

bool blockFile::split(block& b)
{
	if (b.getActive()) {
		int tempi;
		block temp1, temp2;
		b.split(temp1);
		if (avail == 0){

			tempi = b.getNext();
			b.setNext(++numBlocks);

			buf.read(iData, b.getPrev());
			buf.unpack(temp2);
			buf.clear();

			temp1.setPrev(temp2.getNext());
			temp1.setNext(tempi);

			buf.pack(b);
			buf.write(oData, tempi);
			buf.clear();
			index.add(b.getHighestZip(), tempi);

			buf.pack(temp1);
			buf.write(oData, numBlocks);
			buf.clear();
			index.add(temp1.getHighestZip(), numBlocks);

			return true;
		}
		else{

			tempi = b.getNext();

			b.split(temp1);

			temp1.setNext(tempi);

			b.setNext(avail);

			buf.read(iData, avail);
			buf.unpack(temp2);
			buf.clear();

			avail = temp2.getNext();

			buf.read(iData, b.getPrev());
			buf.unpack(temp2);
			buf.clear();

			temp1.setPrev(temp2.getNext());

			buf.pack(b);
			buf.write(oData, temp2.getNext());
			buf.clear();

			buf.pack(temp1);
			buf.write(oData, b.getNext());
			buf.clear();

			return true;
		}

	}
	return false;
}
