#include "TWJ/list.h"
#include "TWJ/tree.h"
#include "TWJ/map.h"
#include "TWJ/menu.h"

float money;


NodeUser *Find_User_number(List_User *list,long int number){
	NodeUser *tmp = list->head;
	while(tmp != NULL && tmp->data->number != number){
		tmp = tmp->next;
	}
	return tmp;
}//通过name查找节点并返回

NodeUser *Find_User_name(List_User *list,char name[]){
	NodeUser *tmp = list->head;
	while(tmp != NULL && strcmp(tmp->data->name,name)){
		tmp = tmp->next;
	}
	return tmp;
}//通过name查找节点并返回


void Seek_name(){
	system("clear");
	char name[20];
	NodeUser *user;
	List_User *list = initList_User();
	UserFromFile_list(list);
	
	printf("请输入你要查找的用户名\n");
	scanf("%s",name);
	user = Find_User_name(list,name);
	if(user != NULL)
		display_User(user);
	else
		printf("未找到 !\n");
	
	Free_Userlist(list->head);
	printf("\n");
	getchar();
	printf("请按任意键返回\n");
	getchar();
	system("clear");

	return;
}

void Seek_number(){
	system("clear");
	long int number;
	NodeUser *user;
	List_User *list = initList_User();
	UserFromFile_list(list);
	
	printf("请输入你要查找的账号\n");
	scanf("%ld",&number);
	user = Find_User_number(list,number);
	if(user != NULL)
		display_User(user);
	else
		printf("未找到 !\n");
	
	Free_Userlist(list->head);
	printf("\n");
	getchar();
	printf("请按任意键返回\n");
	getchar();
	system("clear");

	return;
}


void Seek_Menu(){
	system("clear");
	char flat;
	while(1){
		printf("请选择你要进行的操作\n");
		printf("1.用户名查找\n");
		printf("2.账号查找\n");
		printf("3.退出\n");
		flat = getchar();
		switch(flat){
			case '1':	Seek_name();
						break;
			case '2':	Seek_number();
						break;
			case '3':	system("clear");
						return;
		}

	}


	return;
}

void InOrder_User_Money(TreeNode_User *tree){
	if(tree){
		InOrder_User_Money(tree->left);
		money += tree->data->consume;
		InOrder_User_Money(tree->right);
	}
}


void Turnover(){
	system("clear");
	Tree_User *tree = (Tree_User *)malloc(sizeof(Tree_User));
	tree->root = NULL;
	UserFromFile_Tree(tree);
	InOrder_User_Money(tree->root);

	printf("营业额为:  %.2f\n",money);
	printf("请按任意键返回\n");
	getchar();
	system("clear");

	return;

}


User *Input_User_Data(){
	system("clear");
	long int number;
	char password[50];
	char name[30];
	User *user = (User *)malloc(sizeof(User));
	user->money = 0;
	user->consume = 0;
	user->seat = 0;
	printf("请输入你要注册的账户\n");
	scanf("%ld",&number);
	user->number = number;

	printf("请输入姓名\n");
	scanf("%s",name);
	strcpy(user->name,name);

	printf("请输入密码\n");
	scanf("%s",password);
	strcpy(user->password,password);
	
	printf("\n");
	printf("请按任意键返回\n");
	getchar();
	getchar();
	system("clear");


	return user;
}


long int SignIn_User(){
	system("clear");
	long int number;
	char password[50];
	int sign1 = 1, sign2 = 1;
	Tree_User *tree = (Tree_User *)malloc(sizeof(Tree_User));
	TreeNode_User *node;
	tree->root = NULL;
	UserFromFile_Tree(tree);
	printf("请输入账号\n");
	scanf("%ld",&number);

	while(1){
		if(sign1 >= 3){
				printf("账号错误三次 !\n");
				printf("正在退出....\n");
				sleep(2);
				system("clear");
				return 0;
				
		}else if((node = Tree_Search_User(tree->root,number)) == NULL){
				printf("账号不存在 !\n");
				printf("请重新输入\n");
				scanf("%ld",&number);
				
				sign1++;
			
		}else{
			break;
		}
	}
	printf("请输入密码\n");
	scanf("%s",password);
	while(1){
		if(sign2 >= 3){
				printf("密码错误三次 !\n");
				printf("正在退出....\n");
				sleep(2);
				system("clear");
				return 0;
				
		}else if(strcmp(node->data->password,password)){
				printf("密码错误 !\n");
				printf("请重新输入\n");
				scanf("%s",password);

				sign2++;
		}else{
			break;
		}
	}
	FreeTree_User(tree->root);
	printf("\n");
	printf("正在登入.....\n");
	sleep(2);
	getchar();
	system("clear");

	return number;
}

void SignIn_User_Menu(){
	system("clear");
	char flag;
	long int number;
	User *user = (User *)malloc(sizeof(User));
	User *user1;
	Tree_User *tree = (Tree_User *)malloc(sizeof(Tree_User));
	TreeNode_User *node;
	tree->root = NULL;
	UserFromFile_Tree(tree);
	while(1){
		printf("1.登入\n");
		printf("2.注册\n");
		printf("3.退出\n");
		flag = getchar();
		switch(flag){
			case '1':	UserFromFile_Tree(tree);
						if((number = SignIn_User(user)) != 0){
							node = Tree_Search_User(tree->root,number);
							User_Menu(node->data);
							
						}
						FreeTree_User(tree->root);
						tree->root = NULL;
						getchar();
						break;
			case '2':	user1 = Input_User_Data();
						UserToFile(user1);
						FreeTree_User(tree->root);
						tree->root = NULL;
						//UserFromFile_Tree(tree);
						break;
			case '3':	free(user);
						FreeTree_User(tree->root);
						getchar();
						system("clear");
						
						return;
		}
	}


	return;
}

void displayTree_User(TreeNode_User *tree){	
	timeform *form;
	if(tree->data->number == 0 || tree->data->number > 1000000000000)		return;
	printf("账号: %ld\t",tree->data->number);
	printf("用户名: %s\t",tree->data->name);
	printf("充值: %.2f\t",tree->data->money );
	printf("消费: %.2f\t",tree->data->consume );

	form = localtime(&(tree->data->atime));
	printf("开始时间:%04u-%02u-%02u  %02u:%02u:%02u\t",
	form->tm_year+1900,form->tm_mon+1,form->tm_mday,form->tm_hour,form->tm_min,form->tm_sec );

	form = localtime(&(tree->data->ltime));
	if(tree->data->ltime == 0){
		printf("结束时间: 尚未结束\n");
	}else{
		printf("结束时间:%04u-%02u-%02u  %02u:%02u:%02u\n",
		form->tm_year+1900,form->tm_mon+1,form->tm_mday,form->tm_hour,form->tm_min,form->tm_sec );
	}
	printf("\n");
	printf("_____________________________________________________________________________________\n");

	return;
}


void InOrder_User(TreeNode_User *tree){
	if (tree){
		InOrder_User(tree->left);
		displayTree_User(tree);
		InOrder_User(tree->right);
	}
	return;
}


void Manage_Menu(){
	char flag;
	char password[32];
	char password1[32];
	strcpy(password,"123");
	printf("请输入管理员密码\n");
	scanf("%s",password1);
	if(strcmp(password1,password)){
		printf("密码错误 !\n");
		printf("正在退出....\n");
		sleep(2);
		system("clear");
		return;
	}else{
		system("clear");
		getchar();
	}
	Tree_User *tree = (Tree_User *)malloc(sizeof(Tree_User));
	tree->root = NULL;
	UserFromFile_Tree(tree);
	while(1){
		printf("1.客户信息\n");
		printf("2.查找客户\n");
		printf("3.营业额\n");
		printf("4.退出\n");
		flag = getchar();
		switch(flag){

			case '1':	getchar();
						system("clear");
						InOrder_User(tree->root);
						printf("\n");
						printf("请按任意键返回\n");
						getchar();
						system("clear");
						break;
			case '2':	getchar();
						Seek_Menu();
						getchar();
						break;
			case '3':	getchar();
						Turnover();
						break;
			case '4':	system("clear");
						
						return;
		}
		
	}
	return;
}

void Main_Menu(){
	char flag;
	while(1){
		printf("请选择你要进行的操作\n");
		printf("1.用户登入\n");
		printf("2.管理\n");
		printf("3.退出\n");
		flag = getchar();
		switch(flag){

			case '1':	getchar();
						system("clear");
						SignIn_User_Menu();
						system("clear");
						break;
			case '2':	system("clear");
						getchar();
						Manage_Menu();		
						system("clear");
						getchar();
						break;

			case '3':	system("clear");
						return;


		}
		
	}
}
