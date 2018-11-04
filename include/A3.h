/*  A3.h
    Header File for : CIS 2520 Assignment 3.
    By: James Arthur Anderson
    Student ID #: 1013076
    Date: Nov. 5, 2018
*/
/*including of standard libraries*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


#ifndef A1_H
#define A1_H

/*Question 1 stucts and functions*/
//structs
typedef struct treeNodeStruct treeNode;
struct treeNodeStruct{
    treeNode *parent;
    char value[5];

    treeNode *leftBranch;
    treeNode *rightBranch;
};

typedef struct lnkdLstVarStruct varLst;
struct lnkdLstVarStruct{
    char name[5];
    double actual;

    varLst *next;
};
//functions


treeNode * stringParser (char *string);

void printPreOrder (treeNode *node);
void printPostOrder (treeNode *node);
void printInOrder (treeNode *node);

double getVar (char varName[5], varLst **list);
void setVar (char varName[5], double varValue, varLst **list);

void printTreeVisual (treeNode *node,varLst **list);
int getTreeHeight (treeNode *node);

double calculate (treeNode *current,varLst **list);

treeNode *newTreeNode (char value[5]);
varLst *newVarLst (double actual, char value[5]);
void createVarLst (treeNode *tree,varLst *list);

void deleteTree (treeNode *node);
void deleteList (varLst **list);

/*Question 2 functions*/
void downHeap(int heap[20][10],int parentIndex);
int compare(int heap[20][10], int index1, int index2);
void switchNodes(int heap[20][10],int index1, int index2);

#endif

  
