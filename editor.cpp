#include <iostream>
#include <conio.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <windows.h>

class Editor{
private:
	Editor(char* path){
		currentLine = 0;
		currentChar = 0;
		startLine = 0;
		maxWindow = 46;
		openFile(path);
		printText();
		navigate();
	}
	
	Editor() = default;
	static Editor* editor;
	std::ifstream file;
	std::vector<std::string> fileLines;
	std::string line;
	int currentLine;
	int currentChar;
	int startLine;
	int maxWindow;
	char move;
public: 
	static Editor& get_instance(char* path){
		static Editor editor(path);
		return editor;
	}

	void openFile(char* path){
		file.open(path);	
		if(!file) throw std::invalid_argument("file dosen't exist");

		while(getline(file, line))
			fileLines.push_back(line);
		
	}
	void printLineNumber(int i){
		std::cout << "\033[1;33m" << " " << i + 1 << " " << "\033[0m";
	}
	void printText(){
		int endLine = startLine + std::min(maxWindow, (int)fileLines.size());

		for(int i = startLine; i < endLine; i++){
			if(currentLine == i){
				printLineNumber(i);
				for(int j = 0; j < currentChar; j++)
					std::cout << fileLines[i][j];
				
				std::cout <<"\033[7;49;95m" << fileLines[i][currentChar] << "\033[0m";

				for(int j = currentChar + 1; j < fileLines[i].size(); j++)
					std::cout << fileLines[i][j];

				std::cout << std::endl;	
			}else{
				printLineNumber(i);
				std::cout << fileLines[i] << std::endl;
			}
		}
		std::cout << move;
	}

	void navigate(){
		bool cl = true;
		while(move != 'q'){
			//_getch is the same as getch but the latter is deprecated and doesn't go with the naming conventions
			move = _getch();
			cl = true;
			switch(move){
				case 'k':
					std::cout << "\rk";
					currentLine += currentLine == 0 ? 0 : -1;
					if(currentLine < startLine) startLine--;
					if(currentChar >= fileLines[currentLine].size()) currentChar = fileLines[currentLine].size() - 1;
					
					break;          
				case 'j':               
					std::cout << "\rj";
					currentLine += currentLine + 1 < fileLines.size() ? 1 : 0;
					if(currentLine > startLine + maxWindow) startLine++;
					if(currentChar >= fileLines[currentLine].size()) currentChar = fileLines[currentLine].size() - 1;
					break;          
				case 'l':               
					std::cout << "\rl";
					currentChar += currentChar + 1 < fileLines[currentLine].size() ? 1 : 0;
					break;          
				case 'h':               
					std::cout << "\rh";
					currentChar += currentChar == 0 ? 0 : -1;
					break;
				case 'i':               
					insert();
					break;
				default:
					cl = false;
					std::cout << "\r" ;
					break;
			}
			if(cl){
				system("cls");
				printText();
			}
		}


	}
	void insert(){
		bool getOut = false;
		while(!getOut){
			move = _getch();
			switch(move){
				//new line in windows is \r\n Carrige return + Line feed
				case '\r':
					//using these brackets to be able to declare variables in switch scope
					{
						std::string after = fileLines[currentLine];
						after.erase(0, currentChar);
						fileLines[currentLine].erase(currentChar, fileLines[currentLine].size() - currentChar);
						fileLines.insert(fileLines.begin() + currentLine + 1, after);
						currentChar = 0;
						currentLine++;
					}
					break;
				case ':':
					getOut = true;
					break;
				default:
					fileLines[currentLine].insert(fileLines[currentLine].begin() + currentChar, move);
					currentChar++;
					break;

			}
			system("cls");
			printText();
		}
	}
};
