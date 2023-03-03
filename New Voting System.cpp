///////////////////////////////////////
//			  Deon Anoth			 //
//		 Programming Project		 //
//		  New Voting System!		 //
//			  10/14/2022			 //
///////////////////////////////////////

#include <iostream>
#include <fstream>
#include <ostream>

using namespace std;

int main()
{
	int tn_voter = 0;												// Declaring basic Variables - Total number of voters.
	int ncand = 0;													// The number of candidates.
	int cvoter = 0;													// The number of voters per candidate.
	int l = 0;
	double pelim_nCand = 0;
	bool Elect_Won = false;											// Boolean variable to check if the candidate is still in the race.

	ifstream f_vdata;												// Opening the file.
	f_vdata.open("Election2.txt");

	f_vdata >> tn_voter;											// Getting total number of voters from the file.
	f_vdata >> ncand;												// Getting total number of contestants from the file.

	int** v_data = new int* [tn_voter];								// Declaring the Voting data array.
	string* varr = new string[tn_voter];							// Declaring voter ID array.
	double* vtally = new double[ncand];								// Declaring a tally in array.
	double* vpercent = new double[ncand];							// Declaring a percentage.
	double* v_count = new double[tn_voter];							// Declaring counting register.
	bool* c_run = new bool[ncand];									// Boolean array to register the eliminated candidates to false.

	cout << " Election Results:" << endl;
	cout << " Number of voters: " << tn_voter << endl;
	cout << " Number of contestants: " << ncand << endl;

	for (int i = 0; i < tn_voter; i++)								// Initializing a multidimensinal pointer array.
	{
		v_data[i] = new int[ncand];
	}

	for (int i = 0; i < tn_voter; i++)								// Reading data from file to the pointer array.
	{
		f_vdata >> varr[i];
		for (int j = 0; j < ncand; j++)
		{
			f_vdata >> v_data[i][j];
		}
	}


	for (int i = 0; i < tn_voter; i++)								// Initializing counting register.
	{
		v_count[i] = v_data[i][0];
	}



	for (int l = 0; l < ncand; l++)									// Initializing Candidate validity.
	{
		c_run[l] = true;
	}

	f_vdata.close();												// Closing the file after use.

	while (Elect_Won != true)
	{

		for (int j = 0; j < ncand; j++)								// Initializing/reseting the tally array.
		{
			vtally[j] = 0;
		}




		for (int i = 0; i < tn_voter; i++)							// Tallying from the count register.
		{
			for (int k = 0; k < ncand; k++)
			{
				if (v_count[i] == k + 1 && v_count[i] != 0)
				{
					vtally[k] = ++vtally[k];
				}
			}
		}

		for (int z = 0; z < ncand; z++)
		{
			if (vtally[z] == 0)
			{
				c_run[z] = false;
			}
		}


		for (int z = 0; z < ncand; z++)								// Calculating the percentage.
		{
			vpercent[z] = (vtally[z] * 100) / (tn_voter);
		}


		cout << endl;
		cout << " Current Results:" << endl;
		for (int i = 0; i < ncand; i++)
		{
			cout << " " << i + 1 << ": " << "	" << vtally[i] << "	" << vpercent[i] << endl;
		}

		for (int z = 0; z < ncand; z++)								// Final Result : Candidate Won.
		{
			if (vpercent[z] > 50)
			{
				Elect_Won = true;
				cout << " Final Result: Candidate " << z + 1 << " wins." << endl;
				cout << " ********************************" << endl;
				return 0;
			}
		}

		int f = 0;
		if (ncand > 0)												// Finding the lowest number of votes and Elimination of Candidates.
		{
			int l = 0;
			for (int z = 0; z < ncand; z++)
			{
				if (vtally[z] == 0)
				{
					continue;
				}
				if (vtally[z] > 0)
				{
					pelim_nCand = vtally[z];
					l = z;
					break;
				}
			}
			for (int z = l + 1; z < ncand; z++)
			{
				if (pelim_nCand > vtally[z] && vtally[z] != 0)
				{
					pelim_nCand = vtally[z];
					f = z;
				}
			}
			c_run[f] = false;										// Eliminating the lowest candidate and Elimination Output.
			cout << " Candidate " << f + 1 << " is eliminated." << endl;
			if (pelim_nCand == vtally[0])
			{
				c_run[0] = false;
			}
		}


		for (int z = 0; z < ncand; z++)								// Turning eliminated to 0 in the large multi-dimensional array.
		{
			if (c_run[z] == false)
			{
				for (int i = 0; i < tn_voter; i++)
				{
					for (int j = 0; j < ncand; j++)
					{
						if (v_data[i][j] == z + 1)
						{
							v_data[i][j] = 0;
						}
					}
				}
			}
		}



		for (int i = 0; i < tn_voter; i++)							// Switching and getting value from the next valid column.
		{
			for (int j = 0; j < ncand; j++)
			{
				if (v_data[i][j] == 0)
				{
					continue;
				}
				if (v_data[i][j] > 0)
				{
					v_count[i] = v_data[i][j];
					break;
				}
			}
		}
	}
	return 0;
}