#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<vector>

using namespace std;

vector <string> sequence;
string tempStr;
double a, b;
int nSize =0;
int main() {
	freopen ("test.txt","r",stdin);
	
	while (cin >> tempStr)  {
		sequence.push_back(tempStr);
		tempStr.assign("");	
	}
	
	nSize = sequence.size ()-2;
	a = atof(sequence.back().c_str());
	sequence.pop_back();
	b =  atof(sequence.back().c_str());
	sequence.pop_back();
	cout << "Initial beta prior: " << endl;
 	cout <<"a: " << a << " b:" << b << endl;
	cout << endl;
	cout << endl;
	double likelihood=0,betaPrior =0 , posteriorProb =0 ;
	int countHead =0 ;
	for (int ith =0; ith < nSize; ith++) {// for each line
		cout << (ith+1) << "th: " <<endl;
		countHead =0 ;
		// countHead;
		for (int i=0; i < sequence[ith].size () ; i++)
			countHead += sequence[ith].at(i)- '0';
		
		likelihood =  (countHead*1.0f) / sequence[ith].size();
		cout <<"\tLikelihood:\t" << likelihood << endl;
		betaPrior = ((a - 1) / (a + b - 2)); 
		posteriorProb = likelihood * betaPrior;
		cout <<"\tPosterior Prob:\t" << posteriorProb <<endl; 
		
		a = a + countHead; 
        b = b + (sequence[ith].size()) - countHead;
        cout << "\tBeta Posterior:\ta: " << a << "\n\t\t\tb: " << b << endl;
	}
	
	
	return 0;
	
}
