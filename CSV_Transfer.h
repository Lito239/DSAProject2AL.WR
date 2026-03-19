#pragma once
#include <string>
#include <vector>

struct CSVData 
{
    int malID;
    std::string title;
    std::string type;
    double rating;
    int ratingBy;
    std::string status;
    int episode;
    std::string startAirDate;
    std::string endAirDate;
    std::string source;
    std::string category;
};

void loadCSVData(const std::string& filename, std::vector<CSVData>& data, const std::string& category);