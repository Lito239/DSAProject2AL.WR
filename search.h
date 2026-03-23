#pragma once
#include <vector>
#include <string>
#include "CSV_Transfer.h"

std::vector<CSVData> searchName(const std::vector<CSVData>& data, const std::string& key);
std::vector<CSVData> filterByPopularity(const std::vector<CSVData>& data, double leastPopular);
std::vector<CSVData> filterBySeasons (const std::vector<CSVData>& data, int leastNumSeasons);
