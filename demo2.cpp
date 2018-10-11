/*Program to Use online learning to learn the beta distribution of the parameter p (chance to see 1) of the coin tossing trails in batch.*/
/*Author: Siffi Singh */
/*Dated: 15/10/2017 */

/* standard Headers */
#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#include <fstream>
using namespace std;
int main() {
	/*Reading lines of binary outcomes from a file*/
    ifstream f("input.txt");
    vector < string > data;
    int size = 0;
    for (string n; f >> n;) {
        data.push_back(n);
        size++;
    }
    int a, b;
    cout << "Enter Initial Parameters:\na: ";
    cin >> a;
    cout<<"b: ";
    cin>> b;
    cout << "Initial shape parameters of Beta Prior:\na: " << a << "\nb: " << b << endl;
    double MLE, prior, posterior;
    int count1 = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < data[i].size(); j++) {
            if (data[i][j] == '1')
                count1++;
        }
        /*Calculating Likelihood*/
        MLE = (double) count1 / data[i].size();
        cout << "\nLikelihood: " << MLE << endl;
        /*Calculating Prior*/
        prior = ((double)(a - 1) / (a + b - 2)); //peak value of beta function : (a-1)/(a+b-2)
        cout << "Prior: " << prior << endl;
        /*Calculating Posterior*/
        posterior = MLE * prior;
        cout << "Posterior: " << posterior << endl;
        /*Calculating new parameters 'a' and 'b'*/
        a = a + count1; //a= a+k; where k=no of 1's in one iteration
        b = b + (data[i].size()) - count1; //b= b+n-k; where k=no of 1's in one iteration
        cout << "New shape parameters for Beta Posterior:\na: " << a << "\nb: " << b << endl;
        count1 = 0;
    }
    return 0;
}


