#include<stdio.h>
#include "pm.h"
#include <minix/keymap.h>
#include <minix/callnr.h>
#include <minix/com.h>
#include <minix/endpoint.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <string.h>
#include "mproc.h"
#include "param.h"
#include <math.h>

#define runLimit 30


float calculateSD(float localeByteArr[runLimit], int nrHoles )
{
    float sum = 0.0, mean, standardDeviation = 0.0;
    int i;
    for(i=0; i<nrHoles; ++i)
    {
        sum += localeByteArr[i];
    }
	mean = sum/nrHoles;
	for(i=0; i<nrHoles; ++i)
    {
		standardDeviation += pow(localeByteArr[i] - mean, 2);
	}
	return sqrt(standardDeviation/nrHoles);
}


float calculateMedian(float localeByteArr[runLimit], int nrHoles ) 
{
    float temp;
    int i, j;
    
	for(i=0; i<nrHoles-1; i++) {
        for(j=i+1; j<nrHoles; j++) {
            if(localeByteArr[j] < localeByteArr[i]) {
                temp = localeByteArr[i];
                localeByteArr[i] = localeByteArr[j];
                localeByteArr[j] = temp;
            }
        }
    }

    if(nrHoles%2==0) {
       return((localeByteArr[nrHoles/2] + localeByteArr[nrHoles/2 - 1]) / 2.0);
    } else {
        return localeByteArr[nrHoles/2];
    }
}


PUBLIC int main(int argc, char *argv[])
{
	struct pm_mem_info pmi;
	int numofholes, h;
	int total_bytes = 0, total_bytes_per_hole = 0;
	FILE *fptr;
	int runCount = 0;
	
	if(argc < 2)
	{
		printf("Usage memlog logfilename\n");
		exit(-1);
	}
	
	fptr = fopen(argv[1], "w");
	if(fptr == NULL)
	{
	  printf("File Error!");
	  exit(-2);
	} 
	fprintf(fptr, "-------------------------------------------------------------\n");
	fprintf(fptr, "Time(s)\t nholes \t avg_size_in_bytes \t std_dev_size_in_bytes \t median_in_bytes\n");
	fclose(fptr);
	
	while(runCount < runLimit)
	{
		float byteArrForCalc[runLimit];
		int noOfValidBytes = 0;
		total_bytes = 0, total_bytes_per_hole = 0;
		fptr = fopen(argv[1], "a");
		if(fptr == NULL)
		{
		  printf("File Error!");
		  exit(-2);
		} 
		getsysinfo(PM_PROC_NR, SI_MEM_ALLOC, &pmi);
		for(h = 0; h < _NR_HOLES; h++) 
		{
			if(pmi.pmi_holes[h].h_base && pmi.pmi_holes[h].h_len) 
			{
				int bytes;
				bytes = pmi.pmi_holes[h].h_len << CLICK_SHIFT;
				total_bytes += bytes;
				
				if(bytes > 0)
				{
					byteArrForCalc[noOfValidBytes]=bytes;
					noOfValidBytes++;
				}
			}
		}

		total_bytes_per_hole = (total_bytes/(noOfValidBytes));
		
		
		
		
		fprintf(fptr, "%d\t    %d\t\t  %d\t\t  %f\t%f\n",runCount, noOfValidBytes, total_bytes_per_hole, calculateSD(byteArrForCalc,noOfValidBytes), calculateMedian(byteArrForCalc,noOfValidBytes));
		fclose(fptr);
		runCount++;
		sleep(1);
	}	
	
	return 0;
}

