#include "CSV_Transfer.h"
#include <fstream>
#include <sstream>
#include <iostream>

int stringToInt(const std::string& val) {
    if (val.empty()) {
        return 0;
    }
    try {
        return std::stoi(val);
    }
    catch(...) {
        return 0;
    }
}

double stringToDouble(const std::string& val) {
    if (val.empty()) {
        return 0.0;
    }
    try {
        return std::stod(val);
    }
    catch(...) {
        return 0.0;
    }
}

bool stringToBool(const std::string& val) {
    if (val == "1" || val == "true" || val == "TRUE") {
        return true;
    }
    return false;
}

void loadCSVData(const std::string& filename, std::vector<CSVData>& data) {
    std::ifstream file(filename);
    if (file.is_open() == false) {
        std::cout<<"Error: Could not open file " <<filename <<std::endl;
        return;
    }

std::string line;
std::getline (file, line);

while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string val;
    CSVData dataEntry;
    
    std::getline(ss, val, ',');
    dataEntry.ShowID = stringToInt(val);

    std::getline(ss, dataEntry.name, ',');
    std::getline(ss, val, ',');
    dataEntry.seasons = stringToInt(val);

    std::getline(ss,val, ',');
    dataEntry.episodes = stringToInt(val);
    
    std::getline(ss, dataEntry.overview, ',');
    std::getline(ss,val,',');
    dataEntry.isAdult = stringToBool(val);
    
    std::getline(ss, val, ',');
    dataEntry.inProduction = stringToBool(val);

    std::getline(ss, dataEntry.originalName, ','); 
    
    std::getline(ss, val, ',');
    dataEntry.popularity = stringToDouble(val);
    
    std::getline(ss, dataEntry.tagline, ',');
    std::getline(ss, val, ',');
    dataEntry.showRunTime = stringToInt(val);
    
    std::getline(ss, val, ',');
    dataEntry.typeID = stringToInt(val);
    
    std::getline(ss, val, ',');
    dataEntry.statusID= stringToInt(val);
    
    data.push_back(dataEntry);
}
file.close();
std::cout << "Loaded..."<<data.size()<< " entries from..."<<filename<<std::endl;
}