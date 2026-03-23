#include <iostream>
#include <vector>
#include "CSV_Transfer.h"
#include "search.h"
//The main for me SO FAR is only to make sure that the search function is actually working
int main()
{
    std::vector<CSVData> shows;
    loadCSVData("shows.csv", shows);
    std::cout <<"\n Total Shows Loaded: " <<shows.size()<<std::endl;
    
    //First Test - By Name
    std::string key;
    std::cout<<"\nEnter a show name: ";
    std::getline(std::cin, key);
    std::vector<CSVData> results = searchName(shows, key);
    std::cout <<"\nFound " <<results.size() <<" results:\n";

    for (int i = 0; i < results.size() && i < 10; i++)
    {
        std::cout << results[i].name <<
        " | Popularity: " << results[i].popularity<<
        " | Seasons: " << results[i].seasons <<
        std::endl;
    }


    //Second Test - By Popularity
    double minimumPop;
    std::cout <<"\nEnter minimum Popularity: ";
    std::cin >> minimumPop;
    std::vector<CSVData> popularityResults= filterByPopularity(shows, minimumPop);
    std::cout << "\nShows with popularity >="<< minimumPop <<": "
    << popularityResults.size() <<std::endl;

    for (int i = 0; i<popularityResults.size() && i<10; i++)
    {
        std::cout <<popularityResults[i].name <<
        " | Popularity: " << popularityResults[i].popularity <<
        std::endl;
    }
    return 0;
}