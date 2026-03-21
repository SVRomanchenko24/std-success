#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cstdint>

#include "../include/ui.h"
#include "../include/leaderboard.h"

using namespace std;

struct Entry {
    string name;
    int avg;
};

int leaderboard()
{
    vector<string> names;
    vector<int> avgs;

    loadLeaderboard(names, avgs);

    vector<Entry> board;

    for (size_t i = 0; i < names.size(); i++) {
        board.push_back({names[i], avgs[i]});
    }

    sort(board.begin(), board.end(), [](const Entry& a, const Entry& b) {
        return a.avg > b.avg;
    });

    system("clear"); // или "cls" на Windows

    cout << "===== LEADERBOARD =====\n\n";

    for (size_t i = 0; i < board.size(); i++) {
        cout << setw(2) << i + 1 << ". "
             << setw(15) << left << board[i].name
             << " | Avg: " << board[i].avg << endl;
    }

    cout << "\nPress Ctrl+C to exit\n";

    uint8_t in;
    while ((in = term_getch()) != CONTROL('C'))
    {
        switch (in)
        {
            default:
                break;
        }
    }

    return 0;
}
