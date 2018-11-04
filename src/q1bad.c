/*  q1.c
    Main Function file for CIS 2520 Assignment 3 question 1.
    By: James Arthur Anderson
    Student ID #: 1013076
    Date: Nov. 5, 2018
*/
#include"A3.h"

int main(int argc, char **argv){
    char test[] ="(((x1+5.12)*(x2-7.68))/x3)";
    char userVar[5];
    double userVal =0.0;
    /*if (argc !=2){
        printf("Invalid number of command line argumetns\n");
        return 0;
    }*/
    treeNode *tree;
    stringParser(test,tree);
    varLst *list = newVarLst(0.0,"blank");
    createVarLst(tree,list);
    int input = 0;
    printf("Treehighet %d\n",getTreeHeight(tree));
    while (input !=7){
        printf("Press 1 to Display the binary tree\n");
        printf("Press 2 to Display function in Preorder notation\n");
        printf("Press 3 to Display function in Inorder notation\n");
        printf("Press 4 to Display function in Postorder notation\n");
        printf("Press 5 to update a variable\n");
        printf("Press 6 to calculate the value\n");
        printf("Press 7 to quit\n");
        scanf("%d", &input);
        switch (input){
            case 1:
                printTreeVisual(tree,&list);
                break;
            case 2:
                printPreOrder(tree);
                break;
            case 3:
                printInOrder(tree);
                break;
            case 4:
                printPostOrder(tree);
                break;
            case 5:
                printf("Please the name of the varible you want to change\n");
                scanf(" %s", userVar);
                printf("Please enter the new value of said varible\n");
                scanf("%lf",&userVal);
                setVar(userVar,userVal,&list);
                break;
            case 6:
                printf("The total calculated value is %.2lf\n",calculate (tree,&list));
                break;
            case 7:
                printf("Thank you for using the program\n");
                break;
            default:
                printf("Invalid Input\n");
       }
    }
    deleteTree(tree);
    deleteList(&list);
    return 0;
}

double stringToDouble (char string[5]){
    return 0.0;
}

void stringParser (char *string, treeNode *node){
    char *newString;
    char charHolder[2];
    newString = malloc(2);
    charHolder[1] ='\0';
    char holding[5] = "";
    int i;
    for (i= 0;string[i]!='\0';i++){
        if (string[i]!='('){
            newString = realloc(newString,sizeof(newString)+2);
            charHolder [0] = string[i];
            strcat(newString,charHolder);
            string[i+1] = '\0';
        }
    }






    printf("%s\n",newString);
    for (i= 0;newString[i]!='\0';i++){
        switch (newString[i]){
            case '+':
            case '-':
            case '*':
            case '/':
                charHolder [0] = newString[i];
                if (!node){
                    node = newTreeNode(charHolder);
                    if(!(node->leftBranch)){

                    }

                }
                break;
            default:
                charHolder [0] = newString[i];
                strcat(holding,charHolder);
        }
    }
    stringParser(newString,node);

}

void printPreOrder (treeNode *node){
     if (node){
        printf("%s",node->value);
        printPreOrder (node->leftBranch);
        printPreOrder (node->rightBranch);
    }else{
        return;
    }   
}
void printPostOrder (treeNode *node){
    if (node){
        printPostOrder (node->leftBranch);
        printPostOrder (node->rightBranch);
        printf("%s",node->value);
    }else{
        return;
    }
}
void printInOrder (treeNode *node){
    if (node){
        printf("(");
        printInOrder (node->leftBranch);
        printf("%s",node->value);
        printInOrder (node->rightBranch);
        printf(")");
    }else{
        return;
    }
}


double getVar (char varName[5], varLst **list){
    varLst *tempLst;
    tempLst = *list;
    while(tempLst){
        if (strcmp(varName,tempLst->name) == 0){
            return tempLst->actual;
        }
        tempLst = tempLst->next;
    }
    return 0.00;
}
void setVar (char varName[5], double varValue, varLst **list){
    varLst *tempLst;
    tempLst = *list;
    while(tempLst){
        if (strcmp(varName,tempLst->name) == 0){
            tempLst->actual = varValue;
            return;
        }
        tempLst = tempLst->next;
    }
}

void printTreeVisual (treeNode *node, varLst **list){
    int i;
    if (!node){
        return;
    }
    printTreeVisual(node->leftBranch,list);

    for (i =0; i< (getTreeHeight(node)*2);i++){
        printf(" ");
    }
    printf("%s",node->value);

    if (strcmp(node->value,"x0")>0){
        printf(" %.2lf",getVar(node->value,list));   
    }
    printf("\n");
//    printTreeVisual(node->leftBranch,list);
    printTreeVisual(node->rightBranch,list);
    
}
int getTreeHeight (treeNode *node){
    int left;
    int right;
    if (node){
        left = getTreeHeight(node->leftBranch)+1;
        right = getTreeHeight(node->rightBranch)+1;
        if (right > left){
            return right;
        }else{
            return left;
        }
    }else{
        return 1;
    }

}

double calculate (treeNode *current, varLst **list){
    //using if else if style because strings 
    double hold;
    double var1;
    double var2;
    printf("Current cal Node %p\n",current);
    if (current){
        if (!(current->leftBranch && current->rightBranch)){
            if(strcmp(current->value,"x0")>0){//checking to see if value is a variable
                printf("var: %s;%.2lf",current->value,getVar(current->value,list));
                return getVar(current->value,list);
            }else if (strcmp(current->value,"")!=0){
                printf("float %s,",current->value);
                printf("Returning %lf", atof(current->value));
                return atof(current->value);
            }
        }else{
            if (strcmp(current->value,"+") ==0 ){
                printf("+");
                var1 = calculate(current->leftBranch,list);
                var2 = calculate(current->rightBranch,list);
                hold = var1+var2;
                printf("\n%.2lf+%.2lf:'%.2lf',",var1,var2,hold);
                return hold;
            }else if(strcmp(current->value,"-")==0){
                printf("-");
                var1 = calculate(current->leftBranch,list);
                var2 = calculate(current->rightBranch,list);
                hold = var1-var2;
                printf("\n%.2lf-%.2lf:'%.2lf',",var1,var2,hold);
                return hold;
            }else if(strcmp(current->value,"*")==0){
                printf("*");
                var2 = calculate(current->rightBranch,list);
                var1 = calculate(current->leftBranch,list);
                hold = var1*var2;
                printf("\n%.2lf*%.2lf:'%.2lf',",var1,var2,hold);
                return hold;
            }else if(strcmp(current->value,"/")==0){
                printf("/");
                if (calculate(current->rightBranch,list) != 0){
                    var1 = calculate(current->leftBranch,list);
                    var2 = calculate(current->rightBranch,list);
                    hold = var1/var2;
                    printf("\n%.2lf/%.2lf:'%.2lf',",var1,var2,hold);    
                    return hold;       
                }else{
                    printf("\nDivide by zero occured\n");
                    return 1000000000.0;
                }
            }else{
                printf("Derp");
            }
        }
    }else{
        return 0.0;
    }
}

treeNode *newTreeNode (char value[5]){
    treeNode *newNode = NULL;
    newNode = malloc(sizeof(treeNode));
    strcpy (newNode->value,value);
    newNode->parent = NULL;
    newNode->leftBranch =NULL;
    newNode->rightBranch = NULL;
    return newNode;
}
varLst *newVarLst (double actual, char value[5]){
    varLst *newNode = NULL;
    newNode = malloc (sizeof(varLst));
    strcpy(newNode->name,value);
    newNode->actual = actual;
    newNode->next = NULL;
    return newNode;
}
void createVarLst (treeNode *tree, varLst *list){
    varLst *temp;
    if (tree){
//printf("var: %s\n",tree->value);

        if(strcmp(tree->value,"x0")>0){
            printf("var: %s\n",tree->value);
            temp = newVarLst(0.0,tree->value);
            temp->next = list->next;
            list->next = temp;
        }
        createVarLst(tree->leftBranch,list);
        createVarLst(tree->rightBranch,list);
    }else{
        return;
    }
}

void deleteTree (treeNode *node){
    if (node){
        deleteTree (node->leftBranch);
        deleteTree (node->rightBranch);
        free (node);
    }else{
        return;
    }
}
void deleteList (varLst **list){
    varLst *temp;
    while (*list){
        temp = (*list)->next;
        free(*list);
        *list = temp;
    }
}

