/*  q1.c
    Main Function file for CIS 2520 Assignment 3 question 1.
    By: James Arthur Anderson
    Student ID #: 1013076
    Date: Nov. 5, 2018
*/
#include"A3.h"

int main(int argc, char **argv){
    //char test[] ="(x1*(7.45-(x2/2.03)))";
    //char test[] ="(((x1+5.12)*(x2-7.68))/3)";
    char userVar[5];
    double userVal =0.0;
    if (argc !=2){
        printf("Invalid number of command line argumetns\n");
        return 0;
    }
    treeNode *tree = stringParser(argv[1]);
    varLst *list = newVarLst(0.0,"blank");
    createVarLst(tree,list);
    int input = 0;
    //printf("Treehighet %d\n",getTreeHeight(tree));
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
                printf("\n");
                break;
            case 3:
                printInOrder(tree);
                printf("\n");
                break;
            case 4:
                printPostOrder(tree);
                printf("\n");
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

/*Takes a string and goes through each value to build a tree
 *returns the completed tree from input
 */
treeNode *stringParser (char *string){
    int i;
    char holding[5] = "";
    char temp[2];
    treeNode *head = NULL;
    treeNode *shuttle = NULL;
    //going through each value of the string and depending on the vA
    for (i = 0; i< strlen(string); i++){
        switch (string[i]) {
            /*If it is a arthimitic varible moves said varible into the value pointed to by shuttle
             * then checks to see if the leftBranch exists
             * if it does creates a new node with whats in holding and clears holding
             */
            case '+':
            case '-':
            case '*':
            case '/':
                temp[0] = string[i];
                temp[1] = '\0';
                strcpy(shuttle->value, temp);

                    if (!(shuttle->leftBranch)) {
                        shuttle->leftBranch = newTreeNode(holding);
                        shuttle->leftBranch->parent = shuttle;
                        strcpy(holding,"");
                    }
                break;
            /* If its an open bracket creates a new node
             * Will create the node in which ever node is empty with it prefering leftBranch and move shuttle down
             */
            case '(':
                if (!shuttle) {
                 //   printf("Changing head:");
                    shuttle = newTreeNode("^");
                    head = shuttle;
                }else {
                    if (!(shuttle->leftBranch)) {

                        shuttle->leftBranch = newTreeNode("^");
                        shuttle->leftBranch->parent = shuttle;
                        shuttle = shuttle->leftBranch;
                    } else if (!shuttle->rightBranch) {
                        shuttle->rightBranch = newTreeNode("");
                        shuttle->rightBranch->parent = shuttle;
                        shuttle = shuttle->rightBranch;

                    }
                }
                break;
            /* Checks if right is empty if it is creates a new node
             * moves shuttle up if a valid parent exits
             */
            case ')':
                if (!shuttle->rightBranch){

                    shuttle->rightBranch = newTreeNode(holding);
                    shuttle->rightBranch->parent = shuttle;
                    strcpy(holding,"");

                }
                if (!shuttle->parent){
                    //printf("Top reached\n");

                }else{
                    shuttle = shuttle->parent;
                }
                break;
            default:
                temp[0] = string[i];
                temp[1]= '\0';
                strcat(holding,temp);
        }

    //printInOrder(head);
    //printf("\n");
    }
    return head;
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
        if ((node->leftBranch)&&(node->rightBranch)) {
            printf("(");
        }
        printInOrder (node->leftBranch);
        printf("%s",node->value);
        printInOrder (node->rightBranch);
        if ((node->leftBranch)&&(node->rightBranch)) {
            printf(")");
        }
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
    if (current){
        if (!(current->leftBranch && current->rightBranch)){
            if(strcmp(current->value,"x0")>0){//checking to see if value is a variable
                return getVar(current->value,list);
            }else if (strcmp(current->value,"")!=0){
                return atof(current->value);
            }
        }else{
            if (strcmp(current->value,"+") ==0 ){
                var1 = calculate(current->leftBranch,list);
                var2 = calculate(current->rightBranch,list);
                hold = var1+var2;
                return hold;
            }else if(strcmp(current->value,"-")==0){
                var1 = calculate(current->leftBranch,list);
                var2 = calculate(current->rightBranch,list);
                hold = var1-var2;
                return hold;
            }else if(strcmp(current->value,"*")==0){
                var2 = calculate(current->rightBranch,list);
                var1 = calculate(current->leftBranch,list);
                hold = var1*var2;
                return hold;
            }else if(strcmp(current->value,"/")==0){
                //divide by zero handling
                if (calculate(current->rightBranch,list) != 0){
                    var1 = calculate(current->leftBranch,list);
                    var2 = calculate(current->rightBranch,list);
                    hold = var1/var2;
                    return hold;       
                }else{
                    printf("\nDivide by zero occured; Ingnore next line\n");
                    return 1000000000.0;
                }
            }else{
                printf("Derp");
            }
        }
    }else{
        return 0.0;
    }
    return 0.0;
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


        if(strcmp(tree->value,"x0")>0){
            //printf("var: %s\n",tree->value);
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

