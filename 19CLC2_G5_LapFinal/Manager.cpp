#include "Manager.h"


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
				cout << "**** WELCOME " << manager[i].m_fullName << " TO THE QUA MON OOP BOOKSTORE ****" << endl;
				repeatMenuInvalidCustomer();
				gotoxy(30, 19);
				cout << "Enter your choice (1-5): ";
				cin >> choice;
				cin.ignore(1);
			}
			while (choice == "1")
			{
				system("cls");
				manager[i].printInfoOneManager();
				repeatMenuCustomer();
				gotoxy(30, 21);										// cho khop voi dong cuoi cua ham repeatMenuCustomer
				cout << "Enter your choice: ";
				cin >> choice;
				cin.ignore(1);
				while (choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5")
				{
					system("cls");
					gotoxy(30, 12);
					cout << "**** WELCOME " << manager[i].m_fullName << " TO THE QUA MON OOP BOOKSTORE ****" << endl;
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
				manager[i].changePass();
				saveInfoManager(manager);
				repeatMenuCustomer();								// cho khop voi dong cuoi cua ham  repeatMenuCustomer
				gotoxy(30, 21);
				cout << "Enter your choice: ";
				cin >> choice;
				cin.ignore(1);
				while (choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5")
				{
					system("cls");
					gotoxy(30, 12);
					cout << "**** WELCOME " << manager[i].m_fullName << " TO THE QUA MON OOP BOOKSTORE ****" << endl;
					repeatMenuInvalidCustomer();
					gotoxy(30, 19);
					cout << "Enter your choice (1-5): ";
					cin >> choice;
					cin.ignore(1);
				}
				while (choice == "1")
				{
					system("cls");
					manager[i].printInfoOneManager();
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