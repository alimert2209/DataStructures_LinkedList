#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>

//191180055 - Ali Mert KOCAMAN

//You can find the main function at the end of the code

struct lecture // this is the struct i made for the lectures
{
    char name[100]; //name of the lecture
    int lecture_code; // code of the lecture
};

struct ali //ali represents the node (linked list)
{
    struct lecture data;
    struct ali *next;
};

struct ali *head = NULL; // creating an empty linked list

void addLecture(struct lecture lctr)
{
	//this if statement controls, if the line is valid format or not
    if (lctr.lecture_code == 0)
        return;

    struct ali *new_ali = (struct ali *)malloc(sizeof(struct ali)); //We free up memory for our linked lists nodes

	//adding new node to the beginning of the linked list
    new_ali->data = lctr;
    new_ali->next = head;
    head = new_ali;
}

struct lecture lectureSplit(char line[])
{
    struct lecture tempLct; //temporary lecture to return
    char tempCd[4]; //temporary lecture code like 101 (Bilgisayar Programlama)

    strncpy(tempCd, strrev(line), 4);// transfering last 4 character of the line to the tempCd
    tempLct.lecture_code = atoi(strrev(tempCd)); // we put the code in front of the lecture name and assigned the code of tempLct
    line[strlen(strrev(line)) - 5] = '\0'; // we did this to print the lectures in the true format to the Sorted.dat file
    strcpy(tempLct.name, line); // we assigned line to the tempLct.name
    return tempLct;
}

void sort()
{
    struct ali *tempN = head; //creating a temporary node to scan the linked list
    struct ali *insideTempN = NULL;//We used the bubble sort algorithm here. so we need a second temporary internal node
    struct lecture tempLct;

    while (tempN != NULL){ // until the all linked list is scanned
        insideTempN = tempN->next;
        while (insideTempN != NULL){
        	//classsic bubble sort algorithm
            if (tempN->data.lecture_code > insideTempN->data.lecture_code){
                tempLct = tempN->data;
                tempN->data = insideTempN->data;
                insideTempN->data = tempLct;
            }
            insideTempN = insideTempN->next;
        }
        tempN = tempN->next;
    }
}

void delete()
{
    struct ali *tempN = head; // creating a temporary node to scan linked list

    while (tempN != NULL && tempN->next != NULL){  //until the all linked list is scanned
    	//we sorted the data before we delete the duplicated elements
    	//so we have sorted data, that means we should check the lectures if they are repeated, like this:
    	//we compared the code of each lesson with the code of the lesson found in the next node
        if (tempN->data.lecture_code == tempN->next->data.lecture_code){
        	tempN->next = tempN->next->next;
		} else { // if the lecture is unique, then go ahead to the next node
        	tempN = tempN->next;
		}
    }
}

void writeToFile(FILE *file)
{
    file = fopen("Sorted.dat", "w"); //opening the file as Data.dat in 'write' mode

    struct ali *tempN = head; // creating a temporary node

    while (tempN != NULL) // until the all linked list is scanned
    {
        fprintf(file, "%d\t%s\n", tempN->data.lecture_code, tempN->data.name); //writing lectures and codes to the Sorted.dat file
        printf("%d\t%s\n",tempN->data.lecture_code, tempN->data.name); //writing lectures and codes to the console
        tempN = tempN->next;
    }
    fclose(file); // close the file
}



void main()
{
    FILE *file; // Creating a file pointer
    
    char lecture[100]; // creating a string for lectures

    file = fopen("Data.dat", "r"); //opening the file as Data.dat in 'read' mode
    
    while (fgets(lecture, sizeof(lecture), file)){
    	//this while loop reads all the lectures in the Data.dat file 
    	//and transfer them to the linked list
    	addLecture(lectureSplit(lecture)); 
	}
    
    fclose(file); // close the file
    
    sort(); // sort the lectures according to ascending order
    delete(); // deleting the same elements until one is left
    writeToFile(file); // writing the lectures to the sorted file
    
    printf("\nCheck the Sorted.dat file!");
}
