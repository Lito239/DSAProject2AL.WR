#include <iostream>
#include <vector>
#include "CSV_Transfer.h"
#include "search.h"
#include "sort.h"
#include <chrono>

void sortHelper (std::vector<CSVData>& quickSortData, std::vector<CSVData>& mergeSortData, const std::string& sortBy) {
    if (quickSortData.empty() || mergeSortData.empty()) {
        std::cout << "No data to sort.\n" << std::endl;
        return;
    }

    auto start = std::chrono::high_resolution_clock::now();
    quickSort(quickSortData, 0, quickSortData.size() - 1, sortBy);
    auto end = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> quickSortDuration = end - start;
    std::cout << "Quick Sort Duration: " << quickSortDuration.count() << " seconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    mergeSort(mergeSortData, 0, mergeSortData.size() - 1, sortBy);
    end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> mergeSortDuration = end - start;
    std::cout << "Merge Sort Duration: " << mergeSortDuration.count() << " seconds" << std::endl;
    
    std::cout << "\nSorting Performance Comparison:\n";
    std::cout << "Quick Sort Time: " << quickSortDuration.count() << " seconds\n";
    std::cout << "Merge Sort Time: " << mergeSortDuration.count() << " seconds\n";
}

int main()
{
    std::vector<CSVData> shows;
    loadCSVData("shows.csv", shows);
    std::cout <<"\n Total Shows Loaded: " <<shows.size()<<std::endl;

    if (shows.empty())
    {
        std::cout << "No shows loaded." << std::endl;
        return 1;
    }
    
    std::string key;
    std::cout<<"\nEnter a show name: ";
    std::getline(std::cin, key);
    std::vector<CSVData> results = searchName(shows, key);
    std::cout <<"\nFound " <<results.size() <<" results:\n";

    std::vector<CSVData> quickSortData = shows;
    std::vector<CSVData> mergeSortData = shows;

    int comparison_value = -1;
    while (comparison_value < 1 || comparison_value > 3) 
    {
        std::cout << "\nChoose sorting criteria:\n";
        std::cout << "1: Name\n";
        std::cout << "2: Popularity\n";
        std::cout << "3: Seasons\n";
        std::cin >> comparison_value;

        if (comparison_value < 1 || comparison_value > 3)
        {
            std::cout << "Invalid choice. Please enter a number between 1 and 3." << std::endl;
        }
    }

    if (comparison_value == 1)
    {
        std::cout << "\nSorting by name...\n";
        sortHelper(quickSortData, mergeSortData, "name");
    }
    else if (comparison_value == 2) 
    {
        std::cout << "\nSorting by popularity...\n";
        sortHelper(quickSortData, mergeSortData, "popularity");
    }
    else if (comparison_value == 3) 
    {
        std::cout << "\nSorting by seasons...\n";
        sortHelper(quickSortData, mergeSortData, "seasons");
    }
    
    std::cout << "\nTop 10 Results:\n";
    for (int i = 0; i < results.size() && i < 10; i++)
    {
        std::cout << i + 1 << ". " << results[i].name <<
        " | Popularity: " << results[i].popularity<<
        " | Seasons: " << results[i].seasons <<
        std::endl;
    }

    /*
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
    */

    return 0;
}