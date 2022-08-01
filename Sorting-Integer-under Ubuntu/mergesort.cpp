#include "mergesort.h"
#include <sys/wait.h>

int* MergeSort::sort(int* arr, int l, int r, int depth)
{
    using namespace std;
    
    if (l < r) 
    {   

        int m = l+(r-l)/2; 
        
        pid_t lpid, rpid;
        lpid = fork();
        if(lpid< 0)
        {
            cout<< "Left child is not created" << endl;
            _exit(-1);
        }
        else if(lpid ==0)
        {
            cout<< depth << " depth | PID:" << getpid() << " | left split ";
            for(int i = l; i<=m; i++)
            {
                cout<<arr[i]<<" ";
            }
            cout<< endl << flush;
            sort(arr, l, m, depth +1);

            
            
            _exit(0);
            
        }
        

       /*  rpid = fork();
        if (rpid< 0)
        {
            cout<< "right child is not created"<< endl;
            _exit(-1);
        }
        else if (rpid ==0)
        {
            sort(arr, m+1, r); 
            _exit(0);    
        }
 */     cout<< depth << " depth | PID:" << getpid() << " | right split ";
        for(int i = m+1; i<=r; i++)
        {
            cout<<arr[i]<<" ";
        }
        cout<< endl << flush;
        sort(arr, m+1, r,depth +1); 
        int status; 
  
        // Wait for child processes to finish 
        waitpid(lpid, &status, 0); 
        //waitpid(rpid, &status, 0); 
        merge(arr, l, m, r); 
    } 
}

void MergeSort::merge(int *arr, int l, int m , int r)
{
    /*shared between all function calls
    static int x = 0;
    x++;

    // Not shared between all function calls (local to current call)
    int y = 0;
    y++;

    // Non static
    MergeSort s;
    s.sort(nullptr);

    // Static
    MergeSort::sort(nullptr);
    */
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    /* create temp arrays */
    int L[n1], R[n2]; 
  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
  
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = l; // Initial index of merged subarray 
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    /* Copy the remaining elements of L[], if there 
       are any */
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    /* Copy the remaining elements of R[], if there 
       are any */
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
}