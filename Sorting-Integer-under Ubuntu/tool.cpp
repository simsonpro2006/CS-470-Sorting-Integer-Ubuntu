#include "tool.h"

std::vector<std::string> split(std::string input, const std::string &delimiter)
{
    using namespace std;
    size_t loca = 0;
    vector<string> numberfromtext;
    while ((loca = input.find(delimiter)) != string::npos)
    {
        string TokenNumber = input.substr(0, loca);
        input.erase(0, loca+ delimiter.size());
        numberfromtext.push_back(TokenNumber);


    }
    numberfromtext.push_back(input);

    //string token = input.substr(0,)
    return numberfromtext;
}
void printArray(int A[], int size)
{
    int i; 
    for (i=0; i < size; i++) 
    {
        printf("%d ", A[i]); 
    }
        
    printf("\n"); 
}