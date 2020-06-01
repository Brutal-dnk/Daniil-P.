#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <iomanip>
#include <string>
#include "header.h"
#include <limits>

using namespace std;

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) { return; }

	while (true)
	{
		SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
		sockaddr_in dest_addr;
		dest_addr.sin_family = AF_INET;
		dest_addr.sin_port = htons(1280);
		dest_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
		if (connect(s, (sockaddr*)&dest_addr, sizeof(dest_addr)) == NULL) {
			cout << "����������..........." << endl << endl;
			cout << "����������� � ������� ������ �������." << endl << endl;
			cout << "������� ������� ��� �����������." << endl;
			_getch();
			system("cls");
		}
		else {
			cout << "����������� � ������� �� ������� :( ..." << endl;
			exit(-1);
		}
		char strinG[20];
		char buf[20];
		char buf1[20];
		char name[20];
		Chek<int> vv;
		Authorization client;
		Matrix mat;
		bool signl = false;
		char res[20];
		int result;
		int choice = 0;

		while (1)
		{
			cout << "1. �������������" << endl;
			cout << "2. ������������" << endl;
			cout << "3. ���������� ������" << endl;
			cout << endl;
			int flag;
			vv.inputNumber(flag);
			itoa(flag, strinG, 10);
			send(s, strinG, 20, 0);
			switch (flag)
			{
			case 1:
			{
				system("cls");
				int t = 0;
				while (t == 0)
				{
					cout << "1.  ���������� ������\n";
					cout << "2.  ����� \n";
					vv.inputNumber(choice);
					itoa(choice, buf, 10);
					send(s, buf, 20, 0);
					switch (choice)
					{
					case 1:
					{
						system("cls");
						cout << "������� ����� ��������������: " << endl;
						client.inputLogin();
						string temp = client.getLogin();
						char* tmp = new char[temp.size() + 1];
						strcpy(tmp, temp.c_str());
						send(s, tmp, temp.size() + 1, 0);
						cout << "������� ������ ��������������: " << endl;
						client.inputPass();
						temp = client.getPass();
						strcpy(tmp, temp.c_str());
						send(s, tmp, temp.size() + 1, 0);
						if (recv(s, res, sizeof(res), 0) != 0)
						{
							result = atoi(res);
							if (result == 1)
							{
								system("cls");
								int u = 0;
								while (u == 0)
								{
									cout << "\t���� ������:\n" << endl;
									cout << "1. ������ ������ ���������" << endl;
									cout << "2. ������������� ��������� ��������" << endl;
									cout << "3. ��������� �������� ������ ������" << endl;
									cout << "4. ������� ������� ���������� ������" << endl;
									cout << "5. �������� ������� � �����" << endl;
									cout << "6. ���������� ������� ������ �� ������" << endl;
									cout << "7. �������� ������ �� ���" << endl;
									cout << "8. ������� ������ ���" << endl;
									cout << "9. �������� ������ ���" << endl;
									cout << "10. ����� ����� ���" << endl;
									cout << "11. �����\n\n" << endl;
									int x;
									vv.inputNumber(x);
									itoa(x, buf1, 10);
									send(s, buf1, 20, 0);
									switch (x) {
									case 1: {
										system("cls");
										cout << "������� ���������� ���������:" << endl;
										fflush(stdin);
										int expertNum;
										vv.inputNumber(expertNum);
										memset(buf, 20, 0);
										itoa(expertNum, buf, 10);
										send(s, buf, 10, 0);
										cout << "������� ���������� ��������(�����������):" << endl;
										int factorsNum;
										vv.inputNumber(factorsNum);
										memset(buf, 20, 0);
										itoa(factorsNum, buf, 10);
										send(s, buf, 10, 0);
										mat.Create(expertNum, factorsNum);
										cout << "������� ��������" << endl;
										for (int i = 0; i < expertNum; i++) {
											cout << "������� � " << i + 1 << endl;
											for (int j = 0; j < factorsNum; j++) {
												cout << "������ ������������ � " << j + 1 << ':';
												vv.inputNumber(mat.Element(i, j));

											}
										}
										signl = true;
										for (int i = 0; i < expertNum; i++)
											for (int j = 0; j < factorsNum; j++) {
												memset(buf, 20, 0);
												itoa(mat.Element(i, j), buf, 10);
												send(s, buf, sizeof(buf), 0);
											}
										_getch();
										system("cls");
										break;
									}
									case 2: {
										system("cls");
										if (!signl) {
											cout << "�� �� ����� �������";
											_getch();
										}
										else {
											cout << "������� ��������" << endl;
											for (int i = 0; i < mat.getM(); i++) {
												cout << "������� � " << i + 1 << endl;
												for (int j = 0; j < mat.getN(); j++) {
													cout << "������ ������������ � " << j + 1 << ':';
													vv.inputNumber(mat.Element(i, j));

												}
											}
											for (int i = 0; i < mat.getM(); i++)
												for (int j = 0; j < mat.getN(); j++) {
													memset(buf, 20, 0);
													itoa(mat.Element(i, j), buf, 10);
													send(s, buf, sizeof(buf), 0);
												}
											_getch();
										}
										system("cls");
										break;
									}
									case 3: {
										system("cls");
										if (!signl) {
											cout << "�� �� ����� �������";
											_getch();
										}
										else {
											char longstr[1024];
											recv(s, longstr, sizeof(longstr), 0);
											cout << longstr;
											_getch();
										}
										system("cls");
										break;
									}
									case 4: {
										system("cls");
										printmatr(mat);
										system("cls");
										break;
									}
									case 5: {
										system("cls");
										cout << "������� �������� ����� � ������� <<name.txt>>: ";
										cin >> name;
										send(s, name, sizeof(name), 0);
										_getch();
										system("cls");
										break;
									}
									case 6: {
										system("cls");
										char longstr[1024];
										while (true) {
											cout << "������� �������� ����� � ������� <<name.txt>>: ";
											cin >> name;
											send(s, name, sizeof(name), 0);
											recv(s, name, sizeof(name), 0);
											if (strcmp(name, "0") == 0) {
												cout << "���� � ����� ������ �� ����������" << endl;
											}
											else break;
										}
										memset(buf, 20, 0);
										recv(s, buf, sizeof(buf), 0);
										int expertNum = atoi(buf);
										memset(buf, 20, 0);
										recv(s, buf, sizeof(buf), 0);
										int factorsNum = atoi(buf);
										Matrix sec(expertNum, factorsNum);
										for (int i = 0; i < expertNum; i++)
										{
											for (int j = 0; j < factorsNum; j++)
											{
												memset(buf, 20, 0);
												recv(s, buf, sizeof(buf), 0);
												sec.Element(i, j) = atoi(buf);
											}
											cout << endl;
										}
										printmatr(sec);
										recv(s, longstr, sizeof(longstr), 0);
										cout << longstr;
										_getch();
										system("cls");
										break;
									}
									case 7: {
										system("cls");
										string name;
										int cost;
										cin.ignore(cin.rdbuf()->in_avail());
										cout << "������� �������� ������:";
										getline(cin, name, '\n');
										char* buffer = new char[name.size() + 1];
										strcpy(buffer, name.c_str());
										send(s, buffer, name.size() + 1, 0);
										delete[] buffer;
										cout << "������� ����:";
										vv.inputNumber(cost);
										memset(buf, 20, 0);
										itoa(cost, buf, 10);
										send(s, buf, sizeof(buf), 0);
										cout << endl << endl;
										getServices(s);
										_getch();
										system("cls");
										break;
									}
									case 8: {
										system("cls");
										int choice;
										getServices(s);
										cout << endl << "����� ������ �������?" << endl;
										vv.inputNumber(choice);
										memset(buf, 20, 0);
										itoa(choice, buf, 10);
										send(s, buf, sizeof(buf), 0);
										system("cls");
										getServices(s);
										_getch();
										system("cls");
										break;
									}
									case 9: {
										system("cls");
										getServices(s);
										int choice;
										cout << endl << "����� ������ ��������?" << endl;
										cout << "������� �����:" << endl;
										vv.inputNumber(choice);
										memset(buf, 20, 0);
										itoa(choice, buf, 10);
										send(s, buf, sizeof(buf), 0);
										string name;
										int cost;
										cout << "�������� ������:";
										cin.ignore(cin.rdbuf()->in_avail());
										getline(cin, name, '\n');
										char* buffer = new char[name.size() + 1];
										strcpy(buffer, name.c_str());
										send(s, buffer, name.size() + 1, 0);
										delete[] buffer;
										cout << "��������� ������:";
										vv.inputNumber(cost);
										memset(buf, 20, 0);
										itoa(cost, buf, 10);
										send(s, buf, sizeof(buf), 0);
										system("cls");
										getServices(s);
										_getch();
										system("cls");
										break;
									}
									case 10: {
										system("cls");
										getServices(s);
										_getch();
										system("cls");
										break;
									}
									case 11: {
										recv(s, res, sizeof(res), 0);
										u = atoi(res);
										break;
									}
									}
								}
							}
							else if (result == 2)
								cout << "����� ������ �������� ������ �� �������� ����." << endl;
							else
								cout << "�������� ����." << endl;
						}
						_getch();
						system("cls");
						break;
					}
					case 2:
						recv(s, res, sizeof(res), 0);
						t = atoi(res);
						break;
					default:
						system("cls");
						cout << "��������� ����." << endl;
						_getch();
					}
				}
				system("cls");
				break;
			}
			case 2: {
				system("cls");
				int t = 0;
				while (t == 0) {
					cout << "1.  ����\n";
					cout << "2.  ����������� \n";
					cout << "3.  ����� \n";
					cin >> choice;
					itoa(choice, buf, 10);
					send(s, buf, 20, 0);
					switch (choice) {
					case 1: {
						system("cls");
						cout << "������� �����: " << endl;
						client.inputLogin();
						string temp = client.getLogin();
						char* tmp = new char[temp.size() + 1];
						strcpy(tmp, temp.c_str());
						send(s, tmp, temp.size() + 1, 0);
						cout << "������� ������: " << endl;
						client.inputPass();
						temp = client.getPass();
						strcpy(tmp, temp.c_str());
						send(s, tmp, temp.size() + 1, 0);
						if (recv(s, res, sizeof(res), 0) != 0) {
							result = atoi(res);
							if (result == 1) {
								system("cls");
								int u = 0;
								while (u == 0) {
									cout << "\t���� ������������:\n" << endl;
									cout << "1. ������ ������� ������������� ����������" << endl;
									cout << "2. ������������� ��������� ��������" << endl;
									cout << "3. ��������� �������� ������ ������" << endl;
									cout << "4. ������� ������� �������������" << endl;
									cout << "5. ����� ����� ���" << endl;
									cout << "6. �����\n\n" << endl;
									int x;
									vv.inputNumber(x);
									itoa(x, buf1, 10);
									send(s, buf1, 20, 0);
									switch (x) {
									case 1:
										system("cls");
										cout << "������� ���������� ���������:" << endl;
										fflush(stdin);
										int expertNum;
										vv.inputNumber(expertNum);
										memset(buf, 20, 0);
										itoa(expertNum, buf, 10);
										send(s, buf, 10, 0);
										cout << "������� ���������� ��������(�����������):" << endl;
										int factorsNum;
										vv.inputNumber(factorsNum);
										memset(buf, 20, 0);
										itoa(factorsNum, buf, 10);
										send(s, buf, 10, 0);
										mat.Create(expertNum, factorsNum);
										cout << "������� ��������" << endl;
										for (int i = 0; i < expertNum; i++) {
											cout << "������� � " << i + 1 << endl;
											for (int j = 0; j < factorsNum; j++) {
												cout << "������ ������������ � " << j + 1 << ':';
												vv.inputNumber(mat.Element(i, j));

											}
										}
										signl = true;
										for (int i = 0; i < expertNum; i++)
											for (int j = 0; j < factorsNum; j++) {
												memset(buf, 20, 0);
												itoa(mat.Element(i, j), buf, 10);
												send(s, buf, sizeof(buf), 0);
											}
										_getch();
										system("cls");
										break;
									case 2:
										system("cls");
										if (!signl) {
											cout << "�� �� ����� �������";
											_getch();
										}
										else {
											cout << "������� ����� ��������, ������ �������� �� ������ ��������: ";
											int num;
											vv.inputNumber(num);
											cout << "������� ����� ��������. " << endl;
											for (int j = 0; j < mat.getN(); j++) {
												cout << "������ ������������ � " << j + 1 << ':';
												vv.inputNumber(mat.Element(num, j));
												cout << endl;
											}
											for (int i = 0; i < mat.getM(); i++)
												for (int j = 0; j < mat.getN(); j++) {
													memset(buf, 20, 0);
													itoa(mat.Element(i, j), buf, 10);
													send(s, buf, sizeof(buf), 0);
												}
											_getch();
										}
										system("cls");
										break;
									case 3:
										system("cls");
										if (!signl) {
											cout << "�� �� ����� �������";
											_getch();
										}
										else {
											char longstr[1024];
											recv(s, longstr, sizeof(longstr), 0);
											cout << longstr;
											_getch();
										}
										system("cls");
										break;
									case 4: {
										system("cls");
										printmatr(mat);
										system("cls");
										break;
									}
									case 5: {
										system("cls"); char stroka[100];
										recv(s, stroka, sizeof(stroka), 0);
										int size = atoi(stroka);
										Product* mass = new Product[size + 1];
										string name;
										int cost;
										for (int i = 0; i < size; ++i) {
											recv(s, stroka, sizeof(stroka), 0);
											name = stroka;
											mass[i].setName(name);
											recv(s, stroka, sizeof(stroka), 0);
											cost = atoi(stroka);
											mass[i].setCost(cost);
										}
										for (int i = 0; i < size; ++i) {
											cout << setw(4) << left << i + 1 << setw(70) << mass[i].getName() << setw(6) << mass[i].getCost() << "���." << endl;
										}
										delete[] mass;
										_getch();
										system("cls");
										break;
									}
									case 6: {
										recv(s, res, sizeof(res), 0);
										u = atoi(res);
										break;
									}
									}
								}
							}
							else if (result == 0)
								cout << "�������! ��������� ����!." << endl;
							else if (result == 2)
								cout << "����� ������ �������� ������ �� �������� ����." << endl;
							else if (result == -1)
								cout << "��� ������������������ �������������." << endl;

						}
						_getch();
						system("cls");
						break;
					}
					case 2: {
						system("cls");
						cout << "������� �����: " << endl;
						client.inputLogin();
						string temp = client.getLogin();
						char* tmp = new char[temp.size() + 1];
						strcpy(tmp, temp.c_str());
						send(s, tmp, temp.size() + 1, 0);
						cout << "������� ������: " << endl;
						client.inputPass();
						temp = client.getPass();
						strcpy(tmp, temp.c_str());
						send(s, tmp, temp.size() + 1, 0);
						if (recv(s, res, sizeof(res), 0) != 0) {
							result = atoi(res);
							if (result == 0) {
								cout << "����������� ������ �������." << endl;
							}
							else if (result == 1)
								cout << "����� ����� ��� ������������." << endl;
							else if (result == 2)
								cout << "����� ������ �������� ������ �� �������� ����." << endl;
						}
						_getch();
						system("cls");
						break;
					}
					case 3:
						recv(s, res, sizeof(res), 0);
						t = atoi(res);
						break;
					default:
						system("cls");
						cout << "�������� ����. ������� ������ �����\n";
						system("pause");
					}
				}
				system("cls");
				break;
			}
			case 3:
				return;
			default:
				cout << "�������� �����" << endl;
				break;
			}
		}
		closesocket(s);
	}
	WSACleanup();
}
