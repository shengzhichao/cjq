#include "TWJ/list.h"
#include "TWJ/tree.h"
#include "TWJ/map.h"
#include "TWJ/menu.h"

float money;

void CreateTree_User(Tree_User *tree, User *data){
	TreeNode_User *node = (TreeNode_User *)malloc(sizeof(TreeNode_User));
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	if (tree->root == NULL){
		tree->root = node;
	}else{
		TreeNode_User *tmp = tree->root;
		while(tmp != NULL){
			if (tmp->data->number > data->number ){
				if (tmp->left == NULL){
					tmp->left = node;
					return;
				}else{
					tmp = tmp->left;
				}
			}else{
				if (tmp->right ==NULL){
					tmp->right = node;
					return;
				}else{
					tmp = tmp->right;
				}
			}
		}
	}
	return;
}

void UserFromFile_Tree(Tree_User *tree){
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

			CreateTree_User(tree, user);
		}

		fclose(fp);

	}else{
		printf("文件打开失败 ！\n");
	}
	return;	
}

void FreeTree_User(TreeNode_User *tree){
	if (tree){
		FreeTree_User(tree->left);
		free(tree->data);
		free(tree);
		FreeTree_User(tree->right);
	}
	return;
}


TreeNode_User *Tree_Search_User(TreeNode_User *tree,long int number){
	TreeNode_User *ptr = tree;
	while(ptr){
		if ( ptr->data->number == number )	return(ptr);
		if (ptr->data->number > number )		ptr = ptr->left;
		else	ptr = ptr->right;
	}
	return NULL;
}


void UserToFile(User *user){
	
	FILE *fp;
	fp = fopen("Data/user.txt","a");
	if (fp != NULL){
			if(user->number == 0)		return;
			fprintf(fp, "%ld\t", user->number);
			fprintf(fp, "%d\t",user->seat);
			fprintf(fp, "%s\t", user->password);
			fprintf(fp, "%s\t", user->name);
			fprintf(fp, "%f\t", user->money);
			fprintf(fp, "%f\t", user->consume);
			fprintf(fp, "%ld\t", user->atime);
			fprintf(fp, "%ld\n", user->ltime);

		fclose(fp);
	}else{
		printf("文件保存失败 ！\n");
	}
	return;
}

void Recharge_User(long int number){
	system("clear");
	FILE *fp;
	float money;
	Tree_User *tree = (Tree_User *)malloc(sizeof(Tree_User));
	TreeNode_User *Treenode;
	tree->root = NULL;
	UserFromFile_Tree(tree);
	Treenode = Tree_Search_User(tree->root,number);
	List_User *list;
	list = initList_User();
	UserFromFile_list(list);
	NodeUser *tmp1 = list->head;
	while(tmp1 != NULL && tmp1->data->number != Treenode->data->number){
		tmp1 = tmp1->next;
	}
	
	NodeUser *node = tmp1;
	if(node == list->head){
		if(list->head->next == NULL){
			list->head = list->tail = NULL;
		}else{
			list->head = list->head->next;
		}
	}else{
		NodeUser *tmp = list->head;
		while(tmp != NULL && tmp->next != node){
			tmp = tmp->next;
		}
		if(tmp != NULL){
			tmp->next = node->next;
		}
	}
	free(node);

	fp = fopen("Data/user.txt","w");
	//memset(fp,0,sizeof(fp));
	printf("请输入要充值的金额\n");
	scanf("%f",&money);
	Treenode->data->money += money;
	UserToFile(Treenode->data);
	NodeUser *tmp2 = list->head;
	while(tmp2 != NULL){
		UserToFile(tmp2->data);
		tmp2 = tmp2->next;
	}
	fclose(fp);
	Free_Userlist(list->head);
	FreeTree_User(tree->root);

	return;
}

void Quit_User(int seat,long int number){

	system("clear");
	MGraph *graph = (MGraph *)malloc(sizeof(MGraph));
	TableFromFile(graph);
	graph->vexs[seat - 1].mark = 0;
	BFSTraverseAL_File(graph);

	FILE *fp;
	Tree_User *tree = (Tree_User *)malloc(sizeof(Tree_User));
	TreeNode_User *Treenode;
	tree->root = NULL;
	UserFromFile_Tree(tree);
	Treenode = Tree_Search_User(tree->root,number);
	List_User *list;
	list = initList_User();
	UserFromFile_list(list);
	NodeUser *tmp1 = list->head;
	while(tmp1 != NULL && tmp1->data->number != Treenode->data->number){
		tmp1 = tmp1->next;
	}
	
	NodeUser *node = tmp1;
	if(node == list->head){
		if(list->head->next == NULL){
			list->head = list->tail = NULL;
		}else{
			list->head = list->head->next;
		}
	}else{
		NodeUser *tmp = list->head;
		while(tmp != NULL && tmp->next != node){
			tmp = tmp->next;
		}
		if(tmp != NULL){
			tmp->next = node->next;
		}
	}
	free(node);

	fp = fopen("Data/user.txt","w");
	//memset(fp,0,sizeof(fp));
	Treenode->data->ltime = time(0);
	if(Treenode->data->seat <11){
		printf("您本次消费 :%.2f ￥\t",(Treenode->data->ltime - Treenode->data->atime)*0.001666);	
		Treenode->data->consume += (Treenode->data->ltime - Treenode->data->atime)*0.001666;
	}else{
		printf("您本次消费 :%.2f ￥\t",(Treenode->data->ltime - Treenode->data->atime)*0.003333);	
		Treenode->data->consume += (Treenode->data->ltime - Treenode->data->atime)*0.003333;
	}

	printf("累计消费 : %.2f ￥\t",Treenode->data->consume );
	printf("上网时长 : %ld 秒\n", Treenode->data->ltime - Treenode->data->atime);
	Treenode->data->seat = 0;
	Treenode->data->money -= (Treenode->data->ltime - Treenode->data->atime)*0.003333;

	UserToFile(Treenode->data);
	NodeUser *tmp2 = list->head;
	while(tmp2 != NULL){
		UserToFile(tmp2->data);
		tmp2 = tmp2->next;
	}
	fclose(fp);
	Free_Userlist(list->head);
	FreeTree_User(tree->root);

	return;

}

void Enter_User(long int number,int seat){
	FILE *fp;
	Tree_User *tree = (Tree_User *)malloc(sizeof(Tree_User));
	TreeNode_User *Treenode;
	tree->root = NULL;
	UserFromFile_Tree(tree);
	Treenode = Tree_Search_User(tree->root,number);
	List_User *list;
	list = initList_User();
	UserFromFile_list(list);
	NodeUser *tmp1 = list->head;
	while(tmp1 != NULL && tmp1->data->number != Treenode->data->number){
		tmp1 = tmp1->next;
	}
	
	NodeUser *node = tmp1;
	if(node == list->head){
		if(list->head->next == NULL){
			list->head = list->tail = NULL;
		}else{
			list->head = list->head->next;
		}
	}else{
		NodeUser *tmp = list->head;
		while(tmp != NULL && tmp->next != node){
			tmp = tmp->next;
		}
		if(tmp != NULL){
			tmp->next = node->next;
		}
	}
	free(node);
	fp = fopen("Data/user.txt","w");
	//memset(fp,0,sizeof(fp));

	Treenode->data->atime = time(0);
	Treenode->data->seat = seat;
	UserToFile(Treenode->data);
	NodeUser *tmp2 = list->head;
	while(tmp2 != NULL){
		UserToFile(tmp2->data);
		tmp2 = tmp2->next;
	}
	fclose(fp);
	Free_Userlist(list->head);
	FreeTree_User(tree->root);

	return;
}


void display_User(NodeUser *node){

	timeform *form;
	if(node->data->number == 0 || node->data->number > 1000000000000)		return;
	printf("账号: %ld\t",node->data->number);
	printf("用户名: %s\t",node->data->name);
	printf("充值: %.2f\t",node->data->money );
	printf("消费: %.2f\t",node->data->consume );

	form = localtime(&(node->data->atime));
	printf("开始时间:%04u-%02u-%02u  %02u:%02u:%02u\t",
	form->tm_year+1900,form->tm_mon+1,form->tm_mday,form->tm_hour,form->tm_min,form->tm_sec );

	form = localtime(&(node->data->ltime));
	if(node->data->ltime == 0){
		printf("结束时间: 尚未结束\n");
	}else{
		printf("结束时间:%04u-%02u-%02u  %02u:%02u:%02u\n",
		form->tm_year+1900,form->tm_mon+1,form->tm_mday,form->tm_hour,form->tm_min,form->tm_sec );
	}
	printf("\n");

	return;
}


/***************************************************/

void User_Menu(User *user){
	char flag;
	int sign = 0;
	int seat = 0;
	TreeNode_User *node;
	Tree_User *tree = (Tree_User *)malloc(sizeof(Tree_User));
	tree->root = NULL;

	while(1){
		printf("欢迎您: %s\n",user->name );
		printf("1.选座\n");
		printf("2.充值\n");
		printf("3.查询网费\n");
		printf("4.下机\n");
		printf("5.返回上层\n");
		flag = getchar();
		switch(flag){

			case '1':	UserFromFile_Tree(tree);
						node = Tree_Search_User(tree->root,user->number);
						if(sign == 0 && node->data->seat == 0){
							sign = 1;
							getchar();
							
							seat = PromptInput_Table(user);
							Enter_User(user->number,seat);
							system("clear");
						}else{
							system("clear");
							printf("您已经选过座位了 !\n");
							printf("\n");
							getchar();
							printf("请按任意键返回\n");
							getchar();
							system("clear");
						}
						FreeTree_User(tree->root);
						tree->root = NULL;
						
						break;
			case '2':	getchar();
						Recharge_User(user->number);
						getchar();
						printf("充值成功 !\n");
						printf("\n");
						printf("请按任意键返回\n");
						getchar();
						system("clear");
						break;
			case '3':	system("clear");
						UserFromFile_Tree(tree);
						node = Tree_Search_User(tree->root,user->number);
						printf("您的账号还剩: %.2f ￥\n",node->data->money );
						printf("\n");
						getchar();
						printf("请按任意键返回\n");
						getchar();
						FreeTree_User(tree->root);
						tree->root = NULL;
						system("clear");

						break;
			case '4':	getchar();
						Quit_User(user->seat,user->number);
						printf("\n");
						printf("请按任意键返回\n");
						getchar();
						system("clear");
						break;
			case '5':	FreeTree_User(tree->root);
						system("clear");
						//getchar();
						return;
		}
		
	}
	return;
}


/*******************************************************/
