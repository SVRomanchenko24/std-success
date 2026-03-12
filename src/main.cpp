#include <iostream>
#include "../include/test.h"
#include "../include/leaderboard.h"
#include "../include/ui.h"

void mainmenu()
{
	term_init();
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
	return mainmenu();
}
