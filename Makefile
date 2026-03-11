# For cross-compilation from Linux

CROSSCXX := x86_64-w64-mingw32-g++ 
CXXFLAGS := -Wall -Werror
SOURCEFILES := src/main.cpp src/ui.cpp src/sha256.cpp

all: main keycodes sha256

main:
	$(CROSSCXX) $(SOURCEFILES) $(CXXFLAGS) -o main.exe

keycodes:
	$(CROSSCXX) src/keycode_test.cpp src/ui.cpp $(CXXFLAGS) -o keycodes.exe

sha256:
	g++ src/sha256.cpp tests/sha256/sha256test.cpp $(CXXFLAGS) -o tests/sha256-test
