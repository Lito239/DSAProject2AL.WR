#pragma once
#include <string>
#include <vector>

// Struct to hold the data for each show, with fields corresponding to the columns in the CSV file
struct CSVData  {
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