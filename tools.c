void calcTime()
{
    time_start = TimeValue_Start.tv_sec * 1000000 + TimeValue_Start.tv_usec;
    time_end = TimeValue_Final.tv_sec * 1000000 + TimeValue_Final.tv_usec;
    time_overhead = time_overhead + (time_end - time_start)/1000000.0;
    //printf("Time Overhead = %lf\n", time_overhead); 
}