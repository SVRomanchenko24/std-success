# For cross-compilation from Linux

SOURCEFILES := src/main.cpp src/accounts.cpp src/ui.cpp

main:
	x86_64-w64-mingw32-g++ $(SOURCEFILES) -o main.exe
