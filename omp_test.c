#include <stdio.h>
#include <omp.h>
#include <time.h>
     


int main(int argc, char** argv){

    clock_t start, end;
    int * arr = malloc(sizeof(int) * 1000000);

    start = clock();
    #pragma omp parallel shared(arr)
    {

        #pragma omp for 
        for(int i = 0; i<1000000;i++)
        {
            arr[i] = i;
        }

    }
    end = clock();
    printf("threaded: %f\n",((double) (end - start)) / CLOCKS_PER_SEC);
    int * arr2 = malloc(sizeof(int) * 1000000);
    start = clock();
    for(int i = 0; i<1000000;i++)
    {
        arr2[i] = i;
    }

    end = clock();
    printf("single core: %f\n",((double) (end - start)) / CLOCKS_PER_SEC);


    return 0;
}