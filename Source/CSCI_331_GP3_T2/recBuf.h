//RecBuf.h
#pragma once
#ifndef RECBUF
#define RECBUF

#include <iostream>
#include <string>
#include <fstream>



class RecBuf {
private:
	string buf;

public:
	void read();
	void pack();
	void write();
	void unpack();
	void buildHeader();


};
#endif