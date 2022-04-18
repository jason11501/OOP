#include "Book.h"
#define _CRT_SECURE_NO_WARNINGS

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

void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}
//
//int countEmptySeat(int** arr)
//{
//	int temp = 0;
//	for (int i = 0; i < 10; i++)
//	{
//		for (int j = 0; j < 10; j++)
//		{
//			if (arr[i][j] == 0)
//				temp = temp + 1;
//		}
//	}
//	return temp;
//}

//
//void showingSeat(int** &arr)
//{
//	system("cls");
//	arr = new int*[10];
//	for (int i = 0; i < 10; i++)
//	{
//		arr[i] = new int[10];
//		for (int j = 0; j < 10; j++)
//		{
//			arr[i][j] = 0 + rand() % (1 + 1 - 0);
//		}
//	}
//
//	for (int i = 0; i < 10; i++)
//	{
//		for (int j = 0; j < 10; j++)
//		{
//			cout << arr[i][j] << " ";
//		}
//		cout << endl;
//	}
//	cout << endl;
//	cout << "Total seat: " << 10 * 10;
//	cout << "\t\t\t\t\t" << "Empty seat: " << countEmptySeat(arr);
//	cout << "\t\t\t\t\t" << "Full Seat: " << 10 * 10 - countEmptySeat(arr);
//	cout << endl;
//}
//
//void deleteSeat(int**& arr, int row, int col)
//{
//	for (int i = 0; i < row; i++)
//	{
//		delete[]arr[i];
//	}
//	delete[]arr;
//}

string str_tolower(string s) {
	transform(s.begin(), s.end(), s.begin(), tolower);
	return s;
}

Customer::Customer()
{
	_username = "c.customer";
	_fullName = "customer name";
	_telephoneNumber = "000000000";
	_sex = "male";
	_status = 1;
	struct tm newTime;
	time_t info = time(NULL);
	localtime_s(&newTime, &info);
	int day = newTime.tm_mday;
	int month = newTime.tm_mon;
	int year = newTime.tm_year;
	
	string date = to_string(day) + " / " + to_string(month + 1) + " / " + to_string(year + 1900);
	_dateCreateAccount = date;
	_tPoint = "0";
	_cPoint = "0";
	_address = "00 000 000";
}

Customer::Customer(string username)
{
	_username = username;
}

Customer::Customer(const Customer& c)
{
	_username = c._username;
	_fullName = c._fullName;
	_telephoneNumber = c._telephoneNumber;
	_sex = c._sex;
	_dateCreateAccount = c._dateCreateAccount;
	_status = c._status;
	_tPoint = c._tPoint;
	_cPoint = c._cPoint;
	_address = c._address;
}

Customer& Customer::operator=(const Customer& c)
{
	_username = c._username;
	_fullName = c._fullName;
	_telephoneNumber = c._telephoneNumber;
	_sex = c._sex;
	_dateCreateAccount = c._dateCreateAccount;
	_status = c._status;
	_tPoint = c._tPoint;
	_cPoint = c._cPoint;
	_address = c._address;

	return *this;
}

void Customer::inputInfo()
{
	cout << "\nEnter full name: ";
	getline(cin, _fullName);
	cout << "Enter telephoneNumber: ";
	getline(cin, _telephoneNumber);
	cout << "Enter gender: (MALE/ FEMALE)";
	getline(cin, _sex);
	cout << "Enter address: ";
	getline(cin, _address);
	_status = "1";
	_tPoint = "0";
	_cPoint = "0";
}

void Customer::createnew()
{
	inputInfo();
	vector<string> tokens;

	tokens = Tokenizer::split(str_tolower(_fullName), " ");
	string username = "c." + tokens[tokens.size() - 1] + tokens[0];
	_username = username;

	Account newAcc(username, "123");
	ListAccount lAcc;
	lAcc.SignUp(newAcc);

	ofstream fout(username + ".txt");

	fout << _username << endl;
	fout << _fullName << endl;
	fout << _telephoneNumber << endl;
	fout << _sex << endl;
	fout << _dateCreateAccount << endl;
	fout << _status << endl;
	fout << _tPoint << endl;
	fout << _cPoint << endl;
	fout << _address << endl;
	fout << 0 << endl;
	fout << 0 << endl;

	fout.close();
}

void Customer::loadInfo()
{
	string infoFileName = "";
	infoFileName += _username;
	infoFileName += ".txt";

	ifstream fin(infoFileName);

	if (!fin.is_open()) {
		std::cout << "Failed to open - " << infoFileName << endl;
		return;
	}

	getline(fin, _username);
	getline(fin, _fullName);
	getline(fin, _telephoneNumber);
	getline(fin, _sex);
	getline(fin, _dateCreateAccount);
	getline(fin, _status);
	getline(fin, _tPoint);
	getline(fin, _cPoint);
	getline(fin, _address);

	fin.close();
}

void Customer::printInfo()
{
	system("cls");
	std::cout << "**********\n\n";
	cout << "Username: " << _username << endl;
	cout << "Password: *** " << endl;
	cout << "Full Name: " << _fullName << endl;
	cout << "Telephone Number: " << _telephoneNumber << endl;
	cout << "Gender: " << _sex << endl;
	cout << "Date Create Account: " << _dateCreateAccount << endl;
	cout << "Is online: " << endl;
	cout << "Total point : " << _tPoint << endl;
	cout << "Current point: " << _cPoint << endl;
	cout << "Address: " << _address << endl;
	cout << "**********\n\n";
}
void Customer::changePassword(Account& account)
{
	account.changePassword();
}

void Customer::buyABook()
{
	Bookshelf bs;
	bs.loadAllBook();
	cout << "ALL BOOK\n";
	bs.printAllBook();
	int booknum;
	cout << "Choose the book you want to buy: ";
	cin >> booknum;
	booknum--;

	system("cls");
	system("dir");
	int BNUM = booknum + 1;
	string pic = to_string(BNUM) + ".jpg";
	system(pic.c_str());
	system("cls");
	bs.printABook(booknum);
	
	cout << "Do you want to buy this book? (Y/N)\n";
	string choseBuy;

	while (true) {
		getline(cin, choseBuy);
		if (choseBuy == "Y" || choseBuy == "y") {
			cout << "Do you want to use voucher? (Y/N)\n";
			int temp = 0;
			getline(cin, choseBuy);	
			if (choseBuy == "Y" || choseBuy == "y") {
				cout << "Enter voucher: ";
				string vch;
				getline(cin, vch);
				Voucher voucher;
				voucher.loadVoucherList();
				voucher.loadVoucherUsed(_username);
				voucher.useVoucherCode(vch, _username, temp);
			}
				Book book = bs.findAbook(booknum);
				bs.sellAbook(booknum);
				book.addHistory(_username, temp);
				//TEST: book.printBook();		

			bs.printBillABook(booknum, temp);
			system("pause");
			break;
		}
		else if (choseBuy == "N" || choseBuy == "n") {

			cout << "Choosing again!\n";
			system("pause");
			break;
		}
	}
}

void Customer::viewBuyingHistory()
{
	system("cls");
	cout << "*** BUYING HISTORY ***\n\n";
	string filename = _username;
	filename = _username + ".txt";

	ifstream fin(filename);
	string temp;

	for (int i = 0; i < 10; i++) {
		getline(fin, temp);
	}
	int count = stoi(temp);
	for (int i = 0; i < count; i++) {
		cout << i + 1 << ". ";
		getline(fin, temp);
		cout << "NAME: " << temp << endl;
		getline(fin, temp);
		cout << "PRICE: " << temp << endl;
		getline(fin, temp);
		cout << "DATE: " << temp << "\n\n\n";
	}

	fin.close();
	system("pause");
	system("cls");
}

Manager::Manager(string username)
{
	_username = username;
}

void Manager::loadInfo()
{
	string infoFileName = "";
	infoFileName += _username;
	infoFileName += ".txt";

	ifstream fin(infoFileName);

	if (!fin.is_open()) {
		cout << "Failed to open - " << infoFileName << endl;
		return;
	}

	getline(fin, _username);
	getline(fin, _fullName);
	getline(fin, _telephoneNumber);
	getline(fin, _sex);

	fin.close();
}

void Manager::chagePassword(Account& account)
{
	account.changePassword();
}

void Manager::deleteACustomer()
{
	cin.ignore();
	string CustomerUsername;
	cout << "Enter the username of the customer you want to delete: ";
	getline(cin, CustomerUsername);
	ListAccount l;
	l.removeAccount(CustomerUsername);

	cout << "Delete succesfully!\n";
	system("pause");
}

void Manager::addACustomer()
{
	Customer customer;
	customer.createnew();
	cout << "Adding successfully!" << endl;
}

void Manager::printInfo()
{
	system("cls");
	cout << "**********\n\n";
	cout << "Username: " << _username << endl;
	cout << "Password: *** " << endl;
	cout << "Full Name: " << _fullName << endl;
	cout << "Telephone Number: " << _telephoneNumber << endl;
	cout << "Gender: " << _sex << endl << endl;
	cout << "**********\n\n";
}


////Khoa

Account::Account()
{
	_username = "username";
	_password = "password";
}

Account::Account(string username, string password)
{
	_username = username;
	_password = password;
}

bool Account::operator==(const Account& account)
{
	if (_username == account._username && _password == account._password)
		return true;
	return false;
}

Account Account::loadAnAccount(ifstream& fin)
{
	getline(fin, _username);
	getline(fin, _password);

	return *this;
}

string Account::inputPassword()
{
	string passWord = "";
	char c = _getch();
	while (c != '\n' && c != '\r')
	{
		if (c == '\b')
		{
			int count = passWord.length();
			if (count > 0)
			{
				std::cout << "\b \b";
				passWord = passWord.substr(0, passWord.length() - 1);
			}
		}
		else
			if (c == 27)
			{
				return "";
			}
			else
			{
				std::cout << "*";
				passWord += c;
			}
		c = _getch();
	}
	std::cout << "\n";
	return passWord;
}

string Account::getUsernametype()
{
	return _username.substr(0, 2);
}

bool Account::checkAccount(string username, string password)
{
	if (_username == username && _password == password)
		return true;
	return false;
}

bool Account::checkPassword(string password)
{
	if (_password == password)
		return true;
	return false;
}

bool Account::checkUsername(string username)
{
	if (_username == username)
		return true;
	return false;
}

bool Account::checkUsername(const Account& account)
{
	if (_username == account._username)
		return true;
	return false;
}

void Account::saveAccount(ofstream& fout)
{
	fout << _username << endl;
	fout << _password << endl;
}

Account Account::createNewAccount(string username, string password)
{
	_username = username;
	_password = password;

	return *this;
}

void Account::changePassword()
{
	system("cls");
	string oldPass = "", newPass = "";

	do {
		cout << "Current password: ";
		//cin.ignore();
		oldPass = inputPassword();
		if (oldPass != _password) {
			cout << "Retype password and new password is not match\n" << endl;
			cout << "Do you want to try again?(Y/N) ";
			while (true)
			{
				char ch;
				cin >> ch;
				if (ch == 'y' || ch == 'Y')
				{
					cin.ignore();
					break;
				}
				else if (ch == 'n' || ch == 'N')
					return;
				else
					cout << "Choice again\n";
			}
			system("cls");
		}
	} while (oldPass != _password);

	cout << "New password: ";
	newPass = inputPassword();

	_password = newPass;

	ListAccount listAcc;
	listAcc.setAccount(*this);
}

void ListAccount::loadListAccount(string filename)
{
	ifstream fin;
	fin.open(filename);

	if (!fin.is_open()) {
		cout << "Failed to open -" << filename << endl;
		return;
	}

	int nAccount;
	fin >> nAccount;
	fin.ignore();
	for (int i = 0; i < nAccount; i++) {
		Account account;
		_listAccount.push_back(account.loadAnAccount(fin));
	}
	fin.close();
}

// manager return 1
// customer return 2
// fail return 0
int ListAccount::login(string username, string password) {
	if (username.substr(0, 2) == "m.") {
		loadListAccount("Manager.txt");

		for (int i = 0; i < _listAccount.size(); i++) {
			if (_listAccount[i].checkAccount(username, password)) {
				_listAccount.clear();
				return 1; // manager return 1
			}
		}
		return 0;
	}

	else if (username.substr(0, 2) == "c.") {
		loadListAccount("Customer.txt");

		for (int i = 0; i < _listAccount.size(); i++) {
			if (_listAccount[i].checkAccount(username, password)) {
				_listAccount.clear();
				return 2;
			}
		}
		return 0;
	}

	return 0;
}

void ListAccount::saveListAccount(string filename)
{
	ofstream fout(filename);
	if (!fout.is_open()) {
		cout << "Can't save Account!" << endl;
		return;
	}
	fout << _listAccount.size() << endl;
	for (int i = 0; i < _listAccount.size(); i++)
		_listAccount[i].saveAccount(fout);
	fout.close();
}

void ListAccount::SignUp(Account& newAccount)
{
	loadListAccount("Customer.txt");
	_listAccount.push_back(newAccount);
	saveListAccount("Customer.txt");
	_listAccount.clear();
}

void ListAccount::removeAccount(string name) {

	loadListAccount("Customer.txt");

	for (int i = 0; i < _listAccount.size(); i++)
		if (_listAccount[i].checkUsername(name))
			_listAccount.erase(_listAccount.begin() + i);

	saveListAccount("Customer.txt");
	string fileNameremove = name + ".txt";
	char* c = new char[fileNameremove.length() + 1];
	remove(fileNameremove.c_str());
	_listAccount.clear();
}

Account ListAccount::findAccount(string username)
{
	if (username.substr(0, 2) == "m.") {
		loadListAccount("Manager.txt");
		for (int i = 0; i < _listAccount.size(); i++) {
			if (_listAccount[i].checkUsername(username))
				return _listAccount[i];
		}
	}

	else if (username.substr(0, 2) == "c.") {
		loadListAccount("Customer.txt");
		for (int i = 0; i < _listAccount.size(); i++) {
			if (_listAccount[i].checkUsername(username))
				return _listAccount[i];
		}
	}

	// neu account sai thi return ve gi? -> tra loi:
	Account temp;
	return temp;
}

void ListAccount::setAccount(Account& newAccount)
{
	if (newAccount.getUsernametype() == "m.") {
		loadListAccount("Manager.txt");

		for (int i = 0; i < _listAccount.size(); i++) {
			if (_listAccount[i].checkUsername(newAccount))
				_listAccount[i] = newAccount;
		}
		saveListAccount("Manager.txt");
	}

	else if (newAccount.getUsernametype() == "c.")
	{
		loadListAccount("Customer.txt");

		for (int i = 0; i < _listAccount.size(); i++) {
			if (_listAccount[i].checkUsername(newAccount))
				_listAccount[i] = newAccount;
		}
		saveListAccount("Customer.txt");
	}
}

void Menu::startMenu()
{
	textcolor(10);
	gotoxy(30, 10);
	cout << "******** QUA MON OOP BOOKSTORE ********" << endl;
	gotoxy(30, 11);
	cout << "1. Sign in" << endl;
	gotoxy(30, 12);
	cout << "2. Back" << endl;
	gotoxy(30, 14);
	cout << "Enter your choice: ";
}


void Menu::repeatMenuCustomer()
{
	gotoxy(30, 16);								// cho khop voi gotoxy cuoi cung trong ham printInfoOneCustomer
	cout << "1. View profile" << endl;
	gotoxy(30, 17);
	cout << "2. Change password" << endl;
	gotoxy(30, 18);
	cout << "3. Buying books" << endl;
	gotoxy(30, 19);
	cout << "4. View buying history" << endl;
	gotoxy(30, 20);
	cout << "5. Seat" << endl;
	gotoxy(30, 21);
	cout << "6. Exit" << endl;
}


void Menu::repeatMenuManager()
{
	gotoxy(30, 14);
	cout << "1. View profile" << endl;
	gotoxy(30, 15);
	cout << "2. Change password" << endl;
	gotoxy(30, 16);
	cout << "3. Adding books" << endl;
	gotoxy(30, 17);
	cout << "4. Deleting books" << endl;
	gotoxy(30, 18);
	cout << "5. Editing books" << endl;
	gotoxy(30, 19);
	cout << "6. Adding member" << endl;
	gotoxy(30, 20);
	cout << "7. Deleting member" << endl;
	gotoxy(30, 21);
	cout << "8.Exit" << endl;
}


void Bookshelf::loadAllBook()
{
	ifstream fin("BookList.txt");
	if (!fin.is_open())
	{
		cout << "can not open book file" << endl;
		return;
	}
	string count;
	getline(fin, count);
	for (int i = 0; i < stoi(count); i++) {
		Book b;
		b.loadBookInfo(fin);
		_lbook.push_back(b);
	}
	cout << "READ FILE CSV COMPLETELY!!!" << endl;
	fin.close();
}

void Bookshelf::printAllBook()
{
	system("cls");
	gotoxy(8, 10);
	cout << "ID";
	gotoxy(15, 10);
	cout << "NAME";
	gotoxy(60, 10);
	cout << "AUTHOR";
	gotoxy(90, 10);
	cout << "TYPE";
	gotoxy(120, 10);
	cout << "PUBLISH YEAR";
	gotoxy(140, 10);
	cout << "NUMSELL";
	gotoxy(150, 10);
	cout << "NATIONAL" << endl;
	gotoxy(160, 10);
	cout << "PRICE" << endl;
	int locateX = 8;
	int locateY = 11;
	for (int i = 0; i < _lbook.size(); i++) {
		//cout << i + 1 << " - " << endl;
		_lbook[i].printABook(locateX,locateY);
		locateX = 8;
		locateY = locateY + 1;
	}
}

void Bookshelf::printABook(int i)
{
	_lbook[i].printBook();
}

void Bookshelf::printBillABook(int i, int temp)
{
	_lbook[i].printBill(temp);
}

Book Bookshelf::findAbook(int id)
{
	return _lbook[id];
}

void Bookshelf::sellAbook(int id)
{
	ifstream fin("BookList.txt");

	if (_lbook[id].isLastBook()) {
		_lbook.erase(_lbook.begin() + id);
	}
	else {
		_lbook[id].sellOne();
	}
	
	ofstream fout("BookList.txt");

	printAllBook(fout);
	
	fout.close();

}

void Bookshelf::printAllBook(ofstream& fout)
{
	fout << _lbook.size() << endl;
	for (int i = 0; i < _lbook.size(); i++) {
		_lbook[i].printBook(fout);
	}
}


Book& Book::operator=(const Book& b)
{
	_ID = b._ID;
	_name = b._name;
	_author = b._author;
	_type = b._type;
	_publishYear = b._publishYear;
	_numSell = b._numSell;
	_national = b._national;
	_price = b._price;
	
	return *this;
}

void Book::loadBookInfo(ifstream& fin)
{
	getline(fin, _ID);
	getline(fin, _name);
	getline(fin, _author);
	getline(fin, _type);
	getline(fin, _publishYear);
	getline(fin, _numSell);
	getline(fin, _national);
	getline(fin, _price);
}

void Book::printABook(int x,int y)
{
	gotoxy(x, y);
	cout << _ID << endl;

	x = x + 7;
	gotoxy(x, y);
	cout << _name << endl;

	x = x + 45;
	gotoxy(x, y);
	cout << _author << endl;

	x = x + 30;
	gotoxy(x, y);
	cout << _type << endl;

	x = x + 30;
	gotoxy(x, y);
	cout << _publishYear << endl;

	x = x + 20;
	gotoxy(x, y);
	cout << _numSell << endl;;

	x = x + 10;
	gotoxy(x, y);
	cout  << _national << endl;

	x = x + 10;
	gotoxy(x, y);
	cout <<  _price << endl << endl;

}

void Book::printBook()
{
	cout << "ID: " << _ID << endl;
	cout << "Name: " << _name << endl;
	cout << "Author: " << _author << endl;
	cout << "Type: " << _type << endl;
	cout << "Publish Year: " << _publishYear << endl;
	cout << "Num Sell: " << _numSell << endl;;
	cout << "Nation: " << _national << endl;
	cout << "Price: " << _price << endl << endl;
}

void Book::printBill(int temp)
{
	struct tm newTime;
	time_t info = time(NULL);
	localtime_s(&newTime, &info);
	int day = newTime.tm_mday;
	int month = newTime.tm_mon;
	int year = newTime.tm_year;
	//dd = day;
	//mm = month;
	//yy = year;
	cout << "Name: " << _name << endl;
	cout << day << " / " << month + 1 << " /"  << year + 1900 << endl;
	cout << "Price: " << stoi(_price) * (10 - temp) / 10 << endl << endl;
//	cout << "Successfully!" << endl;
}

void Book::addHistory(string username, int temp)
{
	string fileName = username + ".txt";
	ifstream fin(fileName);
	vector<string> buf;
	string s;

	if (!fin.is_open()) {
		cout << "Failed to open " << username << "file!\n";
		return;
	}

	while (!fin.eof()) {
		getline(fin, s);
		buf.push_back(s);
	}
	
	fin.close();
//	int temp = stoi(buf[stoi(buf[9]) * 3 + 10]);

	ofstream fout(fileName);
	if (!fout.is_open()) {
		cout << "Failed to open " << username << "file!\n";
		return;
	}
	int i = 0;
	for (i; i < 9; i++) {
		fout << buf[i] << endl;
	}
	int t = stoi(buf[i]) + 1;
	fout << t << endl;

	for (int j = 10; j < stoi(buf[i]) * 3 + 10; j++) {
		fout << buf[j] << endl;
	}
	
	//
	struct tm newTime;
	time_t info = time(NULL);
	localtime_s(&newTime, &info);
	int day = newTime.tm_mday;
	int month = newTime.tm_mon;
	int year = newTime.tm_year;
	//dd = day;
	//mm = month;
	//yy = year;
	fout << _name << endl;
	fout << stoi(_price) * (10 - temp) / 10 <<  endl;
	fout << day << " / " << month + 1 << " /" << year + 1900 << endl;

	for (int j = stoi(buf[i]) * 3 + 10; j < buf.size(); j++)
		fout << buf[j] << endl;
	fout.close();
}

void Book::sellOne()
{
	_numSell = to_string(stoi(_numSell) - 1);
}

bool Book::isLastBook()
{
	if (stoi(_numSell) == 1) {
		return true;
	}
	return false;
}

void Book::printBook(ofstream& fout)
{
	fout << _ID << endl;
	fout << _name << endl;
	fout << _author << endl;
	fout << _type << endl;
	fout << _publishYear << endl;
	fout << _numSell << endl;
	fout << _national << endl;
	fout << _price << endl;
}


Voucher::Voucher() {
	loadVoucherList();
}

Voucher::Voucher(const Voucher& voucher) {
	loadVoucherList();

	_voucherUsed.clear();

	for (int i = 0; i < voucher._voucherUsed.size(); i++) {
		_voucherUsed.push_back(voucher._voucherUsed[i]);
	}
}

Voucher::~Voucher() {
}

Voucher& Voucher::operator=(const Voucher& voucher) {
	loadVoucherList();

	_voucherUsed.clear();

	for (int i = 0; i < voucher._voucherUsed.size(); i++) {
		_voucherUsed.push_back(voucher._voucherUsed[i]);
	}

	return *this;
}

void Voucher::loadVoucherList() {
	ifstream fin;
	fin.open("Voucher.txt");

	if (!fin.is_open()) {
		cout << "Failed to open -Voucher.txt- file~\n";
		return;
	}

	_voucherList.clear();

	string voucherStrTemp = "";
	int count = 0;

	fin >> count;
	fin.ignore();

	for (int i = 0; i < count; i++) {
		getline(fin, voucherStrTemp);
		_voucherList.push_back(voucherStrTemp);
	}

	fin.close();
}

void Voucher::loadVoucherUsed(const string& username) {
	string filename = username + ".txt";

	fstream fin(filename, ios::in);
	if (!fin.is_open()) {
		cout << "Failed to open " << username << "file!\n";
		return;
	}

	string buf;
	for (int i = 0; i < 10; i++) {
		getline(fin, buf);
	}
	int temp = stoi(buf);
	for (int i = 0; i <= temp * 3; i++) {
		getline(fin, buf);
	}
	temp = stoi(buf);
	for (int i = 0; i < temp; i++) {
		getline(fin, buf);
		_voucherUsed.push_back(buf);
	}

	fin.close();
}

bool Voucher::isCorrectCode(const string& code) {
	loadVoucherList();

	for (int i = 0; i < _voucherList.size(); i++) {
		if (_voucherList[i] == code)
			return true;
	}

	return false;
}

bool Voucher::hasBeenUsed(const string& code) {
	//Chưa hoàn thành: load Vochers has been used~

	for (int i = 0; i < _voucherUsed.size(); i++) {
		if (_voucherUsed[i] == code)
			return true;
	}

	return false;
}

void Voucher::useVoucherCode(const string& code, const string& username, int& temp) {
	system("cls");
	_voucherUsed.clear();
	loadVoucherUsed(username);

	if (hasBeenUsed(code) == true) {
		cout << "This code has been used!\n";
		cout << "Please re-enter the code\n";
		temp = 0;
		system("pause");
		cout << "do you want to re-enter the code? (Y/N)";
		return;

		//back to menu
	}
	else if (isCorrectCode(code) == false) {
		cout << "This code is not correct!\n";
		cout << "Please re-enter the code\n";
		temp = 0;
		return;
		//back to menu
	}

	else {
		_voucherUsed.push_back(code);
		temp = 1;
		reWritedata(username);
	}

}
void Voucher::reWritedata(const string& username) {
	string filename = username + ".txt";

	fstream fin(filename, ios::in);
	if (!fin.is_open()) {
		cout << "Failed to open " << username << "file!\n";
		return;
	}

	vector<string> buf;
	string s;

	while (!fin.eof()) {
		getline(fin, s);
		buf.push_back(s);
	}
	//buf.push_back(_voucherUsed[_voucherUsed.size() - 1]);

	fin.close();
	int temp = stoi(buf[stoi(buf[9]) * 3 + 10]);

	fstream fout(filename, ios::out);
	if (!fout.is_open()) {
		cout << "Failed to open " << username << "file!\n";
		return;
	}
	int i = 0;
	for (i; i < stoi(buf[9]) * 3 + 10; i++) {
		fout << buf[i] << endl;
	}
	fout << stoi(buf[i]) + 1 << endl;
	for (int j = 0; j < _voucherUsed.size() - 1; j++) {
		fout << _voucherUsed[j] << endl;
	}
	fout << _voucherUsed[_voucherUsed.size() - 1];

	fout.close();
}

Rank::Rank() {
	_rank = "Herald";
	_tPoint = 0;
	_cPoint = 0;
	_discounts = 1;
}

Rank::Rank(const Rank& r) {
	_rank = r._rank;
	_tPoint = r._tPoint;
	_cPoint = r._cPoint;
	_discounts = r._discounts;
}

Rank::~Rank() {
}

void Rank::plusPoints(int selling, int borrowing) {
	_tPoint += selling * 5;
	_cPoint += selling * 5;
	_tPoint += borrowing;
	_cPoint += borrowing;
}

Rank& Rank::operator= (const Rank& r) {
	_rank = r._rank;
	_tPoint = r._tPoint;
	_cPoint = r._cPoint;
	_discounts = r._discounts;

	return *this;
}

void Rank::printRank() {
	system("cls");

	cout << "\n******* RANK: " << _rank << " *******\n";
	cout << "Total points: " << _tPoint << endl;
	cout << "Current points: " << _cPoint << endl;
	cout << "Discounts: " << _discounts << endl;
	cout << "\t*******\t*******";
}

bool Rank::checkRankup() {
	if (_rank == "Herald" && _tPoint >= 50)
		return true;
	if (_rank == "Guardian" && _tPoint >= 150)
		return true;
	if (_rank == "Crusader" && _tPoint >= 300)
		return true;
	if (_rank == "Archon" && _tPoint >= 500)
		return true;
	if (_rank == "Legend" && _tPoint >= 750)
		return true;
	if (_rank == "Ancient" && _tPoint >= 1000)
		return true;
	if (_rank == "Divine" && _tPoint >= 1500)
		return true;

	return false;

}

void Rank::rankUp() {
	system("cls");

	if (checkRankup() == false) {
		cout << "Not enough points!\n";
		return;
	}

	if (50 <= _tPoint < 150) {
		_rank = "Guardian";
		_discounts = 1;
	}
	else if (150 <= _tPoint < 300) {
		_rank = "Crusader";
		_discounts = 2;
	}
	else if (300 <= _tPoint < 500) {
		_rank = "Archon";
		_discounts = 4;
	}
	else if (500 <= _tPoint < 750) {
		_rank = "Legend";
		_discounts = 7;
	}
	else if (750 <= _tPoint < 1000) {
		_rank = "Ancient";
		_discounts = 10;
	}
	else if (1000 <= _tPoint < 1500) {
		_rank = "Divine";
		_discounts = 13;
	}
	else if (1500 <= _tPoint) {
		_rank = "Immortal";
		_discounts = 15;
	}

	cout << " *** Rank up successfully! *** \n";
	printRank();
}

void Rank::exchangeGifts() {
	system("cls");

	cout << "\n *** 1. 10 points -> a pen\n"
		<< "\n *** 2. 50 points -> a book (49k ~ 99k) *** "
		<< "\n *** 3. 75 points -> a book (99k ~ 149k) *** "
		<< "\n *** 4. 100 points -> a book (149k ~ 199k) *** "
		<< "\n *** 5. 125 points -> a book (199k ~ 249k) *** "
		<< "\n *** 6. 150 points -> a book (249k ~ 399k) *** " << endl
		<< "\n *** 0. Exit!\n";

	int g[] = { 0, 10, 50, 75, 100 , 125, 150 };
	int choose;

	cout << "-> Choose: ";
	cin >> choose;

	if (choose == 0) {
		return;
		//back to menu
	}

	else if (_cPoint < g[choose]) {
		cout << "Not enough points!\n";
		system("pause");
		return exchangeGifts();
	}

	else {
		cout << "Please choose a book!\n";
		system("pause");
		cout << "\n *** successfully ***";
		_tPoint -= g[choose];
	}
}

vector<string> Tokenizer::split(string haystack, string separator)
{
	vector<string> result;
	int startPos = 0;
	while (true) {
		size_t foundPos = haystack.find(separator, startPos);
		if (foundPos != string::npos) {
			string token = haystack.substr(startPos, foundPos - startPos);
			result.push_back(token);
			startPos = separator.length() + foundPos;
		}
		else {
			string token = haystack.substr(startPos, foundPos - startPos);
			result.push_back(token);
			break;
		}
	}
	return result;
}

//------------------------------
void introduction() {

	system("cls");
	int line = 1;
	ifstream fin;
	fin.open("introduction.txt");
	if (!fin.is_open())
	{
		cout << "Can't open file." << endl;
		return;
	}
	while (!fin.eof())
	{
		string s;
		getline(fin, s);
		gotoxy(85 - s.size() / 2, line);
		cout << s;
		line += 2;
	}
	fin.close();
	getchar();
}
bool is_open() {
	system("cls");
	Time tm1, tm2, tm3;
	time_t current = time(NULL);
	struct tm* now = localtime(&current);
	tm1.sec = now->tm_sec;
	tm1.min = now->tm_min;
	tm1.hour = now->tm_hour;
	tm1.wday = now->tm_wday;
	ifstream fin;
	fin.open("introduction.txt");
	if (!fin.is_open())
	{
		cout << "Can't open file." << endl;
		return false;
	}
	vector<string> line;
	while (!fin.eof())
	{
		string s;
		getline(fin, s);
		line.push_back(s);
	}
	vector<string> s1 = Tokenizer::split(line[3], " ");
	vector<string> s2 = Tokenizer::split(line[4], " ");
	vector<string> s3 = Tokenizer::split(line[5], " ");
	tm2.Parse1(s1[2]);
	tm3.Parse1(s2[2]);
	tm2.Parse2(s3[1]);
	tm3.Parse2(s3[3]);
	if (tm1.wday > tm3.wday || tm1.wday < tm2.wday) {
		cout << "Today is off day";
		return false;
	}
	if (tm1.hour > tm3.hour || tm1.hour < tm2.hour || (tm1.hour == tm2.hour && tm1.min < tm2.min) ||
		(tm1.hour == tm3.hour && tm1.min > tm3.min)) {
		gotoxy(120, 1);
		cout << "Now is closing time" << endl;
		return false;
	}
	gotoxy(120, 1);
	cout << "Now is opening time" << endl;
	return true;
	fin.close();
}
void Upper_First_Pos(string& temp) {
	bool check = true;
	for (int i = 0; i < temp.size(); i++) {
		if (temp[i] >= '1' && temp[i] <= '9') {
			check = false;
		}
	}
	if (check == false)
		return;
	vector<string> str = Tokenizer::split(temp, " ");
	for (int j = 0; j < str.size(); j++) {
		for (int i = 0; str[j][i] != '\0'; i++)
		{
			if (str[j][i] >= 'A' && str[j][i] <= 'Z')
				str[j][i] = str[j][i] + 32;
		}
		str[j][0] -= 32;
	}
	temp = "";
	for (int j = 0; j < str.size(); j++) {
		temp += str[j];
		if (j == str.size() - 1)
			break;
		else
			temp += " ";
	}
}
Time Time::Parse1(string obj) {
	vector<string> value = Tokenizer::split(obj, ":");
	hour = stoi(value[0]);
	min = stoi(value[1]);
	return *this;
}
Time Time::Parse2(string obj) {
	if (obj.compare("Monday") == 0)
		wday = 1;
	else if (obj.compare("Tuesday") == 0)
		wday = 2;
	else if (obj.compare("Wednesday") == 0)
		wday = 3;
	else if (obj.compare("Thursday") == 0)
		wday = 4;
	else if (obj.compare("Friday") == 0)
		wday = 5;
	else if (obj.compare("Saturday") == 0)
		wday = 6;
	else if (obj.compare("Sunday") == 0)
		wday = 0;
	return *this;
}
void Bookshelf::Edit_Book() {
	system("cls");
	string temp, line;
	gotoxy(30, 9);
	cout << "****** EDIT BOOK ******" << endl;
	gotoxy(30, 10);
	cout << "Input book name or id to edit: ";
	getline(cin, temp);
	for (int j = 0; j < _lbook.size(); j++) {
		if (_lbook[j].check_id_name(temp) == true) {
			_lbook[j].printBook();
			_lbook[j].edit();
			cout << "Editing book successfully!" << endl;
			break;
		}
	}


}
void Bookshelf::Add_Book() {
	int count;
	system("cls");
	gotoxy(30, 9);
	cout << "****** ADD BOOK ******" << endl;
	gotoxy(30, 10);
	cout << "How many books do you want to add: "; cin >> count;
	cin.ignore(1);
	for (int i = 0; i < count; i++) {
		Book bk;
		bk.input(i);
		_lbook.push_back(bk);
	}
}
void Bookshelf::Delete_Book() {
	system("cls");
	gotoxy(30, 9);
	cout << "****** DELETE BOOK ******" << endl;
	string temp;
	int count;
	gotoxy(30, 10);
	cout << "How many books do you want to delete: "; cin >> count;
	cin.ignore(1);
	for (int i = 0; i < count; i++) {
		system("cls");
		gotoxy(30, 9);
		cout << "Book " << i + 1;
		gotoxy(30, 10);
		cout << "Input book id or name : ";
		getline(cin, temp);
		for (int j = 0; j < _lbook.size(); j++) {
			if (_lbook[j].check_id_name(temp) == true) {
				_lbook.erase(_lbook.begin() + j);
				break;
			}
		}
	}
	gotoxy(30, 15);
	cout << "Successfully Delete Book" << endl;
}
void Bookshelf::saveAllBook() {
	ofstream fout("BookList.txt");
	if (!fout.is_open())
	{
		cout << "can not open book file" << endl;
		return;
	}
	fout << _lbook.size() << endl;
	for (int i = 0; i < _lbook.size(); i++) {
		_lbook[i].saveBookInfo(fout);
	}
}

void Book::input(int n) {
	system("cls");
	gotoxy(30, 9);
	cout << "INPUT BOOK " << n + 1;
	gotoxy(30, 10);
	cout << "Enter book id: ";
	getline(cin, this->_ID);
	gotoxy(30, 11);
	cout << "Enter your book name: ";
	getline(cin, this->_name);
	gotoxy(30, 12);
	cout << "Enter your book author: ";
	getline(cin, this->_author);
	gotoxy(30, 13);
	cout << "Enter your book type: ";
	getline(cin, this->_type);
	gotoxy(30, 14);
	cout << "Enter your book publish year: ";
	getline(cin, this->_publishYear);
	gotoxy(30, 15);
	cout << "Enter your book price: ";
	getline(cin, this->_price);
	gotoxy(30, 16);
	cout << "Enter your numbers of book sell: ";
	getline(cin, this->_numSell);
	gotoxy(30, 17);
	cout << "Enter national of the book: ";
	getline(cin, this->_national);
	cout << "Adding book succesfully!" << endl;
}
bool Book::check_id_name(string temp) {
	Upper_First_Pos(temp);
	if (this->_name == temp || this->_ID == temp)
		return true;
	return false;
}
void Book::edit() {
	string line;
	gotoxy(30, 11);
	cout << "1 ID" << endl;
	gotoxy(30, 12);
	cout << "2 Name" << endl;
	gotoxy(30, 13);
	cout << "3 Author" << endl;
	gotoxy(30, 14);
	cout << "4 Type" << endl;
	gotoxy(30, 15);
	cout << "5 Publish Year" << endl;
	gotoxy(30, 16);
	cout << "6 Num Sell" << endl;;
	gotoxy(30, 17);
	cout << "7 Price" << endl;
	gotoxy(30, 18);
	int choice;
	cout << "Input your choice:";
	cin >> choice;
	cin.ignore(1);
	while (choice < 1 || choice>7) {
		gotoxy(30, 11);
		cout << "1 ID" << endl;
		gotoxy(30, 12);
		cout << "2 Name" << endl;
		gotoxy(30, 13);
		cout << "3 Author" << endl;
		gotoxy(30, 14);
		cout << "4 Type" << endl;
		gotoxy(30, 15);
		cout << "5 Publish Year" << endl;
		gotoxy(30, 16);
		cout << "6 Num Sell" << endl;;
		gotoxy(30, 17);
		cout << "7 Price" << endl;
		gotoxy(30, 18);
		cout << "                                   " << endl;
		gotoxy(30, 20);
		cout << "Invalid choice!" << endl;
		gotoxy(30, 21);
		cout << "Input your choice again:";
		cin >> choice;
		cin.ignore(1);
	}
	if (choice == 1) {
		gotoxy(30, 23);
		cout << "Input new id:";
		getline(cin, line);
		this->_ID = line;
	}
	if (choice == 2) {
		gotoxy(30, 23);
		cout << "Input new name:";
		getline(cin, line);
		Upper_First_Pos(line);
		this->_name = line;
	}
	if (choice == 3) {
		gotoxy(30, 23);
		cout << "Input new author:";
		getline(cin, line);
		Upper_First_Pos(line);
		this->_author = line;
	}
	if (choice == 4) {
		gotoxy(30, 23);
		cout << "Input new type:";
		getline(cin, line);
		Upper_First_Pos(line);
		this->_type = line;
	}
	if (choice == 5) {
		gotoxy(30, 23);
		cout << "Input new publish year:";
		getline(cin, line);
		this->_publishYear = line;
	}
	if (choice == 6) {
		gotoxy(30, 23);
		cout << "Input new num sell:";
		getline(cin, line);
		this->_numSell = line;
	}
	if (choice == 7) {
		gotoxy(30, 23);
		cout << "Input new price:";
		getline(cin, line);
		this->_price = line;
	}
}
void Book::saveBookInfo(ofstream& fout) {
	fout << _ID << endl;
	fout << _name << endl;
	fout << _author << endl;
	fout << _type << endl;
	fout << _publishYear << endl;
	fout << _numSell << endl;
	fout << _national << endl;
	fout << _price << endl;
}

//===
Seat::Seat() {
	ifstream fin("Seat.txt");
	if (!fin.is_open()) {
		cout << "Failed to open -Seat.txt- file!\n";
		return;
	}

	fin >> _x;
	fin >> _y;

	_isEmpty = new bool* [_y];
	for (int i = 0; i < _y; i++) {
		_isEmpty[i] = new bool[_x];
	}

	for (int i = 0; i < _y; i++) {
		for (int j = 0; j < _x; j++) {
			fin >> _isEmpty[i][j];
		}
	}

	fin.close();
}

Seat::Seat(const Seat& s) {
	_x = s._x;
	_y = s._y;

	for (int i = 0; i < _y; i++) {
		delete[]_isEmpty[i];
	}
	delete[]_isEmpty;

	_isEmpty = new bool* [_y];
	for (int i = 0; i < _y; i++) {
		_isEmpty[i] = new bool[_x];
	}

	for (int i = 0; i < _y; i++) {
		for (int j = 0; j < _x; j++) {
			_isEmpty[i][j] = s._isEmpty[i][j];
		}
	}
}

Seat::~Seat() {}

void Seat::loadSeat() {
	ifstream fin("Seat.txt");
	if (!fin.is_open()) {
		cout << "Failed to open -Seat.txt- file!\n";
		return;
	}

	fin >> _x;
	fin >> _y;

	for (int i = 0; i < _y; i++) {
		delete[]_isEmpty[i];
	}
	delete[]_isEmpty;

	_isEmpty = new bool* [_y];
	for (int i = 0; i < _y; i++) {
		_isEmpty[i] = new bool[_x];
	}

	for (int i = 0; i < _y; i++) {
		for (int j = 0; j < _x; j++) {
			fin >> _isEmpty[i][j];
		}
	}

	fin.close();
}

Seat& Seat::operator = (const Seat& s) {
	_x = s._x;
	_y = s._y;

	for (int i = 0; i < _y; i++) {
		delete[]_isEmpty[i];
	}
	delete[]_isEmpty;

	_isEmpty = new bool* [_y];
	for (int i = 0; i < _y; i++) {
		_isEmpty[i] = new bool[_x];
	}

	for (int i = 0; i < _y; i++) {
		for (int j = 0; j < _x; j++) {
			_isEmpty[i][j] = s._isEmpty[i][j];
		}
	}

	return *this;
}

void Seat::checkAllSeats() {
	system("cls");

	ifstream fin("Seat.txt");
	if (!fin.is_open()) {
		cout << "Failed to open -Seat.txt- file!\n";
		return;
	}

	int countEmpty = 0;
	for (int i = 0; i < _y; i++) {
		for (int j = 0; j < _x; j++) {
			if (_isEmpty[i][j] == 1)
				++countEmpty;
		}
	}
	cout << "\n\t\tEmpty: " << countEmpty << "\n\t\tNot Empty: " << _y * _x - countEmpty << endl;
	cout << "X: not empty, O: is empty\n";

	for (int i = 0; i < _y; i++) {
		cout << endl << "|";
		for (int j = 0; j < _x; j++) {
			if (_isEmpty[i][j] == 1)
				cout << "O\t|\t";
			else
				cout << "X\t|\t";
		}
	}

	system("pause");
}

void Seat::checkASeat(int x, int y) {
	if (_isEmpty[y][x] == 1)
		cout << "Seat is empty!\n";
	else
		cout << "Seat is not empty!\n";
}

void Seat::bookASeat(int x, int y) {
	if (_isEmpty[y][x] == 1) {
		_isEmpty[y][x] = 0;


		ofstream fout("Seat.txt");
		if (!fout.is_open()) {
			cout << "Failed to open -Seat.txt- file!\n";
			return;
		}
		fout << _x << endl << _x;

		for (int i = 0; i < _y; i++) {
			fout << endl;
			for (int j = 0; j < _x; j++) {
				fout << _isEmpty[i][j] << "\t";
			}
		}

		fout.close();
		cout << "Successful!\n";
	}
	else
		cout << "Seat is reserved!\n";
}