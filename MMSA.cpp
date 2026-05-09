#include<iostream>
#include<omp.h>
#include<vector>
using namespace std;


int sum_p(int n,vector<int>&arr)
{
    int tot=0;
    #pragma omp parallel for reduction(+:tot)
    for(int i=0;i<n;i++)
    {
        tot+=arr[i];
    }
    return tot;
}
int average_p(int n,vector<int>&arr)
{
    int tot=0;
    #pragma omp parallel for reduction(+:tot)
    for(int i=0;i<n;i++)
    {
        tot+=arr[i];
    }
    return tot/n;
}
int maximum_p(int n,vector<int>&arr)
{
    int max_value=arr[0];
    #pragma omp parallel for reduction(max:max_value)
    for(int i=0;i<n;i++)
    {
        if(max_value<arr[i])
        {
            max_value=arr[i];
        }
    }
    return max_value;
}
int minimum_p(int n,vector<int>&arr)
{
    int min_value=arr[0];
    #pragma omp parallel for reduction(min:min_value)
    for(int i=0;i<n;i++)
    {
        if(min_value>arr[i])
        {
            min_value=arr[i];
        }
    }
    return min_value;
}
//Sequential
int sum(int n,vector<int>&arr)
{
    int tot=0;
    for(int i=0;i<n;i++)
    {
        tot+=arr[i];
    }
    return tot;
}
int average(int n,vector<int>&arr)
{
    int tot=0;
    for(int i=0;i<n;i++)
    {
        tot+=arr[i];
    }
    return tot/n;
}
int maximum(int n,vector<int>&arr)
{
    int max_value=arr[0];
    for(int i=0;i<n;i++)
    {
        if(max_value<arr[i])
        {
            max_value=arr[i];
        }
    }
    return max_value;
}
int minimum(int n,vector<int>&arr)
{
    int min_value=arr[0];
    for(int i=0;i<n;i++)
    {
        if(min_value>arr[i])
        {
            min_value=arr[i];
        }
    }
    return min_value;
}
int main()
{
    vector<int>arr;
    int n=1e7;

    for(int i=0;i<n;i++)
    {
        arr.push_back(rand()%n);
        //cout<<arr[i]<<" ";
    }
    cout<<"\nFor Sequential Execution\n";

    double start= omp_get_wtime();
    int seq_sum=sum(n,arr);
    double end= omp_get_wtime();
    double seq_sum_time=end-start;
    cout<<"Sum: "<<seq_sum<<"\n";
    cout<<"Time taken: "<<seq_sum_time<< "seconds\n";

    start=omp_get_wtime();
    int seq_avg=average(n,arr);
    end=omp_get_wtime();
    double seq_avg_time=end-start;
    cout<<"Average: "<<seq_avg<<"\n";
    cout<<"Time taken: "<<seq_avg_time<< "seconds\n";

    start=omp_get_wtime();
    int seq_max=maximum(n,arr);
    end=omp_get_wtime();
    double seq_max_time=end-start;
    cout<<"Maximum: "<<seq_max<<"\n";
    cout<<"Time taken: "<<seq_max_time<< "seconds\n";

    start=omp_get_wtime();
    int seq_min=minimum(n,arr);
    end=omp_get_wtime();
    double seq_min_time=end-start;
    cout<<"Minimum: "<<seq_min<<"\n";
    cout<<"Time taken: "<<seq_min_time<< "seconds\n";

    cout<<"\nFor Parallel Execution\n";
    
    start=omp_get_wtime();
    int par_sum=sum_p(n,arr);
    end=omp_get_wtime();
    double par_sum_time=end-start;
    cout<<"Sum: "<<par_sum<<"\n";
    cout<<"Time taken: "<<par_sum_time<< "seconds\n";

    start=omp_get_wtime();
    int par_avg=average_p(n,arr);
    end=omp_get_wtime();
    double par_avg_time=end-start;
    cout<<"Average: "<<par_avg<<"\n";
    cout<<"Time taken: "<<par_avg_time<< "seconds\n";


    start=omp_get_wtime();
    int par_max=maximum_p(n,arr);
    end=omp_get_wtime();
    double par_max_time=end-start;
    cout<<"Maximum: "<<par_max<<"\n";
    cout<<"Time taken: "<<par_max_time<< "seconds\n";

    start=omp_get_wtime();
    int par_min=minimum_p(n,arr);
    end=omp_get_wtime();
    double par_min_time=end-start;
    cout<<"Minimum: "<<par_min<<"\n";
    cout<<"Time taken: "<<par_min_time<< "seconds\n";



}

