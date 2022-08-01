#include <iostream>
#include<stdlib.h>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include "tool.h"
#include "mergesort.h"

int main(int argc, char **argv)
{ 
    
    using namespace std;
    string number = "";

    int numberfromtxt = 0;
    ifstream file;
    if (argc < 3)
    {
        cout << "Not enough arguments"<< endl;
        cout << "Usage: " << argv[0] << " [file name] [delimeter]" << endl;
        return 1;
    }

    file.open(argv[1]);

    char ch;

    while (file >> noskipws >> ch) {
        number += ch;
    }

    std::vector<std::string>inputNumber = split(number, argv[2]);
    int* numbersArr = new int[inputNumber.size()];

    for (int i =0; i< inputNumber.size(); i++)
    {
        try{numbersArr[i]=stoi(inputNumber[i]);}
        catch(const std::invalid_argument& e)
        {
            cout<< "file has character"<< endl;
            cout << "Usage: " << argv[0] << " [int file name] [delimeter]" << endl;
            exit(1);
        }
    }
  
    printf("Given array is \n");
    printArray(numbersArr, inputNumber.size());

    int shmid;
    key_t key = IPC_PRIVATE;
    int *shm_array; 
    size_t SHM_SIZE = inputNumber.size()*sizeof(int);
    if ((shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666)) < 0) 
    { 
        perror("shmget"); 
        _exit(1); 
    } 
    if ((shm_array = (int*)shmat(shmid, NULL, 0)) == (int *) -1) 
    { 
        perror("shmat"); 
        _exit(1); 
    } 
    


    for(int i =0; i<inputNumber.size(); i++)
    {
        shm_array[i]=numbersArr[i];
    }

    MergeSort::sort(shm_array, 0 , inputNumber.size() -1, 0);
    printf("\nSorted array is \n"); 
    printArray(shm_array, inputNumber.size());

    if (shmdt(shm_array) == -1) 
    { 
        perror("shmdt"); 
        _exit(1); 
    } 
  
    /* Delete the shared memory segment. */
    if (shmctl(shmid, IPC_RMID, NULL) == -1) 
    { 
        perror("shmctl"); 
        _exit(1); 
    }
       

    

    file.close();

    return 0;



}