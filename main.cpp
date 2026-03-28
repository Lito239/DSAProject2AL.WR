#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include "CSV_Transfer.h"
#include "search.h"
#include "sort.h"

void printTopResults(const std::vector<CSVData>& data, bool ordered, int limit = 10) {   
    if (data.empty()) {
        std::cout<<"No results found! \n";
        return;
    }

    int amountToPrint = limit;
    int printed = 0;
    int i = 0;

    if (data.size() < limit) {
        amountToPrint = data.size();
    }
    if (ordered) {
        std::cout << "\nShowing top " << amountToPrint << " ordered results:" << std::endl;
    }
    else {
        std::cout << "\nShowing the first " << amountToPrint << " matching unordered results:" << std::endl;
    }

    while (printed < amountToPrint && i < data.size()) {
        if (!data[i].name.empty()) {
            std::cout << printed + 1 << ". " << data[i].name
                    << " | Popularity: " << data[i].popularity
                    << " | Seasons: " << data[i].seasons
                    << std::endl;
            printed++;
        }
        i++;
    }
}

void sortHelper (std::vector<CSVData>& quickSortData, std::vector<CSVData>& mergeSortData, const std::string& sortBy) {
    if (quickSortData.empty() || mergeSortData.empty()) {
        std::cout << "No data to sort.\n" << std::endl;
        return;
    }

    auto start = std::chrono::high_resolution_clock::now();
    quickSort(quickSortData, 0, quickSortData.size() - 1, sortBy);
    auto end = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> quickSortDuration = end - start;

    start = std::chrono::high_resolution_clock::now();
    mergeSort(mergeSortData, 0, mergeSortData.size() - 1, sortBy);
    end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> mergeSortDuration = end - start;
    
    std::cout << "\nSorting Performance Comparison:\n";
    std::cout << "Quick Sort Time: " << quickSortDuration.count() << " seconds\n";
    std::cout << "Merge Sort Time: " << mergeSortDuration.count() << " seconds\n";
}

int main() {
    std::vector<CSVData> shows;
    loadCSVData("shows.csv", shows);
    std::cout <<"\n Total Shows Loaded: " <<shows.size()<<std::endl;
    bool ordered = false;

    if (shows.empty()) {
        std::cout << "No shows loaded." << std::endl;
        return 1;
    }
    
    int menu = -1;
    while (menu != 0) {
        std::cout << "\n ************ SEARCH-A-SHOW ************"<<std::endl;
        std::cout<< "1. Search by Name"<<std::endl;
        std::cout<< "2. Filter by Popularity"<<std::endl;
        std::cout<< "3. Filter By Seasons"<<std::endl;
        std::cout<< "4. Sort and Benchmark All Shows"<<std::endl;
        std::cout<< "0. Exit"<<std::endl;
        std::cout<< "\nEnter Choice: ";
        std::cin >> menu;

        if (menu == 1) {
            std::cin.ignore();
            std::string key;
            std::cout <<"\nEnter a show name: ";
            std::getline(std::cin, key);
            std::vector<CSVData>results = searchName(shows, key);
            std::cout <<"\nFound "<<results.size() << " matching results."<<std::endl;
            printTopResults(results, ordered);
        }
        else if (menu ==2) {
            double minimumPop;
            std::cout<<"\nEnter minimum popularity: ";
            std::cin >> minimumPop;
            std::vector<CSVData> popularityResults = filterByPopularity(shows, minimumPop);
            std::cout << "\nShows with more than "<<minimumPop<<" popularity rating: "
            <<popularityResults.size() <<std::endl;
            printTopResults(popularityResults, ordered);
        }
        else if (menu ==3) {
            int minimumSeasons;
            std::cout<<"\nEnter minimum number of seasons: ";
            std::cin >> minimumSeasons;
            std::vector<CSVData> seasonResults = filterBySeasons(shows, minimumSeasons);
            std::cout<<"\nShows with more than " <<minimumSeasons<<" seasons: "
            <<seasonResults.size() <<std::endl;
            printTopResults(seasonResults, ordered);
        }
        else if (menu ==4) {
            ordered = true;
            std::vector<CSVData> quickSortDataName = shows;
            std::vector<CSVData> quickSortDataPopularity = shows;
            std::vector<CSVData> quickSortDataSeasons = shows;
            std::vector<CSVData> mergeSortData = shows;
            
            int comparisonValue = -1;

            while(comparisonValue < 1 || comparisonValue > 3) {
                std::cout<<"\nCHOOSE SORTING CRITERIA: "<<std::endl;
                std::cout<<"1. Sort by Name"<<std::endl;
                std::cout<<"2. Sort by Popularity"<<std::endl;
                std::cout<<"3. Sort by Seasons"<<std::endl;
                std::cout<<"\nEnter choice: ";
                std::cin >> comparisonValue;

                if (comparisonValue < 1 || comparisonValue >3) {
                    std::cout<<"Invalid choice. Please enter 1, 2, or 3."<<std::endl;
                }
            }
            if(comparisonValue == 1) {
                std::cout <<"\nSorting by name..."<<std::endl;
                sortHelper(quickSortDataName, mergeSortData, "name");
                printTopResults(quickSortDataName, ordered);
                
                bool continueShowing = true;
                int positionIndex = 10;
                int moreResults = 0;

                while (continueShowing == true) {
                    int continueSelection = -1;
                    std::cout << "\nKEEP SHOWING?" << std::endl;
                    std::cout << "1. Yes" << std::endl;
                    std::cout << "2. No" << std::endl;
                    std::cout << "\nEnter Choice: ";
                    std::cin >> continueSelection;

                    if (continueSelection == 1) {
                        std::cout << "\nHow many more results would you like to see? ";
                        std::cin >> moreResults;
                        
                        positionIndex += moreResults;
                        if (positionIndex >= quickSortDataName.size()) {
                            std::cout << "\nNo more results to show." << std::endl;
                            continueShowing = false;
                        } else {
                            printTopResults(quickSortDataName, ordered, positionIndex);
                        }
                    } 
                    else {
                        continueShowing = false;
                    }
                }
            }
            else if (comparisonValue == 2) {
                std::cout <<"\nSorting by popularity..."<<std::endl;
                sortHelper(quickSortDataPopularity, mergeSortData, "popularity");
                printTopResults(quickSortDataPopularity, ordered);

                bool continueShowing = true;
                int positionIndex = 10;
                int moreResults = 0;

                while (continueShowing == true) {
                    int continueSelection = -1;
                    std::cout << "\nKEEP SHOWING?" << std::endl;
                    std::cout << "1. Yes" << std::endl;
                    std::cout << "2. No" << std::endl;
                    std::cout << "\nEnter Choice: ";
                    std::cin >> continueSelection;

                    if (continueSelection == 1) {
                        std::cout << "\nHow many more results would you like to see? ";
                        std::cin >> moreResults;
                        
                        positionIndex += moreResults;
                        if (positionIndex >= quickSortDataPopularity.size()) {
                            std::cout << "\nNo more results to show." << std::endl;
                            continueShowing = false;
                        } else {
                            printTopResults(quickSortDataPopularity, ordered, positionIndex);
                        }
                    } 
                    else {
                        continueShowing = false;
                    }
                }
            }
            else if (comparisonValue == 3) {
                std::cout <<"\nSorting by seasons..."<<std::endl;
                sortHelper(quickSortDataSeasons, mergeSortData, "seasons");
                printTopResults(quickSortDataSeasons, ordered);

                bool continueShowing = true;
                int positionIndex = 10;
                int moreResults = 0;

                while (continueShowing == true) {
                    int continueSelection = -1;
                    std::cout << "\nKEEP SHOWING?" << std::endl;
                    std::cout << "1. Yes" << std::endl;
                    std::cout << "2. No" << std::endl;
                    std::cout << "\nEnter Choice: ";
                    std::cin >> continueSelection;

                    if (continueSelection == 1) {
                        std::cout << "\nHow many more results would you like to see? ";
                        std::cin >> moreResults;
                        
                        positionIndex += moreResults;
                        if (positionIndex >= quickSortDataSeasons.size()) {
                            std::cout << "\nNo more results to show." << std::endl;
                            continueShowing = false;
                        } 
                        else {
                            printTopResults(quickSortDataSeasons, ordered, positionIndex);
                        }
                    } 
                    else {
                        continueShowing = false;
                    }
                }
            }
        }
        else if (menu == 0) {
            std::cout <<"\nExiting program."<<std::endl;
        }
        else {
            std::cout<<"\nInvalid option. Please try again."<<std::endl;
        }
        ordered = false;
    }
    return 0;
}