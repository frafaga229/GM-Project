#include<iostream>
#include "utils.hpp"
#include "args.hpp"

using namespace std;


int main(int argc, char* argv[])
{

	string file_in;
	bool coordinates=0;
	int N=0;
	double xx, yy;
	double dd;
	double rd;
	string line;
	int ncoords=0;
	vector<double> X, Y;
	vector<double> D1, D2;
	bool TriangSup=1;
	bool periodicB=0;
	double frac=0.9;
	double rdval=0.000005; //order of the random correction in case of null distances;
	//(null distances should be avoided!)

	if (!parse_command_line(file_in, frac, argc, argv)) 
	{
		exit(EXIT_FAILURE);
	};

	ifstream file_in_1(file_in.c_str());
	double MAXdist;

	long int Ntemp=0;
	vector<double> Dist;

	// store the input file in a vector: X for coordinates, Dist for distances 
	// and generate vectors D1 D2 containing the first and second neighbour for each point

  getline(file_in_1, line);
  stringstream sline(line);
  while (sline >> xx)
  {
    ncoords++;
    X.push_back(xx);
  }
  N++;
  while(getline(file_in_1, line))
  {
    stringstream sline(line);
    while (sline >> xx)
    {
      X.push_back(xx);
    }
    N++;
  }
  if (file_in_1.fail() && !(file_in_1.eof())) 
  {
    cout << "Read file error!" << endl;
  }  
  cout<<"Do you want periodic boundary conditions? (YES=1, NO=0) ";
  cin>>periodicB;  
  cout<<endl;

	// Reshuffle the dataset
	vector<int> IND;
	IND.reserve(N);

	for(int i=0; i<N; i++)
	{
		IND.push_back(i);
	}
	std::random_shuffle(IND.begin(), IND.end());

  int N_retained;
	double dim;
	double dim_tot;
  
	cout<<endl;

  int i=0;
  int nbox=1;
  int Npoints=N/nbox;
  double ave_temp=0;
  double var_temp=0;
  cout<<"nbox"<<' '<<nbox<<endl;
  cout<<endl;

  for(int box=0; box<nbox; box++)
  {
    vector<int> IND_loc(IND.begin()+(Npoints*box),IND.begin()+(Npoints*(box+1)));
    vector<double> D1_loc, D2_loc;		    
    vector<double> X_loc;
    X_loc.reserve(Npoints*ncoords);
    
    for (int j=0; j<IND_loc.size(); j++)
    {
      int ind=IND_loc[j];

      for (int k=0; k<ncoords; k++) 
      {
        X_loc.push_back(X.at(ind*ncoords+k));
      }
    }

    assert(X_loc.size()==Npoints*ncoords);
    
    find_2_nn_dist( D1_loc, D2_loc, X_loc, Npoints, ncoords, periodicB); 
    compute_ID( D1_loc, D2_loc, dim, Npoints, frac, nbox, N_retained);
    
  }

  if(i==0) dim_tot=dim;

	int upper_bound=int(dim_tot+10);
	int lower_bound=max(int(dim_tot-10),0);


	// S-set plot
	
	ofstream file_gpl_fun("S_set.gpl");
    	file_gpl_fun<<fixed;
	file_gpl_fun.precision(2);
	file_gpl_fun<< "set key top left box lw 1  lc rgb \"#7F7F7F\" font \",10\" spacing 5" <<endl;
	file_gpl_fun<< "set border 4095 lw 1 lc rgb \"#7F7F7F\" " <<endl; 
	file_gpl_fun<< "set title \"S set "<<file_in<<"\" font \",20\"" <<endl;
	file_gpl_fun<< "p \'fun.dat\' lc rgb \"#7F7F7F\" pt 7 not, "<<"\"<head -"<<N_retained<<" 'fun.dat'\" lc rgb \"#DC143C\" pt 7 t \"S set\", "<<dim_tot<<"*x"<<" lw 2 lc rgb \"#00BFFF\" t \" "<<dim_tot<<"*x\"" <<endl;
	system("gnuplot -persist S_set.gpl");

	file_gpl_fun.close();
		
	return 0;

}




