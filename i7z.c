//i7z.c
/* ----------------------------------------------------------------------- *
 *
 *   Copyright 2009 Abhishek Jaiantilal
 *
 *   Under GPL v2
 *
 * ----------------------------------------------------------------------- */

#include <memory.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <inttypes.h>
#include <sys/types.h>
#include <sys/time.h>
#include <time.h>
#include <ncurses.h>

#include "i7z.h"
//#include "CPUHeirarchy.h"

struct program_options prog_options;

int Single_Socket();
int Dual_Socket();


/////////////////////LOGGING TO FILE////////////////////////////////////////
FILE *fp_log_file;
FILE *fp_log_file1, *fp_log_file2;

void logOpenFile_single()
{
    if(prog_options.logging==1)
	fp_log_file = fopen(CPU_FREQUENCY_LOGGING_FILE_single,"w");
    else if(prog_options.logging==2)
	fp_log_file = fopen(CPU_FREQUENCY_LOGGING_FILE_single,"a");
}

void logCloseFile_single()
{
    if(prog_options.logging!=0){
	if(prog_options.logging==2)
	    fprintf(fp_log_file,"\n");
	//the above line puts a \n after every freq is logged.
	fclose(fp_log_file);
    }
}

void logCpuFreq_single(float value)
{
    //below when just logging
    if(prog_options.logging==1)
	fprintf(fp_log_file,"%f\n",value); //newline, replace \n with \t to get everything separated with tabs
   
    //below when appending
    if(prog_options.logging==2)
	fprintf(fp_log_file,"%f\t",value);
}

void logCpuFreq_single_c(char* value)
{
    //below when just logging
    if(prog_options.logging==1)
	fprintf(fp_log_file,"%s\n",value); //newline, replace \n with \t to get everything separated with tabs
   
    //below when appending
    if(prog_options.logging==2)
	fprintf(fp_log_file,"%s\t",value);
}

void logCpuFreq_single_d(int value)
{
    //below when just logging
    if(prog_options.logging==1)
	fprintf(fp_log_file,"%d\n",value); //newline, replace \n with \t to get everything separated with tabs
   
    //below when appending
    if(prog_options.logging==2)
	fprintf(fp_log_file,"%d\t",value);
}


// For dual socket make filename based on the socket number
void logOpenFile_dual(int socket_num)
{
	char str_file[100];
	snprintf(str_file,100,CPU_FREQUENCY_LOGGING_FILE_dual,socket_num);

	if(socket_num==0){
		if(prog_options.logging==1)
			fp_log_file1 = fopen(str_file,"w");
		else if(prog_options.logging==2)
			fp_log_file1 = fopen(str_file,"a");
	}
	if(socket_num==1){
		if(prog_options.logging==1)
			fp_log_file2 = fopen(str_file,"w");
		else if(prog_options.logging==2)
			fp_log_file2 = fopen(str_file,"a");
	}
}

void logCloseFile_dual(int socket_num)
{
	if(socket_num==0){
		if(prog_options.logging!=0){
			if(prog_options.logging==2)
				fprintf(fp_log_file1,"\n");
			//the above line puts a \n after every freq is logged.
			fclose(fp_log_file1);
		}
	}
	if(socket_num==1){
		if(prog_options.logging!=0){
			if(prog_options.logging==2)
				fprintf(fp_log_file2,"\n");
			//the above line puts a \n after every freq is logged.
			fclose(fp_log_file2);
		}
	}
}

void logCpuFreq_dual(float value,int socket_num)
{
	if(socket_num==0){
		//below when just logging
		if(prog_options.logging==1)
		fprintf(fp_log_file1,"%f\n",value); //newline, replace \n with \t to get everything separated with tabs
	   
		//below when appending
		if(prog_options.logging==2)
		fprintf(fp_log_file1,"%f\t",value);
	}
	if(socket_num==1){
		//below when just logging
		if(prog_options.logging==1)
		fprintf(fp_log_file2,"%f\n",value); //newline, replace \n with \t to get everything separated with tabs
	   
		//below when appending
		if(prog_options.logging==2)
		fprintf(fp_log_file2,"%f\t",value);
	}
}

void logCpuFreq_dual_c(char* value,int socket_num)
{
	if(socket_num==0){
		//below when just logging
		if(prog_options.logging==1)
		fprintf(fp_log_file1,"%s\n",value); //newline, replace \n with \t to get everything separated with tabs
	   
		//below when appending
		if(prog_options.logging==2)
		fprintf(fp_log_file1,"%s\t",value);
	}
	if(socket_num==1){
		//below when just logging
		if(prog_options.logging==1)
		fprintf(fp_log_file2,"%s\n",value); //newline, replace \n with \t to get everything separated with tabs
	   
		//below when appending
		if(prog_options.logging==2)
		fprintf(fp_log_file2,"%s\t",value);
	}
}

void logCpuFreq_dual_d(int value,int socket_num)
{
	if(socket_num==0){
		//below when just logging
		if(prog_options.logging==1)
		fprintf(fp_log_file1,"%d\n",value); //newline, replace \n with \t to get everything separated with tabs
	   
		//below when appending
		if(prog_options.logging==2)
		fprintf(fp_log_file1,"%d\t",value);
	}
	if(socket_num==1){
		//below when just logging
		if(prog_options.logging==1)
		fprintf(fp_log_file2,"%d\n",value); //newline, replace \n with \t to get everything separated with tabs
	   
		//below when appending
		if(prog_options.logging==2)
		fprintf(fp_log_file2,"%d\t",value);
	}
}


//Info: I start from index 1 when i talk about cores on CPU

int main (int argc, char **argv)
{
    prog_options.logging=0; //0=no logging, 1=logging, 2=appending

    //////////////////// GET ARGUMENTS //////////////////////
    int c;
    char *cvalue = NULL;
    while( (c=getopt(argc,argv,"w:")) !=-1){
		cvalue = optarg;
    	//printf("argument %c\n",c);
    	if(cvalue == NULL){
    	    printf("With -w option, requires an argument for append or logging\n");
    	    exit(1);
    	}else{
     	    //printf("         %s\n",cvalue);
     	    if(strcmp(cvalue,"a")==0){
     		printf("Appending frequencies to %s (single_socket) or cpu_freq_log_dual_(%d/%d).txt (dual socket)\n", CPU_FREQUENCY_LOGGING_FILE_single,0,1);
     		prog_options.logging=2;
     	    }else if(strcmp(cvalue,"l")==0){
     		printf("Logging frequencies to %s (single socket) or cpu_freq_log_dual_(%d/%d).txt (dual socket) \n", CPU_FREQUENCY_LOGGING_FILE_single,0,1);
     		prog_options.logging=1;
     	    }else{
     		printf("Unknown Option, ignoring -w option.\n");
     		prog_options.logging=0;

     	    }
     	    sleep(3);
        }
    }
    ///////////////////////////////////////////////////////////
    
    
    Print_Version_Information();

    Print_Information_Processor (&prog_options.i7_version.nehalem, &prog_options.i7_version.sandy_bridge);

//	printf("nehalem %d, sandy brdige %d\n", prog_options.i7_version.nehalem, prog_options.i7_version.sandy_bridge);

    Test_Or_Make_MSR_DEVICE_FILES ();


    struct cpu_heirarchy_info chi;
    struct cpu_socket_info socket_0={.max_cpu=0, .socket_num=0, .processor_num={-1,-1,-1,-1,-1,-1,-1,-1}};
    struct cpu_socket_info socket_1={.max_cpu=0, .socket_num=1, .processor_num={-1,-1,-1,-1,-1,-1,-1,-1}};


    construct_CPU_Heirarchy_info(&chi);
    construct_sibling_list(&chi);
    print_CPU_Heirarchy(chi);
    construct_socket_information(&chi, &socket_0, &socket_1);
    print_socket_information(&socket_0);
    print_socket_information(&socket_1);

    if (socket_0.max_cpu>0 && socket_1.max_cpu>0) {
        //Path for Dual Socket Code
        printf("i7z DEBUG: Dual Socket Detected\n");
        //Dual_Socket(&prog_options);
        Dual_Socket();
    } else {
        //Path for Single Socket Code
        printf("i7z DEBUG: Single Socket Detected\n");
        //Single_Socket(&prog_options);
        Single_Socket();
    }
    return(1);
}
