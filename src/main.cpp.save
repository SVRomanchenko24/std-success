#include <iostream>
#include "../include/test.h"
#include "../include/leaderboard.h"
#include "../include/ui.h"
#include "../include/accounts.h"
#include "../include/userdata.h"

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
			term_invertColorPair();
			cout<< menuItems[i];
			term_invertColorPair();
		}
		else
		{
			cout << menuItems[i];
		}
	}
}

void mainmenu()
{
	term_init();
	int selected = 0;
	uint8_t in;
	
	drawMenu(selected);
	while ((in = term_getch()) != CONTROL('C'))
	{
		switch (in)
		{
			case KEY_UP:
				if (selected > 0)
					selected--;
				break;

			case KEY_DOWN:
				if (selected < MENU_SIZE - 1)
					selected ++; 
				break;
			case KEY_ENTER:
				switch (selected)
				{
					case 0:
						term_clear();
						classwork(); // TODO implement viewer and backend
						break;

					case 1:
						term_clear();
						if (hasHomeworkPending)
						{
							int result = test("Homework", 3);
							if (result==-1) break;
							hasHomeworkPending = 0;
							term_printCentered("Well done!");
							break;
						}
						break;

					case 2:
						term_clear();
						showLeaderboard();
						term_getch();
						break;

					case 3:
						term_deinit();
						return;
				 }
				 break;
		}

		drawMenu(selected);
	}

	term_deinit();
}

int main()
{
	restoreSession();
	mainmenu();
	return 0;
}
