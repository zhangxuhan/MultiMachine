#define _CRT_SECURE_NO_WARNINGS

#include <math.h>
#include <stdio.h>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <stdlib.h>

//#include "ame_api.h"
//#include "ame_api_errors.h"

#include "AddDrone.h"



//int main(int argc, char *argv[])
//{
//	AddDrone();
//}

#pragma comment(lib, "pthreadVC2.lib")
void AddDrone()
{
	pthread_mutex_init(&mut, NULL);
	//AMEOpenAmeF0ile("1");
	double samptime = 0.05; /* Sample interval */
	double printinter = samptime / 5.0; /* How often will AMESim model write the result file */
	double tol = 1e-5; /* Solver tolerance */

	/* The following parameter values should be kept at their default values. */
	const int errtype = 0; /* Error check type : mixed */
	const int writelevel = 2; /* Don't output the time for every step taken */
	const int disconpr = 0; /* No extra discontinuity printouts */
	const int runstats = 0; /* No Runstats after the simulation */
	const int runtype = 8; /* Dynamic run */
	const int thesolvertype = 0; /* The default solver config */

	double time = 0;
	int numinputs_to_model = -1;
	int numoutputs_from_model = -1;
	double *inputs = NULL;
	double *outputs = NULL;

	int i;
	int model_initialised = 0;
	static AME_DLL amedll;
	char tmpfullname[1024];
	char *dirsep;

#ifdef DroneWithLag
	char *libname = "..\\drone_asd_ectype_.dll";
#endif
#ifdef DroneWithError
	char *libname = "..\\drone_asd_error1_.dll";
#endif // DroneWithError

	if (!loadamesimdll(libname, &amedll))
	{
		fprintf(stderr, "failed to load DLL %s\n", libname);
		exit(1);
	}
	else
	{
		fprintf(stdout, "AMESim model '%s' loaded OK\n", libname);
	}
	/* set model directory */
	strcpy(tmpfullname, libname);
	dirsep = strrchr(tmpfullname, '/');
	if (dirsep)
	{
		dirsep++;
		*dirsep = '\0';
		fprintf(stdout, "MASTER> Setting model directory to %s\n", tmpfullname);
		amedll.AMEWorkingDir(tmpfullname);
	}
	
	amedll.AMEWorkingDir("..\\");
	{
		int ame_says_numinputs;
		int ame_says_numoutputs;
		int ame_says_numstates;
		int ame_says_numimplicit;
		amedll.AMEInitSizes(&ame_says_numinputs, &ame_says_numoutputs, &ame_says_numstates, &ame_says_numimplicit);
		fprintf(stdout,
			"MASTER> AMESim model2 have \n %d inputs \n %d outputs \n %d state variables \n %d implicit variables\n",
			ame_says_numinputs, ame_says_numoutputs, ame_says_numstates, ame_says_numimplicit);
		numinputs_to_model = ame_says_numinputs;//5
		numoutputs_from_model = ame_says_numoutputs;//6
	}
	/* Create the input/output arrays */
	inputs = (double*)calloc(1, numinputs_to_model * sizeof(double));//Allocates the required memory space and returns a pointer to it
	outputs = (double*)calloc(1, numoutputs_from_model * sizeof(double));


	for (i = 0; i < numinputs_to_model; i++)
	{
		inputs[i] = 0; /* any other signal */

	}
	

	FILE *file = fopen(File1, "wb+");
	while (time <= SimulationTime)
	{
		WaitForSingleObject(g_hThreadEvent[1], INFINITE);//等待信号量 

			for (i = 0; i < numinputs_to_model; i++)
			{
				if (i == 0)
				{
					inputs[i] = recvdata[5]; /* x */
				}
				else if (i == 1)
				{
					inputs[i] = recvdata[6]; /* y */
				}
				else if (i == 2)
				{
					inputs[i] = recvdata[7]; /*z */
				}
				else if (i == 3)
				{
					inputs[i] = recvdata[8]; /* yaw */
				}
				else if (i == 4)
				{
					inputs[i] = recvdata[9]; /* bool */
				}
				else
				{
					inputs[i] = 0; /* Force	   X Y Z
									  Movement X Y Z
									  = 6 */
				}
			} 
			
			if (!model_initialised)
			{
				pthread_mutex_lock(&mut);
				fprintf(stdout, "MASTER> Starting simulation with a call to InitModel.\n\n");
				amedll.AMEInitModel(time, printinter, samptime, tol, errtype, writelevel,
					disconpr, runstats, runtype, thesolvertype,
					numinputs_to_model, numoutputs_from_model, inputs, outputs);
				model_initialised = 1;
				pthread_mutex_unlock(&mut);
			}
			
			pthread_mutex_lock(&mut);
			amedll.AMEdoAStep2(time, numinputs_to_model, numoutputs_from_model, inputs, outputs);
			pthread_mutex_unlock(&mut);


			//for (i = 0; i < numinputs_to_model; i++)
			//{
			//	printf("inputs2[%d] = %f\n", i, inputs[i]);//x
			//}
			////pthread_mutex_unlock(&mut);
			//fprintf(stdout, "time2 = %.3f\t", time);
			//for (i = 0; i < numoutputs_from_model; i++)//numoutputs_from_model = 6
			//{
			//	fprintf(stdout, "out2_%d = %.3f\t", i, outputs[i]);
			//}
			//fprintf(stdout, "\n");




			pthread_mutex_lock(&mut);

			for (int i = 6; i < 12; i++) { //6-11
				senddata[i] = (float)(outputs[i - 6]);
			}
			//SendLock += 1;
			pthread_mutex_unlock(&mut);
			sendstate[1] = 1;
			
			//printf("senddata[9] = %f\n", senddata[9]);//x1

			printf("time1 = %.3f\t\n", time);
			fprintf(file, "time1 = %.3f\t", time);
			for (i = 0; i < numoutputs_from_model; i++)//numoutputs_from_model = 6
			{
				fprintf(file, "out1_%d = %.3f\t", i, outputs[i]);
			}
			fprintf(file, "\n");

			time += samptime;
	}
	fclose(file);
	amedll.AMETerminate();
	unloadamesimdll(&amedll);
	system("pause");
}

void DataInteraction()
{
}
