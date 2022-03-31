#include<stdio.h>
#include<omp.h>
#include<sys/time.h>
#include<time.h>
#include<stdlib.h>

int main(){
    FILE *fp;
    fp = fopen("KittenRGB.txt","r");
    if(fp == NULL)
    {
        printf("Error while opening the file\n ");
        exit(0);
    }

    int i=0,num=0;
    int totalsize = 300*300;
    int red[totalsize],green[totalsize],blue[totalsize];
    while(!feof(fp) && i!= totalsize)
    {
        fscanf(fp,"%d",&num);
        red[i] = num;
        fscanf(fp,"%d",&num);
        green[i] = num;
        fscanf(fp,"%d",&num);
        blue[i] = num;
        i++;
    }
    fclose(fp);

    fp = fopen("KittenGrayscale.txt","w");
    if(fp == NULL)
    {
        printf("Error while opening the file\n ");
        exit(0);
    }

    double grayscale[totalsize];
    struct timeval TimeValue_Start;
    struct timezone TimeZone_Start;
    struct timeval TimeValue_Final;
    struct timezone TimeZone_Final;
    long time_start, time_end;
    double time_overhead;// Sequential Execution
    gettimeofday(&TimeValue_Start,&TimeZone_Start);
    for(i=0;i<totalsize;i++)
    {
        grayscale[i] = red[i]*0.21 + green[i]*0.72 + blue[i]*0.07;
    }
    gettimeofday(&TimeValue_Final,&TimeZone_Final);
    time_start = TimeValue_Start.tv_sec * 1000000 + TimeValue_Start.tv_usec;
    time_end = TimeValue_Final.tv_sec * 1000000 + TimeValue_Final.tv_usec;
    time_overhead = (time_end - time_start)/1000000.0;
    
    for(i=0;i<totalsize;i++)
    {
        printf("Grayscale[%d] = %lf \n",i,grayscale[i]);
        fprintf(fp, "%lf\n",grayscale[i] );
    }
    fclose(fp);
    printf("Time taken for Sequential execution is %lf\n",time_overhead);
    
    // Parallel execution with 2 threads
    gettimeofday(&TimeValue_Start,&TimeZone_Start);    
    #pragma omp parallel num_threads(2) default(shared)
    {
        #pragma omp for
        for(i=0;i<totalsize;i++)
        {
            grayscale[i] = red[i]*0.21 + green[i]*0.72 + blue[i]*0.07;
        }
    }
    gettimeofday(&TimeValue_Final,&TimeZone_Final);
    time_start = TimeValue_Start.tv_sec * 1000000 + TimeValue_Start.tv_usec;
    time_end = TimeValue_Final.tv_sec * 1000000 + TimeValue_Final.tv_usec;
    time_overhead = (time_end - time_start)/1000000.0;
    printf("Time taken for parallel execution with 2 threads is %lf\n",time_overhead);
    
    // Parallel execution with 4 threads
    gettimeofday(&TimeValue_Start,&TimeZone_Start);
    #pragma omp parallel num_threads(4) default(shared)
    {
        #pragma omp for
        for(i=0;i<totalsize;i++)
        {
            grayscale[i] = red[i]*0.21 + green[i]*0.72 + blue[i]*0.07;
        }
    }
    gettimeofday(&TimeValue_Final,&TimeZone_Final);
    time_start = TimeValue_Start.tv_sec * 1000000 + TimeValue_Start.tv_usec;
    time_end = TimeValue_Final.tv_sec * 1000000 + TimeValue_Final.tv_usec;
    time_overhead = (time_end - time_start)/1000000.0;
    printf("Time taken for parallel execution with 4 threads is %lf\n",time_overhead);
    
    // Parallel execution with 8 threads
    gettimeofday(&TimeValue_Start,&TimeZone_Start);
    #pragma omp parallel num_threads(8) default(shared)
    {
        #pragma omp for
        for(i=0;i<totalsize;i++)
        {
            grayscale[i] = red[i]*0.21 + green[i]*0.72 + blue[i]*0.07;
        }
    }
    gettimeofday(&TimeValue_Final,&TimeZone_Final);
    time_start = TimeValue_Start.tv_sec * 1000000 + TimeValue_Start.tv_usec;
    time_end = TimeValue_Final.tv_sec * 1000000 + TimeValue_Final.tv_usec;
    time_overhead = (time_end - time_start)/1000000.0;
    printf("Time taken for parallel execution with 8 threads is %lf\n",time_overhead);
    
    // Parallel execution with 16 threads
    gettimeofday(&TimeValue_Start,&TimeZone_Start);
    #pragma omp parallel num_threads(16) default(shared)
    {
        #pragma omp for
        for(i=0;i<totalsize;i++)
        {
            grayscale[i] = red[i]*0.21 + green[i]*0.72 + blue[i]*0.07;
        }
    }
    gettimeofday(&TimeValue_Final,&TimeZone_Final);
    time_start = TimeValue_Start.tv_sec * 1000000 + TimeValue_Start.tv_usec;
    time_end = TimeValue_Final.tv_sec * 1000000 + TimeValue_Final.tv_usec;
    time_overhead = (time_end - time_start)/1000000.0;
    printf("Time taken for parallel execution with 16 threads is %lf\n",time_overhead);
}