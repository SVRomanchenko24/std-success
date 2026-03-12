#include <iostream>
#include <cstdint>
#include "../include/ui.h"
#include "../include/leaderboard.h"

int leaderboard()
{
	uint8_t in;
	while ((in = term_getch()) != CONTROL('C'))
	{
		switch (in)
		{
		}
	}
	return 0;
}
