#include <stdio.h>
#include <omp.h>

int main(void)
{
    int n;
    printf("Enter number of elements in each array: ");
    scanf("%d", &n);
    int A[100] = {0}, B[100] = {0}, C[100] = {0};
    printf("Enter elements of array B: \n");
    for (int i = 0; i< n; i++)
    {
        scanf("%d", &B[i]);
    }
    
    printf("Enter elements of array C: \n");
    
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &C[i]);
    }
    
    #pragma omp parallel shared(A)
    {
        #pragma omp for
        for (int i = 0; i < n; i++)
        {
            A[i] = B[i] + C[i];
        }
    }
    
    printf("Elements in array A after calculation: \n");
    for (int a = 0; a < n; a++)
    {
        printf("%d ", A[a]);
    }
    printf("\n");
}