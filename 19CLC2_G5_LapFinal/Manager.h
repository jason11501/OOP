#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "DemoBookstore3.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <Windows.h>
using namespace std;

void textcolor(int x);
void gotoxy(int x, int y);

void repeatMenuCustomer();
void repeatMenuInvalidCustomer();


class Manager
{
private:
	string m_fullName;
	string m_id;
	string m_telephoneNumber;
	string m_username;
	string m_password;
	string m_sex;
public:
	void setName(string name);
	void setId(string id);
	void setPhone(string phone);
	void setUserName(string user);
	void setPassWord(string pass);
	void setSex(string sex);


	void showMenuManager(vector<Manager>& manager);
	void createManagerAccount(vector<Manager>& manager);
	void printInfoOneManager();
	void saveInfoManager(vector<Manager> manager);
	void readInfoManager(vector<Manager>& manager);
	void signInManager(vector<Manager>& manager);

	void changePass();
};

#endif
