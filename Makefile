# For cross-compilation from Linux

CROSSCXX := x86_64-w64-mingw32-g++ 
CXXFLAGS := -Wall -Werror -static -lucrt -D_UCRT -O2
SOURCEFILES := src/main.cpp src/ui.cpp src/sha256.cpp src/test.cpp src/task.cpp src/utils.cpp src/accounts.cpp src/ui-common.cpp src/classwork.cpp src/leaderboard.cpp

main:
	$(CROSSCXX) $(SOURCEFILES) $(CXXFLAGS) -o main.exe

all: main keycodes sha256 generatetask

keycodes:
	$(CROSSCXX) tests/keycodes/keycodes.cpp src/ui.cpp $(CXXFLAGS) -o keycodes.exe

sha256:
	g++ src/sha256.cpp tests/sha256/sha256test.cpp $(CXXFLAGS) -o tests/sha256-test

generatetask:
	$(CROSSCXX) tests/generatetask/generatetask.cpp src/task.cpp src/ui.cpp src/utils.cpp src/ui-common.cpp $(CXXFLAGS) -o tests/generatetask-test
