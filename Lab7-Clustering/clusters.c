#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<time.h>
#include<omp.h>
#include<math.h>

double calc_Euclid(double x1,double y1,double x2,double y2)
{
    double num = (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
    return sqrt(num);
}

int main()
{
    srand(time(0));
    struct timeval TimeValue_Start;
    struct timezone TimeZone_Start;
    struct timeval TimeValue_Final;
    struct timezone TimeZone_Final;
    long time_start, time_end;
    double time_overhead;
    int n=1000,x_y_place = 2;
    int arr[n][x_y_place];
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<x_y_place;j++)
        {
            arr[i][j] = rand()%1001;
        }
        printf("Location of Node %d is x=%d and y=%d\n",i,arr[i][0],arr[i][1]);
    }

    int clusters;
    printf("Enter the number of clusters:-\n");
    scanf("%d",&clusters);
    int oldclustermeansx[clusters],oldclustermeansy[clusters];
    
    // Assigning the initial cluster means as the first k values in the array
    for(int i=0;i<clusters;i++)
    {
        oldclustermeansx[i] = arr[i][0];
        oldclustermeansy[i] = arr[i][1];
    }
    int iterations ;
    printf("Enter the number of iterations\n");
    scanf("%d",&iterations);
    int cluster_of_each_sensor[n];
    
    gettimeofday(&TimeValue_Start, &TimeZone_Start);
    #pragma omp parallel num_threads(4) default(shared)
    {
        #pragma omp for schedule(guided,4)
        for(int it=0;it<iterations;it++)
        {
            for(int i=0;i<n;i++)
            {
                cluster_of_each_sensor[i] = -1;
            }
            int clustersumx[clusters],clustersumy[clusters],clustercount[clusters];
            for(int i=0;i<clusters;i++)
            {
                clustersumx[i] = 0;
                clustersumy[i] = 0;
                clustercount[i] = 0;
            }
            // Calculating which cluster each sensor will be
            for(int i=0;i<n;i++)
            {
                double min = 20000;
                for(int j=0;j<clusters;j++)
                {
                    double temp =
                    calc_Euclid(arr[i][0],arr[i][1],oldclustermeansx[j],oldclustermeansy[j]);
                    #pragma omp critical
                    {
                        if(temp < min)
                        {
                            min = temp;
                            cluster_of_each_sensor[i] = j;
                        }
                    }
                }   
            int clusterofnode = cluster_of_each_sensor[i];
            clustersumx[clusterofnode] += arr[i][0];
            clustersumy[clusterofnode] += arr[i][1];
            clustercount[clusterofnode] ++;
            }
            double newclusterxmeans[clusters],newclusterymeans[clusters];
            _Bool foundmeans = 1;
            for(int i=0;i<clusters;i++)
            {
                newclusterxmeans[i] = ((double)clustersumx[i])/clustercount[i];newclusterymeans[i] = ((double)clustersumy[i])/clustercount[i];
            }
            _Bool ansfound = 1;
            for(int i=0;i<clusters;i++)
            {
                _Bool flag = 0;
                for(int j=0;j<clusters;j++)
                {
                    if(oldclustermeansx[i] == newclusterxmeans[j] &&
                    oldclustermeansy[i] == newclusterymeans[j])
                    {
                        flag = 1;
                        break;
                    }
                }
                if(!flag)
                {
                    for(int i=0;i<clusters;i++)
                    {
                    oldclustermeansx[i] = newclusterxmeans[i];
                    oldclustermeansy[i] = newclusterymeans[i];
                    }
                    ansfound = 0;
                    break;
                }
            }
        }
    }
    gettimeofday(&TimeValue_Final, &TimeZone_Final);
    time_start = TimeValue_Start.tv_sec * 1000000 + TimeValue_Start.tv_usec;
    time_end = TimeValue_Final.tv_sec * 1000000 + TimeValue_Final.tv_usec;
    time_overhead = (time_end - time_start)/1000000.0;
    printf("The cluster of each sensor is:-\n");
    
    for(int i=0;i<n;i++)
    {
        printf("Node %d is in cluster %d\n",i,cluster_of_each_sensor[i]);
    }
    printf("Final answers\n");
    
    for(int i=0;i<clusters;i++)
    {
        printf("x:-%d y:-%d\n",oldclustermeansx[i],oldclustermeansy[i]);
    }
    printf("The time taken for parallel execution is %f\n",time_overhead);
}