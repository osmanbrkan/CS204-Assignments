#include <iostream>
#include <string>
#include<sstream>
#include<fstream>
#include <iomanip>     // for setw
#include <vector>

using namespace std;

//
//// demonstrate class matrix
//
void Print(const vector<vector<int>> & mat)
{
    for (int j=0; j < mat.size(); j++)
    {   
		for (int k=0; k < mat[0].size(); k++)
        {   
			cout << setw(4) << mat[j][k];
        }
        cout << endl;
    }
}

void SumDiagonal(const vector<vector<int>> & mat)
{
		int sumdiag = 0;
		for (int k=0; k < mat[0].size(); k++)
		{
			sumdiag += mat[k][k];
		}
		cout << "sum of diagonal is " << sumdiag << endl;
}

void SumColumn(const vector<vector<int>> & mat)
{
	for (int j=0; j < mat[0].size(); j++)
	{
		int sum = 0;
		for (int k=0; k < mat.size(); k++)
		{
			sum += mat[k][j];
		}
		cout << "sum of column " << j << " is " << sum << endl;
	}
}

void SumDiagonalReverse(const vector<vector<int>> & mat)
{
	int startRow = 0;
	int startColumn = mat[0].size() - 1;

	int sum = 0;
	for(int i = 0; i< mat[0].size(); i++)
	{
		sum += mat[startRow + i][startColumn - i];
	}
	cout << "sum of diagonal in reverse is " << sum << endl;
}

int sumSubvector(const vector<vector<int>> & mat, int rowIndex, int startColIndex, int subvectorLength)
{
	int sum = 0;

	for(int i = startColIndex; i < (startColIndex + subvectorLength); i++)
	{
		sum += mat[rowIndex][i];
	}

	return sum;
}

void printSubvector(const vector<vector<int>> & mat, int rowIndex, int startColIndex, int subvectorLength) {
    cout << "( ";
    for (int i = startColIndex; i < (startColIndex + subvectorLength); i++) {
        cout << mat[rowIndex][i] << " ";
    }
    cout << ")";
}
int main()
{
	string fileName;
	int j,k;
	vector<vector<int>> mat;
	
	cout<<"Enter the input file name"<< endl;
	cin>>fileName;

	ifstream input;
	input.open(fileName);

	if(input.fail())
	{
		cout<< "Could not open the file "<< fileName<< endl;
		return 0;
	}

	string line;
	while(!input.eof())
	{
		getline(input, line);
		stringstream ss(line);
		
		int num;
		vector<int> temp;
		
		while(ss >> num)
		{
			temp.push_back(num);		
		}
		mat.push_back(temp);
	}

	int rows = mat.size();
	int cols = mat[0].size();

    Print(mat);
	cout << "\n\n";

	SumColumn(mat);

	if (rows == cols)// diagonal only occurs in a square matrix
	{
		cout << "\n";
		SumDiagonal(mat);
		cout << "\n";
		SumDiagonalReverse(mat);
	}

	int rowNumber, subvectorLength;
	cout<<"Enter the row number to search"<<endl;
	cin>>rowNumber;
	cout<<"Enter the length of the subvector"<<endl;
	cin>>subvectorLength;

	int sumOfVector = 0;

	for(int i = 0; i < cols - subvectorLength + 1; i++)
	{
		sumOfVector = sumSubvector(mat, rowNumber, i, subvectorLength);
		printSubvector(mat, rowNumber, i, subvectorLength);
		cout << " sums to : " << sumOfVector << endl;
	}

	cout << "end of execution.\n";
	cin.ignore();
	cin.get();
    return 0;    
}