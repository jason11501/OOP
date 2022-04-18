#include "Book.h"

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




bool isBmpFile(FILE* f)
{
	if (f == NULL)
	{
		return false;
	}
	BmpSignature signature;
	fseek(f, 0, SEEK_SET);
	fread(&signature, sizeof(BmpSignature), 1, f);

	return signature.data[0] == 'B' && signature.data[1] == 'M';
}



void readBmpHeader(FILE* f, BmpFile& bmp)
{
	if (f == NULL)
	{
		return;
	}
	fseek(f, 0, SEEK_SET);
	fread(&bmp.header, sizeof(BmpHeader), 1, f);

}

void readBmpDib(FILE* f, BmpFile& bmp)
{
	fseek(f, sizeof(BmpHeader), SEEK_SET);
	fread(&bmp.Dib, sizeof(BmpDib), 1, f);
}

void printBmpHeader(const BmpFile& bmp)
{
	BmpHeader header = bmp.header;
	cout << "****BMP header*****" << endl;
	cout << "File size: " << header.fileSize << endl;
	cout << "Reverse1: " << header.reverse1 << endl;
	cout << "Reverse2: " << header.reverse2 << endl;
	cout << "Data offset: " << header.dataOffset << endl;
}

void printBmpDib(const BmpFile& bmp)
{
	BmpDib dib = bmp.Dib;

	cout << "****BMP Dib****" << endl;
	cout << "Dib size: " << dib.Dibsize << endl;
	cout << "Image width: " << dib.imageWidth << endl;
	cout << "Image Height: " << dib.imageHeight << endl;
	cout << "Number of color planes: " << dib.colorPlaneCount << endl;
	cout << "Pixel Size: " << dib.PixelSize << endl;
	cout << "Compress Method: " << dib.compressMethod << endl;
	cout << "Bitmap size: " << dib.bitmapByteCount << endl;
	cout << "Horizontal resolution: " << dib.horizontalResolution << endl;
	cout << "Vertical resolution: " << dib.verticalResolution << endl;
	cout << "number of colors: " << dib.colorCount << endl;
	cout << "Number of important color: " << dib.importantColorCount << endl;
}



void readBmpPixelArray(FILE* f, BmpFile& bmp)
{
	if (f == NULL)
	{
		return;
	}
	int widthSize = bmp.Dib.imageWidth * (bmp.Dib.PixelSize / 8);
	bmp.pixelArray1.paddingSize = (4 - (widthSize % 4)) % 4;
	bmp.pixelArray1.lineSize = widthSize + bmp.pixelArray1.paddingSize;
	bmp.pixelArray1.rawByteSize = bmp.pixelArray1.lineSize * bmp.Dib.imageHeight;
	bmp.pixelArray1.rawBytes = new unsigned char[bmp.pixelArray1.rawByteSize];

	fseek(f, bmp.header.dataOffset, SEEK_SET);
	fread(bmp.pixelArray1.rawBytes, bmp.pixelArray1.rawByteSize, 1, f);

	initPixels(bmp.pixelArray1, bmp.Dib.imageWidth, bmp.Dib.imageHeight);
}

void initPixels(PixelArray& pa, int width, int height)
{
	pa.rowCount = height;
	pa.columnCount = width;

	pa.pixels = new Color * [pa.rowCount];
	for (int i = 0; i < pa.rowCount; i++)
	{
		pa.pixels[pa.rowCount - 1 - i] = (Color*)(pa.rawBytes + pa.lineSize * i);
	}
}

void drawBmp(const BmpFile& bmp)
{
	HWND console = GetConsoleWindow();
	HDC hdc = GetDC(console);

	for (int i = 0; i < bmp.Dib.imageHeight; ++i)
	{
		for (int j = 0; j < bmp.Dib.imageWidth; ++j)
		{
			Color pixel = bmp.pixelArray1.pixels[i][j];
			SetPixel(hdc, j, i, RGB(pixel.red, pixel.green, pixel.blue));
		}
	}
	ReleaseDC(console, hdc);
}

void releaseBmPixelArray(BmpFile& bmp)
{
	delete[]bmp.pixelArray1.pixels;
	delete[]bmp.pixelArray1.rawBytes;
}



void changeBmp(PixelArray& p)
{
	for (int i = 0; i < p.rowCount; i++)
	{
		for (int j = 0; j < p.columnCount; j++)
		{
			Color* c = &p.pixels[i][j];
			Color* d = &p.pixels[i][j];

			c->red = d->red;
			c->green = d->green;
			c->blue = d->blue;
		}
	}
}

void printRGB(FILE* f, BmpFile& bmp)
{
	int i, j;
	Color a;
	cout << "enter i: ";
	cin >> i;
	cout << "enter j: ";
	cin >> j;
	int pos = 54 + bmp.pixelArray1.lineSize * (bmp.Dib.imageHeight - 1 - i) + j * bmp.Dib.PixelSize / 8;
	fseek(f, pos, SEEK_SET);
	fread(&a, sizeof(Color), 1, f);
	cout << "Red: " << (int)a.red << endl;
	cout << "Green: " << (int)a.green << endl;
	cout << "Blue: " << (int)a.blue << endl;
}


void Book::readBorrowFileCSV(vector<Book>& book)
{
	ifstream ifs;
	ifs.open("BorrowBookList.csv", ios::in);
	if (!ifs.is_open())
	{
		cout << "can not open borrow book file" << endl;
	}
	else
	{
		Book bookTemp;
		string temp;
		getline(ifs, temp, ',');
		getline(ifs, temp, ',');
		getline(ifs, temp, ',');
		getline(ifs, temp, ',');
		getline(ifs, temp, ',');
		getline(ifs, temp, ',');
		getline(ifs, temp, ',');
		getline(ifs, temp, '\n');
		while(!ifs.eof())					// phai cong i o numberBook vi lat nua dong dau tien doc ko phai la sach ma chi la tieu de,tac gia
		{
			getline(ifs, bookTemp.m_ID, ',');
			getline(ifs, bookTemp.m_name, ',');
			getline(ifs, bookTemp.m_author, ',');
			getline(ifs, bookTemp.m_type, ',');				
			getline(ifs, bookTemp.m_publishYear, ',');
			getline(ifs, bookTemp.m_price, ',');
			getline(ifs, bookTemp.m_numSell, ',');
			getline(ifs, bookTemp.m_numBorrow,'\n');
			book.push_back(bookTemp);
		}
	}
	cout << "READ FILE CSV COMPLETELY!!!" << endl;
}

/*void Book::printInfoBook()
{
	cout << this->m_ID << this->m_name << '\t' << this->m_author << '\t' << this->m_type;
	cout << '\t' << this->m_publishYear << '\t' << this->m_price << "\t" << this->m_numBook << endl;
}*/

void Book::printID()
{
	cout << this->m_ID;
}

void Book::printName()
{
	cout << this->m_name;
}

void Book::printAuthor()
{
	cout << this->m_author;
}

void Book::printType()
{
	cout << this->m_type;
}

void Book::printPublishYear()
{
	cout << this->m_publishYear;
}

void Book::printPrice()
{
	cout << this->m_price;
}

void Book::printNumSell()
{
	cout << this->m_numSell;
}

void Book::printNumBorrow()
{
	cout << this->m_numBorrow;
}

void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void Book::printInfoBorrowFileCSV(vector<Book> book)
{
	system("cls");
	gotoxy(8, 10);
	cout << "ID";
	gotoxy(15, 10);
	cout << "NAME";
	gotoxy(60, 10);
	cout << "AUTHOR";
	gotoxy(100, 10);
	cout << "TYPE";
	gotoxy(120, 10);
	cout << "PUBLISH YEAR";
	gotoxy(140, 10);
	cout << "PRICE";
	gotoxy(160, 10);
	cout << "NUMSELL" << endl;
	gotoxy(180, 10);
	cout << "NUMBOOK" << endl;
	int locateX = 8;
	int locateY = 11;
	

	for (int i = 0; i < book.size(); i++)
	{
		gotoxy(locateX, locateY);
		book[i].printID();

		locateX = locateX + 7;
		gotoxy(locateX, locateY);
		book[i].printName();

		locateX = locateX + 45;
		gotoxy(locateX, locateY);
		book[i].printAuthor();

		locateX = locateX + 40;
		gotoxy(locateX, locateY);
		book[i].printType();

		locateX = locateX + 20;
		gotoxy(locateX, locateY);
		book[i].printPublishYear();

		locateX = locateX + 20;
		gotoxy(locateX, locateY);
		book[i].printPrice();

		locateX = locateX + 20;
		gotoxy(locateX, locateY);
		book[i].printNumSell();

		locateX = locateX + 20;
		gotoxy(locateX, locateY);
		book[i].printNumBorrow();

		locateX = 8;
		locateY = locateY + 1;
	}
}



// CUSTOMER

void Customer::showMenuReader(vector<Customer>& customer)
{
	Customer custom;
	string choice;
	textcolor(6);
	gotoxy(30, 10);
	cout << "******** WELCOME READER TO THE QUA MON OOP BOOKSTORE ********" << endl;
	gotoxy(30, 11);
	cout << "1. Sign up" << endl;
	gotoxy(30, 12);
	cout << "2. Sign in" << endl;
	gotoxy(30, 13);
	cout << "3. Back" << endl;
	gotoxy(30, 14);
	cout << "Enter your choice: ";
	cin >> choice;
	while (choice != "1" && choice != "2" && choice != "3")
	{
		system("cls");
		gotoxy(30, 10);
		cout << "******** WELCOME READER TO THE QUA MON OOP BOOKSTORE ********" << endl;
		gotoxy(30, 11);
		cout << "Invalid choice! Please choose again" << endl;
		gotoxy(30, 12);
		cout << "1. Sign up" << endl;
		gotoxy(30, 13);
		cout << "2. Sign in" << endl;
		gotoxy(30, 14);
		cout << "3. Back" << endl;
		gotoxy(30, 15);
		cout << "Enter your choice: ";
		cin >> choice;
	}
	while (choice == "1")
	{
		system("cls");
		cin.ignore(1);
		custom.readInfoCustomer(customer);
		custom.createCustomerAccount(customer);
		gotoxy(30, 14);
		cout << "Press any key (except enter and 1) and press enter to go back from main menu" << endl;
		cin >> choice;
	}
	while (choice == "2")
	{
		system("cls");
		cin.ignore(1);
		custom.signInCustom(customer);
		cout << "Press any key(except enter and 2) and press enter to go back from main menu " << endl;
		cin >> choice;
	}
}



void Customer::showMenu(vector<Customer>& customer, vector<Manager>& manager)
{
	Manager mana;
	string choice;

	gotoxy(30, 10);
	cout << "******** WELCOME TO THE QUA MON OOP BOOKSTORE ********" << endl;

	gotoxy(30, 11);
	cout << "1. READER" << endl;

	gotoxy(30, 12);
	cout << "2. MANAGER" << endl;

	gotoxy(30, 13);
	cout << "3. Exit" << endl;

	gotoxy(30, 14);
	cout << "Enter your choice: ";
	cin >> choice;

	while (choice != "1" && choice != "2" && choice != "3")
	{
		system("cls");
		gotoxy(30, 10);
		cout << "******** WELCOME TO THE QUA MON OOP BOOKSTORE ********" << endl;

		gotoxy(30, 11);
		cout << "Invalid input! Please choose again" << endl;

		gotoxy(30, 12);
		cout << "1. READER" << endl;

		gotoxy(30, 13);
		cout << "2. MANAGER" << endl;

		gotoxy(30, 14);
		cout << "3. Exit" << endl;

		gotoxy(30, 15);
		cout << "Enter your choice: ";
		cin >> choice;
	}
	while (choice == "1")
	{
		system("cls");
		showMenuReader(customer);
		system("cls");

		textcolor(4);

		gotoxy(30, 10);
		cout << "******** WELCOME TO THE QUA MON OOP BOOKSTORE ********" << endl;

		gotoxy(30, 11);
		choice;
		cout << "1. READER" << endl;

		gotoxy(30, 12);
		cout << "2. MANAGER" << endl;

		gotoxy(30, 13);
		cout << "3. Exit" << endl;

		gotoxy(30, 14);
		cout << "Enter your choice: ";
		cin >> choice;
		while (choice != "1" && choice != "2" && choice != "3")
		{
			system("cls");
			gotoxy(30, 10);
			cout << "******** WELCOME TO THE QUA MON OOP BOOKSTORE ********" << endl;

			gotoxy(30, 11);
			cout << "Invalid input! Please choose again" << endl;

			gotoxy(30, 12);
			cout << "1. READER" << endl;

			gotoxy(30, 13);
			cout << "2. MANAGER" << endl;

			gotoxy(30, 14);
			cout << "3. Exit" << endl;

			gotoxy(30, 15);
			cout << "Enter your choice: ";
			cin >> choice;
		}
	}
	while (choice == "2")
	{
		system("cls");
		mana.showMenuManager(manager);
		system("cls");

		textcolor(4);
		gotoxy(30, 10);
		cout << "******** WELCOME TO THE QUA MON OOP BOOKSTORE ********" << endl;

		gotoxy(30, 11);
		choice;
		cout << "1. READER" << endl;

		gotoxy(30, 12);
		cout << "2. MANAGER" << endl;

		gotoxy(30, 13);
		cout << "3. Exit" << endl;

		gotoxy(30, 14);
		cout << "Enter your choice: ";
		cin >> choice;
		while (choice != "1" && choice != "2" && choice != "3")
		{
			system("cls");
			gotoxy(30, 10);
			cout << "******** WELCOME TO THE QUA MON OOP BOOKSTORE ********" << endl;

			gotoxy(30, 11);
			cout << "Invalid input! Please choose again" << endl;

			gotoxy(30, 12);
			cout << "1. READER" << endl;

			gotoxy(30, 13);
			cout << "2. MANAGER" << endl;

			gotoxy(30, 14);
			cout << "3. Exit" << endl;

			gotoxy(30, 15);
			cout << "Enter your choice: ";
			cin >> choice;
		}
		while (choice == "1")
		{
			system("cls");
			showMenuReader(customer);
			system("cls");

			textcolor(4);

			gotoxy(30, 10);
			cout << "******** WELCOME TO THE QUA MON OOP BOOKSTORE ********" << endl;

			gotoxy(30, 11);
			choice;
			cout << "1. READER" << endl;

			gotoxy(30, 12);
			cout << "2. MANAGER" << endl;

			gotoxy(30, 13);
			cout << "3. Exit" << endl;

			gotoxy(30, 14);
			cout << "Enter your choice: ";
			cin >> choice;
		}
	}

	system("cls");
	cout << "You have been log out from the system!" << endl;
}




void Customer::createCustomerAccount(vector<Customer>& a)
{
	gotoxy(30, 9);
	cout << "****** CREATING ACCOUNT ******" << endl;
	gotoxy(30, 10);
	cout << "Enter your full name: ";
	getline(cin, this->m_fullName);
	gotoxy(30, 11);
	cout << "Enter your national id: ";
	getline(cin, this->m_id);
	gotoxy(30, 12);
	cout << "Enter your sex: ";
	getline(cin, this->m_sex);
	gotoxy(30, 13);
	cout << "Enter your contact number: ";
	getline(cin, this->m_telephoneNumber);
	system("cls");

	gotoxy(30, 9);
	cout << "***** CREATING ACCOUNT *****" << endl;
	gotoxy(30, 10);
	cout << "Enter your username: ";
	getline(cin, this->m_username);
	string pass;
	gotoxy(30, 11);
	cout << "Enter your password: ";
	getline(cin, this->m_password);
	do
	{
		gotoxy(30, 12);
		cout << "enter again your password: ";
		getline(cin, pass);
	} while (this->m_password != pass);
	a.push_back(*this);
	saveInfoCustomer(a);
	gotoxy(30, 13);
	cout << "Register account successfully!" << endl;
}

void Customer::saveInfoCustomer(vector<Customer> a)
{
	ofstream ofs;
	ofs.open("CustomerInfo.txt");
	if (!ofs.is_open()) {
		cout << "can not open file" << endl;
	}
	else
	{
		ofs << a.size() << endl;
		for (int i = 0; i < a.size(); i++)
		{
			ofs << a[i].m_fullName << endl;
			ofs << a[i].m_id << endl;
			ofs << a[i].m_sex << endl;
			ofs << a[i].m_telephoneNumber << endl;
			ofs << a[i].m_username << endl;
			ofs << a[i].m_password << endl;
		}
		ofs.close();
	}
}


// ham set name cho khach hang khi doc tu file txt
void Customer::setName(string name)
{
	this->m_fullName = name;
}

// ham set id cho khach hang khi doc tu file txt
void Customer::setId(string id)
{
	this->m_id = id;
}

// ham set gioi tinh cua khach hang khi doc tu file txt
void Customer::setSex(string sex)
{
	this->m_sex = sex;
}

// ham set dien thoai cho khach hang khi doc tu file txt
void Customer::setPhone(string phone)
{
	this->m_telephoneNumber = phone;
}

// ham set username cua khach hang khi doc tu file txt
void Customer::setUserName(string user)
{
	this->m_username = user;
}


// ham set password cho khach hang khi doc tu file txt
void Customer::setPassWord(string pass)
{
	this->m_password = pass;
}

// ham doc tu file txt de lay du lieu khach hang
void Customer::readInfoCustomer(vector<Customer>& customer)
{
	customer.clear();														// xoa het customer trong vector de khi doc tu file ko bi trung
	ifstream ifs;
	ifs.open("CustomerInfo.txt");
	if (!ifs.is_open())
	{
		cout << "can not open file to read customer" << endl;
	}
	else
	{
		int count;
		ifs >> count;
		ifs.ignore(1);
		for (int i = 0; i < count; i++)
		{
			Customer custom;
			string temp;
			getline(ifs, temp);
			custom.setName(temp);
			getline(ifs, temp);
			custom.setId(temp);
			getline(ifs, temp);
			custom.setSex(temp);
			getline(ifs, temp);
			custom.setPhone(temp);
			getline(ifs, temp);
			custom.setUserName(temp);
			getline(ifs, temp);
			custom.setPassWord(temp);

			customer.push_back(custom);
		}
	}
}


// ham dang nhap cua customer sign in
void Customer::signInCustom(vector<Customer>& customer)
{
	customer.clear();
	string user, pass;
	readInfoCustomer(customer);
	gotoxy(30, 9);
	cout << "****** SIGN IN ******" << endl;
	gotoxy(30, 10);
	cout << "Enter your username: ";
	getline(cin, user);
	gotoxy(30, 11);
	cout << "Enter your password: ";
	getline(cin, pass);
	for (int i = 0; i < customer.size(); i++)
	{
		if (customer[i].m_username == user && customer[i].m_password == pass)
		{
			string choice;
			system("cls");
			textcolor(8);
			gotoxy(30, 12);
			cout << "**** WELCOME " << customer[i].m_fullName << " TO THE QUA MON OOP BOOKSTORE ****" << endl;
			gotoxy(30, 13);
			cout << "1. View profile" << endl;
			gotoxy(30, 14);
			cout << "2. Change password" << endl;
			gotoxy(30, 15);
			cout << "3. Buying books" << endl;
			gotoxy(30, 16);
			cout << "4. Borrowing books" << endl;
			gotoxy(30, 17);
			cout << "5. Exit" << endl;
			gotoxy(30, 18);
			cout << "Enter your choice (1-5): ";
			cin >> choice;
			while (choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5")
			{
				system("cls");
				gotoxy(30, 12);
				cout << "**** WELCOME " << customer[i].m_fullName << " TO THE QUA MON OOP BOOKSTORE ****" << endl;
				repeatMenuInvalidCustomer();
				gotoxy(30, 19);
				cout << "Enter your choice (1-5): ";
				cin >> choice;
				cin.ignore(1);
			}
			while (choice == "1")
			{
				system("cls");
				customer[i].printInfoOneCustomer();
				repeatMenuCustomer();
				gotoxy(30, 21);										// cho khop voi dong cuoi cua ham repeatMenuCustomer
				cout << "Enter your choice: ";
				cin >> choice;
				cin.ignore(1);
				while (choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5")
				{
					system("cls");
					gotoxy(30, 12);
					cout << "**** WELCOME " << customer[i].m_fullName << " TO THE QUA MON OOP BOOKSTORE ****" << endl;
					repeatMenuInvalidCustomer();
					gotoxy(30, 19);
					cout << "Enter your choice (1-5): ";
					cin >> choice;
					cin.ignore(1);
				}
			}
			while (choice == "2")
			{
				system("cls");
				customer[i].changePass();
				saveInfoCustomer(customer);
				repeatMenuCustomer();								// cho khop voi dong cuoi cua ham  repeatMenuCustomer
				gotoxy(30, 21);
				cout << "Enter your choice: ";
				cin >> choice;
				cin.ignore(1);
				while (choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5")
				{
					system("cls");
					gotoxy(30, 12);
					cout << "**** WELCOME " << customer[i].m_fullName << " TO THE QUA MON OOP BOOKSTORE ****" << endl;
					repeatMenuInvalidCustomer();
					gotoxy(30, 19);
					cout << "Enter your choice (1-5): ";
					cin >> choice;
					cin.ignore(1);
				}
				while (choice == "1")
				{
					system("cls");
					customer[i].printInfoOneCustomer();
					repeatMenuCustomer();							// cho khop voi dong cuoi cua ham repeatMenuCustomer
					gotoxy(30, 21);
					cout << "Enter your choice: ";
					cin >> choice;
					cin.ignore(1);
				}
			}
		}
	}
}


void repeatMenuCustomer()
{
	gotoxy(30, 16);								// cho khop voi gotoxy cuoi cung trong ham printInfoOneCustomer
	cout << "1. View profile" << endl;
	gotoxy(30, 17);
	cout << "2. Change password" << endl;
	gotoxy(30, 18);
	cout << "3. Buying books" << endl;
	gotoxy(30, 19);
	cout << "4. Borrowing books" << endl;
	gotoxy(30, 20);
	cout << "5. Exit" << endl;
}

void repeatMenuInvalidCustomer()
{
	gotoxy(30, 13);
	cout << "Invalid choice! Please enter again" << endl;
	gotoxy(30, 14);
	cout << "1. View profile" << endl;
	gotoxy(30, 15);
	cout << "2. Change password" << endl;
	gotoxy(30, 16);
	cout << "3. Buying books" << endl;
	gotoxy(30, 17);
	cout << "4. Borrowing books" << endl;
	gotoxy(30, 18);
	cout << "5. Exit" << endl;
}

void Customer::printInfoOneCustomer()
{
	gotoxy(30, 9);
	cout << "***** INFORMATION ABOUT CUSTOMER *****" << endl;
	gotoxy(30, 10);
	cout << "Full name: " << this->m_fullName << endl;
	gotoxy(30, 11);
	cout << "National id: " << this->m_id << endl;
	gotoxy(30, 12);
	cout << "Sex: " << this->m_sex << endl;
	gotoxy(30, 13);
	cout << "Phone number: " << this->m_telephoneNumber << endl;
}

void Customer::changePass()
{
	string newPass1, newPass2, oldPass;
	gotoxy(30, 9);
	cout << "***** CHANGING PASSWORD FOR CUSTOMER *****" << endl;
	gotoxy(30, 10);
	cout << "Enter your old password: ";
	getline(cin, oldPass);
	while (oldPass != this->m_password)
	{
		gotoxy(30, 10);
		cout << "Invalid old password! Enter again your old passworld: ";
		getline(cin, oldPass);
	}
	gotoxy(30, 11);
	cout << "Enter your new password: ";
	getline(cin, newPass1);
	gotoxy(30, 12);
	cout << "Enter again your new password for confirming: ";
	getline(cin, newPass2);
	if (newPass1 == newPass2)
	{
		gotoxy(30, 13);
		cout << "Changing password successfully !" << endl;
		this->m_password = newPass1;
	}
	else
	{
		gotoxy(30, 13);
		cout << "Invalid new password! Changing password fail !" << endl;
	}
}


// MANAGER

void Manager::showMenuManager(vector<Manager>& manager)
{
	Manager mana;
	string choice;
	textcolor(6);
	gotoxy(30, 10);
	cout << "******** WELCOME MANAGER TO THE QUA MON OOP BOOKSTORE ********" << endl;
	gotoxy(30, 11);
	cout << "1. Sign up" << endl;
	gotoxy(30, 12);
	cout << "2. Sign in" << endl;
	gotoxy(30, 13);
	cout << "3. Back" << endl;
	gotoxy(30, 14);
	cout << "Enter your choice: ";
	cin >> choice;
	while (choice != "1" && choice != "2" && choice != "3")
	{
		system("cls");
		gotoxy(30, 10);
		cout << "******** WELCOME MANAGER TO THE QUA MON OOP BOOKSTORE ********" << endl;
		gotoxy(30, 11);
		cout << "Invalid choice! Please choose again" << endl;
		gotoxy(30, 12);
		cout << "1. Sign up" << endl;
		gotoxy(30, 13);
		cout << "2. Sign in" << endl;
		gotoxy(30, 14);
		cout << "3. Back" << endl;
		gotoxy(30, 15);
		cout << "Enter your choice: ";
		cin >> choice;
	}
	while (choice == "1")
	{
		system("cls");
		cin.ignore(1);
		mana.readInfoManager(manager);
		mana.createManagerAccount(manager);
		gotoxy(30, 14);
		cout << "Press any key (except enter and 1) and press enter to go back from main menu" << endl;
		cin >> choice;
	}
	while (choice == "2")
	{
		system("cls");
		cin.ignore(1);
		mana.signInManager(manager);
		cout << "Press any key(except enter and 2) and press enter to go back from main menu " << endl;
		cin >> choice;
	}
}




void Manager::createManagerAccount(vector<Manager>& a)
{
	gotoxy(30, 9);
	cout << "****** CREATING ACCOUNT ******" << endl;
	gotoxy(30, 10);
	cout << "Enter your full name: ";
	getline(cin, this->m_fullName);
	gotoxy(30, 11);
	cout << "Enter your national id: ";
	getline(cin, this->m_id);
	gotoxy(30, 12);
	cout << "Enter your sex: ";
	getline(cin, this->m_sex);
	gotoxy(30, 13);
	cout << "Enter your contact number: ";
	getline(cin, this->m_telephoneNumber);
	system("cls");

	gotoxy(30, 9);
	cout << "***** CREATING ACCOUNT *****" << endl;
	gotoxy(30, 10);
	cout << "Enter your username: ";
	getline(cin, this->m_username);
	string pass;
	gotoxy(30, 11);
	cout << "Enter your password: ";
	getline(cin, this->m_password);
	do
	{
		gotoxy(30, 12);
		cout << "enter again your password: ";
		getline(cin, pass);
	} while (this->m_password != pass);
	a.push_back(*this);
	saveInfoManager(a);
	gotoxy(30, 13);
	cout << "Register account successfully!" << endl;
}

void Manager::saveInfoManager(vector<Manager> a)
{
	ofstream ofs;
	ofs.open("ManagerInfo.txt");
	if (!ofs.is_open()) {
		cout << "can not open file" << endl;
	}
	else
	{
		ofs << a.size() << endl;
		for (int i = 0; i < a.size(); i++)
		{
			ofs << a[i].m_fullName << endl;
			ofs << a[i].m_id << endl;
			ofs << a[i].m_sex << endl;
			ofs << a[i].m_telephoneNumber << endl;
			ofs << a[i].m_username << endl;
			ofs << a[i].m_password << endl;
		}
		ofs.close();
	}
}


// ham set name cho khach hang khi doc tu file txt
void Manager::setName(string name)
{
	this->m_fullName = name;
}

// ham set id cho khach hang khi doc tu file txt
void Manager::setId(string id)
{
	this->m_id = id;
}

// ham set gioi tinh cua khach hang khi doc tu file txt
void Manager::setSex(string sex)
{
	this->m_sex = sex;
}

// ham set dien thoai cho khach hang khi doc tu file txt
void Manager::setPhone(string phone)
{
	this->m_telephoneNumber = phone;
}

// ham set username cua khach hang khi doc tu file txt
void Manager::setUserName(string user)
{
	this->m_username = user;
}


// ham set password cho khach hang khi doc tu file txt
void Manager::setPassWord(string pass)
{
	this->m_password = pass;
}

// ham doc tu file txt de lay du lieu khach hang
void Manager::readInfoManager(vector<Manager>& manager)
{
	manager.clear();														// xoa het manager trong vector de khi doc tu file ko bi trung
	ifstream ifs;
	ifs.open("ManagerInfo.txt");
	if (!ifs.is_open())
	{
		cout << "can not open file to read manager" << endl;
	}
	else
	{
		int count;
		ifs >> count;
		ifs.ignore(1);
		for (int i = 0; i < count; i++)
		{
			Manager mana;
			string temp;
			getline(ifs, temp);
			mana.setName(temp);
			getline(ifs, temp);
			mana.setId(temp);
			getline(ifs, temp);
			mana.setSex(temp);
			getline(ifs, temp);
			mana.setPhone(temp);
			getline(ifs, temp);
			mana.setUserName(temp);
			getline(ifs, temp);
			mana.setPassWord(temp);

			manager.push_back(mana);
		}
	}
}

// ham lap lai Menu Manager
void repeatMenuManager()
{
	gotoxy(30, 13);
	cout << "1. View profile" << endl;
	gotoxy(30, 14);
	cout << "2. Change password" << endl;
	gotoxy(30, 15);
	cout << "3. Adding books" << endl;
	gotoxy(30, 16);
	cout << "4. Deleting books" << endl;
	gotoxy(30, 17);
	cout << "5. Editing books" << endl;
	gotoxy(30, 18);
	cout << "6. Adding member" << endl;
	gotoxy(30, 19);
	cout << "7. Deleting member" << endl;
	gotoxy(30, 20);
	cout << "8.Exit" << endl;
}

// ham bao loi nhap sai va lap lai menu Manager
void repeatMenuInvalidManager()
{
	gotoxy(30, 13);
	cout << "Invalid input! Please choice again" << endl;
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
	cout << "8. Exit" << endl;
}



// ham dang nhap cua customer sign in
void Manager::signInManager(vector<Manager>& manager)
{
	manager.clear();
	string user, pass;
	readInfoManager(manager);
	gotoxy(30, 9);
	cout << "****** SIGN IN ******" << endl;
	gotoxy(30, 10);
	cout << "Enter your username: ";
	getline(cin, user);
	gotoxy(30, 11);
	cout << "Enter your password: ";
	getline(cin, pass);
	for (int i = 0; i < manager.size(); i++)
	{
		if (manager[i].m_username == user && manager[i].m_password == pass)
		{
			string choice;
			system("cls");
			textcolor(8);
			gotoxy(30, 12);
			cout << "**** WELCOME " << manager[i].m_fullName << " TO THE QUA MON OOP BOOKSTORE ****" << endl;
			gotoxy(30, 13);
			cout << "1. View profile" << endl;
			gotoxy(30, 14);
			cout << "2. Change password" << endl;
			gotoxy(30, 15);
			cout << "3. Adding books" << endl;
			gotoxy(30, 16);
			cout << "4. Deleting books" << endl;
			gotoxy(30, 17);
			cout << "5. Editing books" << endl;
			gotoxy(30, 18);
			cout << "6. Adding member" << endl;
			gotoxy(30, 19);
			cout << "7. Deleting member" << endl;
			gotoxy(30, 20);
			cout << "8.Exit" << endl;
			gotoxy(30, 21);
			cout << "Enter your choice (1-8): ";
			cin >> choice;
			while (choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5"  && choice!="6"&&
				choice !="7" && choice!="8")
			{
				system("cls");
				gotoxy(30, 12);
				cout << "**** WELCOME " << manager[i].m_fullName << " TO THE QUA MON OOP BOOKSTORE ****" << endl;
				repeatMenuInvalidManager();
				gotoxy(30, 24);
				cout << "Enter your choice (1-8): ";
				cin >> choice;
				cin.ignore(1);
			}
			while (choice == "1")
			{
				system("cls");
				manager[i].printInfoOneManager();
				repeatMenuManager();
				gotoxy(30, 21);										// cho khop voi dong cuoi cua ham repeatMenuCustomer
				cout << "Enter your choice: ";
				cin >> choice;
				cin.ignore(1);
				while (choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5" && choice!="6"&&
					choice != "7" && choice != "8")
				{
					system("cls");
					gotoxy(30, 12);
					cout << "**** WELCOME " << manager[i].m_fullName << " TO THE QUA MON OOP BOOKSTORE ****" << endl;
					repeatMenuInvalidManager();
					gotoxy(30, 24);
					cout << "Enter your choice (1-8): ";
					cin >> choice;
					cin.ignore(1);
				}
			}

			while (choice == "2")
			{
				system("cls");
				manager[i].changePass();
				saveInfoManager(manager);
				repeatMenuManager();								// cho khop voi dong cuoi cua ham  repeatMenuCustomer
				gotoxy(30, 21);
				cout << "Enter your choice: ";
				cin >> choice;
				cin.ignore(1);
				while (choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5" && choice !="6" &&
					choice != "7" && choice != "8")
				{
					system("cls");
					gotoxy(30, 12);
					cout << "**** WELCOME " << manager[i].m_fullName << " TO THE QUA MON OOP BOOKSTORE ****" << endl;
					repeatMenuInvalidManager();
					gotoxy(30, 24);
					cout << "Enter your choice (1-8): ";
					cin >> choice;
					cin.ignore(1);
				}
				while (choice == "1")
				{
					system("cls");
					manager[i].printInfoOneManager();
					repeatMenuManager();							// cho khop voi dong cuoi cua ham repeatMenuManager
					gotoxy(30, 21);
					cout << "Enter your choice: ";
					cin >> choice;
					cin.ignore(1);
				}
			}

			while (choice == "3")
			{
				system("cls");
				vector<Book> books;
				Book bookTemp;
				bookTemp.readBorrowFileCSV(books);
				bookTemp.printInfoBorrowFileCSV(books);
				cout << endl;
	
				cout << "Enter your choice: ";
				cin >> choice;

				while (choice == "2")
				{
					system("cls");
					manager[i].changePass();
					saveInfoManager(manager);
					repeatMenuManager();								// cho khop voi dong cuoi cua ham  repeatMenuCustomer
					gotoxy(30, 21);
					cout << "Enter your choice: ";
					cin >> choice;
					cin.ignore(1);
				}

				while (choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5" && choice!="6" &&
					choice != "7" && choice != "8")
				{
					system("cls");
					gotoxy(30, 12);
					cout << "**** WELCOME " << manager[i].m_fullName << " TO THE QUA MON OOP BOOKSTORE ****" << endl;
					repeatMenuInvalidManager();
					gotoxy(30, 24);
					cout << "Enter your choice (1-8): ";
					cin >> choice;
					cin.ignore(1);
				}
				while (choice == "1")
				{
					system("cls");
					manager[i].printInfoOneManager();
					repeatMenuManager();							// cho khop voi dong cuoi cua ham repeatMenuCustomer
					gotoxy(30, 21);
					cout << "Enter your choice: ";
					cin >> choice;
					cin.ignore(1);
				}
			}

			while (choice == "6")
			{
				
			}
		}
	}
}




void Manager::printInfoOneManager()
{
	gotoxy(30, 9);
	cout << "***** INFORMATION ABOUT MANAGER *****" << endl;
	gotoxy(30, 10);
	cout << "Full name: " << this->m_fullName << endl;
	gotoxy(30, 11);
	cout << "National id: " << this->m_id << endl;
	gotoxy(30, 12);
	cout << "Sex: " << this->m_sex << endl;
	gotoxy(30, 13);
	cout << "Phone number: " << this->m_telephoneNumber << endl;
}

void Manager::changePass()
{
	string newPass1, newPass2, oldPass;
	gotoxy(30, 9);
	cout << "***** CHANGING PASSWORD FOR MANAGER *****" << endl;
	gotoxy(30, 10);
	cout << "Enter your old password: ";
	getline(cin, oldPass);
	while (oldPass != this->m_password)
	{
		gotoxy(30, 10);
		cout << "Invalid old password! Enter again your old passworld: ";
		getline(cin, oldPass);
	}
	gotoxy(30, 11);
	cout << "Enter your new password: ";
	getline(cin, newPass1);
	gotoxy(30, 12);
	cout << "Enter again your new password for confirming: ";
	getline(cin, newPass2);
	if (newPass1 == newPass2)
	{
		gotoxy(30, 13);
		cout << "Changing password successfully !" << endl;
		this->m_password = newPass1;
	}
	else
	{
		gotoxy(30, 13);
		cout << "Invalid new password! Changing password fail !" << endl;
	}
}