#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

void add();
void list();
void delete1();
void search();

struct CustomerDetails
{
  char roomnumber[10];
  char name[20];
  char address[25];
  char phonenumber[15];
  char period[10];
} s;

int main()
{
  int i;
  char choice;
  system("clear");
  printf("\t\t*********************************************\n");
  printf("\t\t*                                           *\n");
  printf("\t\t*                                           *\n");
  printf("\t\t*       ----------------------------        *\n");
  printf("\t\t*               DIBEK HOTEL                 *\n");
  printf("\t\t*       ----------------------------        *\n");
  printf("\t\t*                                           *\n");
  printf("\t\t*                                           *\n");
  printf("\t\t*                                           *\n");
  printf("\t\t*********************************************\n\n\n");

  printf("\nOption 1: Book a room");
  printf("\nOption 2: View Customer Record");
  printf("\nOption 3: Delete Customer Record");
  printf("\nOption 4: Search Customer Record");
  printf("\nOption 5: Exit");

  printf(" \n\n\t\t\t Press any key to continue:");
  getchar();
  system("clear");

  while (1)
  {
    system("clear");
    for(i = 0; i < 80; i++)
      printf("-");
    printf("\n");
    printf("   ******************************  |MAIN MENU|  ***************************** \n");
    for(i = 0; i < 80; i++)
      printf("-");
    printf("\n");
    printf("\t\t *Please enter your choice for menu*:");
    printf("\n\n");
    printf(" \n Enter 1: Book a room");
    printf(" \n Enter 2: View Customer Record");
    printf(" \n Enter 3: Delete Customer Record");
    printf(" \n Enter 4: Search Customer Record");
    printf(" \n Enter 5: Exit");
    printf("\n");

    choice = getchar();
    choice = toupper(choice);
    getchar(); // consume the newline character

    switch(choice)
    {
      case '1':
        add();
        break;
      case '2':
        list();
        break;
      case '3':
        delete1();
        break;
      case '4':
        search();
        break;
      case '5':
        system("clear");
        printf("\n\n\t *****THANK YOU*****");
        printf("\n\t FOR TRUSTING OUR SERVICE");
        exit(0);
        break;
      default:
        system("clear");
        printf("Incorrect Input");
        printf("\n Press any key to continue");
        getchar();
        return 0;
    }
  }
}

void add()
{
  FILE *f;
  char test;
  f = fopen("details.txt", "a+");
  if(f == NULL)
  {
    f = fopen("details.txt", "w+");
    system("clear");
    printf("\n Process completed press any key to continue!! ");
    getchar();
  }
  
  while(1)
  {
    system("clear");
    printf("\n Enter Customer Details:");
    printf("\n**************************");
    printf("\n Enter Room number:\n");
    scanf("%s", s.roomnumber);
    getchar(); // consume the newline character
    
    printf("Enter Name:\n");
    scanf("%s", s.name);
    getchar();
    
    printf("Enter Address:\n");
    scanf("%s", s.address);
    getchar();
    
    printf("Enter Phone Number:\n");
    scanf("%s", s.phonenumber);
    getchar();
    
    printf("Enter Period(\'x\'days):\n");
    scanf("%s", s.period);
    getchar();

    fwrite(&s, sizeof(s), 1, f);
    fflush(stdin);
    printf("\n\n1 Room is successfully booked!!");
    printf("\n Press esc key to exit, any other key to add another customer detail:");
    test = getchar();
    if(test == 27)
      break;
  }

  fclose(f);
}

void list()
{
  FILE *f;
  int i;
  
  if((f = fopen("details.txt", "r")) == NULL)
    exit(0);
  
  system("clear");
  printf("ROOM    ");
  printf("NAME\t ");
  printf("\tADDRESS ");
  printf("\tPHONENUMBER ");
  printf("\t\tPERIOD ");

  while(fread(&s, sizeof(s), 1, f) == 1)
  {
    printf("\n%s \t%s \t\t%s \t%s \t\t%s", s.roomnumber, s.name, s.address, s.phonenumber, s.period);
  }
  
  fclose(f);
  getchar();
}

void delete1()
{
  FILE *f, *t;
  int i = 1;
  char roomnumber[20];
  
  if((t = fopen("temp.txt", "w")) == NULL)
    exit(0);
  
  if((f = fopen("details.txt", "r")) == NULL)
    exit(0);
  
  system("clear");
  printf("Enter the Room Number of the hotel to be deleted from the database: \n");
  scanf("%s", roomnumber);
  getchar();
  
  while(fread(&s, sizeof(s), 1, f) == 1)
  {
    if(strcmp(s.roomnumber, roomnumber) == 0)
    {
      i = 0;
      continue;
    }
    else
      fwrite(&s, sizeof(s), 1, t);
  }
  
  if(i == 1)
  {
    printf("\n\n Records of Customer in this  Room number is not found!!");
    getchar();
    fclose(f);
    fclose(t);
    main();
  }
  
  fclose(f);
  fclose(t);
  remove("details.txt");
  rename("temp.txt", "details.txt");
  
  printf("\n\nThe Customer is successfully removed....");
  fclose(f);
  fclose(t);
  getchar();
}

void search()
{
  system("clear");
  FILE *f;
  char roomnumber[20];
  int flag = 1;
  
  f = fopen("details.txt", "r+");
  if(f == NULL)
    exit(0);
  
  printf("Enter Room number of the customer to search its details: \n");
  scanf("%s", roomnumber);
  getchar();
  
  while(fread(&s, sizeof(s), 1, f) == 1)
  {
    if(strcmp(s.roomnumber, roomnumber) == 0)
    {
      flag = 0;
      printf("\n\tRecord Found\n ");
      printf("\nRoom Number:\t%s", s.roomnumber);
      printf("\nName:\t%s", s.name);
      printf("\nAddress:\t%s", s.address);
      printf("\nPhone number:\t%s", s.phonenumber);
      printf("\nPeriod:\t%s", s.period);
      flag = 0;
      break;
    }
  }
  
  if(flag == 1)
  {
    printf("\n\tRequested Customer could not be found!");
  }
  
  getchar();
  fclose(f);
}
