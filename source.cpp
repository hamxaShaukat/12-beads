#include<conio.h>
#include<iostream>
#include<iomanip>
#include<fstream>
#include<Windows.h>
using namespace std;

#define board 40
#define brows 10
#define bcols 10
#define geeti 2
#define BLACK 0
#define BROWN 6
#define WHITE 15
#define GREEN 2
#define RED 4
#define LBLUE 9

enum TURN{White,Black};
struct position {
	int ri, ci;
};
void SetClr(int tcl, int bcl)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (tcl + (bcl * 16)));
}
void getRowColbyLeftClick(int& rpos, int& cpos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}
void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}
void Toss(int& turn)
{
	turn = rand() % 2;
}
void gotiClr(string pName[], int turn, int* &clr)
{
	cout << "Please Enter Color from this \n 1.0 for black.......\n2. 6 for brown......\n3. 9 for blue....\n4. 15 for white ";
	for (int i = 0; i < 2; i++)
	{
		cout << "Enter your color " << pName[turn];
		cin >> clr[i];
	}
}
void init(char**& B, string pName[], int& turn, int& dim,int *&clr)
{
	ifstream rdr("Text.txt");

	rdr >> dim;

	B = new char* [dim];
	clr = new int[2];
	for (int i = 0; i < dim; i++)
	{
		B[i] = new char[dim];
	}
	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			rdr >> B[i][j];
		}
	}
	for (int i = 0; i < 2; i++)
	{
		cout << "Enter " << i + 1 << "'s name: ";
		cin >> pName[i];
		cout << pName[i] << " Enter your clr: \n";
		cout << "Please Enter Color from this \n 1.0 for black.......\n2. 6 for brown......\n3. 9 for blue....\n4. 15 for white ";
		cin >> clr[i];
	}
	
	Toss(turn);

}
void printBaord(int dim)
{
	for (int i = 0; i < (dim+2) * brows; i++)
	{
		for (int j = 0; j < (dim+2) * bcols; j++)
		{
			SetClr(2, 0);
			gotoRowCol(i, j);
			cout << char(-37);
		}
	}
	//Horizontal lines
	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < board; j++)
		{
				int lnsp = i * brows;
				SetClr(4, 0);
				gotoRowCol(lnsp, j);
				cout << char(-37);
		}
	}

	//Verticle lines
	
	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < board; j++)
		{
				int lnsp = i * brows;
				SetClr(4, 0);
				gotoRowCol(j, lnsp);
				cout << char(-37);
		}
	}

	//Full left diagonal

	for (int i = 0, j = 0; i < board; i++, j++)
	{
		SetClr(4, 0);
		gotoRowCol(i, j);
		cout << char(-37);
	}
	
	//Full right diagonal

	for (int i = board, j = 0; j < board; i--, j++)
	{
		SetClr(4, 0);
		gotoRowCol(i, j);
		cout << char(-37);
	}

	//lower left diagonal

	for (int i = board/2, j = 0; i < board; i++, j++)
	{
		SetClr(4, 0);
		gotoRowCol(i, j);
		cout << char(-37);
	}
	//lower Right diagonal

	for (int i = board / 2, j = board; i < board; i++, j--)
	{
		SetClr(4, 0);
		gotoRowCol(i, j);
		cout << char(-37);
	}

	//upper left diagonal

	for (int i = 0, j = board/2; i < board/2; i++, j--)
	{
		SetClr(4, 0);
		gotoRowCol(i, j);
		cout << char(-37);
	}
	//upper right diagonal

	for (int i = 0, j = board / 2; i < board / 2; i++, j++)
	{
		SetClr(4, 0);
		gotoRowCol(i, j);
		cout << char(-37);
	}
}
void printGoti(int sr,int sc)
{
	for (int i = 0; i < geeti; i++)
	{
		for (int j = 0; j < geeti; j++)
		{
			gotoRowCol(i+sr, j+sc);
			cout << char(-37);
		}
	}
}
bool isBlackPiece(char sym)
{
	if (sym == 'X')
		return true;
	return false;
}
bool isWhitePiece(char sym)
{
	if (sym == 'A')
		return true;
	return false;
}
bool isMyTurn(char sym,int turn)
{
	if (turn == White)
	{
		return isWhitePiece(sym);
	}
	else if (turn == Black)
	{
		return isBlackPiece(sym);
	}
}
bool isValidSrc(char **B,position S,int dim, int turn)
{
	if (S.ri < 0 || S.ri>dim)
		return false;
	else if (S.ci<0 || S.ci>dim)
		return false;

	return isMyTurn(B[S.ri][S.ci],turn);
}
bool isValiddes(char** B,position S, position D, int dim, int turn)
{
	if (D.ri < 0 || D.ri>dim)
		return false;
	else if (D.ci<0 || D.ci>dim)
		return false;
	if (B[D.ri][D.ci] == '-')
		return true;
	else
	{
		cout << "You have selected wrong des please try again......" << endl;
		return false;
	}
}
void sel_src(position& S,int turn)
{
	cout << "Select source position of your geeti:    ";
	int r, c;
	getRowColbyLeftClick(r, c);
	S.ri = (r / geeti) / 5;
	S.ci = (c / geeti) / 5;
}
void sel_des(position& D, int turn)
{
	cout << "Select destination position of your geeti:    ";
	int r, c;
	getRowColbyLeftClick(r, c);
	D.ri = (r / geeti) / 5;
	D.ci = (c / geeti) / 5;
}
void boardWithGeeti(char** B,int dim,int *clr)
{
	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			if (B[i][j] != '-')
			{
				switch (B[i][j])
				{
				case('X'):
					if (i == 0)
					{
						if (j == 0)
						{
							gotoRowCol(i * brows, j * brows);
							SetClr(clr[0], 0);
							printGoti(i * brows, j * bcols);
						}
						else
						{
							gotoRowCol(i * brows, j * brows);
							SetClr(clr[0], 0);
							printGoti(i * brows, j * bcols);

						}
					}
					else
					{
						if (j == 0)
						{
							gotoRowCol(i * brows, j * brows);
							SetClr(clr[0], 0);
							printGoti(i * brows-1, j * bcols);
						}
						else
						{
							gotoRowCol(i * brows, j * brows);
							SetClr(clr[0], 0);
							printGoti(i * brows - 1, j * bcols - 1);

						}
					}
					break;
				case('A'):
					if (i == 0)
					{
						if (j == 0)
						{
							gotoRowCol(i * brows, j * brows);
							SetClr(clr[1], 0);
							printGoti(i * brows, j * bcols);
						}
						else
						{
							gotoRowCol(i * brows, j * brows);
							SetClr(clr[1], 0);
							printGoti(i * brows, j * bcols);

						}
					}
					else
					{
						if (j == 0)
						{
							gotoRowCol(i * brows, j * brows);
							SetClr(clr[1], 0);
							printGoti(i * brows - 1, j * bcols);
						}
						else
						{
							gotoRowCol(i * brows, j * brows);
							SetClr(clr[1], 0);
							printGoti(i * brows - 1, j * bcols - 1);

						}
					}
						

						break;
				default:
					break;
				}
			}
		}
	}
}
void trnmsg(string pName[], int turn)
{
	cout << "It's " << pName[turn] << "'s turn............"<<endl;
}
void trnchng(int& turn)
{
	if (turn == 1)
		turn--;
	else if (turn == 0)
		turn++;
}
bool vermove(char **B,position S, position D)
{
	return B[S.ri][S.ci] == B[D.ri][D.ci];
}
bool hormove(char** B, position S, position D)
{
	return B[S.ri][S.ci] == B[D.ri][D.ci];
}
bool diagmove(char** B, position S, position D)
{
	int dr = abs(S.ri - D.ri);
	int dc = abs(S.ci - D.ci);
	if (dr == dc)
		return true;
	return false;
}
bool verPC(char** B, position S, position D,int dim)
{
	if (S.ri > D.ri)
	{
		for (int i = S.ri; i < D.ri; i--)
		{	
			if (B[i][D.ci] != '-')
				return false;
		}
		return true;
	}
	else
	{
		for (int i = S.ri; i < D.ri; i++)
		{
			if (B[i][D.ci] != '-')
				return false;
		}
		return true;
	}
}
bool HorPC(char** B, position S, position D, int dim)
{
	if (S.ci > D.ci)
	{
		for (int i = S.ci; i < D.ci; i--)
		{
			if (B[D.ri][i] != '-')
				return false;
		}
		return true;
	}
	else
	{
		for (int i = S.ri; i < D.ri; i++)
		{
			if (B[D.ri][i] != '-')
				return false;
		}
		return true;
	}
}
bool isLeftdiagPC(char** B, position S, position D)
{
	if (S.ri < D.ri)
	{
		int dr = D.ri - D.ri - 1;
		for (int d = 1; d <= dr; d++)
		{
			if (B[D.ri + d][S.ci + d] != '-')
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		int dr = abs(S.ri - D.ri - 1);
		for (int d = 1; d <= dr; d++)
		{
			if (B[D.ri + d][D.ci + d] != '-')
			{
				return false;
			}
		}
		return true;
	}
}
bool isRightdiagPC(char** B, position sC, position dC)
{
	if (sC.ri < dC.ri)
	{
		int dr = dC.ri - sC.ri - 1;
		for (int d = 1; d <= dr; d++)
		{
			if (B[sC.ri + d][sC.ci - d] != '-')
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		int dr = abs(sC.ri - dC.ri - 1);
		for (int d = 1; d <= dr; d++)
		{
			if (B[dC.ri + d][dC.ci - d] != '-')
			{
				return false;
			}
		}
		return true;
	}
}
bool diag(char** B, position S, position D)
{
	if (isLeftdiagPC(B, S, D) || isRightdiagPC(B, S, D))
		return true;
	return false;
}
bool simpmove(char** B, position S, position D,int dim)
{
	int dr = abs(S.ri - D.ri);
	int dc = abs(S.ci - D.ci);
	if((verPC(B,S,D,dim) || vermove(B,S,D) && HorPC(B,S,D,dim) || hormove(B,S,D)) || (diag(B,S,D) || diagmove(B,S,D)) || dr==1 &&dc==1)
		return true;
	return false;
}

void updateboard(char**& B, position S, position D)
{
	char sym = B[S.ri][S.ci];
	B[D.ri][D.ci] = sym;
	B[S.ri][S.ci] = '-';

}

int main()
{
	srand(time(0));
	char** B;
	position S, D;
	int turn, dim,*clr;
	string pName[2];

	init(B, pName, turn, dim,clr);
	printBaord(dim);
	boardWithGeeti(B, dim, clr);
	do
	{
		
		printBaord(dim);
		boardWithGeeti(B, dim, clr);
		trnmsg(pName, turn);
		do {
			do
			{
				sel_src(S, turn);

			} while (isValidSrc(B, S, dim, turn) == false);
			sel_des(D, turn);
		} while (isValiddes(B, S,D, dim, turn) == false);

		printBaord(dim);
		updateboard(B, S, D);
		boardWithGeeti(B, dim, clr);



		system("cls");
	} while (true);



	_getch();

}
