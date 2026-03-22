#pragma once
#include <string>
#include <vector>

struct CSVData 
{
    int ShowID;
    std::string name;
    int seasons;
    int episodes;
    std::string overview;
    bool isAdult;
    bool inProduction;
    std::string originalName;
    double popularity;
    std::string tagline;
    int showRunTime;
    int typeID;
    int statusID;
};

void loadCSVData(const std::string& filename, std::vector<CSVData>& data);
