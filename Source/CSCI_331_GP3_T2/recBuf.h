//recBuf.h
#pragma once
#ifndef RECBUF
#define RECBUF

#include <iostream>
#include <string>
#include <fstream>
#include "zip.h" 


class recBuf {
public:
	/*
	* @brief
	* @pre
	* @post
	*/
	recBuf() { buf = ""; size = buf.size(); };

	/*
	* @brief
	* @pre
	* @post
	*/
	void read(const & recText);

	/*
	* @brief
	* @pre
	* @post
	*/
	void write(string& blockText, int offset);

	/*
	* @brief
	* @pre
	* @post
	*/
	void pack(const zip&);

	/*
	* @brief
	* @pre
	* @post
	*/
	bool unpack(zip&);

private:
	string buf;
	const char delim = ',';
	int size;
	int index;
};
#endif