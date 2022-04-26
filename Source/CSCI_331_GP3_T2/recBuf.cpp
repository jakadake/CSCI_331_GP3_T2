/*
* recBuf.cpp
*/

#include "recBuf.h"


void recBuf::pack(zip& z) {
	buf.append(to_string(z.getNum()));
	buf.push_back(',');
	buf.append(z.getCity());
	buf.push_back(',');
	buf.append(z.getStateCode());
	buf.push_back(',');
	buf.append(z.getCounty());
	buf.push_back(',');
	buf.append(to_string(z.getLat()));
	buf.push_back(',');
	buf.append(to_string(z.getLon())); // get long
}

void recBuf::read(const string& recText) {

	buf = recText;

}

void recBuf::write(string& blockText){
	blockText.append(buf);
	buf = "";
}

bool recBuf::unpack(zip& z) {
	
	string temp = buf[0];
	temp.push_back(buf[1]);
	int size = stoi(temp);
	temp = "";

	index = 0;

	int fieldNumber = 0;

	if (index != size && size != 0) { // execute only when buf is not empty
		for (int i = 0; i < size; i++) {
			if (buf[index] == delim)
				i++;
			temp.push_back(buf[index]);
			if (buf[index + 1] == delim || buf[index + 1] == '\n') {
				switch (fieldNumber) {
				case 1: z.setNum(stoi(temp)); break;
				case 2: z.setCity(temp); break;
				case 3: z.setStateCode(temp); break;
				case 4: z.setCounty(temp); break;
				case 5: z.setLat(stof(temp)); break;
				default: z.setLon(stof(temp)); break;

				}
				fieldNumber++;
				temp = "";
			}
		}
	return true;
	}

	return false;
}