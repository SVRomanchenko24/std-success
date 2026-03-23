#include <iostream>
#include <cstring>
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
			term_resetColorPair();
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
						if (!hasTestPending)
						{
							classwork();
							updateInfo(username, currTopic, currAvg, hasHomeworkPending, hasTestPending);
						}
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

							if (currAvg==0) currAvg = result;
							else currAvg = (currAvg+result)/2;

							if (currTopic==3)
							{
								hasTestPending = 1; // start endless test loop
							}

							if (currTopic==4)
							{
								--currTopic;
								hasTestPending = 1; // endless tests after finishing all topics
							}
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
							hasTestPending = 1;
							term_printCentered("Well done!");
							updateInfo(username, currTopic, currAvg, hasHomeworkPending, hasTestPending);
							term_getch();
						}
						else
						{
							term_printCentered("You have no pending homework");
							term_getch();
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

	if (argc==2)
	{
		string userName, password;
		if (!strcmp(argv[1], "login"))
		{
			if (loggedIn)
			{
				cout << "You are already logged in, logout first.\n";
				return 0;
			}
			else
			{
				cout << "Enter your username: ";
				cin >> userName;
				cout << "Enter your password: ";
				cin >> password;
				loggedIn = !loginUser(userName, password, currTopic, currAvg, hasHomeworkPending, hasTestPending);

				if (!loggedIn)
					cout << "Your have entered incorrect password or the account doesn't exist\n";
				else
					cout << "You have logged in successfully\n";

				return 0;
			}
		}
		else if (!strcmp(argv[1], "reg"))
		{
			if (loggedIn)
			{
				cout << "You are already logged in, logout first.\n";
				return 0;
			}
			else
			{
				cout << "Your username can only contain letters and numbers.\nEnter your username: ";
				cin >> userName;
				cin.ignore(100);
				cout << "Your password can only contain letters, numbers and special characters such as #, !. It also has to contain at least 6 charachers\nEnter your password: ";
				char ch;
				while ((ch = term_getch())!=KEY_ENTER&&password.size()<6)
				{
					if ((ch>='A'&&ch<='Z')||(ch>='a'&&ch<='z')||(ch>='0'&&ch<='9')||ch=='#'||ch=='!')
						password.push_back(ch);
					else if (ch==KEY_BACKSPACE)
						password.pop_back();
				}
				if (registerUser(userName, password))
					cout << "The user with that name already exists.\n";
				else
					cout << "You have registered successfully! Use " << argv[0] << " login to log in with your new account.\n";
				return 0;
			}
		}
		else if (!strcmp(argv[1], "logout"))
		{
			if (!loggedIn)
			{
				cout << "You are not logged in yet.\n";
				return 0;
			}
			else
			{
				logoutUser();
				cout << "You have logged out successfully!\n";
				return 0;
			}
		}
		else if (!strcmp(argv[1], "help"))
		{
			cout << "std-success help\n\treg - register an account\n\tlogin - log into an existing account\n\tlogout - log out of currently logged in account\n";
			return 0;
		}
	}

	if (!loggedIn)
	{
		cout << "You are not logged in yet, use " << argv[0] << " login to log in or " << argv[0] << " reg to register\n";
		return 0;
	}

	if (argc>1)
	{
		cout << "Invalid arguments. Use " << argv[0] << " help to get help.\n";
		return 0;
	}

	mainmenu();
	return 0;
}
