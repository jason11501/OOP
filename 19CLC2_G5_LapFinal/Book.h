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
using namespace std;

struct BmpSignature
{
	unsigned char data[2];
};


struct BmpHeader
{
	BmpSignature signature;
	int32_t fileSize;
	int16_t reverse1;
	int16_t reverse2;
	int32_t dataOffset;
};

struct BmpDib
{
	uint32_t Dibsize;
	int32_t imageWidth;
	int32_t imageHeight;
	uint16_t colorPlaneCount;
	uint16_t PixelSize;
	uint32_t compressMethod;
	uint32_t bitmapByteCount;
	int32_t horizontalResolution;
	int32_t verticalResolution;
	uint32_t colorCount;
	uint32_t importantColorCount;
};

struct Color
{
	unsigned char blue;
	unsigned char green;
	unsigned char red;
};

struct  ColorTable
{
	Color* colors;
	uint32_t length;
};

struct PixelArray
{
	unsigned char* rawBytes;
	int rawByteSize;
	int lineSize;
	char paddingSize;

	Color** pixels;
	uint32_t rowCount;
	uint32_t columnCount;
};

struct BmpFile
{
	BmpHeader header;
	BmpDib Dib;
	ColorTable colorTable1;
	PixelArray pixelArray1;
};

bool isBmpFile(FILE* f);


void readBmpHeader(FILE* f, BmpFile& bmp);
void readBmpDib(FILE* f, BmpFile& bmp);

void printBmpHeader(const BmpFile& bmp);


void printBmpDib(const BmpFile& bmp);


void initPixels(PixelArray& pa, int width, int height);


void readBmpPixelArray(FILE* f, BmpFile& bmp);


void drawBmp(const BmpFile& bmp);

void releaseBmPixelArray(BmpFile& bmp);

void changeBmp(PixelArray& p);

void printRGB(FILE* f, BmpFile& bmp);

void textcolor(int x);
void gotoxy(int x, int y);
void resizeConsole(int width, int height);


class Book
{
private:
	string m_ID;
	string m_name;
	string m_author;
	string m_type;
	string m_publishYear;
	string m_numSell;
	string m_numBorrow;
	string m_price;
public:
	void readBorrowFileCSV(vector<Book>& book);
	void printInfoBorrowFileCSV(vector<Book> book);
	void printID();
	void printName();
	void printAuthor();
	void printType();
	void printPublishYear();
	void printNumSell();
	void printNumBorrow();
	void printPrice();
};

void repeatMenuCustomer();
void repeatMenuInvalidCustomer();

void repeatMenuManager();
void repeatMenuInvalidManager();


class Manager;

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


	void showMenu(vector<Customer>& customer, vector<Manager>& manager);


	void showMenuReader(vector<Customer>& customer);
	void createCustomerAccount(vector<Customer>& Customer);
	void printInfoOneCustomer();
	void saveInfoCustomer(vector<Customer> Customer);
	void readInfoCustomer(vector<Customer>& Customer);
	void signInCustom(vector<Customer>& customer);

	void changePass();
};


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
