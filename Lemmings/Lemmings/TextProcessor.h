#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <istream>
#include <sstream>
#include <glm/gtc/matrix_transform.hpp>
using namespace std;

class TextProcessor
{
public:
	static TextProcessor &instance()
	{
		static TextProcessor G;

		return G;
	}

	glm::ivec2 startDoor, endDoor, lemmingsStart, lemmingsEnd, camPos, bombPos, orangePos, bluePos;
	int levelNumber, minLemmings, width, height, maxTime, lemmings, spawnrate, numbDig, numbStop, numbBash, numbCli, numbFlo, numbBomb, numbBuild, doorStartColor, doorEndColor, isBomb, isPortal;
	string levelName, path, mPath, musicPath;
	void loadFileAndProcess(string path);
	TextProcessor() {}
	~TextProcessor();

private:
	ifstream file;
	void processText();
	void copyStringToVar(string var, int &variable);
	void copyStringToString(string var, string &variable);
	void copyStringTovec2(string var1, string var2, glm::ivec2 & vector);

};

