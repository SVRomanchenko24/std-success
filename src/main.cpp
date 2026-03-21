#include <iostream>
#include "../include/test.h"
#include "../include/leaderboard.h"
#include "../include/ui.h"
#include "../include/accounts.h"
#include "../include/keycodes.h"
#include "../include/defines.h"
#include "../include/classwork.h"

using namespace std;

string username;

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
			if (!hasTestPending||i)
				cout << menuItems[i];
			else cout << "1. Test";
			term_invertColorPair();
		}
		else
		{
			if (!hasTestPending||i)
				cout << menuItems[i];
			else cout << "1. Test";
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
			case KEY_ARROW_UP:
				if (selected > 0)
					selected--;
				break;
			case KEY_ARROW_DOWN:
				if (selected < MENU_SIZE - 1)
					selected++; 
				break;
			case KEY_ENTER:
				switch (selected)
				{
					case 0:
						term_clear();
						if (!hasTestPending) classwork(); // TODO implement viewer and backend
						else
						{
							int result = test("Test", 10);
							if (result==-1) break;
							term_printCentered(result>=7?"Well done!":"Study more and try again!");
							if (result>=7)
							{
								currTopic++;
								hasTestPending = 0;
							}
							currAvg = (currAvg+result)/2;
							updateInfo(username, currTopic, currAvg, hasHomeworkPending, hasTestPending);
							term_getch();
						}
						break;
					case 1:
						term_clear();
						if (hasHomeworkPending)
						{
							int result = test("Homework", 3);
							if (result==-1) break;
							hasHomeworkPending = 0;
							term_printCentered("Well done!");
							term_getch();
							break;
						}
						break;
					case 2:
						term_clear();
						leaderboard();
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

int main(int argc, char **argv)
{
	loggedIn = !restoreSession(username, currTopic, currAvg, hasHomeworkPending, hasTestPending);
	if (!loggedIn) return 1; //temp
	mainmenu();
	return 0;
}
