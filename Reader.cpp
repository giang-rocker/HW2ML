/*
	Name: Reader.cpp
	Copyright:
	Author: Cao Hoang Giang
	Date:
	Description: Definition of Reader
*/
//include

#ifndef READER_CPP
#define READER_CPP

#include "Reader.h"

int bin = BIN;
int scale = (256/bin);
 
Reader::Reader(){
	this->row=0;
	this->col=0;
}

int ReverseInt (int i)
{
    unsigned char ch1, ch2, ch3, ch4;
    ch1 = i & 255;
    ch2 = (i >> 8) & 255;
    ch3 = (i >> 16) & 255;
    ch4 = (i >> 24) & 255;
    return((int) ch1 << 24) + ((int)ch2 << 16) + ((int)ch3 << 8) + ch4;
}


void Reader::readDataMNIST(char fileName[],vector <vector <int > >& data, int& numOfImage, char type){ // read data later
//string fileName  = ;
//cout << scale << endl;
cout << fileName << endl;
data.clear();
ifstream file (fileName, ios::binary);
	
    if (file.is_open())
    {
        int magic_number = 0;
        int number_of_images = 0;
        int n_rows = 0;
        int n_cols = 0;
        file.read((char*) &magic_number, sizeof(magic_number));
        magic_number = ReverseInt(magic_number);
        file.read((char*) &number_of_images,sizeof(number_of_images));
        number_of_images = ReverseInt(number_of_images);
        numOfImage = number_of_images;
    if (type=='I'){// label set
        file.read((char*) &n_rows, sizeof(n_rows));
        this->row = ReverseInt(n_rows);
        file.read((char*) &n_cols, sizeof(n_cols));
        this->col = ReverseInt(n_cols);
        
        int count =0;
     //   cout << numOfImage << " " << this->row << " " << this->col << endl;
        for(int i = 0; i < numOfImage; i++)
        {
         
            vector<int> tp;
            for(int r = 0; r < this->row; ++r)
            {
                for(int c = 0; c < this->col; ++c)
                {
                    unsigned char temp = 0;
                    file.read((char*) &temp, sizeof(temp));
                    tp.push_back(((int)temp)/scale); // scale to bin
                }
            }
            data.push_back(tp);
            /*
            int index = 0;
            std::string out_string;
			std::stringstream ss;
			ss << (i+1);
			string path="MNIST_RECOVER/";
			out_string = ss.str();
			path.append(out_string);
			path.append(".txt");
			freopen (path.c_str(),"w",stdout);
		   	for(int r = 0; r < n_rows; ++r)
            {
                for(int c = 0; c < n_cols; ++c)
                {
                   cout << vec[i][index++] <<" ";
                }
            }
            */

        }
    }
    else { // label set
    	vector<int> vec;
    	 for(int i = 0; i < numOfImage; i++)
        {
        	unsigned char temp = 0;
            file.read((char*) &temp, sizeof(temp));
            vec.push_back(((int)temp));
        }
        data.push_back(vec);
    }
    
}
else {
	cout << "FAIL TO LOAD FILE " << endl;
}

}


 
	
#endif
