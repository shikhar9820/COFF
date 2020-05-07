// C program to Open a File, 
// Write in it, And Close the File 

# include <stdio.h> 
#include<stdlib.h>
# include <string.h>
           
    struct test_case{
       char input [1000];
       char output[1000];
    };
    struct constraints{
       char constraint[1000];
    };
    struct example{
      char example[1000];
    };
    struct question
    {
         char question[1000];
         int  no_of_constraints;
         int  no_of_example;
         int  no_of_test_cases;
         struct test_case *test;
         struct constraints *constraint;
         struct example *examples;
    };

    int main(){
        struct question q;
        int i;
        printf("Enter the question\n");
        scanf("%s",q.question);
        printf("Enter the no of constraint\n");
        scanf("%d",&q.no_of_constraints);
        q.constraint = (struct constraints *)malloc(q.no_of_constraints * sizeof(struct constraints));
        for(i=0;i<q.no_of_constraints;i++){
            printf("constraint no  %d\n",i);
            scanf("%s",q.constraint[i].constraint);
        }
        printf("Enter the no of examples\n");
        scanf("%d",&q.no_of_example);
        q.examples = (struct example *)malloc(q.no_of_example *  sizeof(struct example));
        for(i=0;i<q.no_of_example;i++){
            printf("Examples no  %d\n",i);
            scanf("%s",q.examples[i].example);
        }
        printf("Enter the no test cases\n");
        scanf("%d",&q.no_of_test_cases);
        q.test = (struct test_case *)malloc(q.no_of_test_cases * sizeof(struct test_case));
        for(i=0;i<q.no_of_test_cases;i++){
            printf("Test case no  %d\n",i);
                    printf("Input\n");
                    scanf("%s",q.test[i].input);
                    printf("Output\n");
                    scanf("%s",q.test[i].output);
        }
} 



/*	// Declare the file pointer 
	FILE *filePointer ; 
	
	// Get the data to be written in file 
	char dataToBeWritten[50] 
		= "GeeksforGeeks-A Computer Science Portal for Geeks"; 

	// Open the existing file GfgTest.c using fopen() 
	// in write mode using "w" attribute 
	filePointer = fopen("GfgTest.c", "w") ; 
	
	// Check if this filePointer is null 
	// which maybe if the file does not exist 
	if ( filePointer == NULL ) 
	{ 
		printf( "GfgTest.c file failed to open." ) ; 
	} 
	else
	{ 
		
		printf("The file is now opened.\n") ; 
		
		// Write the dataToBeWritten into the file 
		if ( strlen ( dataToBeWritten ) > 0 ) 
		{ 
			
			// writing in the file using fputs() 
			fputs(dataToBeWritten, filePointer) ; 
			fputs("\n", filePointer) ; 
		} 
		
		// Closing the file using fclose() 
		fclose(filePointer) ; 
		
		printf("Data successfully written in file GfgTest.c\n"); 
		printf("The file is now closed.") ; 
	} 
	return 0;		 
*/
