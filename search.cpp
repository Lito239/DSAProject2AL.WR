#include "search.h"
#include <cctype>

std::string lowercaseHelper(std::string text) {
  for (int i = 0; i < text.length(); i++) {
      text[i] = std::tolower((unsigned char)text[i]);
    }
    return text;
}
std::vector<CSVData> searchName(const std::vector<CSVData>& data, const std::string& key) {
  std::vector<CSVData> results;
  std::string lowerKey = lowercaseHelper(key);
  for (int i = 0; i <data.size(); i++) {
      std::string lowercaseName = lowercaseHelper(data[i].name);
      if (lowercaseName.find(lowerKey) != std::string::npos) {
        results.push_back(data[i]);
      }
  }
  return results;
}
std::vector<CSVData> filterByPopularity(const std::vector<CSVData>& data, double leastPopular) {
  std::vector<CSVData> results;
  for (int i = 0; i<data.size();i++) {
      if (data[i].popularity >= leastPopular) {
        results.push_back(data[i]);
      }
    }
  return results;
}
std::vector<CSVData> filterBySeasons(const std::vector<CSVData>& data, int leastNumSeasons) {
  std::vector<CSVData> results;
  for (int i = 0; i<data.size();i++) {
      if (data[i].seasons >= leastNumSeasons) {
        results.push_back(data[i]);
      }
    }
  return results;
}
std::vector<CSVData> filterByProduction(const std::vector<CSVData>& data, bool currentlyInProduction) {
  std::vector<CSVData> results;
  for( int i = 0; i<data.size(); i++) {
    if(data[i].inProduction == currentlyInProduction) {
      results.push_back(data[i]);
    }
  }
  return results;
}