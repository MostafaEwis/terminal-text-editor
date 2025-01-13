#include <iostream>
#include <conio.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <windows.h>

#define MAX_WINDOW 46 

//TODO: 
//1- add the functionality to write to a file[]
//2- add the insert mode []
//3- find another way to clear the console to reduce flickering []
//4- consider seprating into a class []
//5- highlight the current character, use the c style coloring []
void navigate(int& currentLine, int& currentChar, int& startLine, std::vector<std::string>& fileLines);
void printText(int& currentLine, int& currentChar, int& startLine, std::vector<std::string>& fileLines);

int main(int argc, char** argv){
	std::ifstream file(argv[1]);
	std::vector<std::string> fileLines;
	std::string line;
	int currentLine = 0;
	int currentChar = 0;
	if(!file) throw std::invalid_argument("file dosen't exist");

	while(getline(file, line))
		fileLines.push_back(line);
	
	int startLine = 0;
	printText(currentLine, currentChar, startLine, fileLines);
	navigate(currentLine, currentChar, startLine, fileLines);
}

void printText(int& currentLine, int& currentChar, int& startLine, std::vector<std::string>& fileLines){
	int endLine = startLine + std::min(MAX_WINDOW, (int)fileLines.size());

	for(int i = startLine; i < endLine; i++){
		if(currentLine == i){
			std::cout << i + 1 << " ";
			for(int j = 0; j < currentChar; j++)
				std::cout << fileLines[i][j];
			
			std::cout << '^';

			for(int j = currentChar + 1; j < fileLines[i].size(); j++)
				std::cout << fileLines[i][j];

			std::cout << std::endl;	
		}else{
			std::cout << i + 1 << " " << fileLines[i] << std::endl;
		}
	}
}
void navigate(int& currentLine, int& currentChar, int& startLine, std::vector<std::string>& fileLines){
	char move = ' ';
	while(move != 'q'){
		move = getch();
		switch(move){
			case 'k':
				std::cout << "\rk";
				currentLine += currentLine == 0 ? 0 : -1;
				if(currentLine < startLine) startLine--;
				
				break;          
			case 'j':               
				std::cout << "\rj";
				currentLine += currentLine + 1 < fileLines.size() ? 1 : 0;
				if(currentLine > startLine + MAX_WINDOW) startLine++;
				break;          
			case 'l':               
				std::cout << "\rl";
				currentChar += currentChar + 1 < fileLines[currentLine].size() ? 1 : 0;
				break;          
			case 'h':               
				std::cout << "\rh";
				currentChar += currentChar == 0 ? 0 : -1;
				break;
			default:
				std::cout << "\r\r " ;
				break;
		}
		system("cls");
		printText(currentLine, currentChar, startLine, fileLines);
	}
}
