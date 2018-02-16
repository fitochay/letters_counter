#include <iostream>
#include <fstream>
#include <map>

using namespace std;

class counter
{
    locale *loc;
    string r_filename, w_filename;
    map<wchar_t, float> counters;
    int number;

    public:

    counter()
    {
        number = 0;
        loc = new locale("");
    }

    void set_filenames();

    void write_to_file();

    void count_letters();
    
    void print_map();
};

void counter::set_filenames()
{
    r_filename = "file";
    w_filename = "file2";
}

void counter::write_to_file()
{
    wofstream stream;
    stream.open(w_filename);
    stream.imbue(*loc);
    for (auto& x:counters)
    {
        x.second /= number;
        stream << x.first << L"; " << x.second << endl;
    }
    stream.close();
}

void counter::count_letters()
{
    wifstream stream(this->r_filename);
    if (stream.is_open())
    {
        stream.imbue(*loc);
        wchar_t ch_low;
        wstring wstr;
        while (getline(stream, wstr))
        {
            for (int i = 0; i < wstr.size(); i ++)
            {
                if (wstr[i] >= L'А' && wstr[i] <= L'Я')
                {
                    number ++;
                    ch_low = wstr[i];
                    if (counters.count(ch_low) != 0)
                    {
                        counters[ch_low] ++;
                    }
                    else
                    {
                        counters.insert(pair<wchar_t,int>(ch_low, 1));
                    }
                }
            }
        }
        stream.close();
    }
}

void counter::print_map()
{
    ios_base::sync_with_stdio(false);
    wcout.imbue(*loc);
    for (auto& x:counters)
    {
        wcout << x.first << L"; " << x.second << endl;
    }
}

int main(int argc, char *argv[])
{
    counter c;
    c.set_filenames();
    c.count_letters();
    c.write_to_file();
    c.print_map();
    return 0;
}
