#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#define MAXNAME 25
#define MAXCODE 25

char service_file_name[40] = "datafile_service.txt";
FILE *fp, *ft;

//smitStarts
struct admin
{
     char username[20];
     char password[20];
};
struct admin a1 = {"admin", "welcome1"};
struct admin a2 = {"customer", "welcome1"};

struct service
{
     char code[MAXCODE];
     char name[MAXNAME];
     float price;
} s1;
//smitEnds

char servicename[MAXNAME];
int found = 0;
long int recsize = sizeof(s1);

//smitStarts
void checkSystemFile();
// void createAuthentication(int authenticated,char *filename,char userinputusername[],char userinputpassword[]);
void createServices(char *filename, char userinputusername[]);
void readServices(char *filename);
void updateServices(char *filename);
void deleteServices(char *filename);
void viewFeedback();
void flush();

void flush()
{
     int c;
     while ((c = getchar()) != '\n' && c != EOF)
          ;
}

void createServices(char *filename, char userinputusername[])
{
     int isExists = 0;
     fp = fopen(filename, "r+");
     fflush(stdin);
     printf("\t\tEnter the service name you want to create: ");
     scanf("%s", servicename);
     rewind(fp);
     while (fread(&s1, recsize, 1, fp) > 0 && found == 0)
     {
          if (strcmp(s1.name, servicename) == 0)
          {
               isExists = 1;
          }
     }
     if (!isExists)
     {
          fseek(fp, 0, SEEK_END);
          flush();
          printf("\n\t\tEnter service code: ");
          scanf("%s", s1.code);
          fflush(stdin);
          printf("\n\t\tEnter name: ");
          scanf("%s", s1.name);
          fflush(stdin);
          printf("\n\t\tEnter price: ");
          scanf("%f", &s1.price);
          fflush(stdin);
          fwrite(&s1, recsize, 1, fp);
     }
     else
     {
          printf("\t\tRecord already exists with name %s\n", servicename);
     }
     fclose(fp);
}

void readServices(char *filename)
{
     printf("\t\t++++ Services ++++\n");
     printf("\n\t\tCODE\t\tNAME\t\tPRICE\n\n");
     fp = fopen(filename, "r+");
     rewind(fp);
     while (fread(&s1, recsize, 1, fp) == 1)
     {
          printf("\t\t%s\t\t%s\t\t%.2f\n", s1.code, s1.name, s1.price);
     }
     fclose(fp);
}

void updateServices(char *filename)
{
     int isExists = 0;
     fp = fopen("datafile_service.txt", "r+");
     fflush(stdin);
     printf("\t\tEnter the service name to modify: ");
     scanf("%s", servicename);
     rewind(fp);
     while (fread(&s1, recsize, 1, fp) > 0 && isExists == 0)
     {
          if (strcmp(s1.name, servicename) == 0)
          {
               isExists = 1;
               printf("\n\t\tEnter new code: ");
               scanf("%s", s1.code);
               printf("\n\t\tEnter new name: ");
               scanf("%s", s1.name);
               fflush(stdin);
               printf("\n\t\tEnter new price: ");
               scanf("%f", &s1.price);
               fseek(fp, -recsize, SEEK_CUR);
               fwrite(&s1, recsize, 1, fp);
               break;
          }
     }
     if (!isExists)
     {
          printf("\t\tEditing failed \n\t\tRecord does not exists with name %s\n", servicename);
     }
     found = 0;
     fclose(fp);
}

void deleteServices(char *filename)
{
     int isExists = 0;
     fp = fopen(filename, "r+");
     fflush(stdin);
     printf("\t\tEnter the service name you want to delete: ");
     scanf("%s", servicename);
     rewind(fp);
     while (fread(&s1, recsize, 1, fp) > 0 && found == 0)
     {
          if (strcmp(s1.name, servicename) == 0)
          {
               isExists = 1;
          }
     }
     if (isExists)
     {
          flush();
          ft = fopen("Tdatafile_service.txt", "w");
          rewind(fp);
          while (fread(&s1, recsize, 1, fp) == 1)
          {
               if (strcmp(s1.name, servicename) != 0)
               {
                    fwrite(&s1, recsize, 1, ft);
               }
          }
          fclose(fp);
          fclose(ft);
          remove("datafile_service.txt");
          rename("Tdatafile_service.txt", "datafile_service.txt");
          printf("Record deleted successfully\n");
          fp = fopen("datafile_service.txt", "r+");
          fclose(fp);
     }
     else
     {
          printf("\t\tDelete failed \nRecord does not exists with name %s\n", servicename);
     }
}

void checkSystemFile()
{
     FILE *fp;
     char *filename = "datafile_service.txt";

     fp = fopen(filename, "r+");
     if (!fp)
     {
          printf("\n\t\tFile not found, Creating new\n");
          fp = fopen(filename, "w+");
          //    fprintf(fp, "username,password,authentication");
          fclose(fp);
     }
     fclose(fp);
}

void viewFeedback()
{
   
}

//smitEnds

int main(int cli_params, char *args[])
{
     //smitStarts
     char choice;
     char userinputusername[40], userinputpassword[40];
     int adminauthenticated, userauthenticated = 0;
     //smitEnds

     //smitStarts
     if (cli_params > 1)
     {
          if (!strcmp(args[1], "syscheck"))
          {
               checkSystemFile();
          }
          exit(1);
     }

     checkSystemFile();

     fp = fopen(service_file_name, "r+");
     if (fp == NULL)
     {
          fclose(fp);
          fp = fopen(service_file_name, "w+");
          if (fp == NULL)
          {
               printf("\t\tConnot create service file");
               exit(1);
               fclose(fp);
          }
          fclose(fp);
     }
     //smitEnds

     printf("\nEnter username: ");
     gets(userinputusername);
     printf("Enter password: ");
     gets(userinputpassword);

     if (strcmp(a1.username, userinputusername) == 0 && strcmp(a1.password, userinputpassword) == 0)
     {
          adminauthenticated = 1;
     }
     else if (strcmp(a2.username, userinputusername) == 0 && strcmp(a2.password, userinputpassword) == 0)
     {
          userauthenticated = 1;
     }
     else
     {
          printf("Authentication failed\n");
     }

     if (adminauthenticated == 1 && strcmp(userinputusername, "admin") == 0)
     {
     //smitStarts
     while (1)
     {
          printf("\nHi,%s\n", userinputusername);
          printf("\nWhat do you want to do ?\n");
          printf("1. Add service\n");
          printf("2. List services\n");
          printf("3. Modify service\n");
          printf("4. Delete service\n");
          printf("5. View Feedback\n");
          printf("6. Exit\n");
          printf("Choice: ");
          fflush(stdin);
          scanf("\n%c", &choice);
          switch (choice)
          {
          case '1':
               createServices(service_file_name, "dummyuser");
               break;
          case '2':
               readServices(service_file_name);
               break;
          case '3':
               updateServices(service_file_name);
               break;
          case '4':
               deleteServices(service_file_name);
               break;
          case '5':
               viewFeedback();
               break;
          case '6':
               fclose(fp);
               exit(0);
          }
     }
     // smitEnds
     }
     if (userauthenticated && strcmp(userinputusername, "customer") == 0)
     {
          printf("\nWelcome %s\n", userinputusername);
     }
     return 0;
}
