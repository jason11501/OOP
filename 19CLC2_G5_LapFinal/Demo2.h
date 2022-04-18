#ifndef _DEMO2_H_
#define _DEMO2_H_

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <Windows.h>
using namespace std;

void textcolor(int x);
void gotoxy(int x, int y);


void showMenuManager();

class Customer
{
private:
	string m_fullName;
	string m_id;
	string m_telephoneNumber;
	string m_username;
	string m_password;
	string m_sex;
	string m_dateCreateAccount;
	string m_dateBorrow;
	string m_dateReturn;
public:
	void setName(string name);
	void setId(string id);
	void setPhone(string phone);
	void setUserName(string user);
	void setPassWord(string pass);
	void setSex(string sex);


	void showMenu(vector<Customer>& customer);
	void showMenuReader(vector<Customer>& customer);
	void createCustomerAccount(vector<Customer>& Customer);
	void printInfoOneCustomer();
	void saveInfoCustomer(vector<Customer> Customer);
	void readInfoCustomer(vector<Customer>& Customer);
	void signInCustom(vector<Customer>& customer);
};

#endif
