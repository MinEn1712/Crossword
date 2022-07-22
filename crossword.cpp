#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct coordinate{
    int x, y;
};
void Input(fstream &file, int &h, int &w, int &stringNum, string *matchString)
{
    file.open("input.txt", ios::out);
    cout << "Input width: "; cin >> w;
    cout << "Input height: "; cin >> h;
    file << w << " " << h << endl;
    char **table;
    table = new char *[h];
    for (int i = 0; i < h; i++){
        table[i] = new char [w];
    }
    for (int i = 0; i < h; i++){
        for (int j = 0; j < w; j++)
            table[i][j] = 65 + rand()%26;
    }

    for (int i = 0; i < h; i++){
        for (int j = 0; j < w; j++)
            file << table[i][j] << " ";
        file << endl;
    }
    for (int i = 0; i < h; i++){
        for (int j = 0; j < w; j++)
            cout << table[i][j] << " ";
        cout << endl;
    }
    cout << "How many strings do you want to enter? >> "; cin >> stringNum;
    matchString = new string [stringNum];
    for (int i = 0; i < stringNum; i++){
        cin >> matchString[i];
    }
    for (int i = 0; i < stringNum; i++){
        for (int j = 0; j < matchString[i].length(); j++){
            matchString[i][j] = toupper(matchString[i][j]);
        }
        file << matchString[i] << endl;
    }
    file << "#";
    file.close();
}

void NaivePatternSearching(string pat, string txt, int &count, int rowNum, int columnNum)
{
    int M = pat.length();
    int N = txt.length();
 
    for (int i = 0; i <= N - M; i++) {
        int j;
 
        for (j = 0; j < M; j++)
            if (txt[i + j] != pat[j])
                break;
 
        if (j == M){
            count++;
            cout << pat << " ";
            cout << "(" << rowNum << ", " << i << ")" << " ";
        }  
    }
}
 

void Output(fstream &file){
    file.open("input.txt", ios::in);
    string *row, *column;
    string firstLine;
    vector<string> matchString;
    int w, h;
    file >> w;
    file >> h;
    getline(file, firstLine);
    row = new string [h];
    column = new string [w];
    for(int i = 0; i < h; i++){
        getline(file, row[i]);
    }
    for(int i = 0; i < h; i++){
        row[i].erase(remove(row[i].begin(), row[i].end(), ' '), row[i].end());
    }
    string buf;
    int matchStringNum = 0;
    while(getline(file, buf)){
        if (buf == "#") break;
        matchString.push_back(buf);
        matchStringNum++;
    }
    int count = 0;
    for (int i = 0; i < matchStringNum; i++){
        for(int j = 0; j < h; j++){
            NaivePatternSearching(matchString[i], row[j], count, j, 0);
        }
    }
    cout << count << endl;
    file.close();
}

int main()
{
    fstream file;
    int height, width, stringNum;
    string *matchString;
    srand((int) time(0));
    Input(file,height,width,stringNum, matchString);
    Output(file);
    return 0;
}