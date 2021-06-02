#ifndef list_h
#define list_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

#define MaxVerNum 25	
#define INFINITY 10000
typedef struct tm timeform;

typedef struct _User{
	long int number;			//用户账号
	int seat;					//座位号
	char name[20]; 				//用户名
	char password[30];			//密码
	float  money;				//充值
	float consume;				//消费
	time_t atime;				//到达时间
	time_t ltime;				//离去时间

}User;


typedef struct _node
{
	User  *data;
	struct _node *next;

}NodeUser;

typedef struct _linkedList
{
	NodeUser *head;
	NodeUser *tail;
	NodeUser *current;

}List_User;

List_User *initList_User();
void addTail_User(List_User *list,User *data);
void Free_Userlist(NodeUser *list);
void UserToFile_list(List_User *list);
void UserFromFile_list(List_User *list);
void display_User(NodeUser *node);


#endif