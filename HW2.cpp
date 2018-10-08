#include "Reader.h"


vector <vector <int> > 	trainingImageSet; //60000 x 784, flat to a vector
		vector <int> 	trainingLabelSet; // 60000 x 1
vector <vector <int> > 	testingImageSet; // 10000 x 784
		vector <int>   	testingLabelSet; // 10000 x 1;
vector <vector <int> > trackingImage; // track image Index By Catagory
vector <vector < int > > tempVec2D;
char fileTraningImageSet[] = "train-images.idx3-ubyte";
char fileTrainingLabelSet[] = "train-labels.idx1-ubyte";
char fileTestingImageSet[] = "t10k-images.idx3-ubyte";
char fileTestingLabelSet[] = "t10k-labels.idx1-ubyte";

vector <int> P_C_Count; 

// DECRETE
vector <vector <vector <int > > > P_X_C_Table_C; // 10 class, 784 index, 32 value
vector <vector <vector <double > > > P_X_C_Table; // 10 class, 784 index, 32 value

// CONTINOUS
vector <vector <double > > SUM_Distribution; // 10 class, sum value at 784 pixels of 60k images
vector <vector <double > > Gausse_Mean; // 10 class, sum value at 784 pixels of 60k images
vector <vector <double > > Gausse_Variance; // 10 class, sum value at 784 pixels of 60k images

void init() {
	// init P_C_Count
	vector <int> blankVec;
	vector <double> blankVecf;
	vector < vector < int> > blankVec2D;
	vector < vector < double> > blankVec2Df;
	for (int i =0; i < 10; i++) {
		P_C_Count.push_back(0);
		trackingImage.push_back( vector<int>());
	}
	
	// init PXC TABLE
	for (int k =0; k < BIN; k++)
		blankVec.push_back(0);
	for (int j=0; j < 784; j++)
		blankVec2D.push_back(blankVec);
	for (int i =0; i < 10; i++)
		P_X_C_Table_C.push_back(blankVec2D);
	
	// init PXC TABLE
	for (int k =0; k < BIN; k++)
		blankVecf.push_back(0);
	for (int j=0; j < 784; j++)
		blankVec2Df.push_back(blankVecf);
	for (int i =0; i < 10; i++)
		P_X_C_Table.push_back(blankVec2Df);
	
 	blankVecf.clear();
	for (int i =0; i  < 784; i++)	 
		blankVecf.push_back(0.0);
 
	// init SUM_Distribution 10x784
	for (int i=0; i < 10; i++) {
		SUM_Distribution.push_back(blankVecf);
		Gausse_Mean.push_back(blankVecf);
		Gausse_Variance.push_back(blankVecf);
	}
	
//	cout << "dont init" << endl;
}

int numOfImage; // current set;

int main () {

	Reader R;

	//reading traning Image
	R.readDataMNIST(fileTraningImageSet,trainingImageSet,numOfImage, 'I');
	//reading traning label
	R.readDataMNIST(fileTrainingLabelSet,tempVec2D,numOfImage,'L');
	trainingLabelSet =  tempVec2D[0];
	// double check data

	cout << "traning Image set size: ";
	cout << trainingImageSet.size() << " x " << trainingImageSet[0].size() << endl;
	cout << "traning label set size: ";
	cout << trainingLabelSet.size() << endl;
	
	init(); // init
	// tracking imageIndex
	for (int i=0; i < trainingLabelSet.size() ; i++) 
		trackingImage[trainingLabelSet[i]].push_back( i );
	
	// calculate PC
	//for (int i =0; i < trainingLabelSet.size(); i ++)
	//	P_C_Count[ trainingLabelSet[i] ] ++;
		
	for (int i =0; i <10; i++)
		P_C_Count[i] = trackingImage[i].size();
	/*
	for (int i =0; i < 10; i ++) 
		cout << i <<": " << ((P_C_Count[i]*1.0)/trainingLabelSet.size()) << endl;
	**/
	
 	// Discrete first
	// search every class and create the P_X_C
	int minCount = trainingLabelSet.size()+1;
	for (int i =0; i < 10; i ++) {// for every class
		for (int j =0; j < P_C_Count[i];j++){ //for every image on that cat
			int currentIndexImg = trackingImage[i][j];	 
			for (int k=0; k < 784; k++) {// for every pixel
				int currentValue = trainingImageSet[currentIndexImg][k];
			//	cout << currentValue << endl;
				P_X_C_Table[i][k][ currentValue ] ++;
			}
		}
	}

    //  calculate probabiliti
	for (int i =0; i < 10; i++)
		for (int j=0; j < 784; j++)
			for (int k =0; k < BIN; k++) {
				P_X_C_Table[i][j][k]= (((P_X_C_Table[i][j][k])*1.0)/P_C_Count[i] )+exp(-18);
			}
	// end of TRAINING PHASE	
	// TEST PHASE
	//reading traning Image
	R.readDataMNIST(fileTestingImageSet,testingImageSet,numOfImage, 'I');
	//reading traning label
	R.readDataMNIST(fileTestingLabelSet,tempVec2D,numOfImage,'L');
	testingLabelSet = tempVec2D[0];
	cout << "testing Image set size: ";
	cout << testingImageSet.size() << " x " << testingImageSet[0].size() << endl;
	cout << "testing Label set size: ";
	cout << testingLabelSet.size() << endl;
	
	// DISCRETE CLASSIFY TESTING SET
	int classify =-1 ;
	int countCorrect =0 ;
	for (int i =0; i < testingImageSet.size(); i ++) { // for each image
		classify =-1;
	 	double max = -999999999;
		for (int j=0; j<10; j++) { // for each class, calculate the PCX
			double currentVal =  log (((P_C_Count[j]*1.0)/trainingLabelSet.size()) ) ; // init= 0 : acourate = 85.14%
			for (int k=0; k < 784; k++) { // for each pixcel
		//	cout <<  log ( P_X_C_Table[j][k][ testingImageSet[i][k] ] ) << endl;
			currentVal += log ( P_X_C_Table[j][k][ testingImageSet[i][k] ] );	
			} // for k 
	
			if ( currentVal > max ){
				max=currentVal;
				classify = j;
			}
			
		} // for j
		if (classify == testingLabelSet[i]) 
			countCorrect ++;
			
	} // for i 
	
	cout << endl << endl;
	cout << "DICRETE" << endl;
	cout << countCorrect << "/" << testingLabelSet.size() << " <=>  " << ( (countCorrect*100.0)/testingLabelSet.size()) <<"%  Error: " <<  ( ((testingLabelSet.size()-countCorrect)*100.0)/testingLabelSet.size()) <<"%"<< endl;
	
	// CONTINUOS
	// get sum value of each pixel (784) of 60k image of 10 class
	for (int i =0 ; i < 10; i ++){ // each class
		for (int j= 0; j < trackingImage[i].size (); j++) { // for each image in class
			int currentIndex = trackingImage[i][j];
			for (int k =0; k < 784; k++) { // for each pixel
				SUM_Distribution[i][k] += trainingImageSet[currentIndex][k];
				
			}
		}
	}
	// calculate mean value
	for (int i =0; i < 10; i++)
		for (int j=0; j <784; j++) {
			Gausse_Mean[i][j] = SUM_Distribution[i][j]/P_C_Count[i];
			SUM_Distribution[i][j] = 0; // reset value to calculate another value
		}
	// calculate varsum
	for (int i =0 ; i < 10; i ++){ // each class
		for (int j= 0; j < trackingImage[i].size (); j++) { // for each image in class
			int currentIndex = trackingImage[i][j];
			for (int k =0; k < 784; k++) { // for each pixel
				double value = pow( trainingImageSet[currentIndex][k] - Gausse_Mean[i][k],2 );
				SUM_Distribution[i][k] += value;				
			}
		}
	}
	// calculate Variance value
	for (int i =0; i < 10; i++)
		for (int j =0; j < 784; j++)
			Gausse_Variance[i][j] = SUM_Distribution[i][j]/P_C_Count[i] ;
	double constPi = log((sqrt(2*PI)));
	// CONTINOUS CLASSIFY TESTING SET
	classify =-1 ;
	countCorrect =0 ;
	for (int i =0; i < testingImageSet.size(); i ++) { // for each image
		classify =-1;
		double max = -999999999;
		for (int j=0; j<10; j++) { // for each class, calculate the PCX
			double currentVal =   log (((P_C_Count[j]*1.0)/trainingLabelSet.size())  ) - constPi; // init= 0 : acourate = 85.14%
			for (int k=0; k < 784; k++) { // for each pixcel
			if (((Gausse_Variance[j][k]) -0.0f)>0.00001f) {
            	double tempVal = -(pow(testingImageSet[i][k] - Gausse_Mean[j][k] ,2)) / (2 * pow(Gausse_Variance[j][k],2));
                currentVal += (( (tempVal))  - log(Gausse_Variance[j][k] ));
            }
			else {
            //	double tempVal = -(pow(testingImageSet[j][k],2) ); 
            //    currentVal += (tempVal);
                }                    																					
        	} // for k 
	
			if ( currentVal > max ){
				max=currentVal;
				classify = j;
			}
			
		} // for j
		if (classify == testingLabelSet[i]) 
			countCorrect ++;			
		 
	 
	} // for i 
	cout << "CONTINOUS" << endl;
	cout << countCorrect << "/" << testingLabelSet.size() << " <=>  " << ( (countCorrect*100.0)/testingLabelSet.size()) <<"%  Error: " <<  ( ((testingLabelSet.size()-countCorrect)*100.0)/testingLabelSet.size()) <<"%"<< endl;
	
	return 0;
}
