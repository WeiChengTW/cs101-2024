#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Clock
{
public:
    int m_h;
    int m_m;
    int m_s;
    string m_AP;
    Clock(int h, int m, int s, string AP)
    {
        m_h = h;
        m_m = m;
        m_s = s;
        m_AP = AP;
    }
    void display()
    {
        cout << "Clock = " << m_h << ":" << m_m << ":" << m_s << " " << m_AP << endl;
        // Clock = 10:25:43 AM\n
    }
};

class ReadClass
{

public:
    void showClass()
    {
        ifstream in;
        string line;
        int count = 0, count_len = 0;
        string *ans = new string[1000];

        in.open("main.cpp");
        if (in.fail())
        {
            cout << "Error opeing a file" << endl;
            in.close();
        }
        while (getline(in, line))
        {

            if (line[0] == 'c' && line[1] == 'l')
            {

                // cout << line << endl;
                ans[count] = line;
                count++;
            }
        }
        cout << count << " class in main.cpp" << endl;
        for (int i = 0; i < count; i++)
        {
            cout << ans[i] << endl;
        }
        in.close();
    }
};

int main()
{
    ReadClass rfile;
    rfile.showClass();
    return 0;
}
