#include "TWJ/list.h"
#include "TWJ/tree.h"
#include "TWJ/map.h"
#include "TWJ/menu.h"



List_User *initList_User(){
	
	List_User *list = (List_User *)malloc(sizeof(List_User));
	list->head = NULL;
	list->tail = NULL;
	list->current = NULL;

	return list;
}//链表初始化

void addTail_User(List_User *list,User *data){
	
	NodeUser *node = (NodeUser *)malloc(sizeof(NodeUser));
	node->data = data;
	node->next = NULL;

	if(list->head == NULL){
		list->head = node;
	}else{
		list->tail->next = node;
	}
	list->tail = node;

	return;
}//头插法构建链表	

void Free_Userlist(NodeUser *list){

	NodeUser *tmp;
	while(list != NULL){
		tmp = list;
		list = list->next;
		free(tmp);
		tmp = NULL;
	}
	return;
}//释放链表	



void UserToFile_list(List_User *list){
	
	NodeUser *tmp = list->head;
	FILE *fp;
	fp = fopen("Data/user.txt","a");
	if (fp != NULL)
	{
		while(tmp != NULL){
			fprintf(fp, "%ld\t", tmp->data->number);
			fprintf(fp, "%d\t",tmp->data->seat);
			fprintf(fp, "%s\t", tmp->data->password);
			fprintf(fp, "%s\t", tmp->data->name);
			fprintf(fp, "%f\t", tmp->data->money);
			fprintf(fp, "%f\t", tmp->data->consume);
			fprintf(fp, "%ld\t", tmp->data->atime);
			fprintf(fp, "%ld\n", tmp->data->ltime);

			tmp = tmp->next;
		}
		fclose(fp);
	}else{
		printf("文件保存失败 ！\n");
	}
}

void UserFromFile_list(List_User *list){
	FILE *fp;
	fp = fopen("Data/user.txt", "r");
	if (fp != NULL)
	{
		while(!feof(fp)){
			User *user = (User *)malloc(sizeof(User));
			fscanf(fp, "%ld", &(user->number));
			fscanf(fp,"%d",&(user->seat));
			fscanf(fp, "%s", user->password);
			fscanf(fp, "%s", user->name);
			fscanf(fp, "%f", &(user->money));
			fscanf(fp, "%f", &(user->consume));
			fscanf(fp, "%ld", &(user->atime));
			fscanf(fp, "%ld", &(user->ltime));

			addTail_User(list,user);
		}

		fclose(fp);

	}else{
		printf("文件打开失败 ！\n");
	}
	return;
}