/*
*/

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#define MAXID 10
#define MAXNAME 25
#define MAXPRICE 10

//entity of admin
struct admin {
    char username[20];
    char password[20];
};
struct admin admin_user1 = {"admin","welcome1"};

//entity of service
struct service
{
    char id[MAXID];
    char name[MAXNAME];
    char price[MAXPRICE];
} s1;

//smsarang
void check_system_files();
void create_authentication_csv(int authenticated,char *filename,char userinputusername[],char userinputpassword[]);
void create_services_csv(char *filename, char userinputusername[]);
void read_services_csv(char *filename, char searchQ[]);
void update_service_price_csv(char *filename, char recordNo[], char newPrice[]);
void generate_backup_file_of_all();

/*
To check if required files are created or not to store information.
@param char pointer variable filename
author : smit
*/
void check_system_files(){
    FILE *fp;
    char *filename="datafile_authenticationlogs.csv";
    printf("\n\n!!!Setting up the required files...\n");
    printf("\nChecking %s", filename);

    fp = fopen(filename, "r");
    if (!fp){
        printf("\nFile not found, Creating new\n");
        fp = fopen(filename, "w");
        fprintf(fp, "username,password,authentication");
        fclose(fp);
        printf("\nfile %s checked...\n",filename);
    }else{
        printf("\nfile %s checked...\n",filename);    
    }
    
    filename="datafile_services.csv";
    printf("\nChecking %s", filename);

    fp = fopen(filename, "r");
    if (!fp){
        printf("\nFile not found, Creating new\n");
        fp = fopen(filename, "w");
        fprintf(fp, "id,name,price,addedby");
        fclose(fp);
        printf("\nfile %s checked...\n",filename);
    }else{
        printf("\nfile %s checked...\n",filename);    
    }
}

/*
To store authentication logs into a file.
@param int authenticated
@param char filename
@param char userinputusername
@param char userinputpassword
author : smit
*/
void create_authentication_csv(int authenticated,char *filename,char userinputusername[],char userinputpassword[]){
    FILE *fp;
    filename = strcat(filename, ".csv");

    fp = fopen(filename, "r");
    if (!fp){
        printf("\nFile %s not found. \nPlease setup the required files\n",filename);
        printf("execute program using 'syscheck' as cli arg\n\n");
        exit(1);
    }else{
        fclose(fp);
        fp = fopen(filename, "a");
    }

    if(authenticated==1){
        fprintf(fp, "\n%s,%s,%s", userinputusername, userinputpassword, "Success");
    }else{
        fprintf(fp, "\n%s,%s,%s", userinputusername, userinputpassword, "Failed");
    }
    fclose(fp);
}

/*
To create services
@param char pointer filename
@param char userinputusername
author : smit
*/
void create_services_csv(char *filename, char userinputusername[])
{
    FILE *fp;
    int i, count;
    filename = strcat(filename, ".csv");

    fp = fopen(filename, "r");
    if (!fp)
    {
        printf("\nFile %s not found. \nPlease setup the required files\n",filename);
        printf("execute program using 'syscheck' as cli arg\n\n");
        exit(1);
    }
    else
    {
        fp = fopen(filename, "a");
    }

    printf("\nHow many rows?");
    scanf("%d", &count);

    for (i = 1; i <= count; i++)
    {
        printf("\nEnter id: ");
        scanf("%s", s1.id);
        printf("\nEnter name: ");
        scanf("%s", s1.name);
        printf("\nEnter price: ");
        scanf("%s", s1.price);
        fprintf(fp, "\n%s,%s,%s,%s", s1.id, s1.name, s1.price,userinputusername);
    }
    fclose(fp);
}


/*
To read services
@param char pointer filename
@param char searchQ
author : smit
*/
void read_services_csv(char *filename, char searchQ[])
{
    char temp[100];
    char lines[100];
    FILE *fp;
    int j;
    filename = strcat(filename, ".csv");
    fp = fopen(filename, "r");
    if (!fp)
    {
        printf("\nFile %s not found. \nPlease setup the required files\n",filename);
        printf("execute program using 'syscheck' as cli arg\n\n");
        exit(1);
    }else{
            printf("\n\n\t++ Services Data ++\n\n");
    }

    while (fgets(lines, sizeof(lines), fp))
    {
        char *token;
        token = strtok(lines, ",");
        while (token != NULL)
        {
            printf("\t%s", token);
            token = strtok(NULL, ",");
            j++;
        }
        printf("\n");
    }
    // printf("\n\tRecords %s------\n", lines);
    fclose(fp);
    printf("\n");
}

/*
To take backup of all the data files.
author : smit
*/
void generate_backup_file_of_all(){
    time_t t;
    time(&t);
    printf("\n!!!generating backup as per %s\n", ctime(&t));
}


// void update_service_price_csv(char *filename, char recordNo[], char newPrice[])
// {
//     char temp[100];
//     char rowData[100];
//     printf("\n\n\t++ Row %s Data ++\n\n", recordNo);
//     FILE *fp;
//     int cntr, k;
//     filename = strcat(filename, ".csv");
//     fp = fopen(filename, "r+");
//     char lines[100];
//     while (fgets(lines, sizeof(lines), fp))
//     {
//         char *token;
//         token = strtok(lines, ",");
//         int i = 0;
//         while (token != NULL)
//         {
//             fscanf(fp, "%[^\n]", rowData);
//             if (strcmp(lines, "2") == 0)
//             {
//                 printf("\t%s", token);
//                 cntr++;
//             }
//             token = strtok(NULL, ",");
//             i++;
//         }
//     }
//     printf("\n");
//     printf("Data from the file:\n%s", rowData);
//     printf("\n-----%d\n", cntr);
//     fclose(fp);

//     int j = 0;
//     char *p = strtok(rowData, ",");
//     char *newArray[3];

//     while (p != NULL)
//     {
//         newArray[j++] = p;
//         p = strtok(NULL, ",");
//     }

//     // printf("old val");
//     // for (j = 0; j < 3; ++j)
//     // {
//     //     printf("\n%s", newArray[j]);
//     // }

//     for (int i = 0; i < 3; i++)
//     {
//         if (i == 2)
//         {
//             newArray[i] = newPrice;
//         }
//     }

//     printf("new val");
//     for (j = 0; j < 3; ++j)
//     {
//         printf("\n%s", newArray[j]);
//     }

//     char ch, source_file[50] = "datafile_services.csv", target_file[50] = "datafile_services copy.csv";
//     FILE *source, *target;

//     source = fopen(source_file, "r");
//     if (source == NULL)
//     {
//         printf("Source File not found...\n");
//     }

//     target = fopen(target_file, "w");
//     if (target == NULL)
//     {
//         fclose(source);
//         printf("Target File not found...\n");
//     }
//     fp = fopen(filename, "r");
//     char c;
//     int counter=1;
//     for (c = getc(fp); c != EOF; c = getc(fp))
//     {
//         if (c == '\n')
//         {
//             counter = counter + 1;
//         }
//     }

//     printf("File will be copied .\n");
//     printf("%d record will be copied.\n", counter);

// }

int main(int cli_params, char *args[])
{
    char filename_services[50] = "datafile_services";
    char filename_authenticaction[50]="logfile_authentication";
    int authenticated=1;
    // char userinputusername[20] = "dummy";
    // char userinputpassword[20];
    if(cli_params>1){
        if(!strcmp(args[1],"syscheck")){
            check_system_files();
        }
        exit(1);
    }
    
    // printf("\nEnter username: ");
    // gets(userinputusername);
    // printf("\nEnter password: ");
    // gets(userinputpassword);

    // if(strcmp(admin_user1.username,userinputusername)==0 && strcmp(admin_user1.password,userinputpassword)==0){
    //     authenticated=1;
    //     create_authentication_csv(authenticated, filename_authenticaction,userinputusername,userinputpassword);
    // }else{
    //     create_authentication_csv(authenticated, filename_authenticaction,userinputusername,userinputpassword);
    // }
    

    if(authenticated){
        int choice;
        printf("Choose:");
        printf("\n1.Create service");
        printf("\n2.View all services");
        printf("\n3.Generate backup file");
        printf("\nans:");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:
            create_services_csv(filename_services, "dummyuser");
            break;
        case 2:
            read_services_csv(filename_services, "usernameofadmin");
            break;
        case 3:
            generate_backup_file_of_all();
        default:
            break;
        }
    // update_service_price_csv(filename_services, "2", "999");
    // generate_backup_file_of_all();
    }else{
        printf("\nAuth failed");
    }
    return 0;
}