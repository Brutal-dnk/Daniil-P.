#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

using namespace std;

void inputNumber(int& integer) {
	while (!(cin >> integer) || (cin.peek() != '\n'))
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "Ошибка ввода!Попробуйте еще раз." << endl;
	}

}

class Authorization {
public:
	string login;
	string password;
public:
	Authorization() {}

	void inputLogin() { cin >> this->login; }

	void inputPass() { cin >> this->password; }

	string getLogin() { return this->login; }

	string getPass() { return this->password; }

	int RegistAdmin();

	int RegistUser();

	int AuthorAdmin();

	int AuthorUser();

	~Authorization() {}
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

	~Matrix() {}

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
		if (i <= m && j <= n)
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

	int getM() { return this->m; }

	int getN() { return this->n; }
};


void printmatr(Matrix mat) {
	std::cout << "Матрица :" << std::endl;
	char k = 'A';
	cout << setfill('_') << setw(10) << "_" << setw(mat.getN() * 7 - 1) << "_" << endl;
	cout << setw(10) << setfill(' ') << "|" << setw(mat.getN() * 7) << "Альтернативы |" << endl;
	cout << setw(10) << "Эксперты |" << setw(mat.getN() * 7) << setfill('-') << "|" << endl;
	cout << setw(10) << setfill(' ') << "|";
	for (int i = 0; i < mat.getN(); i++)
		cout << setw(6) << i + 1 << "|";
	cout << endl << setfill('-') << setw(10) << "|" << setw(mat.getN() * 7) << "|" << setfill(' ') << endl;
	for (int i = 0; i < mat.getM(); i++) {
		cout << setw(9) << k << "|"; k += 1;
		for (int j = 0; j < mat.getN(); j++) {
			std::cout << std::setw(6) << mat.Element(i, j) << "|";
		}
		cout << endl << setfill('-') << setw(10) << "|" << setw(mat.getN() * 7) << "|" << setfill(' ') << endl;
	}
	_getch();
}

template <class T>
class Chek {
public:
	T input();
};

template<>
class Chek<int> {
public:
	void inputNumber(int& integer) {
		while (!(cin >> integer) || (cin.peek() != '\n'))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "Ошибка ввода!Попробуйте еще раз." << endl;
		}
	}
};

template<>
class Chek<string> {
public:
	string input() {
		string str;
		const char* p;
		int s = 1;
		while (s != 0) {
			s = 0;
			cin >> str;
			p = str.c_str();
			if ((int)p[0] > -65 && (int)p[0] < -32) {
				for (int i = 1; i < str.size() && s != 1; i++) {
					if ((int)p[i]<0 && (int)p[i] > -65 || (int)p[i] == 45)
						s = 0;
					else {
						s = 1;
						cout << "Возможно вы ввели запрещенный символ. Попробуйте еще раз.(раскладка клавиатуры русская)" << endl;
					}
				}
			}
			else {
				cout << "Первая буква в фамилии, отчестве, имени - заглавная!(раскладка клавиатуры русская)" << endl;
				s = 1;
			}
		}
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
	void getInfo();
	Product();
	Product(string name, float cost);

	friend ostream& operator<<(ostream& os, const Product& product);
	friend istream& operator>>(istream& is, Product& product);
};

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

void Product::getInfo() {
	vector<Product> product;
	string nameOfFile = "STO.txt";
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
	int i = 0;
	for (vector<Product>::iterator it = product.begin(); it != product.end(); ++it, ++i) {
		//for (int i = 0; i < product.size(); ++i) {
		cout << setw(4) << left << i + 1 << setw(70) << it->getName() << setw(6) << it->getCost() << "руб." << endl;
	}
}

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

void getServices(const SOCKET &sock) {
	char stroka[100];
	recv(sock, stroka, sizeof(stroka), 0);
	int size = atoi(stroka);
	Product* mass = new Product[size + 1];
	string name;
	int cost;
	for (int i = 0; i < size; ++i) {
		recv(sock, stroka, sizeof(stroka), 0);
		name = stroka;
		mass[i].setName(name);
		recv(sock, stroka, sizeof(stroka), 0);
		cost = atoi(stroka);
		mass[i].setCost(cost);
	}
	for (int i = 0; i < size; ++i) {
		cout << setw(4) << left << i + 1 << setw(70) << mass[i].getName() << setw(6) << mass[i].getCost() << "руб." << endl;
	}
	delete[] mass;
}