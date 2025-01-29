// Including Required Header Files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

// Checking if it is pre-defined as this program is planned to be used as a sub file for a big system
#ifndef NLN
#define NLN printf("\n")
#endif

#ifndef CONTINUE_PROGRAM
int CONTINUE_PROGRAM = 0;
#endif

// The Compliter is informed that the memory address for Main_File has an Exclusive pointer, thus restrict is used. This allows optimizations.
FILE* pMain_File;

// Initializing the functions
void FILE_CHECKER();
void Reader(FILE* restrict pToReadFrom, int Number_Of_Students);
void Writer(FILE* restrict pToWriteTo, char* pName);

// Precalling FILE_CHECKER() as it is a necessary check
void __attribute__((constructor)) FILE_CHECKER();

// Main Starts Here, when we make it main(FILE* restrict pMain_File) then __attribute__ will not be used
// and FILE_CHECKER will be moved inside main nor will we define pMain_File in this c file
int main()
{

if(CONTINUE_PROGRAM && !ferror(pMain_File))
{

printf("Enter Number Of Students: "); int Number_Of_Students = 1; scanf("%d",&Number_Of_Students);

// Reading and Writing From The File On-to a new file
Reader(pMain_File, Number_Of_Students);

fclose(pMain_File);
}

else
{
perror("The Following Error Has Occured");
}

return 0;
}

// The Actual Functions Start From Here

// The reason Reader() was made as these variables created here are just needed once.
// Thus the memory that they take up will be freed when reader completes its work
void Reader(FILE* restrict pToReadFrom, int Number_Of_Students)
{
    char pcurrent_name[100];

    FILE* pToWriteTo = fopen("Attendence.txt","a");

    NLN; printf("Just Write P/A for Present/Absent respectively:"); NLN;

    while(((int) fgets(pcurrent_name, 100, pToReadFrom) != EOF) && !ferror(pToReadFrom)) // See if needed to change with a loop and fgetc
    {
        NLN; printf("%s",pcurrent_name); NLN; // For Debugging
        Writer(pToWriteTo, pcurrent_name);
    }
    
    fclose(pToWriteTo);
    return;
}

void Writer(FILE* restrict pToWriteTo, char* pName)
{
    char ANS[] = "N";
    while(strupr(ANS) != "P" || strupr(ANS) != "A")
    {
    printf("%s : ",*pName); scanf("%s",ANS);
    (strupr(ANS) != "P" || strupr(ANS) != "A") ? (fputs(strcat(pName, strcat(" | ", strupr(ANS))), pToWriteTo)) : (printf("\nThe Input Is Not Valid, Try Again\n"));
    }
    return;
}

void FILE_CHECKER()
{
    char File_Name[100];

    printf("### Please place the text file of names in the same folder as this program before starting ###");NLN;
    printf("Enter Name Of File and Press Enter To Continue\n-> "); scanf("%s",&File_Name);

    // File Opened And Checked
    pMain_File = fopen(strcat(File_Name,".txt"),"r");
    if(pMain_File != NULL && !ferror(pMain_File))
    {    
        CONTINUE_PROGRAM = 1;
    }
    
    return;
}