///**This is a simple example of a code that loads an AMESim DLL (shared library)
//* created for Co-simulation and use this DLL for doing some simple simulation
//* \author: Arne Jansson (arne.jansson@lmsintl.com)
//* \date Dec 17 2007 last modification
//* COPYRIGHT 2007 IMAGINE SA
//*/
//#define _CRT_SECURE_NO_WARNINGS
//
////#include "ame_api.h"
////#include "ame_api_errors.h"
//
//#include "AddDrone.h"
//
//#pragma comment(lib, "ws2_32.lib")
//
//
//
//static int sendstate = 0;
//float senddata[SendDataAmount];//roll p y x y z	6
//float recvdata[RecvataAmount];//x y z yaw boo1   5
//static float recvdata_1[5];
//double syncTime = 0;
//int RecvLock = 0;
//
//DWORD WINAPI AddDrone_1Proc(LPVOID lpParam)//add 1
//{
//	//AddDrone();
//	//return 0;
//}
//
//typedef struct ViewStruct
//{
//	double roll;
//	double pitch;
//	double yaw;
//	double x;
//	double y;
//	double z;
//}ViewStruct;
//
//DWORD WINAPI ThreadProc(LPVOID lpParam)//Send
//{
//	int nStatus;
//	unsigned long cmd;//阻塞或非阻塞的模式
//	ViewStruct data;
//	char* sendbuf = (char*)malloc(sizeof(ViewStruct));
//	struct sockaddr_in clientAddr;
//	WORD sockVision = MAKEWORD(2, 2);
//	WSADATA wsadata;
//
//
//	int ret = -1;
//	int len = -1;
//	if (WSAStartup(sockVision, &wsadata) != 0)
//	{
//		printf("WSA failed\n");
//		return 0;
//	}
//	SOCKET sclient = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
//	if (sclient == INVALID_SOCKET)
//	{
//		printf("socket failed\n");
//		return 0;
//	}
//	clientAddr.sin_family = AF_INET;
//	clientAddr.sin_port = htons(10086);
//	clientAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
//	len = sizeof(clientAddr);
//	nStatus = ioctlsocket(sclient, FIONBIO, &cmd);//设置非阻塞模式
//	//while (connect(sclient, (struct sockaddr *)&clientAddr, sizeof(clientAddr)) == SOCKET_ERROR)
//	// {
//	//       printf("connect error !");
//	//       //closesocket(sclient);
//	//}
//	printf("connect success !\n");
//	while (sendstate == 1)
//	{
//		//printf("sbuf[0]=%d\n", sbuf[0]);
//		//memcpy(sendbuf, senddata, sizeof(senddata));
//		sendto(sclient, senddata, sizeof(senddata), 0, (SOCKADDR*)&clientAddr, len);
//		//send(sclient, senddata, sizeof(senddata), 0);
//		//printf("udpx= %f\n", senddata[3]);
//		Sleep(50);
//	}
//	closesocket(sclient);
//	printf("THREAD CLOSE\n");
//}
//
//
//
//
//
//
//
//
//
//
//
//
////Unicode 转换成 GB2312：
//char* UnicodeToGB2312(const wchar_t* szUnicodeString)
//{
//	UINT nCodePage = 936; //GB2312
//	int nLength = WideCharToMultiByte(nCodePage, 0, szUnicodeString, -1, NULL, 0, NULL, NULL);
//	char* pBuffer = (char*)malloc(nLength * sizeof(char));
//	//char* pBuffer = new char[nLength + 1];
//	//wchar_t* pwszUnicode = (wchar_t *)malloc(iSize * sizeof(wchar_t));
//	WideCharToMultiByte(nCodePage, 0, szUnicodeString, -1, pBuffer, nLength, NULL, NULL);
//	pBuffer[nLength] = 0;
//	return pBuffer;
//}
//
//
//
///* A simple example of a program that loads a DLL
//* (name provided by argument list) and calls the functions
//* in this DLL to do a simple simulation */
//int main(int argc, char *argv[])
//{
//
//	//AMEOpenAmeF0ile("1");
//	double samptime = 0.05; /* Sample interval */
//	double printinter = samptime / 5.0; /* How often will AMESim model write the result file */
//	double tol = 1e-5; /* Solver tolerance */
//
//	/* The following parameter values should be kept at their default values. */
//	const int errtype = 0; /* Error check type : mixed */
//	const int writelevel = 2; /* Don't output the time for every step taken */
//	const int disconpr = 0; /* No extra discontinuity printouts */
//	const int runstats = 0; /* No Runstats after the simulation */
//	const int runtype = 8; /* Dynamic run */
//	const int thesolvertype = 0; /* The default solver config */
//
//	double time = 0;
//	int numinputs_to_model = -1;
//	int numoutputs_from_model = -1;
//	double *inputs = NULL;
//	double *outputs = NULL;
//
//
//	int numinputs_to_model1 = -1;
//	int numoutputs_from_model1 = -1;
//	double *inputs1 = NULL;
//	double *outputs1 = NULL;
//
//
//	int i;
//	int model_initialised = 0;
//	static AME_DLL amedll;
//	char tmpfullname[1024];
//	char *dirsep;
//
//	int i1;
//	int model_initialised1 = 0;
//	static AME_DLL amedll1;
//	char tmpfullname1[1024];
//	char *dirsep1;
//	//strcpy(tmpfullname, argv[1]);
//	/* ********************************************* */
//	if (argc <= 1)
//	{
//		fprintf(stderr, "Need the name of the DLL used as slave AMESim model\n");
//		fprintf(stderr, "EXIT\n");
//		exit(1);
//	}
//
//
//	char *libname = "..\\drone_asd_1_.dll";
//	char *libname1 = "..\\drone_asd_12p_.dll";
//
//
//
//
//
//	/* The DLL (or shared library) is loaded. If it fails to load we exit. */
//	if (!loadamesimdll(libname, &amedll))
//	{
//		fprintf(stderr, "failed to load DLL %s\n", libname);
//		fprintf(stderr, "libname IS %s\n", libname);
//		exit(1);
//	}
//	else
//	{
//		//fprintf(stdout, "AMESim model '%s' loaded OK\n", argv[1]);
//	}
//
//	if (!loadamesimdll(libname1, &amedll1))
//	{
//		fprintf(stderr, "failed to load DLL %s\n", libname1);
//		exit(1);
//	}
//	else
//	{
//		fprintf(stdout, "AMESim model '%s' loaded OK\n", libname1);
//	}
//	/* set model directory */
//	strcpy(tmpfullname, libname);
//	dirsep = strrchr(tmpfullname, '/');
//	//amedll.AMEWorkingDir("C:\\Users\\HZ\\Desktop\\amesim_use\\Ab\\AMEtest\\ConsoleApplication1");
//	amedll.AMEWorkingDir("..\\");
//
//
//	strcpy(tmpfullname1, libname1);
//	dirsep1 = strrchr(tmpfullname1, '/');
//	//if (dirsep1)
//	//{
//	//	dirsep1++;
//	//	*dirsep1 = '\0';
//	//	//fprintf(stdout, "MASTER> Setting model directory to %s\n", tmpfullname);
//	//	amedll1.AMEWorkingDir(tmpfullname1);
//	//}
//	amedll1.AMEWorkingDir("..\\");
//
//	{
//		/* Check that the AMESim model have the same number of inputs
//		* and outputs as we expect. */
//		int ame_says_numinputs;
//		int ame_says_numoutputs;
//		int ame_says_numstates;
//		int ame_says_numimplicit;
//		amedll.AMEInitSizes(&ame_says_numinputs, &ame_says_numoutputs, &ame_says_numstates, &ame_says_numimplicit);
//		
//		int ame_says_numinputs1;
//		int ame_says_numoutputs1;
//		int ame_says_numstates1;
//		int ame_says_numimplicit1;
//		amedll1.AMEInitSizes(&ame_says_numinputs1, &ame_says_numoutputs1, &ame_says_numstates1, &ame_says_numimplicit1);
//
//
//		numinputs_to_model = ame_says_numinputs;//5
//		numoutputs_from_model = ame_says_numoutputs;//6
//
//		numinputs_to_model1 = ame_says_numinputs1;//5
//		numoutputs_from_model1 = ame_says_numoutputs1;//6
//	}
//
//	/* Create the input/output arrays */
//	inputs = (double*)calloc(1, numinputs_to_model * sizeof(double));//Allocates the required memory space and returns a pointer to it
//	outputs = (double*)calloc(1, numoutputs_from_model * sizeof(double));
//
//	inputs1 = (double*)calloc(1, numinputs_to_model1 * sizeof(double));//Allocates the required memory space and returns a pointer to it
//	outputs1 = (double*)calloc(1, numoutputs_from_model1 * sizeof(double));
//	
//
//	pthread_mutex_init(&mut, NULL);
//	//udp Recv
//	DWORD dwThreadId;//线程ID
//	DWORD dwThreadId1;
//
//	//other variables
//	//SOCKET serSocket;
//
//
//
//
//	WORD sockVersion = MAKEWORD(2, 2);
//	WSADATA wsaData;
//
//
//	if (WSAStartup(sockVersion, &wsaData) != 0)
//	{
//		printf("WSAStartup error !");
//		return 0;
//	}
//	//create socket
//	SOCKET serSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//IPPROTO_UDP
//	if (serSocket == INVALID_SOCKET)
//	{
//		printf("socket FAILED\n");
//		return 0;
//	}
//
//	//if (setsockopt(serSocket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) == -1) {
//	//	printf("setsockopt failed:");
//	//}
//	//unsigned long imode = 1;//非阻塞
//	//int nStatus;
//	//nStatus = ioctlsocket(serSocket, FIONBIO, &imode);//*
//	//if (nStatus == SOCKET_ERROR)
//	//{
//	//	printf("非阻塞模式失败\n");
//	//}
//	//printf("nStatus=%d\n", nStatus);
//	//bind ip ports
//	struct sockaddr_in sin;
//	sin.sin_family = AF_INET;
//	sin.sin_port = htons(8888);//remote ports
//	sin.sin_addr.S_un.S_addr = INADDR_ANY;
//	if (bind(serSocket, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
//	{
//		printf("BIND IP & PORTS ERROR\n");
//		return 0;
//	}
//	//ret = recvfrom(serSocket, revdata, 255, 0, (SOCKADDR*)&remoteAddr, &nAddrlen);
//	//开始监听
//	if (listen(serSocket, 5) == SOCKET_ERROR)
//	{
//		printf("listen error !");
//		return 0;
//	}
//
//
//
//
//
//
//
//
//
//	for (i = 0; i < numinputs_to_model; i++)
//	{
//		if (i == 0)
//		{
//			inputs[i] = 0; /* pumpspeed */
//		}
//		else if (i == 1)
//		{
//			inputs[i] = 0; /* valve input signal */
//		}
//		else if (i == 2)
//		{
//			inputs[i] = 0; /* any other signal */
//		}
//		else if (i == 3)
//		{
//			inputs[i] = 0; /* any other signal */
//		}
//		else
//		{
//			inputs[i] = 0; /* any other signal */
//		}
//	}
//
//
//
//	//SEND
//	CreateThread(NULL, 0, ThreadProc, 0, 0, &dwThreadId);
//	sendstate = 1;
//
//	//Test Fly With Format Table  0.1s
//	double Input0[1200] = { 0 };
//	for (int i = 0; i < 1200; i++)
//	{
//		if (i < 110) { Input0[i] = 0; }
//		//else if (i >= 110 && i < 190) { Input0[i] = (10/(19-11)) * (i-110) / 10; }
//		else if (i >= 110 && i < 190) { Input0[i] = (10.0 / (19.0 - 11.0))* (i - 110.0) / 10; }
//		else if (i >= 190 && i < 430) { Input0[i] = 10.0; }
//		else if (i >= 430 && i < 460) { Input0[i] = 3.0 / (3.0) * (i - 430.0) / 10; }
//		else if (i >= 460 && i < 620) { Input0[i] = 13.0; }
//		else if (i >= 620 && i < 660) { Input0[i] = (5 - 13) / (4.0) * (i - 620.0) / 10; }
//		else if (i >= 660 && i <= 1199) { Input0[i] = 5.0; }
//	}
//
//	double Input1[1200] = { 0 };
//	for (int i = 0; i < 1200; i++)
//	{
//		if (i < 230) { Input1[i] = 0.0; }
//		else if (i >= 230 && i < 390) { Input1[i] = (0 - 20) / (39.0 - 23.0) * (i - 320.0) / 10; }
//		else if (i >= 390 && i < 840) { Input1[i] = -20.0; }
//		else if (i >= 840 && i < 890) { Input1[i] = (-10 + 20) / (5.0) * (i - 840.0) / 10; }
//		else if (i >= 890 && i <= 1190) { Input1[i] = -10.0; }
//	}
//	double Input2[1200] = { 0 };
//	for (int i = 0; i < 1200; i++)
//	{
//		if (i < 620) { Input2[i] = -2; }
//		else if (i >= 570 && i < 620) { Input2[i] = (-10 + 2) / (5.0) * (i - 570.0) / 10; }
//		else if (i >= 620 && i < 760) { Input2[i] = -10.0; }
//		else if (i >= 760 && i < 800) { Input2[i] = (-5 + 10) / (6.0) * (i - 760.0) / 10; }
//		else if (i > 800 && i <= 930) { Input2[i] = -5.0; }
//		else if (i >= 930 && i < 1130) { Input2[i] = (-50 + 5) / (10.0) * (i - 930.0) / 10; }
//		else if (i >= 1130 && i <= 1190) { Input2[i] = -50.0; }
//	}
//	double Input3[1200] = { 0 };
//	for (int i = 0; i < 1200; i++)
//	{
//		if (i < 500) { Input3[i] = 0.0; }
//		else if (i >= 500 && i < 530) { Input3[i] = (90) / (3.0) * (i - 500.0) / 10; }
//		else if (i > 500 && i <= 1190) { Input3[i] = 90.0; }
//	}
//	double Input4[1200] = { 0 };
//	for (int i = 0; i < 1200; i++)
//	{
//		if (i < 50) { Input4[i] = 0; }
//		else { Input4[i] = 1; }
//	}
//
//
//	SOCKET sClient;
//	struct sockaddr_in remoteAddr;
//	int ret = -1;
//	int nAddrlen = sizeof(remoteAddr);
//	double revdata[255];
//
//	//CreateThread(NULL, 0, AddDrone_1Proc, 0, 0, &dwThreadId1);//AddDrone
//
//	sClient = accept(serSocket, (SOCKADDR *)&remoteAddr, &nAddrlen);
//	/* Do a simple run up till 10 seconds */
//	while (time <= 200)
//	{
//		
//		ret = recv(sClient, revdata, 255, 0);
//
//		int INTTime = (int)(time * 10);//0.1s
//
//		if (ret > 0) {
//			memcpy(recvdata, revdata, sizeof(recvdata));
//			
//			for (i = 0; i < numinputs_to_model; i++)
//			{
//				if (i == 0)
//				{
//					inputs[i] = recvdata[0]; /* x */
//				}
//				else if (i == 1)
//				{
//					inputs[i] = recvdata[1]; /* y */
//				}
//				else if (i == 2)
//				{
//					inputs[i] = recvdata[2]; /*z */
//				}
//				else if (i == 3)
//				{
//					inputs[i] = recvdata[3]; /* yaw */
//				}
//				else if (i == 4)
//				{
//					inputs[i] = recvdata[4]; /* bool */
//				}
//			}
//			
//
//			if (!model_initialised)
//			{
//				fprintf(stdout, "MASTER> Starting simulation with a call to InitModel.\n\n");
//				amedll.AMEInitModel(time, printinter, samptime, tol, errtype, writelevel,
//					disconpr, runstats, runtype, thesolvertype,
//					numinputs_to_model, numoutputs_from_model, inputs, outputs);
//				model_initialised = 1;
//			}
//
//			amedll.AMEdoAStep2(time, numinputs_to_model, numoutputs_from_model, inputs, outputs);
//			
//			for (i = 0; i < numinputs_to_model1; i++)
//			{
//				if (i == 0)
//				{
//					inputs1[i] = recvdata[5]; /* x */
//				}
//				else if (i == 1)
//				{
//					inputs1[i] = recvdata[6]; /* y */
//				}
//				else if (i == 2)
//				{
//					inputs1[i] = recvdata[7]; /*z */
//				}
//				else if (i == 3)
//				{
//					inputs1[i] = recvdata[8]; /* yaw */
//				}
//				else if (i == 4)
//				{
//					inputs1[i] = recvdata[9]; /* bool */
//				}
//			}
//			if (!model_initialised1)
//			{
//				fprintf(stdout, "MASTER> Starting simulation with a call to InitModel.\n\n");
//				amedll1.AMEInitModel(time, printinter, samptime, tol, errtype, writelevel,
//					disconpr, runstats, runtype, thesolvertype,
//					numinputs_to_model1, numoutputs_from_model1, inputs1, outputs1);
//				model_initialised1 = 1;
//			}
//
//		  amedll1.AMEdoAStep2(time, numinputs_to_model1, numoutputs_from_model1, inputs1, outputs1);
//			
//			fprintf(stdout, "time = %.3f\t", time);
//			for (i = 0; i < numoutputs_from_model1; i++)//numoutputs_from_model = 6
//			{
//				fprintf(stdout, "out%d = %.3f\t", i, outputs1[i]);
//			}
//			fprintf(stdout, "\n");
//			printf("recvdataX = %f\n", recvdata[5]);
//			printf("inputsX = %f\n", inputs1[0]);
//			
//			//for (i = 0; i < numinputs_to_model1; i++)//numoutputs_from_model = 6
//			//{
//			//	fprintf(stdout, "in%d = %.3f\t", i, inputs1[i]);
//			//}
//
//
//
//			for (int i = 0; i < 6; i++) { //0-5
//				senddata[i] = (float)(outputs[i]);
//			}
//			for (int i = 6; i < 12; i++) { //6-11
//				senddata[i] = (float)(outputs1[i-6]);
//			}
//			printf("senddata[3] = %f\n", senddata[3]);//x
//			printf("senddata[9] = %f\n", senddata[9]);//x1
//			//pthread_mutex_unlock(&mut);
//
//			//fprintf(stdout, "\n");
//			//memcpy(senddata, (float*)outputs, sizeof(senddata)); //指针只指向前32位 
//			//printf(" sizeof(senddata)=%d\n", sizeof(senddata));
//			//sendto(sclient, senddata, strlen(senddata), 0, (SOCKADDR*)&clientAddr, len);
//
//			//Sleep(100);//0.1s
//
//			/* Update the time for the next step */
//			time += samptime;
//			
//		}
//	}
//
//	/* Allow for a "clean" end of the AMESim model with Terminate. */
//	amedll.AMETerminate();
//	amedll1.AMETerminate();
//	/* Tell the operating system we no longer use the DLL
//	(freeamesimdll). This will normally unload the DLL. In this
//	example it does not matter, but if one wants to perform several
//	simulations without leaving this program it is important to do
//	this since unloading the DLL will ensure for it to be properly
//	(re-)initialized when loading it. After the call to
//	freeamesimdll it is not possible to use the model until a
//	loadamesimdll has been done.*/
//	printf("DONE AND CLOSE\n");
//	sendstate = 0;
//	unloadamesimdll(&amedll);
//	unloadamesimdll(&amedll1);
//	closesocket(serSocket);
//
//	WSACleanup();
//	//CloseHandle(dwThreadId);
//	system("pause");
//	/* Return 0 - to indicate success */
//	return 0;
//}