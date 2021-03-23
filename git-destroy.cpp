// git-destroy: de-"git init"s a repo by deleting .git/, effectively removing the "git" part of it,
// rendering it from a repo to nothing but some files in a folder. [THE LOCAL REPO IS DELETED.]
// My first attempt supporting both Windows and Linux, this is messy... Yikes. Works nontheless...
// Compile using any compiler, BUT:
// IMPORTANT: Make sure your output binary is called: git-destroy[.exe for windows] and is on PATH or else
// the command `git destroy` will not work.
// Also pls use C++17, thx
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h> // Use WinAPI for colors
#include "windows-colors.h"

#else
#include "linux-colors.h"
#endif
using namespace std;

template<typename T>
void color(T code, ostream& strm) {
	// If windows mate
#if defined(_WIN32) || defined(_WIN64)
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), code);
#else
	strm << T << endl;
#endif
}





void reset(
#ifdef _WIN32
	CONSOLE_SCREEN_BUFFER_INFO orig
#else
	ostream& strm
#endif
) {
#ifdef _WIN32
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), orig.wAttributes);
#else
	strm << RESET; // Add closing tags for the color to render
#endif
}



int main() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	// Get original color -- This will be used to reset colors.
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	color(GREEN, cout);
	cout << "git-destroy: ";
	color(RED, cout);
	cout << "WARNING, THIS CAN'T BE UNDONE! Make sure you have your repo in the final state you want it to be." << endl;
	color(GREEN, cout);
	cout << "git-destroy: ";
#ifdef _WIN32
	reset(csbi);
#else
	reset(cout);
#endif
	cout << "Deleting .git/ ... ";
#ifdef _WIN32
	system("attrib -s -h .git");
	system("cd .git && rd /s /q . > nul 2> nul"); // Dirty way to recursively delete without rd complaining about non-empty dirs; will throw folder-in-use error but we'll mask that
	system("cd ..");
	system("rd .git"); // Now rd won't complain
#else
	filesystem::remove_all(".git");
#endif
	color(GREEN, cout);
	cout << "[DONE]" << endl;
#ifdef _WIN32
	reset(csbi);
#else
	reset(cout);
#endif
	cout << "All done!" << endl;
}
