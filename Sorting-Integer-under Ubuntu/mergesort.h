#ifndef MERGESORT_H_INCLUDED
#define MERGESORT_H_INCLUDED
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <iostream>

class MergeSort
{
    public:
        static int* sort(int* arr, int , int, int);

    private:
        static void merge(int *arr, int l, int m , int r);
};





#endif MERGESORT_H_INCLUDED