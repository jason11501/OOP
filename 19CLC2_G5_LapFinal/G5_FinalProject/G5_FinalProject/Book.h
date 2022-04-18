#ifndef _BOOK_H_
#define _BOOK_H_

#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <stdint.h>
#include <Windows.h>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <time.h>
#include <stdlib.h>

using namespace std;

void textcolor(int x);
void gotoxy(int x, int y);
void resizeConsole(int width, int height);

//void showingSeat(int **&arr);
//int countEmptySeat(int** arr);
//void deleteSeat(int**& arr,int row,int col);

class Tokenizer
{
public:
	static vector<string> split(string haystack, string separator = " ");
};

class Account {
private:
	string _username;
	string _password;
public:
	Account();
	Account(string username, string password);
	bool operator == (const Account&);
	Account loadAnAccount(ifstream&);
	static string inputPassword();
	string getUsernametype();
	bool checkAccount(string username, string password);
	bool checkPassword(string password);
	bool checkUsername(string username);
	bool checkUsername(const Account&);
	void saveAccount(ofstream&);
	Account createNewAccount(string username, string password);
	void changePassword();
};

class ListAccount : public Account {
private:
	vector<Account> _listAccount;
public:
	void loadListAccount(string);
	int login(string username, string password);
	void saveListAccount(string);
	void SignUp(Account&);
	void removeAccount(string);
	Account findAccount(string);
	void setAccount(Account&);
};

class Manager
{
private:
	string _username;
	string _fullName;
	string _telephoneNumber;
	string _sex;
public:
	Manager(string username);
	void loadInfo();
	void printInfo();
	void chagePassword(Account& account);
	void deleteACustomer();
	void addACustomer();

};

class Customer
{
private:
	string _username;
	string _fullName;
	string _telephoneNumber;
	string _sex;
	string _dateCreateAccount;
	string _status;
	string _tPoint;
	string _cPoint;
	string _address;
public:
	Customer();
	Customer(string username);
	Customer(const Customer& c);
	Customer& operator = (const Customer& c);
	void inputInfo();
	void createnew();
	void loadInfo();
	void printInfo();
	void changePassword(Account& account);
	void buyABook();
	void viewBuyingHistory();
};

class Menu {
public:
	void startMenu();
	void repeatMenuCustomer();
	void repeatMenuManager();
};

class Book
{
private:
	string _ID;
	string _name;
	string _author;
	string _type;
	string _publishYear;
	string _numSell;
	string _national;
	string _price;
public:
	Book& operator = (const Book& b);
	void loadBookInfo(ifstream& fin);
	void printABook(int x,int y);
	void printBook();
	void printBill(int temp);
	void addHistory(string username, int temp);
	void sellOne();
	bool isLastBook();
	void printBook(ofstream& fout);
	void saveBookInfo(ofstream& fout);
	void input(int n);
	bool check_id_name(string temp);
	void edit();

};

class Bookshelf {
private:
	vector<Book> _lbook;
public:
	void loadAllBook();
	void printAllBook();
	void printABook(int i);
	void printBillABook(int i, int temp);
	Book findAbook(int id);
	void sellAbook(int id);
	void printAllBook(ofstream& fout);
	void saveAllBook();
	void Edit_Book();
	void Add_Book();
	void Delete_Book();
};

void introduction();
bool is_open();
void Upper_First_Pos(string& temp);

class Time {
public:
	int sec, min, hour, wday;
	Time Parse1(string obj);// hour and min
	Time Parse2(string obj);// wday
};

class Date
{
public:
	int  day, mon, year;
};

class Voucher {
private:
	vector<string> _voucherUsed;
	vector<string> _voucherList;
public:
	Voucher();
	Voucher(const Voucher& voucher);
	~Voucher();
	Voucher& operator = (const Voucher& voucher);
	void loadVoucherList();
	void loadVoucherUsed(const string& username);
	bool isCorrectCode(const string& code);
	bool hasBeenUsed(const string& code);
	void useVoucherCode(const string& code, const string& username, int& temp);
	void reWritedata(const string& username);
};

class Rank {
private:
	string _rank;	// Herald ->> Guardian ->> Crusader ->> Archon ->> Legend ->> Ancient ->> Divine ->> Immortal
	int _tPoint;	//Buying 1 book + 5 point, borrowing a book + 1 point
	int _cPoint;
	int _discounts;
public:
	Rank();
	Rank(const Rank& r);
	~Rank();
	Rank& operator = (const Rank& r);
	void plusPoints(int selling, int borrowing);
	void printRank();
	bool checkRankup();	// Herald(0~49) ->> Guardian(50~149) ->> Crusader(150~299) ->> Archon(300~499) ->> Legend(500~749) ->> Ancient(750~999) ->> Divine(1000~1499) ->> Immortal(1500~)
	void rankUp();
	void exchangeGifts();
};
//===1909

class Seat
{
private:
	int _x;
	int _y;
	bool** _isEmpty;			// 1: empty | 0: not empty
public:
	Seat();
	Seat(const Seat& s);
	~Seat();
	Seat& operator = (const Seat& s);
	void loadSeat();
	void checkAllSeats();
	void checkASeat(int x, int y);
	void bookASeat(int x, int y);
};


#endif