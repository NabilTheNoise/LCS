#include <iostream>
#include <conio.h>
#include <vector>
#include <string>

using namespace std;
///////////////////////////////////  Structs  /////////////////////////////
struct subseq {
	int number;
	char arrow;
	subseq() : number(0), arrow(' ') {};
	subseq(int n) : number(n) {};
	subseq(int n, char a) : number(n), arrow(a) {};
};

//////////////////////////////////  Classes  //////////////////////////////
class seq {
public:
	string sequence;
	int size;
	seq(string s) : sequence(s), size(s.size()) {};
};

////////////////////////////////  Functions  //////////////////////////////
void printMatrix(vector<vector<subseq>> Matrix ,seq fstring, seq sstring) {
	cout << " 	";
	for (int j = 0; j < sstring.size; j++) { cout << sstring.sequence[j] << "\t"; };
	cout << "\n";
	for (int i = 0; i < fstring.size+1; i++) {
		if (i > 0) { 
			cout << fstring.sequence[i-1] << " | "; 
		}
		else cout << "  | ";
		for (int j = 0; j < sstring.size+1; j++) {
			cout << Matrix[i][j].number << Matrix[i][j].arrow<<"\t";
		}
		cout << " |\n";
	}
}

void printLCS(vector<vector<subseq>> Matrix, int i, int j, seq fstring, seq sstring) {
	if (i == 0 || j == 0) {
		cout << "---------------------------------------------------------\n";
		cout << "Your Matrix has traveled this route: \n";
		printMatrix(Matrix, fstring, sstring);
		cout << "---------------------------------------------------------\n";
		cout << "Your Longest Common Subsequence is: ";
		return;
	}
	if (Matrix[i][j].arrow == '\\') {
		Matrix[i][j].arrow = 'X';
		printLCS(Matrix, i - 1, j - 1, fstring, sstring);
		cout << fstring.sequence[i - 1];
	}
	else if (Matrix[i][j].arrow == '|') {
		Matrix[i][j].arrow = 'X';
		printLCS(Matrix, i - 1, j, fstring, sstring);
	}
	else if (Matrix[i][j].arrow == '-') {
		Matrix[i][j].arrow = 'X';
		printLCS(Matrix, i, j - 1, fstring, sstring);
	}
	
}




////////////////////////////////  Main  ///////////////////////////////////
void main() {
	system("color 0a");
	string input;

	//Getting the first string
	cout << "Enter Your First String:\n";
	getline(cin, input);
	seq fstring(input);
	system("cls");
	cout << "First String: " << fstring.sequence <<"\n";

	//Getting the second string
	cout << "Enter Your Second String:\n";
	getline(cin, input);
	seq sstring(input);
	system("cls");
	cout << "First String: " << fstring.sequence << "\n";
	cout << "Second String: " << sstring.sequence << "\n";

	//Creating Matrix
	vector<vector<subseq>> Matrix;
	Matrix.resize(fstring.size+1);
	for (int i = 0; i < fstring.size+1; i++)
		Matrix[i].resize(sstring.size+1);
	
	


	for (int i = 1; i < fstring.size+1; i++) {
		for (int j = 1; j < sstring.size+1; j++) {
			if (fstring.sequence[i-1] == sstring.sequence[j-1]) {
				Matrix[i][j].number = Matrix[i - 1][j - 1].number + 1;
				Matrix[i][j].arrow = '\\';
			}
			else if (Matrix[i - 1][j].number >= Matrix[i][j - 1].number) {
				Matrix[i][j].number = Matrix[i - 1][j].number;
				Matrix[i][j].arrow = '|';
			}
			else {
				Matrix[i][j].number = Matrix[i][j - 1].number;
				Matrix[i][j].arrow = '-';
			}
		}
	}
	cout << "---------------------------------------------------------\n";
	cout << "Your Matrix is:\n";
	printMatrix(Matrix, fstring, sstring);
	cout << "---------------------------------------------------------\n";
	
	printLCS(Matrix, fstring.size, sstring.size, fstring, sstring);



	cout << "\n";
	system("pause");
}
