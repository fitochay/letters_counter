/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: tproo
 *
 * Created on February 14, 2018, 12:02 AM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <map>
#include <cwchar>
#include <string>

using namespace std;

/*
 * 
 */

class counter
{
	string r_filename, w_filename;
	map<wchar_t, float> counters;
	int number;

	public:
	
	counter()
	{
		number = 0;
	}

	void set_filenames();

	void write_to_file();

	void count_letters();

	void print_counter()
	{
		for (auto& x:counters)
		{
			x.second /= number;
			cout << x.first << ":" << x.second << endl;
		}
	}	
};

void counter::set_filenames()
{
	this->r_filename = "file";
	this->w_filename = "file2";
}

void counter::write_to_file()
{
	ofstream file;
	file.open(this->w_filename);
	for (auto& x:counters)
	{
		x.second /= number;
		file << x.first << " " << x.second << endl;
	}
	file.close();
}

void counter::count_letters()
{
	ifstream file(this->r_filename);
	if (file.is_open())
	{
            wchar_t temp;
		string line;
		while (getline(file, line))
		{
                    wstring wstr(line.begin(), line.end());
			for (int i = 0; i < wstr.size(); i ++)
			{
				//if ((line[i] >= 97 && line[i] <= 122) || (line[i] >= 65 && line[i] <= 90) ||
				//		(line[i] >= 160 && line[i] <= 175) || 
				//		(line[i] >= 224 && line[i] <= 239) ||
				//		(line[i] >= 128 && line[i] <= 159))
                            temp = line[i];
                            wcout << wstr[i] << ' ';
				if (wstr[i] >= L'А' && wstr[i] <= L'Я')
				{
					number ++;
					if (counters.count(tolower(line[i])) != 0)
					{
						counters[tolower(line[i])] ++;
					}
					else
					{
						counters.insert(pair<wchar_t,int>(tolower(line[i]), 1));
					}
				}
			}
		}
		file.close();
	}
}

int main(int argc, wchar_t *argv[])
{
	counter c;

        c.set_filenames();
        c.count_letters();
        c.write_to_file();	
	return 0;
}