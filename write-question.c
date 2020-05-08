// C program to Open a File, 
// Write in it, And Close the File 
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "coff.h"

int main()
{
    FILE * outfile;
    outfile = fopen("question.txt", "w");
    if (outfile == NULL) {
        fprintf(stderr, "\nError opend file\n");
        exit(1);
    }
    char str[80];
    struct question q;
    struct test_case test;
    struct constraints cons;
    struct example examples;
    int i;
    printf("Enter the name\n");
    fflush(stdin);
    fgets(q.name,coff_test_case_input_size,stdin);
    printf("Enter the question\n");
    fflush(stdin);
    fgets(q.question,coff_test_case_input_size,stdin);
    printf("Enter the no of constraint\n");
    fflush(stdin);
    scanf("%d", & q.no_of_constraints);
    printf("Enter the no of examples\n");
    fflush(stdin);
    scanf("%d", & q.no_of_example);
    printf("Enter the no test cases\n");
    fflush(stdin);
    scanf("%d", & q.no_of_test_cases);
    fflush(stdin);
    fwrite( & q, sizeof(struct question), 1, outfile);
    if (fwrite != 0){
        printf("contents to file written successfully !\n");
    }
    else{
        printf("error writing file !\n");
    }
    for (i = 0; i < q.no_of_constraints; i++)
     {
        fflush(stdout);
        printf("constraint no  %d\n", i);
        fflush(stdout);
        printf("  Enter the Time Limit\n");
        fflush(stdin);


        fgets(cons.Limit,coff_test_case_input_size,stdin);
        fflush(stdin);
        printf("  Enter the Memory Limit\n");
        fflush(stdin);
        fgets(cons.Memory,coff_test_case_input_size,stdin);
        fflush(stdin);
        printf("  Enter the CPU Size\n");
        fflush(stdin);
        fgets(cons.CPU,coff_test_case_input_size,stdin);
        fwrite( & cons, sizeof(struct constraints), 1, outfile);
        if (fwrite != 0)
            printf("contents to file written successfully !\n");
        else
            printf("error writing file !\n");

    }
     fflush(stdin);
    for (i = 0; i < q.no_of_example; i++) {
        printf("Examples no  %d\n", i +1);
        fflush(stdin);
        fgets(examples.example,coff_test_case_input_size,stdin);
        fwrite( & examples, sizeof(struct example), 1, outfile);
        if (fwrite != 0)
            printf("contents to file written successfully !\n");
        else
            printf("error writing file !\n");
    }

    for (i = 0; i < q.no_of_test_cases; i++) {
        printf("Test case no  %d\n", i);
        printf("  Input\n");
        fflush(stdin);
        fgets(test.input,coff_test_case_input_size,stdin);
        printf("  Output\n");
        fflush(stdin);
        fgets(test.output,coff_test_case_input_size,stdin);
        fwrite( & test, sizeof(struct test_case), 1, outfile);
        if (fwrite != 0)
            printf("contents to file written successfully !\n");
        else
            printf("error writing file !\n");
    }

    fclose(outfile);
    return 0;
}