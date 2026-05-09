#include <iostream>
#include <vector>
#include <cstdlib>
#include <omp.h>

using namespace std;

// ---------------- Sequential Bubble Sort ----------------
void sequentialBubbleSort(vector<int>& arr, int n) {

    for (int i = 0; i < n - 1; i++) {

        for (int j = 0; j < n - i - 1; j++) {

            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// ---------------- Parallel Bubble Sort ----------------
// Odd-Even Transposition Sort
void parallelBubbleSort(vector<int>& arr, int n) {

    for (int i = 0; i < n; i++) {

        // Even Phase
        if (i % 2 == 0) {

            #pragma omp parallel for
            for (int j = 0; j < n - 1; j += 2) {

                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }

        // Odd Phase
        else {

            #pragma omp parallel for
            for (int j = 1; j < n - 1; j += 2) {

                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }
}

// ---------------- Merge Function ----------------
void merge(vector<int>& arr, int low, int mid, int high) {

    vector<int> temp;

    int i = low;
    int j = mid + 1;

    while (i <= mid && j <= high) {

        if (arr[i] <= arr[j]) {
            temp.push_back(arr[i]);
            i++;
        }
        else {
            temp.push_back(arr[j]);
            j++;
        }
    }

    while (i <= mid) {
        temp.push_back(arr[i]);
        i++;
    }

    while (j <= high) {
        temp.push_back(arr[j]);
        j++;
    }

    for (int k = low; k <= high; k++) {
        arr[k] = temp[k - low];
    }
}

// ---------------- Sequential Merge Sort ----------------
void sequentialMergeSort(vector<int>& arr, int low, int high) {

    if (low < high) {

        int mid = (low + high) / 2;

        sequentialMergeSort(arr, low, mid);
        sequentialMergeSort(arr, mid + 1, high);

        merge(arr, low, mid, high);
    }
}

// ---------------- Parallel Merge Sort ----------------
void parallelMergeSort(vector<int>& arr, int low, int high) {

    if (low < high) {

        int mid = (low + high) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                parallelMergeSort(arr, low, mid);
            }

            #pragma omp section
            {
                parallelMergeSort(arr, mid + 1, high);
            }
        }

        merge(arr, low, mid, high);
    }
}

// ---------------- Print Array ----------------
void printArray(vector<int>& arr) {

    for (int x : arr) {
        cout << x << " ";
    }

    cout << endl;
}

int main() {

    vector<int>arr;
    int bubbleN=5000;

    for(int i=0;i<bubbleN;i++)
    {
        arr.push_back(rand()%bubbleN);
        //cout<<arr[i]<<" ";
    }

    // Copies of original array
    vector<int> bubbleSeq = arr;
    vector<int> bubblePar = arr;

    vector<int>arr1;
    int mergeN=1900000;

    for(int i=0;i<mergeN;i++)
    {
        arr1.push_back(rand()%mergeN);
        //cout<<arr[i]<<" ";
    }
    vector<int> mergeSeq = arr1;
    vector<int> mergePar = arr1;

    // Sequential Bubble Sort
    double start = omp_get_wtime();

    sequentialBubbleSort(bubbleSeq,bubbleN);

    double end = omp_get_wtime();

    double seqBubbleTime = end - start;

    cout << "\nSequential Bubble Sort:\n";

    cout << "Time Taken: "<< seqBubbleTime<< " seconds\n";

    // Parallel Bubble Sort
    start = omp_get_wtime();

    parallelBubbleSort(bubblePar, bubbleN);

    end = omp_get_wtime();

    double parBubbleTime = end - start;

    cout << "\nParallel Bubble Sort:\n";

    cout << "Time Taken: "<< parBubbleTime<< " seconds\n";

    cout << "Speedup: "<< seqBubbleTime / parBubbleTime<< endl;

    // Sequential Merge Sort
    start = omp_get_wtime();

    sequentialMergeSort(mergeSeq, 0, mergeN- 1);

    end = omp_get_wtime();

    double seqMergeTime = end - start;

    cout << "\nSequential Merge Sort:\n";

    cout << "Time Taken: "<< seqMergeTime<< " seconds\n";

    // Parallel Merge Sort
    start = omp_get_wtime();

    parallelMergeSort(mergePar, 0, mergeN - 1);

    end = omp_get_wtime();

    double parMergeTime = end - start;

    cout << "\nParallel Merge Sort:\n";

    cout << "Time Taken: "<< parMergeTime<< " seconds\n";

    cout << "Speedup: "<< seqMergeTime / parMergeTime<< endl;

    return 0;
}