#define _CRT_SECURE_NO_WARNINGS

#define WhichPlane 1//第几架机

#include "..\AddDrone.h"


#pragma comment(lib, "pthreadVC2.lib")
void AddDrone_1()
{
	//pthread_mutex_init(&mut, NULL);
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
	char *libname = "..\\drone_asd_error2_.dll";
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
	

	FILE *file = fopen(File2, "wb+");
	while (time <= SimulationTime)
	{
		WaitForSingleObject(g_hThreadEvent[2], INFINITE);//等待信号量 
		//Sleep(1);
		//if (RecvLockNum == TestNum) {
		//	RecvLock[2] = 0;
		//	RecvLockNum = 0;
			//pthread_mutex_lock(&mut);
			for (i = 0; i < numinputs_to_model; i++)
			{
				if (i == 0)
				{
					inputs[i] = recvdata[RecvdData_Single * WhichPlane]; /* x */
					//inputs[i] = -500;
				}
				else if (i == 1)
				{
					inputs[i] = recvdata[RecvdData_Single * WhichPlane +1]; /* y */
				}
				else if (i == 2)
				{
					inputs[i] = recvdata[RecvdData_Single * WhichPlane + 2]; /*z */
				}
				else if (i == 3)
				{
					inputs[i] = recvdata[RecvdData_Single * WhichPlane + 3]; /* yaw */
				}
				else if (i == 4)
				{
					inputs[i] = recvdata[RecvdData_Single * WhichPlane + 4]; /* bool */
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
			
			//pthread_mutex_lock(&mut);
			amedll.AMEdoAStep2(time, numinputs_to_model, numoutputs_from_model, inputs, outputs);
			//pthread_mutex_unlock(&mut);


			//for (i = 0; i < numinputs_to_model; i++)
			//{
			//	printf("inputs3[%d] = %f\n", i, inputs[i]);//x
			//}

			printf("time2 = %.3f\t\n", time);

			fprintf(file, "time = %.3f\t", time);
			for (i = 0; i < numoutputs_from_model; i++)//numoutputs_from_model = 6
			{
				fprintf(file, "out_%d = %.3f\t", i, outputs[i]);
			}
			fprintf(file, "\n");



			pthread_mutex_lock(&mut);
			//for (int i = (SendData_Single * WhichPlane); 
			//	i < (SendData_Single * WhichPlane + SendData_Single); i++) { //6-11
			//	senddata[i] = (float)(outputs[i - (SendData_Single * WhichPlane)]);
			//}
			pthread_mutex_unlock(&mut);


			time += samptime;
		//	ReleaseSemaphore(hSemp2, 1, NULL);//释放信号量 
	}
	fclose(file);
	amedll.AMETerminate();
	unloadamesimdll(&amedll);
	system("pause");
}

