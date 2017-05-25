/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: TS
 *
 * Created on 25. Mai 2017, 16:59
 */

#include <cstdlib>
#include <iostream> //ausgabe
//#include <chrono> //zeitmessung
#include <random> //rnd nmbrs

using namespace std;

/*T ist template array ; anzahl ist die genaue anzahl der elemente
//Quelle: https://web.archive.org/web/20150303084352/http://www.sorting-algorithms.com:80/bubble-sort
 Stable
O(1) extra space
O(n2) comparisons and swaps
Adaptive: O(n) when nearly sorted
 */
template<typename T>
void bubbleSort(T liste[], int anzahl) {
    T temp;
    for (int i = 0; i < anzahl; i++) {
        bool swap = false;
        for (int j = i + 1; j < anzahl; j++) {

            if (liste[i] > liste[j]) {
                temp = liste[i];
                liste[i] = liste[j];
                liste[j] = temp;
                swap = true;
            }
        }
        if (!swap) {
            return;
        }
    }
}

/*T ist template array ; anzahl ist die genaue anzahl der elemente
//Quelle: https://web.archive.org/web/20150226113436/http://www.sorting-algorithms.com:80/selection-sort
Not stable
O(1) extra space
Θ(n2) comparisons
Θ(n) swaps
Not adaptive        -> minimale SwapAnzahl!!!!


A small example:
Let b = B in
< B > , < b > , < a > , < C > (with a < b < c)
After one cycle the sequence is sorted but the order of B and b has changed:
< a > , < b > , < B > , < c >
 */
template<typename T>
void selectionSort(T liste[], int anzahl) {
    int k;
    T temp;
    for (int i = 0; i < anzahl; i++) {
        k = i;
        for (int j = i + 1; j < anzahl; j++) {
            if (liste[j] < liste[k]) {
                k = j;
            }
        }
        //swap
        temp = liste[i];
        liste[i] = liste[k];
        liste[k] = temp;


    }

}

/*
 * arr : Liste ; left 0 , right -> anzahl -1
 * Quelle: http://www.algolist.net/Algorithms/Sorting/Quicksort
 */
template<typename T>
void quickSort(T arr[], int left, int right) {
    int i = left, j = right;
    T tmp;
    int pivot = arr[(left + right) / 2];

    /* partition */
    while (i <= j) {
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i <= j) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    };

    /* recursion */
    if (left < j)
        quickSort(arr, left, j);
    if (i < right)
        quickSort(arr, i, right);
}
// quelel: http://www.geeksforgeeks.org/merge-sort/
template<typename T>
void merge(T arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    /* create temp arrays */
    T L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
template <typename T>
void mergeSort(T arr[], int l, int r) {
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

/*
 Quelle: http://www.geeksforgeeks.org/heap-sort/
 */
template <typename T>
void heapify(T arr[], int n, int i)
{
    int largest = i;  // Initialize largest as root
    int l = 2*i + 1;  // left = 2*i + 1
    int r = 2*i + 2;  // right = 2*i + 2
 
    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
        largest = l;
 
    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
        largest = r;
 
    // If largest is not root
    if (largest != i)
    {
        swap(arr[i], arr[largest]);
 
        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}
 
// main function to do heap sort
template <typename T>
void heapSort(T arr[], int n)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
 
    // One by one extract an element from heap
    for (int i=n-1; i>=0; i--)
    {
        // Move current root to end
        swap(arr[0], arr[i]);
 
        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}



template <typename T>
bool checkSorted(T liste[], int anzahl) {
    for (int i = 0; i < anzahl - 1; i++) {
        if (liste[i] > liste[i + 1]) {
            return false;
        }
    }
    return true;

}

template<typename T>
void randomNumbers(T liste[], int von, int bis, int anzahl){
    random_device seed;
    mt19937 engine(seed());
    uniform_int_distribution<T> values(von, bis);
    for(int i = 0; i < anzahl;i++){
        liste[i] = values(engine);
    }
}

template<typename T>
void printArray(T liste[], int count){
        for (int i = 0; i < count; i++) {
        cout << liste[i] << endl;
    }
}

//nur für Arrays

int main(int argc, char** argv) {
    int count = 100000;
    int *a = 0;
    a = new int[count];
    
    randomNumbers(a, 0 , 1000000, count);
    
    
    
    
    
    clock_t begin = clock();
    
    
    
    //bubbleSort(a, count);
    //selectionSort(a, count);
    //quickSort(a, 0, count - 1);
    //mergeSort(a, 0 , count - 1);
    heapSort(a,count);
    
    clock_t end = clock();
    cout << "Sorted: " << checkSorted(a, count) <<" in : "<<end-begin <<" ms"<< CLOCKS_PER_SEC<<  endl;
    

    return 0;
}

