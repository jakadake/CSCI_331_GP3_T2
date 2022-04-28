

#include "blockFile.h"



blockFile::blockFile(string index = "IndexFile.index", string data = "DataFile.licsv") {
	liToBlock(index, data); // dtatata


}


void blockFile::liToBlock(string in, string liData) {

	recBuf recParser; // parse LI records onto zip object 
	LIBuffer libuf;
	zip z;
	primaryIndex pi(in, liData);

	vector<indexElement> ind;
	pi.getIndex(ind);

	fstream lid;
	lid.open(liData);

	oData.open("DataFile.bli");

	for (int i = 0; i < ind.size(); i++) {
		libuf.read(lid, ind[i].offset);
		recParser.read(libuf.getBuffer());
		recParser.unpack(z);
		addRecord(z);
	}
}

bool blockFile::delRecord(string zip){

	block temp;
	int rbn = index.search(zip);
	if (rbn == 0)
		return false;
	else{
		buf.read(oData, rbn);
		buf.pack(temp);
		if (temp.delRecord(zip))
			return true;
		else
			return false;

	}
}

bool blockFile::addRecord(zip& z) {

	block temp1, temp2;
	int rbn = index.search(z.getNum());

	if (rbn == 0) {
		rbn = index.findHighest();
		if (rbn == 0) {
			temp1.addRecord(z);
			temp1.setPrev(0);
			temp1.setNext(0);
			index.add(temp1, 1);

			buf.pack(temp1);
			buf.write(oData, 1);
			buf.clear();
			return true;
		}
		else {
			
			buf.read(iData, rbn);
			buf.unpack(temp1);
			buf.clear();
			if (!temp1.addRecord(z)) {
				split(temp1);
				addRecord(z);
			}
			else {
				buf.pack(temp1);
				buf.write(oData, rbn);
				buf.clear();
				return true;
			}
		}
	}
	else {
		buf.read(iData, rbn);
		buf.unpack(temp1);
		buf.clear();

		if (!temp1.addRecord(z)) {
			split(temp1);
			addRecord(z);
		}
		else {
			index.add(temp1, rbn);
			buf.pack(temp1);
			buf.write(oData, rbn);
			buf.clear();
			return true;
		}
	}
	return false;
}
///asdfasdfasdfasdfakljnsdfasdjf; fsadfasdfasfdasdfasdfasdfasdfasdfoja; asodfi; lfija; sodfjia; sldfij; akls j  as; dfj; djf; alskdjf; alksjdf;/ alksjdfsaodsd ofij   oas dj


void blockFile::readHeader() {

	string temp;
	iData.seekg(0);

	for (int i = 0; i < 512; i++) {
		temp.push_back(iData.get());
	}



}

string blockFile::writeHeader() {

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
	header.append(to_string(recCount));
	header.push_back('\n');

	//block count
	header.append("Block Count: ");
	header.append(to_string(numBlocks));
	header.push_back('\n');

	//Fields per record
	header.append("Fields: 6\n");

	//Fields
	header.append("ZipCode, Place Name, State, County, Lat, Long\n");
	
	//Type Schema
	header.append("Type Schema: Zip Code is an integer. Lon and Lat are floating point decimals. County, State Code, and City are strings.\n");

	//Primary key
	header.append("Zip code is the first key\n");

	//RBN link to avail list
	header.append("First Available Block: ");
	header.append(to_string(avail));
	header.push_back('\n');

	//RBN link to active list
	header.append("First Active Block: ");
	header.append(to_string(first)); //heerad
	header.push_back('\n');

	//Stale flag
	header.append("Stale: true");
	header.push_back('\n');

	return header;
}


void blockFile::dump() // physical dump??
{
	cout << "List Head: " << getFirst() << endl
		<< "Avail Head: " << getAvail() << endl;
	for (int i = 1; i <= numBlocks; ++i) {
		buf.read(iData, i);
		cout << i << ' ';
		if (buf.obj.getCurrentSize() == 0) {
			cout << "\t*Available"
		}
		else {
			for (int j = 0; j < buf.obj.getCurrentSize(); ++j) {
				cout << buf.obj.records[j] << ' ';
			}
		}

	}

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
