#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;

void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void textcolor(int x)
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}


void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x - 1,y - 1 };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}


void XoaManHinh()
{
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}


void ToMau(int x, int y, char* a, int color) 
{
	gotoxy(x, y);
	textcolor(color);
	cout << a;
	textcolor(7);
}

int main()
{
	textcolor(5);
	gotoxy(40, 15);
	cout << "hello world" << endl;
	Sleep(1000);
	system("cls");
	gotoxy(40, 16);
	cout << "my friend" << endl;
	return 0;
}