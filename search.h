#pragma once
#include <vector>
#include <string>
#include "CSV_Transfer.h"

// Function prototypes for searching and filtering shows based on different criteria
std::vector<CSVData> searchName(const std::vector<CSVData>& data, const std::string& key);
std::vector<CSVData> filterByPopularity(const std::vector<CSVData>& data, double leastPopular);
std::vector<CSVData> filterBySeasons (const std::vector<CSVData>& data, int leastNumSeasons);
std::vector<CSVData> filterByProduction(const std::vector<CSVData>& data, bool currentlyInProduction);