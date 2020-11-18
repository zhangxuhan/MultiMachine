///**This is a simple example of a code that loads an AMESim DLL (shared library)
//* created for Co-simulation and use this DLL for doing some simple simulation
//* \author: Arne Jansson (arne.jansson@lmsintl.com)
//* \date Dec 17 2007 last modification
//* COPYRIGHT 2007 IMAGINE SA
//*/
//#define _CRT_SECURE_NO_WARNINGS
//
//#include <math.h>
//#include <stdio.h>
//#include <winsock2.h>
//#include <WS2tcpip.h>
//#include <stdlib.h>
//#include <string.h>
////#include "ame_api.h"
////#include "ame_api_errors.h"
//#include <windows.h>
//#include <wchar.h>
////#include "stdafx.h"
//#include "import_dll_utils.h"
//
//#pragma comment(lib, "ws2_32.lib")
//
//
//static int sendstate = 0;
//static float senddata[6];//roll p y x y z
//static float recvdata[5];//x y z yaw 1
//
//DWORD WINAPI ListenProc(LPVOID lpParam)//Listen
//{
//	
//	return 0;
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
//	char* sendbuf = (char*)malloc(sizeof(ViewStruct) );
//
//	WORD sockVision = MAKEWORD(2, 2);
//	WSADATA wsadata;
//	SOCKET sclient;
//	struct sockaddr_in clientAddr;
//	
//	int ret = -1;
//	int len = -1;
//	if (WSAStartup(sockVision, &wsadata) != 0)
//	{
//		printf("WSA failed\n");
//		return 0;
//	}
//	sclient = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
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
//	while (sendstate == 1)
//	{
//		//printf("sbuf[0]=%d\n", sbuf[0]);
//		//memcpy(sendbuf, senddata, sizeof(senddata));
//
//		sendto(sclient, senddata, sizeof(senddata), 0, (SOCKADDR*)&clientAddr, len);
//		//printf("udpx= %f\n", senddata[3]);
//		Sleep(50);
//	}
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
//
//	char *libname = ".\\drone_asd_.dll";
//
//
//
//
//	//获取输入缓存大小
//	int sBufSize = strlen(libname);
//	DWORD dBufSize = MultiByteToWideChar(CP_ACP, 0, libname, sBufSize, NULL, 0);
//	printf("have wchar_t:  %d\n", dBufSize);
//	int iSize = MultiByteToWideChar(CP_ACP, 0, libname, sBufSize, NULL, 0);
//	wchar_t* pwszUnicode = (wchar_t *)malloc(iSize * sizeof(wchar_t));
//	// 进行转换
//	MultiByteToWideChar(CP_ACP, 0, libname, sBufSize, pwszUnicode, dBufSize);
//
//	printf("pwszUnicode = %s\n", UnicodeToGB2312(libname));
//
//
//
//	/* The DLL (or shared library) is loaded. If it fails to load we exit. */
//	if (!loadamesimdll(argv[1], &amedll))
//	{
//		fprintf(stderr, "failed to load DLL %s\n", argv[1]);
//		fprintf(stderr, "libname IS %s\n", libname);
//		exit(1);
//	}
//	else
//	{
//		fprintf(stdout, "AMESim model '%s' loaded OK\n", argv[1]);
//	}
//
//	/* set model directory */
//	strcpy(tmpfullname, argv[1]);
//	dirsep = strrchr(tmpfullname, '/');
//	if (dirsep)
//	{
//		dirsep++;
//		*dirsep = '\0';
//		fprintf(stdout, "MASTER> Setting model directory to %s\n", tmpfullname);
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
//		fprintf(stdout,
//			"MASTER> AMESim model have \n %d inputs \n %d outputs \n %d state variables \n %d implicit variables\n",
//			ame_says_numinputs, ame_says_numoutputs, ame_says_numstates, ame_says_numimplicit);
//
//		/*In this case we only accept systems with two inputs and three outputs. */
//		/*if (ame_says_numinputs != 5)
//		{
//			fprintf(stderr, "Expected model with 2 inputs. Got %d.\n", ame_says_numinputs);
//			exit(1);
//		}
//		*/
//		numinputs_to_model = ame_says_numinputs;//5
//		numoutputs_from_model = ame_says_numoutputs;//6
//	}
//
//	/* Create the input/output arrays */
//	inputs = (double*)calloc(1, numinputs_to_model * sizeof(double));//Allocates the required memory space and returns a pointer to it
//	outputs = (double*)calloc(1, numoutputs_from_model * sizeof(double));
//
//
//	//initialize output 
//	//for (i = 0; i < numoutputs_from_model; i++)
//	//{
//	//	if (i == 0)
//	//	{
//	//		outputs[i] = 0;
//	//	}
//	//	else if (i == 1)
//	//	{
//	//		outputs[i] = 4.0;
//	//	}
//	//	else if (i == 2)
//	//	{
//	//		outputs[i] = 0;
//	//	}
//	//	else if (i == 3)
//	//	{
//	//		outputs[i] = 180;
//	//	}
//	//	else
//	//	{
//	//		outputs[i] = 1;
//	//	}
//	//}
//
//
//	//udp Recv
//	WSADATA wsaData;
//	DWORD dwThreadId;//线程ID
//	DWORD dwThreadId2;
//	WORD sockVersion = MAKEWORD(2, 2);
//	//other variables
//	SOCKET serSocket;
//	struct sockaddr_in remoteAddr;
//	struct sockaddr_in sin;
//	int ret = -1;
//	int nAddrlen = sizeof(remoteAddr);
//	double revdata[255];
//	fd_set rfd;                     // 描述符集 这个将用来测试有没有一个可用的连接
//	struct timeval timeout;
//	timeout.tv_sec = 0;               //等下select用到这个
//	timeout.tv_usec = 0;              //timeout设置为0，可以理解为非阻塞
//	int rev = 0;
//	int SelectRcv;
//
//
//
//
//	if (WSAStartup(sockVersion, &wsaData) != 0)
//	{
//		printf("WSAStartup error !");
//		return 0;
//	}
//	//create socket
//	serSocket = socket(AF_INET, SOCK_DGRAM, 0);//IPPROTO_UDP
//	if (serSocket == INVALID_SOCKET)
//	{
//		printf("socket FAILED\n");
//		return 0;
//	}
//
//	if (setsockopt(serSocket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) == -1) {
//		printf("setsockopt failed:");
//	}
//	unsigned long imode = 1;//非阻塞
//	int nStatus;
//	nStatus = ioctlsocket(serSocket, FIONBIO, &imode);//*
//	if (nStatus == SOCKET_ERROR)
//	{
//		printf("非阻塞模式失败\n");
//	}
//	printf("nStatus=%d\n", nStatus);
//	//bind ip ports
//	sin.sin_family = AF_INET;
//	sin.sin_port = htons(8888);//remote ports
//	sin.sin_addr.S_un.S_addr = INADDR_ANY;
//	if (bind(serSocket, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
//	{
//		printf("BIND IP & PORTS \n");
//		return 0;
//	}
//	//ret = recvfrom(serSocket, revdata, 255, 0, (SOCKADDR*)&remoteAddr, &nAddrlen);
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
//	for (i = 0; i < numinputs_to_model; i++)
//	{
//		if (i == 0)
//		{
//			inputs[i] = 0; /* pumpspeed */
//		}
//		else if (i == 1)
//		{
//			inputs[i] =0; /* valve input signal */
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
//	double Input0[1200] = {0};
//	for (int i =0; i<1200;i++)
//	{
//		if(i <110){ Input0[i] = 0; }
//		//else if (i >= 110 && i < 190) { Input0[i] = (10/(19-11)) * (i-110) / 10; }
//		else if (i >= 110 && i < 190) { Input0[i] = (10.0 / (19.0 - 11.0))* (i - 110.0) / 10; }
//		else if (i>=190 && i<430){ Input0[i] = 10.0; }
//		else if (i >= 430 && i < 460) { Input0[i] = 3.0 / (3.0) * (i - 430.0) / 10; }
//		else if (i >= 460 && i < 620) { Input0[i] = 13.0; }
//		else if (i >= 620 && i < 660) { Input0[i] = (5-13) / (4.0) * (i - 620.0) / 10; }
//		else if (i >= 660 && i <= 1199) { Input0[i] = 5.0; }	
//	}
//
//	double Input1[1200] = { 0 };
//	for (int i = 0; i < 1200; i++)
//	{
//		if (i < 230) { Input1[i] = 0.0; }
//		else if (i >= 230 && i < 390) { Input1[i] = (0 - 20) / (39.0-23.0) * (i - 320.0) / 10; }
//		else if (i >= 390 && i < 840) { Input1[i] = -20.0; }
//		else if (i >= 840 && i < 890) { Input1[i] = (-10 + 20) / (5.0) * (i - 840.0) / 10; }
//		else if (i >= 890 && i <= 1190) { Input1[i] = -10.0; }
//	}
//	double Input2[1200] = { 0 };
//	for (int i = 0; i < 1200; i++)
//	{
//		if (i < 620) { Input2[i] = -2; }
//		else if (i >= 570 && i < 620) { Input2[i] = (-10 +2) / (5.0) * (i - 570.0) / 10; }
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
//		else  { Input4[i] = 1; }
//	}
//
//
//
//	/* Do a simple run up till 10 seconds */  
//	while (time <= 200)
//	{
//		//ret = recvfrom(serSocket, revdata, 255, 0, (SOCKADDR*)&remoteAddr, &nAddrlen);
//		FD_ZERO(&rfd);           //总是这样先清空一个描述符集
//		FD_SET(serSocket, &rfd); //把sock放入要测试的描述符集
//		SelectRcv = select(serSocket + 1, &rfd, 0, 0, &timeout); //检查该套接字是否可读
//		//FD_ISSET(serSocket, &fdread)
//
//		if (FD_ISSET(serSocket, &rfd))
//		{
//		ret = recvfrom(serSocket, revdata, 255, 0, (SOCKADDR*)&remoteAddr, &nAddrlen);
//		
//			/* SET THE INPUTS TO THE AMESIM MODEL HERE */
//		int INTTime = (int)(time * 10);//0.1s
//		 
//			 if (ret > 0) {
//				 memcpy(recvdata, revdata, sizeof(recvdata));
//				 //printf("recvdata[0]=%f\n", recvdata[0]);
//				 for (i = 0; i < numinputs_to_model; i++)
//				 {
//					 if (i == 0)
//					 {
//						 inputs[i] = Input0[INTTime]; /* Pumpspeed */
//					 }
//					 else if (i == 1)
//					 {
//						 inputs[i] = Input1[INTTime]; /* Valve input signal */
//					 }
//					 else if (i == 2)
//					 {
//						 inputs[i] = Input2[INTTime]; /* Any other signal */
//					 }
//					 else if (i == 3)
//					 {
//						 inputs[i] = Input3[INTTime]; /* Any other signal */
//					 }
//					 else if (i == 4)
//					 {
//						 inputs[i] = Input4[INTTime]; /* Any other signal */
//					 }
//					 else if (i == 5)
//					 {
//						 inputs[i] = recvdata[3]; 
//					 }
//					 else if (i == 6)
//					 {
//						 inputs[i] = recvdata[2]; /* Any other signal */
//					 }
//					 else if (i == 7)
//					 {
//						 inputs[i] = recvdata[1]; /* Any other signal */
//					 }
//					 else if (i == 8)
//					 {
//						 inputs[i] = recvdata[0]; /* Any other signal */
//					 }
//				 }
//			 }
//		
//
//		if (!model_initialised)
//		{
//			/* InitModel loads the AMESim model data, set up the model
//			(with an init call) and checks that number of
//			inputs/outputs agree. We do the init in the loop since it
//			will also do a call to the model and it needs to have the
//			inputs set properly. */
//			fprintf(stdout, "MASTER> Starting simulation with a call to InitModel.\n\n");
//			amedll.AMEInitModel(time, printinter, samptime, tol, errtype, writelevel,
//				disconpr, runstats, runtype, thesolvertype,
//				numinputs_to_model, numoutputs_from_model, inputs, outputs);
//			model_initialised = 1;
//		}
//
//		/* Here we do a call to the AMESim model and asks it to
//		calculate its outputs up to time="time" using the inputs sent. */
//		//double t,               /**< final integration time */
//		//	int numInputs,          /**< num inputs to the AMESim model */
//		//	int numOutputs,         /**< num outputs from the AMESim model */
//		//	const double *theInputs,/**< vector with inputs to the AMESim model */
//		//	double *theOutputs      /**< vector with outputs from the AMESim model */
//		amedll.AMEdoAStep2(time, numinputs_to_model, numoutputs_from_model, inputs, outputs);
//		//AMEInputs
//		//amedll.AMEOutputs(time, numoutputs_from_model, outputs);
//
//		//sendto(sclient, outputs, strlen(outputs), 0, (SOCKADDR*)&clientAddr, len);
//		/* The vector "outputs" now contains the outputs from
//		* the AMESim model at time "time".
//		* In this simple example we only print the values. */
//		fprintf(stdout, "time = %.3f\t", time);
//		for (i = 0; i < numoutputs_from_model; i++)//numoutputs_from_model = 6
//		{
//			fprintf(stdout, "out%d = %.3f\t", i, outputs[i]);
//			
//		}
//		fprintf(stdout, "\n");
//
//		//udp
//		for (int i = 0; i < 6; i++) {
//			senddata[i] = (float)(outputs[i]);
//		}
//		//memcpy(senddata, (float*)outputs, sizeof(senddata)); //指针只指向前32位 
//		//printf(" sizeof(senddata)=%d\n", sizeof(senddata));
//		//sendto(sclient, senddata, strlen(senddata), 0, (SOCKADDR*)&clientAddr, len);
//
//		//Sleep(100);//0.1s
//
//		/* Update the time for the next step */
//		time += samptime;
//		}
//	}
//
//	/* Allow for a "clean" end of the AMESim model with Terminate. */
//	amedll.AMETerminate();
//
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
//	closesocket(serSocket);
//	WSACleanup();
//	//CloseHandle(dwThreadId);
//	system("pause");
//	/* Return 0 - to indicate success */
//	return 0;
//}