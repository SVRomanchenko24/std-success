#include <iostream>
#include "../include/test.h"
#include "../include/leaderboard.h"
#include "../include/ui.h"
#include "../include/accounts.h"
using namespace std;
const char* menuItems[] = 
{
          "1. Classwork",
          "2. Homework",
          "3. Leaderboard",
          "4. Exit"
};

const int MENU_SIZE = 4;

void drawMenu(int selected)
{
    term_clear();

    short width, height;
    term_getTermSize(width, height);

    int startY = height / 2 - MENU_SIZE / 2;

    for (int i = 0; i < MENU_SIZE; i++)
    {
        term_moveCursor(width / 2 - 10, startY + i);
        if (i == selected)
{
	term_inverted_ColorPair();
	cout<< menuItems[i];
	term_invertColorPair();
}
else
{
	cout<< menuItems[i];
}
}
}

void mainmenu()
{
	term_init();
	cout << registerUser("test", "123123");
	uint8_t in;

	while ((in = term_getch()) != CONTROL('C'))
	{
		switch (in)
		{
		}
	}

	term_deinit();
}

int main()
{
	mainmenu();
	return 0;
}
