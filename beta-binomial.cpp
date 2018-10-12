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
	freopen ("test2.txt","r",stdin);
	
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
		//posteriorProb = ((countHead+a - 1) / (sequence[ith].size()+a + b - 2)); 
		posteriorProb = ((countHead+a) / (sequence[ith].size()+a + b)); 
		//posteriorProb = likelihood * betaPrior;
		cout <<"\tposteriorProb:\t" << posteriorProb <<endl; 
		
		a += countHead; 
        b += (sequence[ith].size()) - countHead;
        cout << "\tBeta prior:\ta: " << a << "\n\t\t\tb: " << b << endl;
	}
	
	
	return 0;
	
}
