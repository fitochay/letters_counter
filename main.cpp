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
#include <clocale>

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
			wcout << x.first << L":" << x.second << endl;
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
	wofstream file;
	file.open(this->w_filename);
	for (auto& x:counters)
	{
		x.second /= number;
		file << x.first << L"; " << x.second << endl;
	}
	file.close();
}

void counter::count_letters()
{
	wifstream file(this->r_filename);
	if (file.is_open())
	{
		string line;
        wstring wstr;
		while (getline(file, wstr))
		{
			for (int i = 0; i < wstr.size(); i ++)
			{
				if (wstr[i] >= L'А' && wstr[i] <= L'Я')
				{
					number ++;
					if (counters.count(wstr[i]) != 0)
					{
						counters[wstr[i]] ++;
					}
					else
					{
						counters.insert(pair<wchar_t,int>(wstr[i], 1));
					}
				}
			}
		}
		file.close();
	}
}

int main(int argc, char *argv[])
{
	counter c;
    setlocale(LC_ALL, "ru_RU.utf-8");

        c.set_filenames();
        c.count_letters();
        c.write_to_file();	
	return 0;
}
