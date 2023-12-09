

// Osman Berk An  28849 Take Home1

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "strutils.h"

using namespace std;


void Print( vector<vector<char>> mat)   // matrix printing
{
    for (int j=0; j < mat.size(); j++)
    {
        for (int k=0; k < mat[0].size(); k++)
        {
            cout <<  mat[j][k];
        }
        cout << endl;
    }
}

bool checkValid(vector<vector<char>> mat)  //check the validity of the input file
{

    bool result = true;
    int rowSize = mat.size();
    int colSize = mat[0].size();
    for(int i=0; i<rowSize; i++){
        if(mat[i].size() != colSize){
            result = false;
        }
        for(int j=0; j<colSize; j++){
            if(mat[i][j] != '#' && mat[i][j] != '-'){  // check hashes and dashes
                result = false;
            }

        }
    }
    return result;
}

void makeStringToMatrix(vector<char> row, vector<vector<char>> &shape, string strQuery)  // make string query to a shape(matrix)
{
    int colLength = 0;
    int maxRowLength = 0;
    int tempMaxRowLength = 0;
    for(int t=0; t<strQuery.length()-1; t++){
        if(strQuery[t] >= 49 && strQuery[t] <= 57){    // 1 2 3 4 5 6 7 8 9
            int num = strQuery[t] - '0';
            tempMaxRowLength += num;

        }
        else if(strQuery[t] == '/'){
            if(tempMaxRowLength > maxRowLength){
                maxRowLength = tempMaxRowLength;

            }
            tempMaxRowLength  = 0;
            colLength++;

        }

    }
    colLength++;

    if(tempMaxRowLength > maxRowLength){
        maxRowLength = tempMaxRowLength;

    }

    for(int i=0; i<strQuery.size(); i++){
        if( (strQuery[i] == '1' && strQuery[i+1] == 's')){
            row.push_back('*');
        }
        else if( (strQuery[i] == '2' && strQuery[i+1] == 's')){
            for(int k=0; k<2; k++){
                row.push_back('*');
            }
        }
        else if( (strQuery[i] == '3' && strQuery[i+1] == 's')){
            for(int k=0; k<3; k++){
                row.push_back('*');
            }
        }
        else if( (strQuery[i] == '4' && strQuery[i+1] == 's')){
            for(int k=0; k<4; k++){
                row.push_back('*');
            }
        }
        else if( (strQuery[i] == '5' && strQuery[i+1] == 's')){
            for(int k=0; k<5; k++){
                row.push_back('*');
            }
        }
        else if( (strQuery[i] == '6' && strQuery[i+1] == 's')){
            for(int k=0; k<6; k++){
                row.push_back('*');
            }
        }
        else if( (strQuery[i] == '7' && strQuery[i+1] == 's')){
            for(int k=0; k<7; k++){
                row.push_back('*');
            }
        }
        else if( (strQuery[i] == '8' && strQuery[i+1] == 's')){
            for(int k=0; k<8; k++){
                row.push_back('*');
            }
        }
        else if( (strQuery[i] == '9' && strQuery[i+1] == 's')){   // end of stars
            for(int k=0; k<9; k++){
                row.push_back('*');
            }
        }
        else if( (strQuery[i] == '1' && strQuery[i+1] == 'b')){   // start of blanks
            row.push_back(' ');
        }
        else if( (strQuery[i] == '2' && strQuery[i+1] == 'b')){
            for(int n=0; n<2; n++){
                row.push_back(' ');
            }
        }
        else if( (strQuery[i] == '3' && strQuery[i+1] == 'b')){
            for(int n=0; n<3; n++){
                row.push_back(' ');
            }
        }
        else if( (strQuery[i] == '4' && strQuery[i+1] == 'b')){
            for(int n=0; n<4; n++){
                row.push_back(' ');
            }
        }
        else if( (strQuery[i] == '5' && strQuery[i+1] == 'b')){
            for(int n=0; n<5; n++){
                row.push_back(' ');
            }
        }
        else if( (strQuery[i] == '6' && strQuery[i+1] == 'b')){
            for(int n=0; n<6; n++){
                row.push_back(' ');
            }
        }
        else if( (strQuery[i] == '7' && strQuery[i+1] == 'b')){
            for(int n=0; n<7; n++){
                row.push_back(' ');
            }
        }
        else if( (strQuery[i] == '8' && strQuery[i+1] == 'b')){
            for(int n=0; n<8; n++){
                row.push_back(' ');
            }
        }
        else if( (strQuery[i] == '9' && strQuery[i+1] == 'b')){  // end of blanks
            for(int n=0; n<9; n++){
                row.push_back(' ');
            }
        }
        else if(strQuery[i] == 's'){
            continue;
        }
        else if(strQuery[i] == 'b'){
            continue;
        }
        else if(strQuery[i] == '/'){
            for(int b=0; b<maxRowLength-row.size(); b++){
                row.push_back('B');

            }


            shape.push_back(row);
            row.clear();
        }

    }

    shape.push_back(row);
}

bool searchPlaces(vector<vector<char>> shape, vector<vector<char>> mat) // check the places that stars written into mat
{

    bool result = false;

    int count = 0;

    int big_row = mat.size();
    int big_col = mat[0].size();
    int small_row = shape.size();
    int small_col = shape[0].size();

    for(int i=0; i< big_row-small_row +1; i++) {
        for(int j=0; j< big_col-small_col +1; j++) {
            result = true;
            for( int k=0; k<small_row; k++){
                for(int l=0; l<small_col; l++){
                    if(mat[i+k][j+l] == '#' && shape[k][l] == '*'){
                        result = false;
                        break;
                    }

                }
                if (!result) {
                    break;
                }
            }
            if (result) {
                count++;
                cout << "Placement number " << count << ":" << endl;
                for( int k=0; k<small_row; k++) {
                    for (int l = 0; l < small_col; l++) {
                        if (shape[k][l] == '*'){
                            cout << "(" << k + i << "," << l + j << ")" << "\t";

                        }
                    }

                }
                cout << endl;

            }

        }
    }

    if(count ==0){
        cout << "No placement found."<< endl;
    }


    return result;

}

int main()
{

    string line,filename,strQuery;
    ifstream input;
    vector<vector<char>> matrix;
    vector<vector<char>> matShape;
    vector<char> rows;

    cout << "Please enter the file name: " << endl;
    cin >> filename;
    input.open(filename.c_str());
    while(input.fail()){
        cout << "Could not open the file. Please enter a valid file name:";
        cin >> filename;
        input.open(filename.c_str());
    }

    while(!input.eof()){
        getline(input,line);
        stringstream ss(line);  // read line as a string separately
        char ch;
        vector<char> temp;
        while(ss>>ch){
            temp.push_back(ch);

        }
        matrix.push_back(temp);

    }

    if(!checkValid(matrix)){
        cout << "Erroneous file content. Program terminates." << endl;
    }
    else{
        cout << "The matrix file contains: " << endl;
        Print(matrix);
        cout << "Enter the string query for a shape, or" <<  " Quit " <<  "to terminate the program:" << endl;
        cin >> strQuery;    // f.e  1s1b1s/1b1s     9s      or Quit


        if(strQuery == "Quit"){
            return 0;
        }

        while(strQuery != "Quit"){   // 1s1b1s/1b1s   3s
            makeStringToMatrix(rows, matShape, strQuery);
            Print(matShape);

            searchPlaces(matShape, matrix);

            cout << "Enter the string query for a shape, or" <<  " Quit " <<  "to terminate the program:" << endl;
            cin.clear();



            matShape.clear();

            cin >> strQuery;   // 1s/3b1b1s/1s -> solve that problem.

        }

    }

    return 0;
}