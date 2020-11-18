////TCP 单机的例子
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
//int sendstate[2] = { 0 };
//static int recvforcestate = 0;
//static BOOL CollisioneState = FALSE;//Have collision!
//float senddata[SendDataAmount];//roll p y x y z	6
//float recvdata[RecvataAmount];//x y z yaw boo1   5
//float recvForce[6];//Force x y z  Movement x y z   6
//static float recvdata_1[5];
//double syncTime = 0;
//int RecvLock = 0;
//int SendLock = 0;
//int ExeOK = 0;
//
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
//DWORD WINAPI AddDrone_1Proc(LPVOID lpParam)//add 1
//{
//	//AddDrone();
//	return 0;
//}
//
//DWORD WINAPI RecvForceProc(LPVOID lpParam)//add 1
//{
//	WORD sockVersion = MAKEWORD(2, 2);
//	WSADATA wsaData;
//	if (WSAStartup(sockVersion, &wsaData) != 0)
//	{
//		printf("WSAStartup error !");
//		return 0;
//	}
//	SOCKET ForceSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//IPPROTO_UDP
//	if (ForceSocket == INVALID_SOCKET)
//	{
//		printf("socket FAILED\n");
//		return 0;
//	}
//	struct sockaddr_in sin1;
//	sin1.sin_family = AF_INET;
//	sin1.sin_port = htons(8889);//remote ports
//	sin1.sin_addr.S_un.S_addr = INADDR_ANY;
//	if (bind(ForceSocket, (LPSOCKADDR)&sin1, sizeof(sin1)) == SOCKET_ERROR)
//	{
//		printf("BINDForceSocket IP & PORTS ERROR\n");
//		return 0;
//	}
//	if (listen(ForceSocket, 5) == SOCKET_ERROR)
//	{
//		printf("listenForceSocket error !");
//		return 0;
//	}
//
//
//	SOCKET sClient_force;
//	struct sockaddr_in remoteAddr_force;
//	int ret_force = -1;
//	int nAddrlen_force = sizeof(remoteAddr_force);
//	double revdata_force[255];
//	sClient_force = accept(ForceSocket, (SOCKADDR *)&remoteAddr_force, &nAddrlen_force);
//
//
//	while (recvforcestate == 1)
//	{
//		//printf("666");
//		ret_force = recv(sClient_force, revdata_force, 255, 0);
//		if (ret_force > 0) {
//			memcpy(recvForce, revdata_force, sizeof(recvForce));
//			CollisioneState = TRUE;
//			printf("Collision!!!!!!!!!!!!!!!!!!!!!\r\n");
//			/*	for (int n = 0; n < 6; n++) {
//				inputs[5 + i] = recvForce[i];
//			}*/
//			Sleep(50);
//		}
//		CollisioneState = FALSE;
//	}
//
//	closesocket(ForceSocket);
//	return 0;
//}
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
//	while (1) {
//		
//			//printf("sbuf[0]=%d\n", sbuf[0]);
//			//memcpy(sendbuf, senddata, sizeof(senddata));
//			sendto(sclient, senddata, sizeof(senddata), 0, (SOCKADDR*)&clientAddr, len);
//			//send(sclient, senddata, sizeof(senddata), 0);
//			//printf("udpx= %f\n", senddata[3]);
//			Sleep(50);
//			//SendLock = 0;
//			sendstate[0] = 0;
//			sendstate[1] = 0;
//		
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
//	int i;
//	int model_initialised = 0;
//	static AME_DLL amedll;
//	char tmpfullname[1024];
//	char *dirsep;
//	//strcpy(tmpfullname, argv[1]);
//	/* ********************************************* */
//	if (argc <= 1)
//	{
//		fprintf(stderr, "Need the name of the DLL used as slave AMESim model\n");
//		fprintf(stderr, "EXIT\n");
//		exit(1);
//	}
//
//#ifdef DroneWithLag
//	char *libname = "..\\drone_asd_.dll";
//#endif
//#ifdef DroneWithError
//	char *libname = "..\\drone_asd_error_.dll";
//#endif // DroneWithError
//
//
//
//	//char *libname = "..\\drone_asd_1_.dll";//不带碰撞的5个输入
//
//
//
//	/* The DLL (or shared library) is loaded. If it fails to load we exit. */
//	if (!loadamesimdll(libname, &amedll))
//	{
//		fprintf(stderr, "failed to load DLL %s\n", libname);
//		exit(1);
//	}
//	else
//	{
//		fprintf(stdout, "AMESim model '%s' loaded OK\n", libname);
//	}
//
//	/* set model directory */
//	strcpy(tmpfullname, libname);
//	dirsep = strrchr(tmpfullname, '/');
//	if (dirsep)
//	{
//		dirsep++;
//		*dirsep = '\0';
//		//fprintf(stdout, "MASTER> Setting model directory to %s\n", tmpfullname);
//		amedll.AMEWorkingDir(tmpfullname);
//	}
//	//amedll.AMEWorkingDir("C:\\Users\\HZ\\Desktop\\amesim_use\\Ab\\AMEtest\\ConsoleApplication1");
//	amedll.AMEWorkingDir("..\\");
//	{
//		/* Check that the AMESim model have the same number of inputs
//		* and outputs as we expect. */
//		int ame_says_numinputs;
//		int ame_says_numoutputs;
//		int ame_says_numstates;
//		int ame_says_numimplicit;
//		amedll.AMEInitSizes(&ame_says_numinputs, &ame_says_numoutputs, &ame_says_numstates, &ame_says_numimplicit);
//
//		numinputs_to_model = ame_says_numinputs;//5
//		numoutputs_from_model = ame_says_numoutputs;//6
//	}
//
//	/* Create the input/output arrays */
//	inputs = (double*)calloc(1, numinputs_to_model * sizeof(double));//Allocates the required memory space and returns a pointer to it
//	outputs = (double*)calloc(1, numoutputs_from_model * sizeof(double));
//
//
//
//	//udp Recv
//	DWORD dwThreadId;//线程ID
//	DWORD dwThreadId1;
//	DWORD dwThreadId2;
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
//	for (i = 0; i < numinputs_to_model; i++)
//	{
//		//if(i==11){ inputs[i] = 5; }
//			inputs[i] = 0; /* any other signal */
//	}
//
//
//
//	SOCKET sClient;
//	struct sockaddr_in remoteAddr;
//	int ret = -1;
//	int nAddrlen = sizeof(remoteAddr);
//	double revdata[255];
//
//
//
//	//SEND
//	CreateThread(NULL, 0, ThreadProc, 0, 0, &dwThreadId);
//
//
//
//	//CreateThread(NULL, 0, AddDrone_1Proc, 0, 0, &dwThreadId1);//AddDrone
//
//
//	CreateThread(NULL, 0, RecvForceProc, 0, 0, &dwThreadId2);//RecvForce
//	recvforcestate = 1;
////	sClient = accept(serSocket, (SOCKADDR *)&remoteAddr, &nAddrlen);
//	/* Do a simple run up till 10 seconds */
//	while (time <= 200)
//	{
//
//		if (!model_initialised)
//		{
//
//			fprintf(stdout, "MASTER> Starting simulation with a call to InitModel.\n\n");
//			amedll.AMEInitModel(time, printinter, samptime, tol, errtype, writelevel,
//				disconpr, runstats, runtype, thesolvertype,
//				numinputs_to_model, numoutputs_from_model, inputs, outputs);
//			model_initialised = 1;
//
//			//CreateThread(NULL, 0, AddDrone_1Proc, 0, 0, &dwThreadId1);//AddDrone
//		}
//		//ret = recv(sClient, revdata, 255, 0);
//		/* SET THE INPUTS TO THE AMESIM MODEL HERE */
//		int INTTime = (int)(time * 10);//0.1s
//
//		//if (ret > 0) {
//		//	memcpy(recvdata, revdata, sizeof(recvdata));
//
//			for (i = 0; i < numinputs_to_model; i++)//21
//			{
//				
//				//0 1 2 3 4 5 6 7 8 9 10 ,11 12 13 14 15 16 ..21
//			   // x y z y b 6dof			 x  y  z yaw b 
//
//				if (i == 0)
//				{
//					inputs[i] = senddata[3] + 2; /*x */
//				}
//				else if (i == 1)
//				{
//					inputs[i] = 0; /*y */
//				}
//				else if (i == 2)
//				{
//					inputs[i] = -3; /* z */
//				}
//				else if (i == 3)
//				{
//					inputs[i] = 0; /* yaw */
//				}
//				else if (i == 4)
//				{
//					inputs[i] = 1; /* bool */
//				}
//				else
//				{
//					inputs[i] = 0; /* force	   x y z
//									  movement x y z
//									  = 6 */
//				}
//			}
//			for (i = 0; i < numinputs_to_model; i++)
//			{
//				printf("inputs1[%d] = %f\n", i, inputs[i]);//x
//			}
//
//			if (CollisioneState == TRUE) {
//				for (int n = 0; n < 6; n++) {
//					inputs[5 + n] = recvForce[n];
//				}
//			}
//
//
//
//
//
//			
//			amedll.AMEdoAStep2(time, numinputs_to_model, numoutputs_from_model, inputs, outputs);
//			
//
//
//			fprintf(stdout, "time = %.3f\t", time);
//			for (i = 0; i < numoutputs_from_model; i++)//numoutputs_from_model = 6
//			{
//				fprintf(stdout, "out%d = %.3f\t", i, outputs[i]);
//			}
//			fprintf(stdout, "\n");
//
//
//
//			for (int i = 0; i < 6; i++) { 
//				senddata[i] = (float)(outputs[i]);
//			}
//
//			time += samptime;
//			syncTime = time;
//			//Sleep(10);
//		//}
//	}
//
//	amedll.AMETerminate();
//
//
//	printf("DONE AND CLOSE\n");
//	//sendstate[0] = 0;
//	recvforcestate = 0;
//	unloadamesimdll(&amedll);
//	closesocket(serSocket);
//	WSACleanup();
//	//CloseHandle(dwThreadId);
//	system("pause");
//	/* Return 0 - to indicate success */
//	return 0;
//}