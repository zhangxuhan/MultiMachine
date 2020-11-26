#pragma once

#include <math.h>
#include <stdio.h>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h> 
#include <windows.h>
#include <wchar.h>
//
#include "import_dll_utils.h"

#define DroneNum 2	//无人机数量
#define TestNum 10	
#define SendData_Single  6//单机数据量
#define RecvdData_Single  5
#define SendDataAmount SendData_Single*DroneNum  //总数据量
#define RecvataAmount RecvdData_Single*DroneNum
#define DroneWithError //报错的两架
//#define DroneWithLag
#define SimulationTime 21000

#define File0 "opt\\0.txt"
#define File1 "opt\\1.txt"
#define File2 "opt\\2.txt"
#define File3 "opt\\3.txt"
#define File4 "opt\\4.txt"
#define File5 "opt\\5.txt"
#define File6 "opt\\6.txt"
#define File7 "opt\\7.txt"
#define File8 "opt\\8.txt"
#define File9 "opt\\9.txt"
#define File10 "opt\\10.txt"
#define File11 "opt\\11.txt"

pthread_t thread[10]; //创建线程函数返回类型
pthread_mutex_t mut; //互斥锁类型
HANDLE g_hThreadEvent[TestNum];
HANDLE g_EndThreadEvent[TestNum];
HANDLE hThread[TestNum];


typedef struct ForceStruct
{
	double ForceX;
	double ForceY;
	double ForceZ;
	double MovementX;
	double MovementY;
	double MovementZ;
}ForceStruct;


extern float recvdata[RecvataAmount];
extern float senddata[SendDataAmount];
extern float recvdata_1[5];
extern double syncTime;
extern int RecvLock[TestNum];
extern int RecvLockNum;
extern int SendLock;
extern int ExeOK;
extern int sendstate[2];


void AddDrone();
void AddDrone_1();
void AddDrone_2();
void AddDrone_3();
void AddDrone_4();
void AddDrone_5();
void AddDrone_6();
void AddDrone_7();
void AddDrone_8();
void AddDrone_9();
void AddDrone_10();
void AddDrone_11();
void AddDrone_12();
void AddDrone_13();
void AddDrone_14();
void AddDrone_15();
void AddDrone_16();
void AddDrone_17();
void AddDrone_18();
void AddDrone_19();
void DataInteraction();