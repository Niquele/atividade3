#ifndef __ANALISADOR                 
#define __ANALISADOR   

#include <chrono>
#include <iostream>
#include <vector>
#include <random>
#include <fstream>

using namespace std;

class MapBuilder
{
private:
    int mapId; 
    mt19937 generator;
public:
    MapBuilder(/* args */);
    void build();
};

MapBuilder::MapBuilder(/* args */)
{
    mapId = 0;
    generator.seed(1);

}

void MapBuilder::build(){
    mapId++;
    
    uniform_int_distribution<int> mapDimensions(10,20);
    int rows = mapDimensions(generator), cols = mapDimensions(generator);
    
    vector<vector<bool>> canOccupy(rows, vector<bool>(cols));
    
    int m = rows*cols * 0.7; 
    uniform_int_distribution<int> canOccupyQuantity(max(m - 10, 0), m + 10);
    int q = canOccupyQuantity(generator), cel, row, col;
    
    // mapping a matriz in an array: cel = row * cols + col
    // col = cel % cols
    // row = cel/cols
    uniform_int_distribution<int> posInMatrix(0, rows*cols - 1);
    vector<int> canOccupyCels;
    
    while(q){
        cel = posInMatrix(generator);
        col = cel % cols;
        row = cel/cols;
        if(!canOccupy[row][col]){
            canOccupy[row][col] = true;
            canOccupyCels.push_back(cel);
            q--;
        }
    }

    uniform_int_distribution<int> toBeginOrAchieve(0,q);
    int startPos = toBeginOrAchieve(generator), goalPos = toBeginOrAchieve(generator);
    while (goalPos == startPos)
    {
        goalPos = toBeginOrAchieve(generator);
    }
    
    int day, month, year, num = mapId;
    time_t t = time(nullptr);
    tm * now = localtime(&t);
    day = now->tm_mday;
    month = now->tm_mon + 1;
    year = now->tm_year + 1900;
    //dd-mm-aaaa_num.map
    string fileName = to_string(day) + "-" +to_string(month) + "-" + to_string(year) + "_" + to_string(num)+".map";
    ofstream fileOutput;
    fileOutput.open(fileName, ios::out);
    fileOutput<<rows<<","<<cols<<endl;
    fileOutput<<(startPos/cols)<<","<<(startPos%cols)<<endl;
    fileOutput<<(goalPos/cols)<<","<<(goalPos%cols)<<endl;
    
    
    fileOutput.close();
}

#endif  