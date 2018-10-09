/*
	Name: Reader.h
	Copyright:
	Author: Cao Hoang Giang
	Date:
	Description: Definition of Reader
*/
//include

#ifndef READER_H
#define READER_H

#define BIN 32
#define PI 3.14

#include <vector>
#include <iostream>
#include <cmath>
#include <cstdio> 
#include <algorithm>    // std::random_shuffle
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <cstring>
#include <fstream>
#include <sstream>


using namespace std;
 
class Reader {
public:

	int row,col;
	int numOfImage;
	Reader();

	// type: I for image or L for labe;
	void readDataMNIST(char fileName[],vector <vector <int > >& data, int& numOfImage, char type); // read data later
 

// support function
	void print ();
	 
};


#endif


