#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>

COORD coord={0,0};

void gotoxy(int x, int y)
int main()
{
    struct emp e;
    FILE *fp , *ft;
    char another, choice;

   
    char empname[40];
    long int recsize;

    fp=fopen("EMP.DAT" ,"rb+");

    if(fp==NULL)
    {

      fp=fopen("EMP.DAT" , "wb+");
      if(fp==NULL)
      {
        printf("Cannot open file..\n");
        exit(1);
      }
    }

    recsize=sizeof(e);

    while(1)
    {
        system("cls");
        gotoxy(30,10);
        printf("\n1. Add Record ");
        gotoxy(30,12);
        printf("\n2. List Records ");
        gotoxy(30,14);
        printf("\n3. Modify Records ");
        gotoxy(30,16);
        printf("\n4. Delete Records ");
        gotoxy(30,18);
        printf("\n5. Exit ");
        gotoxy(30,20);
        printf("\nYour Choice: ");
        //fflush(stdin);
        choice = getche();
        switch(choice)
        {
            case '1' :
            system("cls");
            fseek(fp, 0,SEEK_END);
            another = 'y' ;
            while(another == 'y')
            {
                printf("\nEnter name: ");
                scanf("%s" ,e.name);
                printf("\nEnter E_id: ");
                scanf("%d" ,&e.e_id);
                printf("\nEnter age: ");
                scanf("%d" ,&e.age);
                printf("\nEnter basic salary: ");
                scanf("%f" , &e.salary);

                fwrite(&e,recsize,1,fp);

                printf("Add another record(y/n)" );
                fflush(stdin);
                another = getche();
            }
            break;

            case '2' :
            system("cls");
            rewind(fp);
            while(fread(&e,recsize,1,fp)==1)
            {
                printf("\n%s %d %d %.2f", e.name ,e.e_id ,e.age ,e.salary);
            }
            
            getche();
            break;

            case '3' :
            system("cls");
            another = 'y' ;
            while(another == 'y')
            {
                printf("Enter the employee name to modify: ");
                scanf("%s" , empname);
                rewind(fp);
                while(fread(&e,recsize,1,fp)==1)
                {
                    if(strcmp(e.name,empname)==0)
                    {
                        printf("\nEnter new name ,E_id, age and salary: ");
                        scanf("%s%d%f" , e.name,&e.e_id, &e.age, &e.salary);
                        fseek(fp,-recsize,SEEK_CUR);
                        fwrite(&e,recsize,1,fp);
                        break;
                    }
                }
                printf("\nModify another record(y/n)");
                fflush(stdin);
                another = getche();
            }
            break;
            
            case  '4' :
             system("cls");
             another = 'y' ;
             while(another == 'y')
             {
                 printf("\nEnter name of employee to delete: ");
                 scanf("%s" , empname);
                 ft= fopen("Temp.dat" ,"wb");
                 rewind(fp);
                 while(fread(&e,recsize,1,fp)==1)
                 {
                     if(strcmp(e.name,empname)!=0)
                     {
                         fwrite(&e,recsize,1,ft);
                     }
                 }
                 fclose(fp);
                 fclose(ft);
                 remove("EMP.DAT");
                 rename("Temp.dat" , "EMP.DAT");
                 fp = fopen("EMP.DAT" , "rb+");
                 printf("Delete another record(y/n)");
                 fflush(stdin);
                 another = getche();
             }
             break;
             case '5' :
             fclose(fp);
             exit(0);
            }
        }
        return 0;
}


