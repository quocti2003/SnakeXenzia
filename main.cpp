#include <iostream>
#include <fstream>
#include <string>
#include"FunctionsPrototypes.h"
#include"mylib.h"
#include <ctime>
#include <windows.h>
#include <fstream>
#include<iomanip>
#include <mutex>
#include <Windows.h>
using namespace std; 
void main()
{
	//printKeyboard(1, 3, 1, 3);
	//system("pause");
	// ========================================
	
	// ===== chỗ này in ra hình con rắn =======

	string str;
	ifstream fi;
	int lines = 1;
	fi.open("SnakeLogo.txt", ios::in);
	SetColor(10);
	while (!fi.eof())
	{
		gotoXY(58, lines++);
		getline(fi, str);
		cout << str;
	}

	// ===== đã hoàn chỉnh ======

	// Cái này là cái chỗ in Snake Xenzia

	ShowCur(0);
	printWelcome();

	// Cái này là cái chỗ in Snake Xenzia
	
	// chỗ này in thông tin người làm

	printInfo();
	printLoadingBar();

	// =============================
	system("cls");
	highlightMenu();
	if (menu_choice == 1)
	{
		choosePlay();
		srand(time(0));
		ShowCur(0);
		if (game_mode == 1)
			fplay();
		else if (game_mode == 2)
			fplay2();
	}
	else if (menu_choice == 2)
	{
		cout << "SETTING" << endl;
		/*int chon_nhac;
		cout << "SETTING" << endl;
		cout << "Do you want to play music while playing game ?" << endl;
		cout << "Press1: ON" << endl;
		cout << "Press2: OFF" << endl;
		cin >> chon_nhac;
		if (chon_nhac == 1)
		{
			PlaySound("jadujadu.wav", NULL, SND_SYNC);
		}
		else
		{
			continue;
		}*/
	}
	else
	{
		while (true)
		{
			m.lock();
			SetColor(15);
			gotoXY(30, 11);
			cout << "THANKS FOR USING MY PROJECT !!! <3";
			m.unlock();
			Sleep(100);
			xqua = rand() % 89 + 1 + 2;
			yqua = rand() % 17 + 1 + 2;
			if (toadox[0] != xqua && toadoy[0] != yqua)
				ve_qua();
			if (_kbhit() == true)
			{
				char c = _getch();
				if (c == 27)
					return;
			}
			
		}
	}
	_getch();
}