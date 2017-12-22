#include "File.h"

File::File()
{

}

File::~File()
{

}

vector<Brick*> File::Load(string filename)
{
	ifstream infile = ifstream(filename);

	//load data into vector from text file
	//Each brick is on a new line
	//Format is "X Y MAXHITS" ie int int int

	string line;
	while (getline(infile, line))
	{
		//istringstream iss(line);
		int x, y, maxhits;
		maxhits = -1;
		x = -1;
		y = -1;
		string number;
		for (int i = 0; i < line.length(); i++)
		{
			//if the next letter isn't a space
			if (line.compare(i, 1, " ") != 0)
			{
				//add to the string
				number.push_back(line.at(i));
			}
			//if x hasn't been set this means the next value is x
			else if (x == -1)
			{
				istringstream buffer(number);
				buffer >> x;
				number.clear();
			}
			else
			{
				//get y value
				istringstream buffer(number);
				buffer >> y;
				number.clear();
			}
		}
		//leftover numbers will be maxhits value
		istringstream buffer(number);
		buffer >> maxhits;
		m_bricks.push_back(new Brick(x, y, maxhits));
	}
	return m_bricks;
}


