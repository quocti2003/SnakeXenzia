#pragma once
#include<string>
#include<fstream>
#include <iostream>
#include "mylib.h"
#include <thread>
#include<iomanip>
#include <mutex>
#include <cctype>
#include <Windows.h>
#define max 1840
int sdot = 4; // số đốt ban đầu
int Prank[100];
int* toadox = new int[max];
int* toadoy = new int[max];
int direct = -1;
int xqua, yqua;
char Pname[6]; 
int game_mode;
int map_choice;
int snake_head;
int snake_color;
bool game_over = false;
int xdan, ydan;
int xdancu, ydancu;
int i = 0;
int hours = 0; 
int mins = 0; 
int secs = 0;
int diem = 0;
int xvc[100]; 
int yvc[100];
int xvcd; 
int yvcd;
int menu_choice;
using namespace std;
mutex m;
// ====== NGUYEN MAU HAM ======
void ve_tuong(int xleft, int xright, int ytop, int ybot);
void play();
void tao_ran();
void ve_ran();
void xu_ly_ran_di_chuyen(int x, int y);
void tao_qua();
void ve_qua();
bool kt_ran_de_qua();
bool ran_an_qua();
bool kt_gameover();
void printWelcome();
void printInfo();
void printLoadingBar();
void lua_chon_truoc_khi_vao_game();
void ket_qua_lua_chon();
void pressEnter();
void printHeadselect();
void fplay();
void sinh_qua_ngau_nhien();
void choosePlay();
void ve_dan(int x, int y);
void play2();
void dong_ho();
void ve_tuong_tunnel();
bool kt_game_over_map_tunnel();
void tao_vat_can_ngau_nhien();
bool kt_game_over_mode_2();
void highlightMenu();
// ====== NGUYEN MAU HAM ======
bool kt_game_over_mode_2()
{
	if (kt_gameover() == true)
		return true;
	else if (toadox[0] == xvcd && toadoy[0] == yvcd)
		return true;
}
void fplay2()
{
	thread f1(tao_vat_can_ngau_nhien);
	thread f2(play2);
	thread f3(sinh_qua_ngau_nhien);
	f1.join();
	f2.join();
	f3.join();
}
void tao_vat_can_ngau_nhien()
{
	
	srand(time(0));
	// cái này là của phần nếu như mà muốn nhiều cái vật cản
	/*for (int i = 0; i < 100; i++)
	{
		xvc[i] = rand() % 69 + 1 + 16;
		yvc[i] = rand() % 12 + 1 + 5;

		if (xvc[i] == toadox[0] && yvc[i] == toadoy[0])
		{
			i--;
			continue;
		}
			
		Sleep(10000);
		m.lock();
		SetColor(13);
		gotoXY(xvc[i], yvc[i]);
		cout << char(254);
		ShowCur(0);
		m.unlock();
	}*/
	m.lock();
	xvcd = 80; 
	yvcd = 5;
	gotoXY(xvcd, yvcd);
	cout << char(254);
	ShowCur(0);
	m.unlock();
	while (true)
	{
		if (xdan == xvcd && ydan == yvcd)
		{
			xvcd = rand() % 69 + 1 + 16;
			yvcd = rand() % 12 + 1 + 5;
			if (xvcd != toadox[0] && yvcd != toadoy[0])
			{
				m.lock();
				SetColor(15);
				gotoXY(xvcd, yvcd);
				cout << char(254);
				ShowCur(0);
				m.unlock();
			}	
		}
		/*else
		{
			Sleep(10000);
			xvcd = rand() % 69 + 1 + 16;
			yvcd = rand() % 12 + 1 + 5;
			if (xvcd != toadox[0] && yvcd != toadoy[0])
			{
				m.lock();
				SetColor(15);
				gotoXY(xvcd, yvcd);
				cout << char(254);
				ShowCur(0);
				m.unlock();
			}
		}*/
	}	
	if (kt_game_over_mode_2() == true)
		return;
}
void play2()  // cái này cũng ổn nề để lại sài cũng được đấy
{
	// settings 
	ShowCur(0);
	ve_tuong(1, 92, 1, 20);
	tao_ran();
	tao_qua();
	ve_qua();
	int x = 5, y = 2;
	direct = 2;   // int direct
	/* 0: biên trên và đi XUỐNG dưới
	 1: biên dưới và đi LÊN trên
	 2: biên trái và đi qua PHẢI
	 3: biên phải và đi qua TRÁI*/
	while (true)
	{
		// backspace 
		gotoXY(toadox[sdot], toadoy[sdot]);
		cout << "  ";
		// in
		m.lock();
		ve_ran();
		m.unlock();
		// điều khiển để thay đổi hướng
		if (_kbhit() == true)
		{
			char c = _getch();
			if (c == 'w' && direct != 0)
				direct = 1;
			else if (c == 's' && direct != 1)
				direct = 0;
			else if (c == 'a' && direct != 2)
				direct = 3;
			else if (c == 'd' && direct != 3)
				direct = 2;

			if (sdot >= 4)
			{
				if (c == 32)
				{
					sdot--;
					gotoXY(toadox[sdot], toadoy[sdot]);
					cout << " ";
					if (direct == 0)
					{
						xdan = x;
						ydan = y + 2;
						while (ydan <= 18)
						{
							xdancu = xdan;
							ydancu = ydan;
							gotoXY(xdancu, ydancu);
							cout << " ";
							ydan++;
							if (xdan == xvcd && ydan == yvcd)
							{
								gotoXY(xvcd, yvcd);
								cout << " ";
								break;
							}
							gotoXY(xdan, ydan);
							cout << "*";
							ShowCur(0);
							Sleep(1);
							if (ydan == 17)
							{
								gotoXY(xdan, ydan);
								cout << " ";
								break;
							}
						}
					}


					else if (direct == 1)
					{
						xdan = x;
						ydan = y - 2;
						while (ydan >= 4)
						{
							xdancu = xdan;
							ydancu = ydan;
							gotoXY(xdancu, ydancu);
							cout << " ";
							ydan--;
							if (xdan == xvcd && ydan == yvcd)
							{
								gotoXY(xvcd, yvcd);
								cout << " ";
								break;
							}
							gotoXY(xdan, ydan);
							cout << "*";
							ShowCur(0);
							Sleep(1);
							if (ydan == 5)
							{
								gotoXY(xdan, ydan);
								cout << " ";
								break;
							}
						}
					}

					else if (direct == 2)
					{
						xdan = x + 2;
						ydan = y;
						while (xdan <= 86)
						{
							xdancu = xdan;
							ydancu = ydan;
							gotoXY(xdancu, ydancu);
							cout << " ";
							xdan++;
							if (xdan == xvcd && ydan == yvcd)
							{
								gotoXY(xvcd, yvcd);
								cout << " ";
								break;
							}
							gotoXY(xdan, ydan);
							cout << "*";
							ShowCur(0);
							Sleep(1);
							if (xdan == 85)
							{
								gotoXY(xdan, ydan);
								cout << " ";
								break;
							}
								
						}
					}

					else if (direct == 3)
					{
						xdan = x - 2;
						ydan = y;
						while (xdan >= 15)
						{
							xdancu = xdan;
							ydancu = ydan;
							gotoXY(xdancu, ydancu);
							cout << " ";
							xdan--;
							if (xdan == xvcd && ydan == yvcd)
							{
								gotoXY(xvcd, yvcd);
								cout << " ";
								break;
							}
							gotoXY(xdan, ydan);
							cout << "*";
							ShowCur(0);
							Sleep(1);
							if (xdan == 16)
							{
								gotoXY(xdan, ydan);
								cout << " ";
								break;
							}
								
						}
					}
				}
			}
		}
			
		// dựa vào hướng để di chuyển
		if (direct == 0)
		{
			y++;
		}
		else if (direct == 1)
		{
			y--;
		}
			
		else if (direct == 2) // di qua phai
		{
			x++;
		}
		else if (direct == 3) // di qua trai
		{
			x--;
		}
			
		xu_ly_ran_di_chuyen(x, y);
		// xử lí rắn ăn quả
		if (ran_an_qua() == true)
		{
			SetColor(15);
			gotoXY(4, 0);
			cout << "Score: " << ++diem;
			sdot++;
			tao_qua();
			ve_qua();
		}
		if (kt_ran_de_qua() == true)
		{
			tao_qua();
			ve_qua();
		}
		// biên
		if (kt_game_over_mode_2() == true)
		{
			SetColor(15);
			ve_tuong(38, 53, 9, 13);
			gotoXY(40, 11);
			cout << "GAME OVER!!!";
			Sleep(5000);
			system("cls");
			ve_tuong(38, 53, 9, 13);
			ShowCur(0);
			while (true)
			{
				SetColor(15);
				gotoXY(40, 11);
				cout << "GAME OVER!!!";
				Sleep(1000);
				gotoXY(40, 11);
				cout << "            ";
				Sleep(100);
				if (_kbhit() == true)
				{
					char c = _getch();
					if (c == 27)
					{
						system("cls");
						gotoXY(30, 11);
						cout << "THANKS FOR USING MY PROJECT !!! <3";
						break;
					}
				}
				ShowCur(0);
			}
			game_over = true;
			return;
		}
		// speed
		if (direct == 1 || direct == 0)
		{
			Sleep(100 );
		}
		else if (direct == 2 || direct == 3)
		{
			Sleep(100);
		}
	}
	_getch();
}
void ve_dan(int x, int y)
{
	/*gotoXY(45, 11);
	cout << "o";*/
	ShowCur(0);
	/*int xdancu, ydancu;*/
	while (true)
	{
		if (_kbhit() == true)
		{
			char c = _getch();
			if (c == 32)
			{
				if (direct == 0)
				{
					xdan = x;
					ydan = y + 2;
					while (ydan <= 20)
					{
						xdancu = xdan;
						ydancu = ydan;
						gotoXY(xdancu, ydancu);
						cout << " ";
						ydan++;
						gotoXY(xdan, ydan);
						cout << "*";
						ShowCur(0);
						Sleep(1);
					}
				}
				else if (direct == 1)
				{
					xdan = x;
					ydan = y - 2;
					while (ydan >= 1)
					{
						xdancu = xdan;
						ydancu = ydan;
						gotoXY(xdancu, ydancu);
						cout << " ";
						ydan--;
						gotoXY(xdan, ydan);
						cout << "*";
						ShowCur(0);
						Sleep(1);
					}
				}
				else if (direct == 2)
				{
					xdan = x + 2;
					ydan = y;
					while (xdan <= 80)
					{
						xdancu = xdan;
						ydancu = ydan;
						gotoXY(xdancu, ydancu);
						cout << " ";
						xdan++;
						gotoXY(xdan, ydan);
						cout << "*";
						ShowCur(0);
						Sleep(1);
					}
				}
				else if (direct == 3)
				{
					xdan = x - 2;
					ydan = y;
					while (xdan >= 5)
					{
						xdancu = xdan;
						ydancu = ydan;
						gotoXY(xdancu, ydancu);
						cout << " ";
						xdan--;
						gotoXY(xdan, ydan);
						cout << "*";
						ShowCur(0);
						Sleep(1);
					}
				}
			}
		}
	}
}
void fplay() 
{
	// Phần đã test thành công

	if (game_over == true)
	{
		return;
	}
	thread l1(play);
	thread l2(sinh_qua_ngau_nhien);
	/*thread l3(dong_ho);*/  // cái hàm này bị xung đột coi chừng nha
	l1.join();
	l2.join();
	/*l3.join();*/  // cái hàm này bị xung đột coi chừng nha

	// ==== phần đã test thành công
} 
void sinh_qua_ngau_nhien()
{
	while (true)
	{
		Sleep(10000);
		xqua = rand() % 89 + 1 + 2;
		yqua = rand() % 17 + 1 + 2;
		if (toadox[0] != xqua && toadoy[0] != yqua)
			ve_qua();
	}
}
void play()
{
	// settings 
	ShowCur(0);
	if (map_choice == 1)
	{
		ve_tuong(1, 92, 1, 21);
	}
	else if (map_choice == 2)
	{
		ve_tuong_tunnel();
	}
	tao_ran();
	tao_qua();
	ve_qua();
	int x = 5, y = 2;
	direct = 2;   // int direct
	/* 0: biên trên và đi XUỐNG dưới
	 1: biên dưới và đi LÊN trên
	 2: biên trái và đi qua PHẢI
	 3: biên phải và đi qua TRÁI*/
	while (true)
	{
		// backspace 
		gotoXY(toadox[sdot], toadoy[sdot]);
		cout << "  ";
		// in
		ve_ran();
		// điều khiển để thay đổi hướng
		if (_kbhit() == true)
		{
			char c = _getch();
			if (c == -32)
			{
				c = _getch();
				if (c == 72 && direct != 0)
					direct = 1;
				else if (c == 80 && direct != 1)
					direct = 0;
				else if (c == 75 && direct != 2)
					direct = 3;
				else if (c == 77 && direct != 3)
					direct = 2;
			}
		}
		// dựa vào hướng để di chuyển
		if (direct == 0)
			y++;
		else if (direct == 1)
			y--;
		else if (direct == 2) // di qua phai
			x++;
		else if (direct == 3) // di qua trai
			x--;
		xu_ly_ran_di_chuyen(x, y);
		// xử lí rắn ăn quả
		if (ran_an_qua() == true )
		{
			SetColor(15);
			gotoXY(4, 0);
			cout << "Score: " << ++diem;
			sdot++;
			tao_qua();
			ve_qua();
		}
		if (kt_ran_de_qua() == true)
		{
			tao_qua();
			ve_qua();
		}
		// biên
		if (kt_gameover() == true || (kt_game_over_map_tunnel() == true && map_choice == 2))
		{
			ve_tuong(38, 53, 9, 13);
			gotoXY(40, 11);
			cout << "GAME OVER!!!";
			Sleep(5000);
			system("cls");
			ve_tuong(38, 53, 9, 13);
			ShowCur(0);
			while (true)
			{
				SetColor(15);
				gotoXY(40, 11);
				cout << "GAME OVER!!!";
				Sleep(150);
				gotoXY(40, 11);
				cout << "            ";
				Sleep(100);
				if (_kbhit() == true)
				{
					char c = _getch();
					if (c == 27)
					{
						system("cls");
						gotoXY(30, 11);
						cout << "THANKS FOR USING MY PROJECT !!! <3";
						break;
					}
				}
				ShowCur(0);
			}
			game_over = true;
			return;
		}
		// speed
		if (direct == 1 || direct == 0)
		{
			Sleep(100);
		}
		else if (direct == 2 || direct == 3)
		{
			Sleep(80);
		}
	}
	_getch();
}
// đã hoàn chỉnh ko đụng tới
void ve_tuong_tunnel()
{
	ve_tuong(1, 92, 1, 21);
	gotoXY(23, 5);
	for (int i = 23; i < 73; i++)
	{
		cout << "-";
	}
	gotoXY(23, 16);
	for (int i = 23; i < 73; i++)
	{
		cout << "-";
	}
}
bool kt_game_over_map_tunnel()
{
	if (kt_gameover() == true)
		return true;
	else
	{
		for (int i = 23; i < 73; i++)
		{
			if (toadox[0] == i && toadoy[0] == 5)
				return true;
			else if (toadox[0] == i && toadoy[0] == 16)
				return true;
		}
	}
}
void ve_tuong(int xleft, int xright, int ytop, int ybot)
{
	SetColor(10);
	for (int i = xleft; i <= xright; i++)  //1
	{
		gotoXY(i,ytop);
		cout << char(196);
		gotoXY(i, ybot);
		cout << char(196);
	}
	for (int i = ytop; i <= ybot; i++) //1
	{
		gotoXY(xleft, i);
		cout << char(179);
		gotoXY(xright, i);
		cout << char(179);
	}
	gotoXY(xleft, ytop); // 1 1
	cout << char(218);
	gotoXY(xright, ytop); // 92 20
	cout << char(191);
	gotoXY(xleft, ybot);  // 1 20
	cout << char(192);
	gotoXY(xright, ybot); // 92 20
	cout << char(217);
	SetColor(15);
}
// đã hoàn chỉnh ko đụng tới
void tao_ran()
{
	int x = 5; int y = 2; // tọa độ của đầu rắn
	for (int i = 0; i < sdot; i++)
	{
		toadox[i] = x;
		toadoy[i] = y;
		x--;
	}
}
// đã hoàn chỉnh ko đụng tới
void ve_ran()
{
	if (snake_color == 1)
		SetColor(10);
	else if (snake_color == 2)
		SetColor(4);
	else if (snake_color == 3)
		SetColor(14);

	for (int i = 0; i < sdot; i++)
	{
		gotoXY(toadox[i], toadoy[i]);
		if (i == 0)
		{
			if (snake_head == 1)
				cout << Pname[0];
			else if (snake_head == 2)
				cout << char(149);
			else if (snake_head == 3)
				cout << char(153);
		}
		else
			cout << "o";
	}
}
void xu_ly_ran_di_chuyen(int x, int y)
{
	
	// dời
	for (int i = sdot; i > 0; i--)
	{
		toadox[i] = toadox[i - 1];
		toadoy[i] = toadoy[i - 1];
	}
	// chèn
	toadox[0] = x;
	toadoy[0] = y;
	// tăng ==> không tăng vì dấu phần tử cuối
}
// đã hoàn chỉnh ko đụng tới
void tao_qua()
{
	
	do{
		xqua = rand() % 89 + 1 + 2;
		yqua = rand() % 17 + 1 + 2;
	} while (kt_ran_de_qua() == true);
}
// đã hoàn chỉnh ko đụng tới
void ve_qua()
{
	SetColor(4);
	gotoXY(xqua, yqua);
	cout << (char)3;
}
bool kt_ran_de_qua()
{
	for (int i = 0; i < sdot; i++)
	{
		if (toadox[i] == xqua && toadoy[i] == yqua)
			return true;
	}
	return false;
}
bool ran_an_qua()
{
	if (toadox[0] == xqua && toadoy[0] == yqua)
		return true; 
	return false;
}
bool kt_gameover()
{
	if (toadox[0] == 0 || toadox[0] == 92)
		return true;
	else if (toadoy[0] == 1 || toadoy[0] == 21)
		return true;
	else
	{
		for (int i = 1; i < sdot; i++)
		{
			if (toadox[0] == toadox[i] && toadoy[0] == toadoy[i])
				return true;
		}
	}
}
// đã hoàn chỉnh ko đụng tới
void printWelcome()
{
	int i;
	while (true)
	{
		i = rand() % 15 + 1 + 1;
		if (i % 16 == 0)
			i = 1;
		SetColor(i);
		gotoXY(8, 1);
		cout << "   _____             _         ";
		gotoXY(8, 2);
		cout << "  / ____|           | |        ";
		gotoXY(8, 3);
		cout << " | (___  _ __   __ _| | _____  ";
		gotoXY(8, 4);
		cout << "  \\___ \\| '_ \\ / _` | |/ / _ \\ ";
		gotoXY(8, 5);
		cout << "  ____) | | | | (_| |   <  __/ ";
		gotoXY(8, 6);
		cout << " |_____/|_| |_|\\__,_|_|\\_\\___| ";

		gotoXY(18, 8);
		cout << "\\ \\ / /             (_)       ";
		gotoXY(18, 9);
		cout << " \\ V / ___ _ __  _____  __ _  ";
		gotoXY(18, 10);
		cout << "  > < / _ \\ '_ \\|_  / |/ _` | ";
		gotoXY(18, 11);
		cout << " / . \\  __/ | | |/ /| | (_| | ";
		gotoXY(18, 12);
		cout << "/_/ \\_\\___|_| |_/___|_|\\__,_| ";
		gotoXY(18, 13);
		Sleep(500);
		if (_kbhit() == true)
		{
			char a = _getch();
			if (a == 13)
				break;
		}

	}
}
// đã hoàn chỉnh ko đụng tới
void printInfo()
{
	int x = 10, y = 22;
	int xcu = -1, ycu = -1;
	while (true)
	{
		// xoa cu
		gotoXY(xcu, ycu);
		cout << "                       ";
		xcu = x;
		ycu = y;
		gotoXY(x, y);
		cout << "Name: LE GIA QUOC TI";
		y--;
		if (y == 14)
			break;
		Sleep(150);
	}
	x = 10, y = 22;
	xcu = -1, ycu = -1;
	while (true)
	{
		// xoa cu
		gotoXY(xcu, ycu);
		cout << "                        ";
		xcu = x;
		ycu = y;
		gotoXY(x, y);
		cout << "Mentor: HUYNH CONG THANH";
		y--;
		if (y == 15)
			break;
		Sleep(150);
	}
	x = 10, y = 22;
	xcu = -1, ycu = -1;
	while (true)
	{
		// xoa cu
		gotoXY(xcu, ycu);
		cout << "                        ";
		xcu = x;
		ycu = y;
		gotoXY(x, y);
		cout << "@BeCodeching";
		y--;
		if (y == 16)
			break;
		Sleep(150);
	}
}
// đã hoàn chỉnh ko đụng tới
void printLoadingBar()
{
	SetColor(11);
	gotoXY(7, 19);
	cout << "LOADING..";
	char x = 219;
	int r = 0;
	for (int i = 18; i <= 80; i++)
	{
		gotoXY(16, 19);
		cout << ".";
		Sleep(80);
		gotoXY(16, 19);
		cout << " ";
		gotoXY(i, 19);
		if (i <= 44)
		{
			Sleep(50);
		}
		else
		{
			Sleep(20);
		}
		cout << x;
		gotoXY(82, 19);
		if (i == 80)
		{
			cout << 100 << "%";
			gotoXY(16, 19);
			cout << ".";
			break;
		}
		else
		{
			cout << r << "%";
			r++;
		}
	}
	_getch();
} 
void lua_chon_truoc_khi_vao_game()
{
	int stage = 0;
	while (true)
	{
		cout << "Input username: "; cin >> Pname;
		stage++;
		system("cls");
		// stage: chọn mode
		do
		{
			cout << "Choose Mode: " << endl;
			cout << "Press1: Normal mode." << endl;
			cout << "Press2: Combat mode." << endl;
			cin >> game_mode;
			if (game_mode != 1 && game_mode != 2)
				cout << "Please input valid value: " << endl;
		} while (game_mode != 1 && game_mode != 2);
		stage++;
		system("cls");
		// stage chọn map cho mode1 
		if (game_mode == 1)
		{
			do
			{
				cout << "Choose Map: " << endl;
				cout << "Press1: Map Basic" << endl;
				cout << "Press2: Map Tunnel" << endl;
				cin >> map_choice;
				if (map_choice != 1 && map_choice != 2)
					cout << "Please input valid value: " << endl;
			} while (map_choice != 1 && map_choice != 2);
		}
		// stage chọn map cho mode 2
		else
			map_choice = 1; // cái này là của cái combat mode chỉ làm cho ở chế độ 

		stage++;
		system("cls");
		// stage chọn đầu con rắn
		do
		{
			cout << "Choose your snake head style: " << endl;
			cout << "1/ First letter of your name " << Pname[0] << endl;
			cout << "2/ " << char(149) << endl;
			cout << "3/ " << char(153) << endl;
			cin >> snake_head;
			if (snake_head != 1 && snake_head != 2 && snake_head != 3)
				cout << "Please input valid value: " << endl;
		} while (snake_head != 1 && snake_head != 2 && snake_head != 3);

		stage++;
		system("cls");
		// stage chọn màu con rắn
		do
		{
			cout << "Choose your snake color: " << endl;
			// hiển thị màu con rắn ví dụ ở đây
			SetColor(10);
			cout << "1.";
			printHeadselect();
			SetColor(4);
			cout << "2.";
			printHeadselect();
			SetColor(14);
			cout << "3.";
			printHeadselect();
			cin >> snake_color;
			if (snake_color != 1 && snake_color != 2 && snake_color != 3)
				cout << "Please input valid value: " << endl;
		} while (snake_color != 1 && snake_color != 2 && snake_color != 3);
		
		if (stage == 4)
		{
			system("cls");
			break;
		}
	}
}
void ket_qua_lua_chon()
{
	SetColor(15);
	cout << "Player name: " << Pname << endl;
	if (game_mode == 1)
	{
		cout << "Game mode: normal" << endl;
		if (map_choice == 1)
			cout << "Map: Basic" << endl;
		else if (map_choice == 2)
			cout << "Map: Tunnel" << endl;
	}
	else if (game_mode == 2)
	{
		cout << "Game mode: Combat" << endl;
		cout << "Map: Basic" << endl;
	}
	if (snake_head == 1)
		cout << "Snake head: " << Pname[0] << endl;
	else if (snake_head == 2)
		cout << "Snake head: " << char(149) << endl;
	else if (snake_head == 3)
		cout << "Snake head: " << char(153) << endl;
	gotoXY(0, 4);
	cout << "Your snake: ";
	gotoXY(12, 4);
	if (snake_color == 1)
	{
		SetColor(10);
		printHeadselect();
	}
	else if (snake_color == 2)
	{
		SetColor(4);
		printHeadselect();
	}
	else if (snake_color == 3)
	{
		SetColor(14);
		printHeadselect();
	}
}
void printHeadselect()
{
	if (snake_head == 1)
		cout << "ooo" << Pname[0] << endl;
	else if (snake_head == 2)
		cout << "ooo" << char(149) << endl;
	else if (snake_head == 3)
		cout << "ooo" << char(153) << endl;
}
void pressEnter()
{
	ShowCur(0);
	while (true)
	{
		
		SetColor(15);
		gotoXY(36, 10); 
		cout << "Press Enter to play game";
		Sleep(1000);
		gotoXY(36, 10);
		cout << "                        ";
		Sleep(100);
		if (_kbhit() == true)
		{
			char c = _getch();
			if (c == 13)
			{
				cout << "Play game.";
				system("cls");
				break;
			}
		}
		ShowCur(0);
	}
}
void choosePlay()
{
	lua_chon_truoc_khi_vao_game();
	ket_qua_lua_chon();
	pressEnter();
}
void dong_ho()
{
	for (int i = 0; i < 86400;)
	{
		m.lock();
		Sleep(1000);
		i++;
		if (i % 60 == 0)
			secs = 0;
		
		SetColor(15);
		gotoXY(80, 0);
		cout << setw(2) << setfill('0') << i / 3600 << ":"
			<< setw(2) << setfill('0') << i / 60 << ":"
			<< setw(2) << setfill('0') << i % 60;
		ShowCur(0);
		m.unlock();
		if (kt_gameover() == true || kt_game_over_map_tunnel() == true)
			break;
	}
}
void highlightMenu()
{
	int xmove = 44;
	int ymove = 9;
	char c; 
	
	int check = 0;
	while (true)
	{
		gotoXY(44, 9);
		textcolor(15);
		cout << "PLAY";
		gotoXY(43, 10);
		textcolor(15);
		cout << "SETTING";
		gotoXY(44, 11);
		textcolor(15);
		cout << "EXIT";
		if (_kbhit() == true)
		{
			c = _getch();
			if (c == 'w')
			{
				ymove--;
			}
			if (c == 's')
			{
				ymove++;
			}
			if (c == '\r')
			{
				if (ymove == 9)
				{
					menu_choice = 1;
					system("cls");
					break;
				}
				else if (ymove == 10)
				{
					menu_choice = 2;
					system("cls");
					break;
				}
				else if (ymove == 11)
				{
					menu_choice = 3;
					system("cls");
					break;
				}
			}
		}
		if (ymove < 9)
			ymove = 11;
		else if (ymove > 11)
			ymove = 9;
		if (ymove == 9)
		{
			gotoXY(44, 9);
			SetColor(11);
			cout << "PLAY";
		}
		if (ymove == 10)
		{
			gotoXY(43, 10);
			SetColor(11);
			cout << "SETTING";
		}
		if (ymove == 11)
		{
			gotoXY(44, 11);
			SetColor(11);
			cout << "EXIT";
		}
		Sleep(100);
		ShowCur(0);
	}
}

void printKeyboard(int xleft, int xright,int ytop, int ybot)
{
	// xleft 0			xright = 2 ytop = 0		ybot = 2
	gotoXY(1, 1);
	cout << "w";
	gotoXY(xleft, ytop); // 0 0
	cout << char(218);
	gotoXY(xright, ytop); // 2 0
	cout << char(191);
	gotoXY(xleft, ybot);  // 0 1
	cout << char(192);
	gotoXY(xright, ybot); // 2 1
	cout << char(217);
	cout << "Hello World";
	for (int i = 1; i <=3; i++)
	{
		gotoXY(i, 1);
		cout << char(196);
	}
	/*for (int i = 1; i <= 3; i++)
	{
		gotoXY(i, 2);
		cout << char(196);
	}
	for (int i = 0; i <= 2; i++)
	{
		gotoXY(3, i);
		cout << char(179);
	}
	for (int i = 0; i <= 2; i++)
	{
		gotoXY(3, i);
		cout << char(179);
	}*/
	

	
	gotoXY(2, 1);
	cout << "w";
	ShowCur(0);
	_getch();
}
