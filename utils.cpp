#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <numeric>

using namespace std;

double DistValue(int i, int j, int N, const vector<double>& Dist, bool TriangSup){
    /*

    */
	int ll, mm, kk;
	ll=max(i,j);
	mm=min(i, j);
	if(TriangSup) 
		kk=mm*(2*N-mm-3)/2.+ll;
	else
		kk=(ll*ll-ll)/2.+mm+1;
	return Dist[kk-1];
}


void find_nearest_coo(vector<double>& D1,vector<double>& D2, vector<double>& X, int N, int ncoords, bool periodicB){
    /*
    Find the two nearest neighbors in the case of a file of coordinates
    */

	double maxdist=numeric_limits<double>::max();;
	double L[ncoords];
	double dist, d1, d2;
	for(int cc=0; cc<ncoords; cc++){
	    	L[cc]=1.;  
	}
	double Xtemp[ncoords];

	for(int i=0; i<N; i++){
		d1=maxdist;
		d2=maxdist;
		for(int j=0; j<N; j++){
			if(j!=i){
				dist=0.;
				for(int cc=0; cc<ncoords; cc++){
					Xtemp[cc]=X.at(i*ncoords+cc)-X.at(j*ncoords+cc);
					if(periodicB){
						if(abs(Xtemp[cc])>L[cc]*0.5) 
							if(X.at(i*ncoords+cc)>X.at(j*ncoords+cc)) Xtemp[cc]=L[cc]-Xtemp[cc];
							else Xtemp[cc]=L[cc]+Xtemp[cc];
					}
					dist+=Xtemp[cc]*Xtemp[cc];
				}
				dist=sqrt(dist); 

				if(dist<d1&&dist<d2){
					d2=d1;
					d1=dist;
				}
				else if(dist>=d1&&dist<d2){
				d2=dist;
				}                   
			}
		}
		D1.push_back(d1);
		D2.push_back(d2);
	}

	return;
}


void find_nearest_dist(vector<double>& D1, vector<double>& D2, const vector<double>& Dist, const int N, const bool TriangSup)
{
	/*
	Find the two nearest neighbors in the case of a file of distances
	*/
	for(int i=0; i<N; i++){
		double d1 = numeric_limits<double>::max();
		double d2 = numeric_limits<double>::max();
		for(int j=0; j<N; j++){
			if(j!=i){
				double dist = DistValue(i,j,N,Dist,TriangSup);
				if(dist<d1&&dist<d2){//controllare
					d2=d1;
					d1=dist;
				}
				else if(dist>=d1&&dist<d2){
					d2=dist;
				}
			}
		}
		D1.push_back(d1);
		D2.push_back(d2);
	}

}

