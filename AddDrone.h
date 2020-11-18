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
#define SendDataAmount 6*DroneNum  
#define RecvataAmount 5*DroneNum
#define DroneWithError //报错的两架
//#define DroneWithLag

pthread_t thread[10]; //创建线程函数返回类型
pthread_mutex_t mut; //互斥锁类型


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
extern int RecvLock;
extern int SendLock;
extern int ExeOK;
extern int sendstate[2];


void AddDrone();
void DataInteraction();