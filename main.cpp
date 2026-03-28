#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include "CSV_Transfer.h"
#include "search.h"
#include "sort.h"

// Function to print the top results based on the ordered flag and limit
void printTopResults(const std::vector<CSVData>& data, bool ordered, int limit = 10) {   
    if (data.empty()) {
        std::cout << "No results found! \n";
        return;
    }

    int amountToPrint = limit;
    int printed = 0;
    int i = 0;

    if (data.size() < limit) {
        amountToPrint = data.size();
    }

    // Print header based on whether results are ordered or not
    if (ordered) {
        std::cout << "\nShowing top " << amountToPrint << " ordered results:" << std::endl;
    }
    else {
        std::cout << "\nShowing the first " << amountToPrint << " matching unordered results:" << std::endl;
    }

    // Loop through the data and print results until the limit is reached or there are no more results
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

// Helper function to call both sorting algorithms and measure their performance
void sortHelper (std::vector<CSVData>& quickSortData, std::vector<CSVData>& mergeSortData, const std::string& sortBy) {
    if (quickSortData.empty() || mergeSortData.empty()) {
        std::cout << "No data to sort.\n" << std::endl;
        return;
    }

    auto start = std::chrono::high_resolution_clock::now(); // Start timer for quick sort
    quickSort(quickSortData, 0, quickSortData.size() - 1, sortBy);
    auto end = std::chrono::high_resolution_clock::now(); // End timer for quick sort
    
    std::chrono::duration<double> quickSortDuration = end - start; // Calculate duration for quick sort

    start = std::chrono::high_resolution_clock::now(); // Start timer for merge sort
    mergeSort(mergeSortData, 0, mergeSortData.size() - 1, sortBy);
    end = std::chrono::high_resolution_clock::now(); // End timer for merge sort

    std::chrono::duration<double> mergeSortDuration = end - start; // Calculate duration for merge sort

    std::cout << "\nSorting Performance Comparison:\n";
    std::cout << "Quick Sort Time: " << quickSortDuration.count() << " seconds\n";
    std::cout << "Merge Sort Time: " << mergeSortDuration.count() << " seconds\n";
}

int main() {
    // Load shows from CSV file
    std::vector<CSVData> shows;
    loadCSVData("shows.csv", shows);
    std::cout << "\n Total Shows Loaded: " << shows.size() << std::endl;
    bool ordered = false;

    if (shows.empty()) {
        std::cout << "No shows loaded." << std::endl;
        return 1;
    }

    // Main menu loop
    int menu = -1;
    while (menu != 0) {
        std::cout << "\n ************ SEARCH-A-SHOW ************" << std::endl;
        std::cout << "1. Search by Name" << std::endl;
        std::cout << "2. Filter by Popularity" << std::endl;
        std::cout << "3. Filter by Seasons" << std::endl;
        std::cout << "4. Sort and Benchmark All Shows" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "\nEnter Choice: ";
        std::cin >> menu;

        // Options 1-3 allow the user to search or filter the shows based on their choice of criteria and then print first 10 results from the unsorted data
        if (menu == 1) {
            std::cin.ignore();
            std::string key;
            std::cout << "\nEnter a show name: ";
            std::getline(std::cin, key);
            std::vector<CSVData>results = searchName(shows, key); // Fucntion call to search by name
            std::cout << "\nFound " << results.size() << " matching results." << std::endl;
            printTopResults(results, ordered);
        }
        else if (menu ==2) {
            double minimumPop;
            std::cout << "\nEnter minimum popularity: ";
            std::cin >> minimumPop;
            std::vector<CSVData> popularityResults = filterByPopularity(shows, minimumPop); // Function call to filter by popularity
            std::cout << "\nShows with more than " << minimumPop << " popularity rating: " << popularityResults.size() << std::endl;
            printTopResults(popularityResults, ordered);
        }
        else if (menu ==3) {
            int minimumSeasons;
            std::cout << "\nEnter minimum number of seasons: ";
            std::cin >> minimumSeasons;
            std::vector<CSVData> seasonResults = filterBySeasons(shows, minimumSeasons); // Function call to filter by seasons
            std::cout << "\nShows with " << minimumSeasons << " seasons or more: " << seasonResults.size() << std::endl;
            printTopResults(seasonResults, ordered);
        }

        // Option 4 allows the user to sort the shows based on their choice of criteria and then compare the performance of quick sort and merge sort
        else if (menu ==4) {
            ordered = true;

            // Create separate vectors for each sorting criteria to ensure both sorting algorithms are working with the same data
            std::vector<CSVData> quickSortData = shows;
            std::vector<CSVData> mergeSortData = shows;
            
            // Menu to select sorting criteria
            int comparisonValue = -1;
            while(comparisonValue < 1 || comparisonValue > 3) {
                std::cout << "\nCHOOSE SORTING CRITERIA: " << std::endl;
                std::cout << "1. Sort by Name" << std::endl;
                std::cout << "2. Sort by Popularity" << std::endl;
                std::cout << "3. Sort by Seasons" << std::endl;
                std::cout << "\nEnter choice: ";
                std::cin >> comparisonValue;

                if (comparisonValue < 1 || comparisonValue >3) {
                    std::cout << "Invalid choice. Please enter 1, 2, or 3." << std::endl;
                }
            }

            // Call the sortHelper function to perform sorting and benchmarking based on the user's choice of criteria
            if(comparisonValue == 1) {
                std::cout << "\nSorting by name..." << std::endl;
                sortHelper(quickSortData, mergeSortData, "name"); // Function call to sort and benchmark by name
                printTopResults(quickSortData, ordered);
                
                bool continueShowing = true;
                int positionIndex = 10;
                int moreResults = 0;

                // Loop to allow the user to continue showing more results until they choose to stop or there are no more results to show
                while (continueShowing == true) {
                    int continueSelection = -1;
                    std::cout << "\nKEEP SHOWING?" << std::endl;
                    std::cout << "1. Yes" << std::endl;
                    std::cout << "2. No" << std::endl;
                    std::cout << "\nEnter Choice: ";
                    std::cin >> continueSelection;

                    // Ask the user how many more results they would like to see and update the position index accordingly
                    if (continueSelection == 1) {
                        std::cout << "\nHow many more results would you like to see? ";
                        std::cin >> moreResults;
                        
                        positionIndex += moreResults;
                        if (positionIndex >= quickSortData.size()) {
                            std::cout << "\nNo more results to show." << std::endl;
                            continueShowing = false;
                        } 
                        else {
                            printTopResults(quickSortData, ordered, positionIndex);
                        }
                    } 
                    else {
                        continueShowing = false;
                    }
                }
            }
            else if (comparisonValue == 2) {
                std::cout << "\nSorting by popularity..." << std::endl;
                sortHelper(quickSortData, mergeSortData, "popularity");
                printTopResults(quickSortData, ordered);

                bool continueShowing = true;
                int positionIndex = 10;
                int moreResults = 0;

                // Loop to allow the user to continue showing more results until they choose to stop or there are no more results to show
                while (continueShowing == true) {
                    int continueSelection = -1;
                    std::cout << "\nKEEP SHOWING?" << std::endl;
                    std::cout << "1. Yes" << std::endl;
                    std::cout << "2. No" << std::endl;
                    std::cout << "\nEnter Choice: ";
                    std::cin >> continueSelection;

                    // Ask the user how many more results they would like to see and update the position index accordingly
                    if (continueSelection == 1) {
                        std::cout << "\nHow many more results would you like to see? ";
                        std::cin >> moreResults;
                        
                        positionIndex += moreResults;
                        if (positionIndex >= quickSortData.size()) {
                            std::cout << "\nNo more results to show." << std::endl;
                            continueShowing = false;
                        } 
                        else {
                            printTopResults(quickSortData, ordered, positionIndex);
                        }
                    } 
                    else {
                        continueShowing = false;
                    }
                }
            }
            else if (comparisonValue == 3) {
                std::cout << "\nSorting by seasons..." << std::endl;
                sortHelper(quickSortData, mergeSortData, "seasons");
                printTopResults(quickSortData, ordered);

                bool continueShowing = true;
                int positionIndex = 10;
                int moreResults = 0;

                // Loop to allow the user to continue showing more results until they choose to stop or there are no more results to show
                while (continueShowing == true) {
                    int continueSelection = -1;
                    std::cout << "\nKEEP SHOWING?" << std::endl;
                    std::cout << "1. Yes" << std::endl;
                    std::cout << "2. No" << std::endl;
                    std::cout << "\nEnter Choice: ";
                    std::cin >> continueSelection;

                    // Ask the user how many more results they would like to see and update the position index accordingly
                    if (continueSelection == 1) {
                        std::cout << "\nHow many more results would you like to see? ";
                        std::cin >> moreResults;
                        
                        positionIndex += moreResults;
                        if (positionIndex >= quickSortData.size()) {
                            std::cout << "\nNo more results to show." << std::endl;
                            continueShowing = false;
                        } 
                        else {
                            printTopResults(quickSortData, ordered, positionIndex);
                        }
                    } 
                    else {
                        continueShowing = false;
                    }
                }
            }
        }
        else if (menu == 0) {
            std::cout << "\nExiting program." << std::endl;
        }
        else {
            std::cout << "\nInvalid option. Please try again." << std::endl;
        }
        ordered = false;
    }
    return 0;
}