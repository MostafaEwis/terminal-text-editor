#include <iostream>
#include <conio.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <windows.h>
#include "editor.cpp"

//TODO: 
//1- add the functionality to write to a file[]
//2- add the insert mode [~] handle the backspace[]
//3- find another way to clear the console to reduce flickering []
//4- consider seprating into a class [x], delete and defualt the constructors[]
//5- highlight the current character, use the bash coloring [x]
//6- move to a singleton [x]
//7- navigating the current character doesn't work properly []
//8- search for syntax highlighting []
//9- get the window dimensions to show lines properly[]
int main(int argc, char** argv){
	Editor& editor = Editor::get_instance(argv[1]);
}
