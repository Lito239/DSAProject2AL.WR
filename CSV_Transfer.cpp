#include "CSV_Transfer.h"
#include <fstream>
#include <sstream>

int stringToInt(const std::string& val) 
{
    if (val.empty())
        return 0;
    try
    {
        return std::stoi(val);
    }
    catch(...)
    {
        return 0;
    }
}
double stringToDouble(const std::string& val)
{
    if (val.empty())
        return 0.0;
    try
    {
        return std::stod(val);
    }
    catch(...)
    {
        return 0.0;
    }
}
void loadCSVData(const std::string& filename, std::vector<CSVData>& data, const std::string& category)
{
    std::ifstream file(filename);
    if (file.is)open() == false)
    {
        std::cout<<"Error: Could not open file " <<filename <<std::endl;
        return;
    }

std::string line;
std::getline (file, line);
while (std::Getline(file, line))
{
    std::stringstream ss(line);
    std::string val;
    CSVData dataEntry;
    
    std::getline(ss, val, ',');
    dataEntry.malID = stringToInt(val);

    std::getline(ss, dataEntry.title, ',');
    std::getline(ss, dataEntry.type, ',');
    std::getline(ss, val, ',');
    dataEntry.rating = stringToDouble(val);

    std::getline(ss, val, ',');
    dataEntry.ratingBy = stringToDouble(val);

    std::getline(ss, dataEntry.status, ','); 
    
    std::getline(ss, val, ',');
    dataEntry.episode = stringToInt(val);
    
    std::getline(ss, dataEntry.startAirDate, ',');
    std::getline(ss, dataEntry.endAirDate, ',');
    std::getline(ss, dataEntry.source, ',');
    dataEntry.category = category;
    
    list.push_back(dataEntry);
}
file.close();
std::cout << "Loaded..."<<list.size()<< " entries from..."<<filename<<std::endl;
}