#include "sort.h"
#include <algorithm>

// Function to compare two CSVData objects based on the specified sorting criteria
bool sortCriteria(const CSVData& a, const CSVData& b, const std::string& sortBy) {
    if (sortBy == "name")
        return a.name < b.name;

    if (sortBy == "popularity")
        return a.popularity > b.popularity;

    if (sortBy == "seasons")
        return a.seasons > b.seasons;

    return false;
}

// Merge helper for merge sort that merges two sorted subarrays based on the specified sorting criteria
void merge(std::vector<CSVData>& data, int left, int mid, int right, const std::string& sortBy) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<CSVData> L(n1);
    std::vector<CSVData> R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = data[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = data[mid + 1 + j];

    int i = 0, j = 0, k = left;

    // Merge the two subarrays based on the specified sorting criteria
    while (i < n1 && j < n2) {
        if (sortBy == "name") {
            if (L[i].name <= R[j].name) {
                data[k] = L[i];
                i++;
            } else {
                data[k] = R[j];
                j++;
            }
        } 
        else if (sortBy == "popularity") {
            if (L[i].popularity >= R[j].popularity) {
                data[k] = L[i];
                i++;
            } else {
                data[k] = R[j];
                j++;
            }
        } 
        else if (sortBy == "seasons") {
            if (L[i].seasons >= R[j].seasons) {
                data[k] = L[i];
                i++;
            } else {
                data[k] = R[j];
                j++;
            }
        }
        k++;
    }

    while (i < n1) {
        data[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        data[k] = R[j];
        j++;
        k++;
    }
}

// Quick sort function that sorts the data based on the specified sorting criteria
void quickSort(std::vector<CSVData>& data, int low, int high, const std::string& sortBy) {
    if (low >= high)
        return;

    const CSVData& pivot = data[high];
    int lessThan = low;
    int greaterThan = high;
    int i = low;

    // Partition the data into three parts: less than, equal to, and greater than the pivot based on the specified sorting criteria
    while (i <= greaterThan) {
        if (sortCriteria(data[i], pivot, sortBy)) {
            std::swap(data[lessThan], data[i]);
            lessThan++;
            i++;
        }
        else if (sortCriteria(pivot, data[i], sortBy)) {

            std::swap(data[i], data[greaterThan]);
            greaterThan--;
        }
        else {
            i++;
        }
    }

    quickSort(data, low, lessThan - 1, sortBy);
    quickSort(data, greaterThan + 1, high, sortBy);
}

// Merge sort function that sorts the data based on the specified sorting criteria
void mergeSort(std::vector<CSVData>& data, int left, int right, const std::string& sortBy) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(data, left, mid, sortBy);
        mergeSort(data, mid + 1, right, sortBy);
        merge(data, left, mid, right, sortBy);
    }
}