#include "Book.h"

int main()
{
	resizeConsole(2000, 2000);
	

	vector<Customer> customer;
	vector<Manager> manager;
	Customer custom;
	textcolor(4);
	//custom.showMenu(customer, manager);
	Manager m;
	m.signInManager(manager);
	return 0;
}