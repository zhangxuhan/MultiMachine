//TCP 单机的例子
/**This is a simple example of a code that loads an AMESim DLL (shared library)
* created for Co-simulation and use this DLL for doing some simple simulation
* \author: Arne Jansson (arne.jansson@lmsintl.com)
* \date Dec 17 2007 last modification
* COPYRIGHT 2007 IMAGINE SA
*/
#define _CRT_SECURE_NO_WARNINGS

//#include "ame_api.h"
//#include "ame_api_errors.h"

#include "AddDrone.h"

#pragma comment(lib, "ws2_32.lib")



int sendstate[2] = { 0 };
static int recvforcestate = 0;
static BOOL CollisioneState = FALSE;//Have collision!
float senddata[SendDataAmount];//roll p y x y z	6
float recvdata[RecvataAmount];//x y z yaw boo1   5
float recvForce[6];//Force x y z  Movement x y z   6
static float recvdata_1[5];
double syncTime = 0;
int RecvLock[TestNum] = {1};
int RecvLockNum = 0;
int SendLock = 0;
int ExeOK = 0;


typedef struct ViewStruct
{
	double roll;
	double pitch;
	double yaw;
	double x;
	double y;
	double z;
}ViewStruct;

DWORD WINAPI AddDrone_0Proc(LPVOID lpParam)//all 2
{
	AddDrone();
	return 0;
}

DWORD WINAPI AddDrone_1Proc(LPVOID lpParam)//add 3
{
	AddDrone_1();
	return 0;
}
DWORD WINAPI AddDrone_2Proc(LPVOID lpParam)//add 1
{
	AddDrone_2();
	return 0;
}
DWORD WINAPI AddDrone_3Proc(LPVOID lpParam)//add 5
{
	AddDrone_3();
	return 0;
}

DWORD WINAPI AddDrone_4Proc(LPVOID lpParam)//add 5
{
	AddDrone_4();
	return 0;
}
DWORD WINAPI AddDrone_5Proc(LPVOID lpParam)//add 5
{
	AddDrone_5();
	return 0;
}
DWORD WINAPI AddDrone_6Proc(LPVOID lpParam)//add 5
{
	AddDrone_6();
	return 0;
}
DWORD WINAPI AddDrone_7Proc(LPVOID lpParam)//add 5
{
	AddDrone_7();
	return 0;
}
DWORD WINAPI AddDrone_8Proc(LPVOID lpParam)//add 5
{
	AddDrone_8();
	return 0;
}
DWORD WINAPI AddDrone_9Proc(LPVOID lpParam)
{
	AddDrone_9();
	return 0;
}
DWORD WINAPI AddDrone_10Proc(LPVOID lpParam)
{
	AddDrone_10();
	return 0;
}
DWORD WINAPI AddDrone_11Proc(LPVOID lpParam)
{
	AddDrone_11();
	return 0;
}
DWORD WINAPI AddDrone_12Proc(LPVOID lpParam)
{
	AddDrone_12();
	return 0;
}
DWORD WINAPI AddDrone_13Proc(LPVOID lpParam)
{
	AddDrone_13();
	return 0;
}
DWORD WINAPI AddDrone_14Proc(LPVOID lpParam)
{
	AddDrone_14();
	return 0;
}
DWORD WINAPI AddDrone_15Proc(LPVOID lpParam)
{
	AddDrone_15();
	return 0;
}
DWORD WINAPI AddDrone_16Proc(LPVOID lpParam)
{
	AddDrone_16();
	return 0;
}
DWORD WINAPI AddDrone_17Proc(LPVOID lpParam)
{
	AddDrone_17();
	return 0;
}
DWORD WINAPI AddDrone_18Proc(LPVOID lpParam)//all 20
{
	AddDrone_18();
	return 0;
}
DWORD WINAPI AddDrone_19Proc(LPVOID lpParam)//;21
{
	AddDrone_19();
	return 0;
}





DWORD WINAPI RecvForceProc(LPVOID lpParam)//add 1
{
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		printf("WSAStartup error !");
		return 0;
	}
	SOCKET ForceSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//IPPROTO_UDP
	if (ForceSocket == INVALID_SOCKET)
	{
		printf("socket FAILED\n");
		return 0;
	}
	struct sockaddr_in sin1;
	sin1.sin_family = AF_INET;
	sin1.sin_port = htons(8889);//remote ports
	sin1.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(ForceSocket, (LPSOCKADDR)&sin1, sizeof(sin1)) == SOCKET_ERROR)
	{
		printf("BINDForceSocket IP & PORTS ERROR\n");
		return 0;
	}
	if (listen(ForceSocket, 5) == SOCKET_ERROR)
	{
		printf("listenForceSocket error !");
		return 0;
	}


	SOCKET sClient_force;
	struct sockaddr_in remoteAddr_force;
	int ret_force = -1;
	int nAddrlen_force = sizeof(remoteAddr_force);
	double revdata_force[255];
	sClient_force = accept(ForceSocket, (SOCKADDR *)&remoteAddr_force, &nAddrlen_force);


	while (recvforcestate == 1)
	{
		//printf("666");
		ret_force = recv(sClient_force, revdata_force, 255, 0);
		if (ret_force > 0) {
			memcpy(recvForce, revdata_force, sizeof(recvForce));
			CollisioneState = TRUE;
			printf("Collision!!!!!!!!!!!!!!!!!!!!!\r\n");
			/*	for (int n = 0; n < 6; n++) {
				inputs[5 + i] = recvForce[i];
			}*/
			Sleep(50);
		}
		CollisioneState = FALSE;
	}

	closesocket(ForceSocket);
	return 0;
}

DWORD WINAPI ThreadProc(LPVOID lpParam)//Send
{
	int nStatus;
	unsigned long cmd;//阻塞或非阻塞的模式
	ViewStruct data;
	char* sendbuf = (char*)malloc(sizeof(ViewStruct));
	struct sockaddr_in clientAddr;
	WORD sockVision = MAKEWORD(2, 2);
	WSADATA wsadata;


	int ret = -1;
	int len = -1;
	if (WSAStartup(sockVision, &wsadata) != 0)
	{
		printf("WSA failed\n");
		return 0;
	}
	SOCKET sclient = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sclient == INVALID_SOCKET)
	{
		printf("socket failed\n");
		return 0;
	}
	clientAddr.sin_family = AF_INET;
	clientAddr.sin_port = htons(10086);
	clientAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	len = sizeof(clientAddr);
	nStatus = ioctlsocket(sclient, FIONBIO, &cmd);//设置非阻塞模式
	//while (connect(sclient, (struct sockaddr *)&clientAddr, sizeof(clientAddr)) == SOCKET_ERROR)
	// {
	//       printf("connect error !");
	//       //closesocket(sclient);
	//}
	printf("connect success !\n");
	while (1) {
		if (sendstate[0] == 1 && sendstate[1] == 1)
		{
			//memcpy(sendbuf, senddata, sizeof(senddata));
			sendto(sclient, senddata, sizeof(senddata), 0, (SOCKADDR*)&clientAddr, len);
			//send(sclient, senddata, sizeof(senddata), 0);
			//printf("udpx= %f\n", senddata[3]);
			//Sleep(50);
			sendstate[0] = 0;
			sendstate[1] = 0;
		}
	}
	closesocket(sclient);
	printf("THREAD CLOSE\n");
}












//Unicode 转换成 GB2312：
char* UnicodeToGB2312(const wchar_t* szUnicodeString)
{
	UINT nCodePage = 936; //GB2312
	int nLength = WideCharToMultiByte(nCodePage, 0, szUnicodeString, -1, NULL, 0, NULL, NULL);
	char* pBuffer = (char*)malloc(nLength * sizeof(char));
	//char* pBuffer = new char[nLength + 1];
	//wchar_t* pwszUnicode = (wchar_t *)malloc(iSize * sizeof(wchar_t));
	WideCharToMultiByte(nCodePage, 0, szUnicodeString, -1, pBuffer, nLength, NULL, NULL);
	pBuffer[nLength] = 0;
	return pBuffer;
}


int main(int argc, char *argv[])
{
	//AMEOpenAmeFile("1");
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
	//strcpy(tmpfullname, argv[1]);
	/* ********************************************* */
	if (argc <= 1)
	{
		fprintf(stderr, "Need the name of the DLL used as slave AMESim model\n");
		fprintf(stderr, "EXIT\n");
		exit(1);
	}

#ifdef DroneWithLag
	char *libname = "..\\drone_asd_.dll";
#endif
#ifdef DroneWithError
	char *libname = "..\\drone_asd_error_.dll";
#endif // DroneWithError



	//char *libname = "..\\drone_asd_1_.dll";//不带碰撞的5个输入



	//获取输入缓存大小
	int sBufSize = strlen(libname);
	DWORD dBufSize = MultiByteToWideChar(CP_ACP, 0, libname, sBufSize, NULL, 0);
	printf("have wchar_t:  %d\n", dBufSize);
	int iSize = MultiByteToWideChar(CP_ACP, 0, libname, sBufSize, NULL, 0);
	wchar_t* pwszUnicode = (wchar_t *)malloc(iSize * sizeof(wchar_t));
	// 进行转换
	MultiByteToWideChar(CP_ACP, 0, libname, sBufSize, pwszUnicode, dBufSize);

	printf("pwszUnicode = %s\n", UnicodeToGB2312(libname));



	/* The DLL (or shared library) is loaded. If it fails to load we exit. */
	if (!loadamesimdll(libname, &amedll))
	{
		fprintf(stderr, "failed to load DLL %s\n", libname);
		exit(1);
	}
	else
	{
		fprintf(stdout, "AMESim model '%s' loaded OK\n", argv[1]);
	}

	/* set model directory */
	strcpy(tmpfullname, libname);
	dirsep = strrchr(tmpfullname, '/');
	if (dirsep)
	{
		dirsep++;
		*dirsep = '\0';
		//fprintf(stdout, "MASTER> Setting model directory to %s\n", tmpfullname);
		amedll.AMEWorkingDir(tmpfullname);
	}
	//amedll.AMEWorkingDir("C:\\Users\\HZ\\Desktop\\amesim_use\\Ab\\AMEtest\\ConsoleApplication1");
	amedll.AMEWorkingDir("..\\");
	{
		/* Check that the AMESim model have the same number of inputs
		* and outputs as we expect. */
		int ame_says_numinputs;
		int ame_says_numoutputs;
		int ame_says_numstates;
		int ame_says_numimplicit;
		amedll.AMEInitSizes(&ame_says_numinputs, &ame_says_numoutputs, &ame_says_numstates, &ame_says_numimplicit);

		numinputs_to_model = ame_says_numinputs;//5
		numoutputs_from_model = ame_says_numoutputs;//6
	}

	/* Create the input/output arrays */
	inputs = (double*)calloc(1, numinputs_to_model * sizeof(double));//Allocates the required memory space and returns a pointer to it
	outputs = (double*)calloc(1, numoutputs_from_model * sizeof(double));





	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;


	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		printf("WSAStartup error !");
		return 0;
	}
	//create socket
	SOCKET serSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//IPPROTO_UDP
	if (serSocket == INVALID_SOCKET)
	{
		printf("socket FAILED\n");
		return 0;
	}


	//if (setsockopt(serSocket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) == -1) {
	//	printf("setsockopt failed:");
	//}
	//unsigned long imode = 1;//非阻塞
	//int nStatus;
	//nStatus = ioctlsocket(serSocket, FIONBIO, &imode);//*
	//if (nStatus == SOCKET_ERROR)
	//{
	//	printf("非阻塞模式失败\n");
	//}
	//printf("nStatus=%d\n", nStatus);
	//bind ip ports
	struct sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(8888);//remote ports
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(serSocket, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		printf("BIND IP & PORTS ERROR\n");
		return 0;
	}
	//ret = recvfrom(serSocket, revdata, 255, 0, (SOCKADDR*)&remoteAddr, &nAddrlen);
	//开始监听
	if (listen(serSocket, 5) == SOCKET_ERROR)
	{
		printf("listen error !");
		return 0;
	}















	for (i = 0; i < numinputs_to_model; i++)
	{
		if (i == 0)
		{
			inputs[i] = 0; /* pumpspeed */
		}
		else if (i == 1)
		{
			inputs[i] = 0; /* valve input signal */
		}
		else if (i == 2)
		{
			inputs[i] = 0; /* any other signal */
		}
		else if (i == 3)
		{
			inputs[i] = 0; /* any other signal */
		}
		else
		{
			inputs[i] = 0; /* any other signal */
		}
	}







	SOCKET sClient;
	struct sockaddr_in remoteAddr;
	int ret = -1;
	int nAddrlen = sizeof(remoteAddr);
	double revdata[255];



	//udp Recv
	DWORD dwThreadId;//线程ID
	DWORD dwThreadId1;
	DWORD dwThreadId2;
	DWORD dwThreadId3;
	DWORD dwThreadId4;
	DWORD dwThreadId5;
	DWORD dwThreadId6;
	DWORD dwThreadId7;
	DWORD dwThreadId8;
	DWORD dwThreadId9;
	DWORD dwThreadId10;
	DWORD dwThreadId11;
	DWORD dwThreadId12;
	DWORD dwThreadId13;
	DWORD dwThreadId14;
	DWORD dwThreadId15;
	DWORD dwThreadId16;
	DWORD dwThreadId17;
	DWORD dwThreadId18;
	DWORD dwThreadId19;
	DWORD dwThreadId20;
	//SEND
	CreateThread(NULL, 0, ThreadProc, 0, 0, &dwThreadId);
	//RecvForce
	CreateThread(NULL, 0, RecvForceProc, 0, 0, &dwThreadId1);


	//AddDrone
	CreateThread(NULL, 0, AddDrone_0Proc, 0, 0, &dwThreadId2);//AddDrone
	CreateThread(NULL, 0, AddDrone_1Proc, 0, 0, &dwThreadId3);
	//CreateThread(NULL, 0, AddDrone_2Proc, 0, 0, &dwThreadId4);
	//CreateThread(NULL, 0, AddDrone_3Proc, 0, 0, &dwThreadId5);
	//CreateThread(NULL, 0, AddDrone_4Proc, 0, 0, &dwThreadId6);
	//CreateThread(NULL, 0, AddDrone_5Proc, 0, 0, &dwThreadId7);
	//CreateThread(NULL, 0, AddDrone_6Proc, 0, 0, &dwThreadId8);
	//CreateThread(NULL, 0, AddDrone_7Proc, 0, 0, &dwThreadId9);//9台
	//CreateThread(NULL, 0, AddDrone_8Proc, 0, 0, &dwThreadId10);
	//CreateThread(NULL, 0, AddDrone_9Proc, 0, 0, &dwThreadId11);
	//CreateThread(NULL, 0, AddDrone_10Proc, 0, 0, &dwThreadId12);
	//CreateThread(NULL, 0, AddDrone_11Proc, 0, 0, &dwThreadId13);
	//CreateThread(NULL, 0, AddDrone_12Proc, 0, 0, &dwThreadId14);
	//CreateThread(NULL, 0, AddDrone_13Proc, 0, 0, &dwThreadId15);
	//CreateThread(NULL, 0, AddDrone_14Proc, 0, 0, &dwThreadId16);
	//CreateThread(NULL, 0, AddDrone_15Proc, 0, 0, &dwThreadId17);
	//CreateThread(NULL, 0, AddDrone_16Proc, 0, 0, &dwThreadId18);
	//CreateThread(NULL, 0, AddDrone_17Proc, 0, 0, &dwThreadId19);
	//CreateThread(NULL, 0, AddDrone_18Proc, 0, 0, &dwThreadId20);// all 20

	
	recvforcestate = 1;
	sClient = accept(serSocket, (SOCKADDR *)&remoteAddr, &nAddrlen);



	for (int m = 0; m < TestNum; m++) {
		RecvLock[m] = 1;
	}



	while (time <= SimulationTime)
	{
		//ret = recvfrom(serSocket, revdata, 255, 0, (SOCKADDR*)&remoteAddr, &nAddrlen);
		//FD_ZERO(&rfd);           //总是这样先清空一个描述符集
		//FD_SET(serSocket, &rfd); //把sock放入要测试的描述符集
		//SelectRcv = select(serSocket + 1, &rfd, 0, 0, &timeout); //检查该套接字是否可读
		//FD_ISSET(serSocket, &fdread)

		//if (FD_ISSET(serSocket, &rfd))
		//sClient = accept(serSocket, (SOCKADDR *)&remoteAddr, &nAddrlen);
		//ret = recvfrom(sClient, revdata, 255, 0, (SOCKADDR*)&remoteAddr, &nAddrlen);
		ret = recv(sClient, revdata, 255, 0);
		/* SET THE INPUTS TO THE AMESIM MODEL HERE */
		int INTTime = (int)(time * 10);//0.1s

		//同步机制
		//for (int m = 0; m < TestNum; m++) {
		//	if (RecvLock[m] == 1) {
		//		RecvLockNum = RecvLockNum +1;
		//	}
		//	else {
		//		RecvLockNum = 0;
		//		break;
		//	}
		//}
		RecvLockNum = TestNum;
		printf("RecvLockNum=%d\r\n", RecvLockNum);
		if (ret > 0 && RecvLockNum == TestNum) {
			memcpy(recvdata, revdata, sizeof(recvdata));

			RecvLockNum = 0;
			RecvLock[0] = 0;

			for (i = 0; i < numinputs_to_model; i++)
			{
				if (i == 0)
				{
					inputs[i] = recvdata[0]; /* x */
				}
				else if (i == 1)
				{
					inputs[i] = recvdata[1]; /* y */
				}
				else if (i == 2)
				{
					inputs[i] = recvdata[2]; /*z */
				}
				else if (i == 3)
				{
					inputs[i] = recvdata[3]; /* yaw */
				}
				else if (i == 4)
				{
					inputs[i] = recvdata[4]; /* bool */
				}
				else
				{
					inputs[i] = 0; /* force	   x y z
									  movement x y z
									  = 6 */
				}
			}


			for (i = 0; i < numinputs_to_model; i++)
			{
				printf("inputs1[%d] = %f\n", i, inputs[i]);//x
			}

			if (CollisioneState == TRUE) {
				for (int n = 0; n < 6; n++) {
					inputs[5 + n] = recvForce[n];
				}
			}

			pthread_mutex_lock(&mut);
			if (!model_initialised)
			{
				/* InitModel loads the AMESim model data, set up the model
				(with an init call) and checks that number of
				inputs/outputs agree. We do the init in the loop since it
				will also do a call to the model and it needs to have the
				inputs set properly. */
				fprintf(stdout, "MASTER> Starting simulation with a call to InitModel.\n\n");
				amedll.AMEInitModel(time, printinter, samptime, tol, errtype, writelevel,
					disconpr, runstats, runtype, thesolvertype,
					numinputs_to_model, numoutputs_from_model, inputs, outputs);
				model_initialised = 1;
			}
			pthread_mutex_unlock(&mut);


			/* Here we do a call to the AMESim model and asks it to
			calculate its outputs up to time="time" using the inputs sent. */
			//double t,               /**< final integration time */
			//	int numInputs,          /**< num inputs to the AMESim model */
			//	int numOutputs,         /**< num outputs from the AMESim model */
			//	const double *theInputs,/**< vector with inputs to the AMESim model */
			//	double *theOutputs      /**< vector with outputs from the AMESim model */
			pthread_mutex_lock(&mut);
			amedll.AMEdoAStep2(time, numinputs_to_model, numoutputs_from_model, inputs, outputs);
			pthread_mutex_unlock(&mut);

			//AMEInputs
			//amedll.AMEOutputs(time, numoutputs_from_model, outputs);

			//sendto(sclient, outputs, strlen(outputs), 0, (SOCKADDR*)&clientAddr, len);
			/* The vector "outputs" now contains the outputs from
			* the AMESim model at time "time".
			* In this simple example we only print the values. */

			fprintf(stdout, "time0 = %.3f\t", time);
			//for (i = 0; i < numoutputs_from_model; i++)//numoutputs_from_model = 6
			//{
			//	fprintf(stdout, "out%d = %.3f\t", i, outputs[i]);
			//}
			//fprintf(stdout, "\n");



			for (int i = 0; i < 6; i++) { //0-5
				senddata[i] = (float)(outputs[i]);
			}
			sendstate[0] = 1;



			//printf("senddata[3] = %f\n", senddata[3]);//x
			//pthread_mutex_unlock(&mut);
			//memcpy(senddata, (float*)outputs, sizeof(senddata)); //指针只指向前32位 
			//printf(" sizeof(senddata)=%d\n", sizeof(senddata));
			//sendto(sclient, senddata, strlen(senddata), 0, (SOCKADDR*)&clientAddr, len);



			/* Update the time for the next step */
			time += samptime;
			syncTime = time;
			RecvLock[0] = 1;
		}
	}

	/* Allow for a "clean" end of the AMESim model with Terminate. */
	amedll.AMETerminate();

	/* Tell the operating system we no longer use the DLL
	(freeamesimdll). This will normally unload the DLL. In this
	example it does not matter, but if one wants to perform several
	simulations without leaving this program it is important to do
	this since unloading the DLL will ensure for it to be properly
	(re-)initialized when loading it. After the call to
	freeamesimdll it is not possible to use the model until a
	loadamesimdll has been done.*/
	printf("DONE AND CLOSE\n");
	recvforcestate = 0;
	unloadamesimdll(&amedll);
	closesocket(serSocket);
	WSACleanup();
	//CloseHandle(dwThreadId);
	system("pause");
	return 0;
}