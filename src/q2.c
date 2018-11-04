/*  q2.c
    Main Function file for CIS 2520 Assignment 3 question 2.
    By: James Arthur Anderson
    Student ID #: 1013076
    Date: Nov 5, 2018
*/
#include"A3.h"

int main(){
    FILE *fp = NULL;
    int values [20][10];
    int i,j;
    int curIndex = 19;
    int parent;
    int show =0;
    //Reading the values from f.dat int values
    fp = fopen("f.dat","r");
    for (i = 0; i<20; i++){
        fscanf(fp,"%d %d %d %d %d %d %d %d %d %d\n",&(values[i][0]),&(values[i][1]),&(values[i][2]),&(values[i][3]),&(values[i][4]),&(values[i][5]),&(values[i][6]),&(values[i][7]),&(values[i][8]),&(values[i][9]));
    }
    fclose(fp);

    printf("Before building heap\n\n");
    for (i=0;i<20;i++){
        for(j =0;j<10;j++){
            printf("%d,",values[i][j]);
        }
        printf("\n");
    }
    //interating through the parent nodes and preforming downheap
    while (curIndex !=0){
        parent = (curIndex-1)/2;
        downHeap(values,parent);
        
        curIndex -= 1;
    }
    printf("\n\nAfter Building heap\n\n");
    for (i=0;i<20;i++){
        for(j =0;j<10;j++){
            if (j<3){
                show += values[i][j];
            }
            printf("%d,",values[i][j]);
        }
        printf("\n");
        show =0;
    }
    return 0;
}
/*Recursive algorythm that vhecks to see which of the parents node children is larger
 *then checks to see if it is larger than the parent, if it is it switches the rows 
 *Retuns if it is not and also returns if the child node is invalid 
 */
void downHeap(int heap[20][10], int parentIndex){
    int left = (2*parentIndex) +1;
    int right = (2*parentIndex) +2;
      
    if (left<20&& (compare(heap,left,right)>0)){
        if (compare(heap,parentIndex,left)<0){
            switchNodes(heap,parentIndex,left);
            downHeap(heap,left);
        }else{
            return;
        }
    }else if (left<20&& right<20&& (compare(heap,left, right)<0)){
        if (compare(heap,parentIndex,right)<0){
            switchNodes(heap,parentIndex,right);
            downHeap(heap,right);
        }else{
            return;
        }
   }else{
        return;       
    }
}
/*Compares the keys at the given indexs of each row 
 *returns negative if key at index1 < key at index2
 *returns zero if key at index1 == key at index2
 *returns positive if key at index1 > key at index2
 */
int compare(int heap[20][10], int index1, int index2){
    int val1 =0;
    int val2 =0;
    int i;
    for (i =0; i<3;i++){
        val1 += heap[index1][i];
    }

    for (i =0; i<3;i++){
        val2 += heap[index2][i];
    }
    
    if (val1 < val2){
        return -1;
    }else if(val1 == val2){
        return 0;
    }else{
        return 1;
    }
}

/*Switches the rows given by index1 and index2*/
void switchNodes(int heap[20][10],int index1, int index2){
    int temp[10];
    int i = 0;
    for(i =0; i<10; i++){
        temp[i] = heap[index2][i];
    }
    for(i =0; i<10; i++){
        heap[index2][i] = heap[index1][i];
    }
    for(i =0; i<10; i++){
        heap[index1][i] = temp[i];
    }
}
