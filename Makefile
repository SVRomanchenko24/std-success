# For cross-compilation from Linux

CROSSCXX := x86_64-w64-mingw32-g++ 
SOURCEFILES := src/main.cpp src/accounts.cpp src/ui.cpp

main:
	$(CROSSCXX) $(SOURCEFILES) -o main.exe

sha256:
	g++ src/sha256.cpp tests/sha256/sha256test.cpp -o tests/sha256-test
