#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "Brick.h"

using namespace std;

class File
{
public:
	File();
	~File();
	vector<Brick*> Load(string filename);
private:
	vector<Brick*> m_bricks;
};

