/*
* recbuf.cpp
*/

#include "recBuf.h"


void recBuf::pack(const zip&){
	buf.append(field);
}

void recBuf::read(const string& recText) {

	buf = recText;

}

void recBuf::write(const string& blockText, int offset){

}

bool recBuf::unpack(zip& z) {
	/*while ( buf[index] != '\n' && buf[index] != ',') {
		field.push_back(buf[i++]);
	}*/
	size = atoi(buf[0]) * 10 + atoi(buf[1]);
	string temp = "";
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
				case 6: z.setLon(stof(temp)); break;

				}
				fieldNumber++;
				temp = "";
			}
		}

	}
	return true;

	//return false;
}