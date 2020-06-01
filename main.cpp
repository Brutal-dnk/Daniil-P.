#include "header.h"
#include <iostream>
#include <iomanip>
#include <locale.h>
#include <fstream>
#include <algorithm>
#include <string.h>
#include <string>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")


using namespace std;


DWORD WINAPI ThreadFunc(LPVOID client_socket) {
	SOCKET s2 = ((SOCKET*)client_socket)[0];
	char string2[20];
	char string1[20];
	int x;
	char login[100];
	char password[100];
	char admin[20] = "admins.txt";
	char user[20] = "users.txt";
	int status = 0;
	char buf[20];
	char res[20];
	char filename[20];
	int result;
	int q;
	char qq[20];
	FILE* f;
	int pro = 0;
	char prov[10];
	Authorization client;
	Matrix mat;
	RankMethod method;
	bool signl = false;
	int r = 0;
	while (r == 0) {
		recv(s2, string2, sizeof(string2), 0);
		int flag = atoi(string2);
		switch (flag) {
		case 1: {
			int n = 0;
			while (n == 0) {
				recv(s2, buf, sizeof(buf), 0);
				int choice = atoi(buf);
				switch (choice) {
				case 1: {
					recv(s2, login, sizeof(login), 0);
					recv(s2, password, sizeof(password), 0);
					result = client.check(admin, login, password);
					itoa(result, res, 10);
					send(s2, res, 20, 0);
					if (result == 0)
						break;
					else if (result == 2)
						break;
					else if (result == -1)
						break;
					int r = 0;
					while (r == 0) {
						recv(s2, string1, sizeof(string1), 0);
						int x = atoi(string1);
						switch (x) {
						case 1: {
							memset(buf, 20, 0);
							recv(s2, buf, sizeof(buf), 0);
							int expertNum = atoi(buf);
							memset(buf, 20, 0);
							recv(s2, buf, sizeof(buf), 0);
							int factorsNum = atoi(buf);
							method.createMatrix(expertNum, factorsNum);
							for (int i = 0; i < expertNum; i++) {
								for (int j = 0; j < factorsNum; j++) {
									memset(buf, 20, 0);
									recv(s2, buf, sizeof(buf), 0);
									method.inputMatrixElem(i, j, atoi(buf));
								}
							}
							signl = true;
							break;
						}
						case 2: {
							if (signl) {
								for (int i = 0; i < method.getExpertNum(); i++) {
									for (int j = 0; j < method.getFactorsNum(); j++) {
										memset(buf, 20, 0);
										recv(s2, buf, sizeof(buf), 0);
										method.inputMatrixElem(i, j, atoi(buf));
									}
								}
							}
							break;
						}
						case 3: {
							if (signl) {
								method.countWeight();
								method.consistencyÑheck();
								string otchet;
								otchet = method.outputResultOfMethod();
								char* resOfMethod = new char[otchet.size() + 1];
								strcpy(resOfMethod, otchet.c_str());
								send(s2, resOfMethod, otchet.size() + 1, 0);
							}
							break;
						}
						case 4: {
							break;	
						}
						case 5: {
							recv(s2, filename, sizeof(filename), 0);
							ofstream fout(filename);
							if (!fout.is_open()) {
								exit(1);
							}
							fout << method.getExpertNum()<<" "<<method.getFactorsNum()<< endl;
							for (int i = 0; i < method.getExpertNum(); i++) {
								fout << endl;
								for (int j = 0; j <method.getFactorsNum(); j++) {
									fout << method.getMatrixElem(i,j) << ' ';
									if (fout.bad()) {
										//cerr << "Error while writing data!" << endl;
										exit(1);
									}
								}
							}

							fout.close();
							break;
						}
						case 6: {
							recv(s2, filename, sizeof(filename), 0);
							ifstream fin(filename);
							if (!fin.is_open()) {	
								send(s2, "0", sizeof("0"), 0);
								exit(1);
							}
							else {
								send(s2, "1", sizeof("1"), 0);
							}
							int expertNum, factorsNum;
							fin >> expertNum >> factorsNum;
							RankMethod method2;
							method2.createMatrix(expertNum,factorsNum);
							int tmp;
							for (int i = 0; i < expertNum; i++) {
								for (int j = 0; j < factorsNum; j++) {
									fin >> tmp;
									method2.inputMatrixElem(i, j, tmp);
									if (fin.bad()) {
										exit(1);
									}
								}
							}
							fin.close();
							memset(buf, 20, 0);
							itoa(expertNum, buf, 10);
							send(s2, buf, sizeof(buf), 0);
							memset(buf, 20, 0);
							itoa(factorsNum, buf, 10);
							send(s2, buf, sizeof(buf), 0);
							for (int i = 0; i < expertNum; i++) {
								for (int j = 0; j < factorsNum; j++) {
									memset(buf, 20, 0);
									itoa(method2.getMatrixElem(i,j), buf, 10);
									send(s2, buf, sizeof(buf), 0);
								}
							}
							method2.countWeight();
							method2.consistencyÑheck();
							string otchet;
							otchet=method2.outputResultOfMethod();
							char* resOfMethod = new char[otchet.size()+1];
							strcpy(resOfMethod, otchet.c_str());
							send(s2, resOfMethod, otchet.size() + 1, 0);
							break;
						}
						case 7: {
							char buffer[200];
							STO smt("STO");
							smt.readFromFile();
							recv(s2, buffer, sizeof(buffer), 0);
							string name = buffer;
							memset(buf, 20, 0);
							recv(s2, buf, sizeof(buf), 0);
							int cost = atoi(buf);
							smt.addProduct(cost, name);
							smt.writeInFile();
							smt.showProductsServ(s2);
							break;
						}
						case 8: {
							STO smt("STO");
							smt.readFromFile();
							smt.showProductsServ(s2);
							int choice;
							memset(buf, 20, 0);
							recv(s2, buf, sizeof(buf), 0);
							choice = atoi(buf);
							smt.deleteProductServ(choice);
							smt.writeInFile();
							smt.showProductsServ(s2);
							break;
						}
						case 9: {
							STO smt("STO");
							smt.readFromFile();
							smt.showProductsServ(s2);
							int choice;
							memset(buf, 20, 0);
							recv(s2, buf, sizeof(buf), 0);
							choice = atoi(buf);
							char buffer[200];
							recv(s2, buffer, sizeof(buffer), 0);
							string name = buffer;
							memset(buf, 20, 0);
							recv(s2, buf, sizeof(buf), 0);
							int cost = atoi(buf);
							smt.changeProductsServ(choice, name, cost);
							smt.writeInFile();
							smt.showProductsServ(s2);
							break;
						}
						case 10: {
							STO smt("STO");
							smt.readFromFile();
							smt.showProductsServ(s2);
							break;
						}
						case 11: {
							r = 1;
							itoa(r, res, 10);
							send(s2, res, 20, 0);
							break;
						}
						}
					}
					break;
				}
				case 2: {
					n = 1;
					itoa(n, res, 10);
					send(s2, res, 20, 0);
					break;
				}
				}
			}
			break;
		}
		case 2: {
			int n = 0;
			while (n == 0) {
				recv(s2, buf, sizeof(buf), 0);
				int choice = atoi(buf);
				switch (choice) {
				case 1: {
					recv(s2, login, sizeof(login), 0);
					recv(s2, password, sizeof(password), 0);
					result = client.check(user, login, password);
					itoa(result, res, 10);
					send(s2, res, 20, 0);
					if (result == 0)
						break;
					else if (result == 2)
						break;
					else if (result == -1)
						break;
					int r = 0;
					while (r == 0) {
						recv(s2, string1, sizeof(string1), 0);
						int x = atoi(string1);
						switch (x) {
						case 1: {
							memset(buf, 20, 0);
							recv(s2, buf, sizeof(buf), 0);
							int expertNum = atoi(buf);
							memset(buf, 20, 0);
							recv(s2, buf, sizeof(buf), 0);
							int factorsNum = atoi(buf);
							method.createMatrix(expertNum, factorsNum);
							for (int i = 0; i < expertNum; i++) {
								for (int j = 0; j < factorsNum; j++) {
									memset(buf, 20, 0);
									recv(s2, buf, sizeof(buf), 0);
									method.inputMatrixElem(i, j, atoi(buf));
								}
							}
							break;
						}
						case 2: {
							for (int i = 0; i < method.getExpertNum(); i++) {
								for (int j = 0; j < method.getFactorsNum(); j++) {
									memset(buf, 20, 0);
									recv(s2, buf, sizeof(buf), 0);
									method.inputMatrixElem(i, j, atoi(buf));
								}
							}
							break;
						}
						case 3:{
							method.countWeight();
							method.consistencyÑheck();
							string otchet;
							otchet = method.outputResultOfMethod();
							char* resOfMethod = new char[otchet.size() + 1];
							strcpy(resOfMethod, otchet.c_str());
							send(s2, resOfMethod, otchet.size() + 1, 0);
							break;
						}
						case 4: {
							break;
						}
						case 5: {
							STO smt("STO");
							smt.readFromFile();
							smt.showProductsServ(s2);
							break;
						}
						case 6: {
							r = 1;
							itoa(r, res, 10);
							send(s2, res, 20, 0);
							break;
						}
						}
					}


					break;
				}
				case 2: {
					recv(s2, login, sizeof(login), 0);
					recv(s2, password, sizeof(password), 0);
					result = client.registration(user, login, password);
					itoa(result, res, 10);
					send(s2, res, 20, 0);
					break;
				}
				case 3: {
					n = 1;
					itoa(result, res, 10);
					send(s2, res, 20, 0);
					break;
				}
				}
			}
			break;
		}
		case 3: {
			r = 1;
			itoa(r, res, 10);
			send(s2, res, 20, 0);
			return 0;
		}
		}
	}
	closesocket(s2);
	return 0;
}





void main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) { return; }
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in local_addr;
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(1280);
	local_addr.sin_addr.s_addr = 0;
	bind(s, (sockaddr*)&local_addr, sizeof(local_addr));
	int c = listen(s, 5);
	cout << "Ñåðâåð íàñòðîåí." << endl;
	cout << "Îæèäàíèå ïîäêëþ÷åíèÿ..." << endl;
	SOCKET client_socket;
	sockaddr_in client_addr;
	int client_addr_size = sizeof(client_addr);
	while ((client_socket = accept(s, (sockaddr*)&client_addr, &client_addr_size))) {
		clientNumb++;
		serverInfo();
		DWORD thID;
		CreateThread(NULL, NULL, ThreadFunc, &client_socket, NULL, &thID);
	}
}