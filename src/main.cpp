#include <iostream>
#include "../include/test.h"
#include "../include/leaderboard.h"
#include "../include/ui.h"
#include "../include/accounts.h"

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
