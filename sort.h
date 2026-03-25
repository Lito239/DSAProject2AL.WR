#pragma once
#include <vector>
#include <string>
#include "CSV_Transfer.h"

void quickSort(std::vector<CSVData>& data, int low, int high, const std::string& sortBy);
void mergeSort(std::vector<CSVData>& data, int left, int right, const std::string& sortBy);