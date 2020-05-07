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
    	 char name[1000];
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
        printf("Enter the name\n");
        scanf("%s",q.name);
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
        FILE *outfile; 
      
    // open file for writing 
    outfile = fopen ("question.txt", "w"); 
    if (outfile == NULL) 
    { 
        fprintf(stderr, "\nError opend file\n"); 
        exit (1); 
    } 
  
    fwrite (&q, sizeof(struct question), 1, outfile); 
      
    if(fwrite != 0)  
        printf("contents to file written successfully !\n"); 
    else 
        printf("error writing file !\n"); 
  
    fclose (outfile); 
        return 0;
} 
