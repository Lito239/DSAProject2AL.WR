#include "sort.h"
#include <algorithm>

bool sortCriteria(const CSVData& a, const CSVData& b, const std::string& sortBy) {
    if (sortBy == "name") {
        return a.name < b.name;
    }

    if (sortBy == "popularity") {
        return a.popularity > b.popularity;
    }

    if (sortBy == "seasons") {
        return a.seasons > b.seasons;
    }

    return false;
}

int partition(std::vector<CSVData>& data, int low, int high, const std::string& sortBy) {
    const CSVData& pivot = data[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {

        if (sortCriteria(data[j], pivot, sortBy)) {
            i++;
            std::swap(data[i], data[j]);
        }

    }

    std::swap(data[i + 1], data[high]);
    return i + 1;
}

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

    while (i < n1 && j < n2) {
        if (sortBy == "name") {
            if (L[i].name <= R[j].name) {
                data[k] = L[i];
                i++;
            } else {
                data[k] = R[j];
                j++;
            }
        } else if (sortBy == "popularity") {
            if (L[i].popularity >= R[j].popularity) {
                data[k] = L[i];
                i++;
            } else {
                data[k] = R[j];
                j++;
            }
        } else if (sortBy == "seasons") {
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

void quickSort(std::vector<CSVData>& data, int low, int high, const std::string& sortBy) {
    if (low < high) {
        int pi = partition(data, low, high, sortBy);
        quickSort(data, low, pi - 1, sortBy);
        quickSort(data, pi + 1, high, sortBy);
    }
}

void mergeSort(std::vector<CSVData>& data, int left, int right, const std::string& sortBy) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(data, left, mid, sortBy);
        mergeSort(data, mid + 1, right, sortBy);
        merge(data, left, mid, right, sortBy);
    }
}