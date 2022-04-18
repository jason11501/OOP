#include "Book.h"

void Demo() {
	resizeConsole(2000, 2000);
	introduction();
	ListAccount demo;
	is_open();
	Menu menu;
	menu.startMenu();
	string choice;
	getline(cin, choice);
	while (choice != "1" && choice != "2")
	{
		system("cls");
		menu.startMenu();
		getline(cin, choice);
	}
	if (choice == "1")
	{
		system("cls");
		string username = "", password = "";
		cout << "Enter username: ";
		getline(cin, username);
		cout << "Enter password: ";
		password = Account::inputPassword();

		int per;
		per = demo.login(username, password);
		Account user = demo.findAccount(username);

		if (per == 1) //Manager
		{
			Manager m(username);
			m.loadInfo();
			bool temp = true;
			while ((temp)) {
				menu.repeatMenuManager();
				cout << "Enter your choice: ";
				getline(cin, choice);
				int t = stoi(choice);
				switch (t)
				{
				case 1: {
					m.printInfo();
					system("pause");
					system("cls");
					break;
				}
				case 2: {
					m.chagePassword(user);
					system("cls");
					break;
				}
				case 3: {
					Bookshelf bk;
					bk.loadAllBook();
					bk.Add_Book();
					bk.saveAllBook();
					system("pause");
					system("cls");
					break;
				}
				case 4: {
					Bookshelf bk;
					bk.loadAllBook();
					bk.Delete_Book();
					bk.saveAllBook();
					system("pause");
					system("cls");
					break;
				}
				case 5: {
					Bookshelf bk;
					bk.loadAllBook();
					bk.Edit_Book();
					bk.saveAllBook();
					system("pause");
					system("cls");
					break;
				}
				case 6: {
					m.addACustomer();
					system("pause");
					system("cls");
					break;
				}
				case 7: {
					m.deleteACustomer();
					system("cls");
					break;
				}
				case 8: {
					system("cls");
					Demo();
					return;
				}
				default:
					temp = false;
					system("cls");
					is_open();
					menu.startMenu();
					getline(cin, choice);
					break;
				}
			}
		}
		else if (per == 2) // Customer
		{
			//int** arr=NULL;
			srand(time(NULL));
			Customer c(username);
			c.loadInfo();
			bool temp = true;
			while (temp) {
				menu.repeatMenuCustomer();
				cout << " Enter your choice: ";
				getline(cin, choice);
				int t = stoi(choice);
				switch (t)
				{
				case 1: {
					c.printInfo();
					system("pause");
					system("cls");
					break;
				}
				case 2: {
					c.changePassword(user);
					cout << "Changing password successfully!" << endl;
					system("pause");
					system("cls");
					break;
				}
				case 3: {
					c.buyABook();
					system("cls");
					break;
				}
				case 4: {
					c.viewBuyingHistory();
					system("cls");
					break;
				}
				case 5:
				{
					Seat seat;
					seat.checkAllSeats();
					//showingSeat(arr);
					system("pause");
					system("cls");
					//deleteSeat(arr,10,10);
					break;
				}
				case 6: {
					system("cls");
					Demo();
				}
				default:
					temp = false;
					system("cls");
					is_open();
					menu.startMenu();
					getline(cin, choice);
					break;
				}
			
			}
		}
		else {
			cout << "Login failed!!\n";
			system("pause");
			system("cls");
			Demo();
		}
	}
	while (choice == "2")
	{
		system("cls");
		cout << "BYE!\n";
		return;
	}
}

int main()
{
	Demo();
	return 0;
}