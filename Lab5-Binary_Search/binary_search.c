#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <omp.h>
void merge(int arr[],int start,int mid,int end)
{
    int arr1[mid-start+1];
    int arr2[end-mid];
    for(int i=start;i<=mid;i++)
    {
        arr1[i-start] = arr[i];
    }
    for(int i=mid+1;i<=end;i++)
    {
        arr2[i-mid-1] = arr[i];
    }
    
    int i=start;
    int j=start;
    int k=mid+1;
    
    while(j<=mid && k<=end)
    {
        if(arr1[j-start] < arr2[k-mid-1])
        {
            arr[i++] = arr[j-start];
            j++;
        }
        else
        {
            arr[i++] = arr[k-mid-1];
            k++;
        }
    }
    
    while(j<=mid)
    {
        arr[i++] = arr[j-start];
        j++;
    }
    
    while(k<=end)
    {
        arr[i++] = arr[k-mid-1];
        k++;
    }
}
    
void mergesort(int arr[],int start,int end)
{
    if(start < end)
    {
        int mid = start + (end-start)/2;
        mergesort(arr,start,mid);
        mergesort(arr,mid+1,end);
        merge(arr,start,mid,end);
    }
}

int binary(int arr[], int l, int r, int ele)
{
    if (l > r)
    {
        return -1;
    }
    if (l == r)
    {
        if (arr[l] == ele)
        {
            return l;
        }
        return -1;
    }

    int mid = l + (r-l)/2;
    if (arr[mid] == ele)
    {
        return mid;
    }
    int ind = -1;
    
    #pragma omp parallel for num_threads(4)
    for(int i=0;i<2;i++)
    {
        if(i==0)
        {
            if(arr[mid] < ele)
            {
                int temp = binary(arr,l,mid-1,ele);
                if(temp>-1)
                    ind = temp;
            }
        }
        else
        {
            if(arr[mid] > ele)
            {
                int temp = binary(arr,mid+1,r,ele);
                if(temp>-1)
                    ind = temp;
            }
        }
    }
    return ind;
}

int main()
{
    srand(time(0));
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand()%n;
    }

    int ind=-1,ele;
    printf("Enter Element to be searched for: ");
    scanf(" %d",&ele);
    
    struct timeval TimeValue_Start;
    struct timezone TimeZone_Start;
    struct timeval TimeValue_Final;
    struct timezone TimeZone_Final;
    long time_start, time_end;
    double time_overhead;
    // Sorting the array using merge sort
    mergesort(arr,0,n-1);
    // Sequential binary search
    ind = -1;
    
    gettimeofday(&TimeValue_Start, &TimeZone_Start);
    long start = 0,end=n-1;
    
    while(start < end && end>0)
    {
        long mid = start + (end-start)/2;
        if(arr[mid] == ele)
        {
            ind = mid;
            start = end+1;
        }
        else if(arr[mid] < ele)
        {
            start = mid+1;
        }
        else
        {
            end = mid-1;
        }
    }
    gettimeofday(&TimeValue_Final, &TimeZone_Final);
    time_start = TimeValue_Start.tv_sec * 1000000 + TimeValue_Start.tv_usec;
    time_end = TimeValue_Final.tv_sec * 1000000 + TimeValue_Final.tv_usec;
    time_overhead = (time_end - time_start)/1000000.0;
    printf("Sequential binary Search Time: %lf\n", time_overhead);
    
    if (ind == -1)
    {
        printf("Element not found\n\n");
    }
    else{
        printf("Element found at: %d\n\n", ind);
    }


    // Parallel Binary Search
    ind = -1;
    
    gettimeofday(&TimeValue_Start, &TimeZone_Start);
    ind = binary(arr,0,n-1,ele);
    gettimeofday(&TimeValue_Final, &TimeZone_Final);
    time_start = TimeValue_Start.tv_sec * 1000000 + TimeValue_Start.tv_usec;
    time_end = TimeValue_Final.tv_sec * 1000000 + TimeValue_Final.tv_usec;
    time_overhead = (time_end - time_start)/1000000.0;
    printf("Parallel binary Search Time: %lf\n", time_overhead);
    
    if (ind == -1)
    {
        printf("Element not found\n\n");
    }
    else
    {
        printf("Element found at: %d\n\n", ind);
    }
}