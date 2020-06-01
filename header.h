#pragma once
#include <winsock2.h>
#include "process.h"
#include <locale.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <conio.h>
#include <vector>
#include <string>
#include <list>
#include <iomanip>
#include <math.h>


#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

using namespace std;

int clientNumb = 0;

void serverInfo() {
	if (clientNumb) {
		cout << "Подключение..." << endl;
		cout << clientNumb << " клиент подключен." << endl;
		char tmpbuf[128];
		_tzset();
		_strtime_s(tmpbuf, 128);
		printf("Время:\t\t\t\t%s\n", tmpbuf);
		_strdate_s(tmpbuf, 128);
		printf("Дата:\t\t\t\t%s\n", tmpbuf);
	}
	else
		cout << "Нет подключенных клиентов." << endl;
}

void inputNumber(int& integer) {
	while (!(cin >> integer) || (cin.peek() != '\n'))
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "Ошибка ввода!Попробуйте еще раз." << endl;
	}

}

class Authorization {
private:
	SOCKET s2;
	char log[20];
	char pass[20];
	string Login;
	string Password;
	int status;
public:
	Authorization() { this->status = 0; }
	int registration(char*, char*, char*);
	int check(char*, char*, char*);
	int CheckAccount();
	~Authorization() {};
};



class Matrix {
private:
	int** Matr;
	int m;
	int n;

public:
	Matrix() { m = 0; n = 0; Matr = NULL; }

	Matrix(int i) : m(i), n(i) { Create(); }

	Matrix(int i, int j) : m(i), n(j) { Create(); }

	~Matrix()
	{
		for (int z = 0; z < m; z++)
			delete[] Matr[z];
	}

	void Create()
	{
		this->Matr = new int* [this->m];
		for (int z = 0; z < this->m; z++)
			Matr[z] = new int[this->n];
	}

	void Create(int m, int n)
	{
		this->m = m;
		this->n = n;
		this->Matr = new int* [m];
		for (int z = 0; z < m; z++)
			Matr[z] = new int[n];
	}

	int& Element(int i, int j)
	{
		if (i < m && j < n)
			return Matr[i][j];
		else
			cout << "Error: 1";
	}

	void Display()
	{
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cout.width(4);
				cout << Matr[i][j];
			}
			cout << endl;
		}
	}

	void inputMatrix() {
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				inputNumber(this->Element(i, j));
	}
};


class RankMethod {
private:
	Matrix matr;
	int expertNum;
	int factorsNum;
	vector<float> weightFactor;
	vector<int> summAlternatives;
	vector<float> dispersionExperts;
	vector<float> dispersionAlternatives;
public:
	RankMethod() {};

	RankMethod(int factorsNum, int expertNum) {
		this->expertNum = expertNum;
		this->factorsNum = factorsNum;
		matr.Create(factorsNum, expertNum);
	}

	~RankMethod() {}

	void countWeight() {
		summAlternatives.clear();
		weightFactor.clear();
		int sum = 0;
		for (int j = 0; j < this->factorsNum; j++) {
			sum = 0;
			for (int i = 0; i < this->expertNum; i++)
				sum += matr.Element(i, j);
			this->summAlternatives.push_back(sum);
		}
		sum = 0;
		for (vector<int>::iterator it = summAlternatives.begin(); it != this->summAlternatives.end(); it++)
			sum += *it;
		float temp;
		for (vector<int>::iterator it = summAlternatives.begin(); it != this->summAlternatives.end(); it++) {
			temp = (float)*it / sum;
			weightFactor.push_back(temp);
		}
	}

	void consistencyСheck() {
		dispersionExperts.clear();
		dispersionAlternatives.clear();
		vector<float> averageAlternatives;
		float temp;
		for (vector<int>::iterator it = summAlternatives.begin(); it != this->summAlternatives.end(); it++) {
			temp = (float)*it / this->expertNum;
			averageAlternatives.push_back(temp);
		}
		vector<float>::iterator iter = averageAlternatives.begin();
		temp = 0;
		float temp2 = 0;
		for (int i = 0; i < this->expertNum; i++) {
			temp2 = 0;
			temp = 0;
			iter = averageAlternatives.begin();
			for (int j = 0; j < this->factorsNum, iter != averageAlternatives.end(); j++) {
				temp += pow((matr.Element(i, j) - *iter), 2);
				iter++;
			}
			temp2 = (float)((float)1 / (this->expertNum - 1)) * temp;
			dispersionExperts.push_back(temp2);
		}
		//dispersionExperts.erase(dispersionExperts.begin());
		iter = averageAlternatives.begin();
		for (int j = 0; j < this->factorsNum; j++) {
			temp2 = 0;
			temp = 0;
			for (int i = 0; i < this->expertNum; i++ ) {
				temp += pow((matr.Element(i, j) - *iter), 2);
			}
			iter++;
			temp2 = (float)((float)1 / (this->expertNum - 1)) * temp;
			dispersionAlternatives.push_back(temp2);
		}
		//dispersionAlternatives.erase(dispersionAlternatives.begin());
	}

	void inputValues() {
		matr.inputMatrix();
	}

	void outputMatrix() {
		matr.Display();
	}

	void inputMatrixElem(int m, int n, int elem) {
		matr.Element(m, n) = elem;
	}

	void createMatrix(int expertNum,int factorsNum){
		this->expertNum = expertNum;
		this->factorsNum = factorsNum;
		matr.Create(expertNum,factorsNum);
	}

	int getExpertNum() { return this->expertNum; }

	int getFactorsNum() { return this->factorsNum; }

	int getMatrixElem(int m, int n) { return matr.Element(m, n); }

	string outputResultOfMethod() {
		int k,tmp;
		tmp = this->weightFactor[0];
		k = 0;
		for (int i = 0; i < this->weightFactor.size(); i++) {
			if (tmp < this->weightFactor[i]) {
				tmp = this->weightFactor[i];
				k = i;
			}
		}
		char;
		string str;
		string s;
		s = to_string(k+1);
		str = "Наиболее предпочтительной, по мнению экспертов, является альтернатива,имеющая максимальный вес. Альтернатива имеющая MAX вес - " + s+". ";
		str += "Ее вес - ";
		s = to_string(this->weightFactor[k]);
		str += s+". ";
		tmp = this->dispersionExperts[0];
		k = 0;
		for (int i = 0; i < this->dispersionExperts.size(); i++) {
			if (tmp < this->dispersionExperts[i]) {
				tmp = this->dispersionExperts[i];
				k = i;
			}
		}
		s = to_string(k+1);
		str += "Наибольшая дисперсия оценок у " + s + " эксперта, равная ";
		s = to_string(this->dispersionExperts[k]);
		str += s + ". ";
		tmp = this->dispersionAlternatives[0];
		for (int i = 0; i < this->dispersionAlternatives.size(); i++) {
			if (tmp < this->dispersionAlternatives[i]) {
				tmp = this->dispersionAlternatives[i];
				k = i;
			}
		}
		s = to_string(k+1);
		str += "Наибольшая дисперсия оценок у " + s + " альтернативы, равная ";
		s = to_string(this->dispersionAlternatives[k]);
		str += s + ".";
		return str;
	}
};

class Product {
	string name;
	float cost;
public:
	void setName();
	void setName(string name);
	string getName();
	void setCost();
	void setCost(float cost);
	float getCost();
	Product();
	Product(string name, float cost);

	friend ostream& operator<<(ostream& os, const Product& product);
	friend istream& operator>>(istream& is, Product& product);
};


class STO {
	string name;
	vector<Product> product;
public:
	STO() {};
	STO(string name);
	~STO() {};
	void setName();
	void setName(string name);
	void showProducts();
	void addProduct();
	void addProduct(float cost,string name);
	void changeProducts();
	void writeInFile();
	void readFromFile();
	void searchProduct();
	void deleteProduct();
	void STO::showProductsServ(const SOCKET &sock);
	void deleteProductServ(int choice);
	void changeProductsServ(int choice, string name, float cost);

	friend ostream& operator<<(ostream& os, const STO& product);
};

STO::STO(string name) {
	this->name = name;
}

void STO::setName() { cin >> this->name; }

void STO::setName(string name) { this->name = name; }

void STO::showProducts() {
	int i = 0;
	for (vector<Product>::iterator it = product.begin(); it != product.end(); ++it, ++i) {
		//for (int i = 0; i < product.size(); ++i) {
		cout << setw(4) << left << i + 1 << setw(70) << it->getName() << setw(6) << it->getCost() << "руб." << endl;
	}
}

void STO::showProductsServ(const SOCKET& sock) {
	char buffer[100];
	sprintf_s(buffer, "%d", product.size());
	send(sock, buffer, sizeof(buffer), 0);
	string name;
	for (vector<Product>::iterator it = product.begin(); it != product.end(); ++it) {
		name = it->getName();
		strcpy(buffer, name.c_str());
		send(sock, buffer, sizeof(buffer), 0);
		int numb = it->getCost();
		sprintf_s(buffer, "%d", numb);
		send(sock, buffer, sizeof(buffer), 0);
	}
}

void STO::addProduct() {
	Product temp;
	temp.setName();
	temp.setCost();
	product.push_back(temp);
}

void STO::addProduct(float cost, string name) {
	Product temp;
	temp.setName(name);
	temp.setCost(cost);
	product.push_back(temp);
}

void STO::writeInFile() {
	string nameOfFile = this->name + ".txt";
	ofstream ofs(nameOfFile, ios::out);
	if (ofs.is_open()) {
		cout << "Файл " << nameOfFile << " открыт" << endl;
		for (vector<Product>::iterator it = product.begin(); it != product.end(); ++it) {
			ofs << *it;
		}
		ofs.close();
	}
	else {
		cout << "Ошибка открытия файла " << this->name << endl;
	}
}

void STO::readFromFile() {
	string nameOfFile = this->name + ".txt";
	ifstream ifs(nameOfFile, ios::in);
	if (ifs.is_open()) {
		cout << "Файл " << nameOfFile << " открыт" << endl;
		while (!ifs.eof()) {
			Product temp;
			ifs >> temp;
			product.push_back(temp);
		}
		product.pop_back();
		ifs.close();
	}
	else {
		cout << "Ошибка открытия файла.Создан новый файл." << this->name << endl;
		ofstream oFile(nameOfFile);
	}
}

void STO::searchProduct() {
	system("cls");
	cout << "1 - Поиск по названию" << endl;
	cout << "2 - По цене" << endl;
	cout << "3 - Выход" << endl;
	switch (_getch()) {
	case '1': {
		system("cls");
		string name;
		cout << "Введите название модели: ";
		getline(cin, name);
		int i = 0;
		for (vector<Product>::iterator it = product.begin(); it != product.end(); ++it, ++i) {
			if (name == it->getName())
				cout << setw(4) << left << i + 1 << setw(70) << it->getName() << setw(30) << it->getCost() << "руб." << endl;
		}
		_getch();
		break;
	}
	case '2': {
		system("cls");
		int min, max;
		cout << "Введите ценовой диапазон." << endl << "От :";
		inputNumber(min);
		cout << "До :";
		inputNumber(max);
		int i = 0;
		for (vector<Product>::iterator it = product.begin(); it != product.end(); ++it, ++i) {
			if (it->getCost() > min&& it->getCost() < max)
				cout << setw(4) << left << i + 1 << setw(70) << it->getName() << setw(30) << it->getCost() << "руб." << endl;
		}
		_getch();
		break;
	}
	case '3': {
		system("cls");
		break;
	}
	default:
		cout << "Нет такого пункта." << endl;
	}
}

void STO::changeProducts() {
	this->showProducts();
	cout << "Какой товар изменить?" << endl;
	int numberOfProduct;
	int ck = 0;
	do {
		cout << "Введите номер :";
		inputNumber(numberOfProduct);
		if (numberOfProduct > this->product.size() || numberOfProduct <= 0) {
			cout << "Нет такого товара" << endl;
		}
		else
			ck = 1;
	} while (ck != 1);
	system("cls");
	cout << "1 - Изменить имя" << endl;
	cout << "2 - Изменить цену" << endl;
	cout << "3 - Выход" << endl;
	switch (_getch()) {
	case '1': {
		system("cls");
		product[numberOfProduct - 1].setName();
		_getch();
		break;
	}
	case '2': {
		system("cls");
		product[numberOfProduct - 1].setCost();
		_getch();
		break;
	}
	case '3': {
		system("cls");
		break;
	}
	default:
		cout << "Нет такого пункта." << endl;
	}
}

void STO::changeProductsServ(int choice, string name,float cost) {
		product[choice - 1].setName(name);
		product[choice - 1].setCost(cost);
}

void STO::deleteProductServ(int choice) {
	this->showProducts();
	choice--;
	product.erase(product.begin() + choice);
}

void STO::deleteProduct() {
	this->showProducts();
	cout << "Какой товар убрать?" << endl;
	int choice;
	cin >> choice;
	choice--;
	product.erase(product.begin() + choice);
}

ostream& operator<<(ostream& os, const STO& station) {
	os << station.name << endl;
	return os;
}



void Product::setName() {
	//std::cin.clear();
	std::cin.ignore();
	getline(cin, this->name, '\n');
}

void Product::setName(string name) { this->name = name; }

string Product::getName() { return this->name; }

void Product::setCost() { cin >> this->cost; }

void Product::setCost(float cost) { this->cost = cost; }

float Product::getCost() { return this->cost; }

Product::Product() { this->name = ""; this->cost = 0; }

Product::Product(string name, float cost) { this->cost = cost; this->name = name; }

ostream& operator<<(ostream& os, const Product& product) {
	os << product.name << endl << product.cost << endl;
	return os;
}

istream& operator>>(istream& is, Product& product) {
	string temp;
	getline(is, product.name);
	is >> product.cost;
	getline(is, temp);
	return is;
}



class Exception : public exception {
protected:
	int numbEr;
public:
	Exception();
	Exception(int);
	int show();
	~Exception();
};

Exception::Exception() {
	numbEr = 0;
}

Exception::Exception(int k) {
	numbEr = k;
}

int Exception::show() {
	if (numbEr == 1)
		return 2;
}

Exception::~Exception() {}


int Authorization::check(char* s, char* login, char* password) throw(Exception) {
	int tmp = 0;
	int result = 0;
	char res[20];
	ifstream fin(s, ios_base::in);
	if (!fin) {
		result = -1;
	}
	else {
		try {
			flushall();
			for (int i = 0; login[i]; i++) {
				if ((login[i] < 'a' || login[i] > 'z') && (login[i] < 'а' || login[i] > 'я'))
					throw Exception(1);
			}
		}
		catch (Exception ob) {
			cin.clear();
			result = ob.show();
		}
	}
	if (fin) {
		while (!fin.eof()) {
			fin >> this->log;
			fin >> this->pass;
			for (unsigned i = 0; pass[i]; i++)
				if (strcmp(login, log) == 0 && strcmp(password, pass) == 0) {
					result = 1;
				}
		}
		fin.close();
	}
	return result;
}

int Authorization::registration(char* s, char* login, char* password) {
	int tm = 0;
	int r = 0;
	char t[20];
	ofstream fout(s, ios_base::app);
	ifstream fin(s, ios_base::in);
	if (!fout.is_open()) {
		r = -1;
	}
	else {
		try {
			flushall();
			for (int i = 0; login[i]; i++) {
				if ((login[i] < 'a' || login[i] > 'z') && (login[i] < 'A' || login[i] > 'Z'))
					throw Exception(1);
			}
		}
		catch (Exception ob) {
			cin.clear();
			r = ob.show();
		}
	}
	for (unsigned i = 0; login[i]; i++)
		strcpy(log, login);
	while (!fin.eof()) {
		fin >> login;
		if (strcmp(login, log) == 0) {
			r = 1;
			fin.close();
		}
	}
	if (r == 0) {
		strcpy(pass, password);
		fout << log << endl;
		fout << pass << endl;
		fout.close();
	}
	return r;
}





