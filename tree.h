#ifndef tree_h
#define tree_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>


typedef struct  _TreeNode{
	User *data;
	struct _TreeNode *left, *right;
}TreeNode_User;

typedef struct _Tree{
	TreeNode_User *root;
}Tree_User;

void CreateTree_User(Tree_User *tree, User *data);
void displayTree_User(TreeNode_User *tree);
void InOrder_User(TreeNode_User *tree);
void FreeTree_User(TreeNode_User *tree);
void UserFromFile_Tree(Tree_User *tree);

User *Input_User_Data();
TreeNode_User *Tree_Search_User(TreeNode_User *tree,long int number);
long int SignIn_User();
void UserToFile(User *user);


#endif