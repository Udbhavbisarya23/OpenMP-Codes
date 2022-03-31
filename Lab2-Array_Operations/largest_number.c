#include <stdio.h>
#include <omp.h>

int main()
{
    int n, cur_max = 0;
    printf("Enter length of array: ");
    scanf("%d", &n);
    int array[100] = {0};
    printf("Enter elements in array: \n");
    
    for (int a = 0; a < n; a++)
    {
        scanf("%d", &array[a]);
    }
    
    #pragma omp parallel for
    for (int i = 0; i < n; i = i + 1)
    {
        if (array[i] > cur_max)
            #pragma omp critical
            if (array[i] > cur_max)
                cur_max = array[i];
    }
    printf("Largest number: %d\n", cur_max);
}