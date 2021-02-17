#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

void readTalbe ( vector<vector<int>> &sudoku , int n);                          // Reads the sudoku table.
bool check (vector<vector<int>> &sudoku , int n);                               // Checks to see if the table is solved.
bool isPerfectSquare (long double x);                                           // Checks to see if the number is a Perfect square.
void printTable (vector<vector<int>> &sudoku , int n);                          // Prints the solution.
void solve (vector<vector<int>> &sudoku , int n);                               // This function solves the sudoku using SAT.
int possible (vector<vector<int>> &sudoku , int n ,int num , int i , int j);    // Checks to see if a number can be put in a cell.

int main ()
{
    int n;

    cout << "Please enter the size of the table!\nPlease note that this number has to be a perfect square.\n";
    cout << "---------------------------------------------\n";

    do
    {
        cin >> n;

        if (!isPerfectSquare(n) )
        {
            cout << "The number you entered is not a perfect square.\nPlease try again!\n";
        }

    } while (! isPerfectSquare(n) );

    vector<vector<int>> sudoku;

    cout << "\n\nPlease enter the table!\n";
    cout << "---------------------------------------------\n";
    readTalbe(sudoku , n);
    solve (sudoku , n);

    if (!check(sudoku , n))
        solve (sudoku , n);

    if (!check(sudoku , n))
        solve (sudoku , n);

    if (! check(sudoku , n))
        cout << "\nThis sudoku cannot be solved!\n";
    else
    {

        cout << "\n\nThe answer is:\n";
        cout << "---------------------------------------------\n";
        printTable(sudoku , n);

    }

    return 0;
}

void readTalbe ( vector<vector<int>> &sudoku , int n)
{
    int value;
    vector <int> temp;

    for(int i = 0; i < n; i++)
    {
		for(int j = 0; j < n; j++)
		{
			cin >> value;
			temp.push_back(value);

        }
        sudoku.push_back(temp);
        temp.clear();
    }
}

bool check(vector<vector<int>> &sudoku , int n)
{
    bool d = true;
    for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (sudoku[i][j] == 0)
                d = false;
		}
	}
	return d;
}

bool isPerfectSquare(long double x)
{
    long double sr = sqrt(x);

    return ((sr - floor(sr)) == 0);
}

void printTable (vector<vector<int>> &sudoku , int n)
{

    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
            cout << sudoku[i][j] << " ";
        cout << "\n";
    }
}

int possible (vector<vector<int>> &sudoku , int n ,int num , int i , int j)
{
    for (int k = 0; k < n; k++)
    {
        if (sudoku[i][k] == num)
        {
            return 0;
        }
    }

    for (int k = 0; k < n; k++)
    {
        if (sudoku[k][j] == num)
        {
            return 0;
        }
    }

    for (int k = (int)(i / (sqrt (n))) * sqrt(n); k < (int)(i / (sqrt (n))) * sqrt(n) + sqrt(n); k++)
    {
        for (int l = (int)(j / (sqrt (n))) * sqrt(n); l < (int)(j / (sqrt (n))) * sqrt(n) + sqrt(n); l++)
        {
            if (sudoku[k][l] == num)
            {
                return 0;
            }
        }
    }

    return num;
}

void solve (vector<vector<int>> &sudoku , int n)
{
    int count;
    for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (sudoku[i][j] == 0)
                {
                    count = 0;
                    for (int k = 1; k <= n; k++)
                    {
                        if (count > 1)
                        {
                            sudoku[i][j] = 0;
                            break;
                        }
                        if (possible(sudoku , n , k , i , j) == k)
                        {
                            sudoku[i][j] = k;
                            count++;
                        }
                    }
                    if (count == 1)
                    {
                        i = 0;
                        j = -1;
                    }
                }
            }
        }
}
