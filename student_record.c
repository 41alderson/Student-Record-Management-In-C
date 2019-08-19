#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <sys/utsname.h>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define WHITE   "\x1b[37m"
#define RESET   "\x1b[0m"

int main();
void found(char usn[15]);

struct student
{
	char name[100],section,usn[10];
	float fees_paid,fees_unpaid;
	char phone[10];
	float marks,percent;	
};

struct time
{
    char time_add[10];
    char time_mod[10];
    char time_login[10];
};

void chk_compat()
{
	char os_type[] = "Linux";
	struct utsname detect;
	uname(&detect);

	printf(YELLOW "\nPlease Wait Checking For OS Compatibility....\n" RESET);
	sleep(1);
	
	if(strcmp(detect.sysname,os_type)==0)
	{
		
		printf(WHITE "\nYou Are Using GNU/Linux\n");
		printf("\nYour Operating System Is Compatible With This Script...\n" RESET);
		sleep(2);
		system("clear");
	}
	
	else
	{
		printf(RED "\nCurrently The Script Supports OS Using Linux Kernels Only.\n");
		printf("\nContact 1JB18CS005 (Abhishek N) To Add Support For Other OS\n" RESET);
		sleep(2);
		exit(0);
	}
	
}

void chk_file()
{
	FILE *fr;
	fr = fopen("ani.txt","rb");

	if(fr==NULL)
	{
		printf(RED "\nFile Doesn't Exist.\nCreating The File Please Wait...\n" RESET);
		sleep(2);
		system("touch ani.txt");		
	}

	else
	{
		printf("\nConnection Succeeded\n");
		sleep(1);
	}
	
}

void add()
{
	int n,i;
	FILE *fp;
	struct student s[100];

	printf(YELLOW "\n\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * * *");
	printf("\n\t\t*             Student Record Management System        *");
	printf("\n\t\t*        Project By 0x41 & 41alderson                 *");
	printf("\n\t\t*           USN: 1JB18CS015 & 1JB18CS005              *");
	printf("\n\t\t*             Special Thanks To: NONE                 *");
	printf("\n\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * * *" RESET);
	sleep(3);

	printf("\n\nPlease Wait Connecting To Database...\n");
	sleep(3);

    chk_file();

	fp=fopen("ani.txt","ab");

	printf("\nEnter No Of Students To Add: ");
	scanf("%d",&n);

	for(i=0;i<n;i++)
	{   
		printf(RED"\n\t\tEntry For Student No %d" RESET,i+1);
		printf(WHITE "\n\t--------------------------------------\n\n" RESET);

		printf("usn Of The Student: ");
		scanf("%s",s[i].usn);
		
		found(s[i].usn);

		printf("\nName Of The Student: ");
		scanf("%s",s[i].name);
		sleep(1);
		
		printf(RED "\n\t\tEntry For %s" RESET,s[i].name);
		printf(WHITE "\n\t--------------------------------------\n" RESET);

		printf("\nSection Of The Student: ");
		scanf(" %c",&s[i].section);

		printf("\nFees Paid By The Student: ");
		scanf("%f",&s[i].fees_paid);

		printf("\nFees To Be Paid By The Student: ");
		scanf("%f",&s[i].fees_unpaid);

		printf("\nPhone-Number Of The Student: ");
		scanf("%s",s[i].phone);
        
		while(strlen(s[i].phone)!=10)
		{
			printf(RED "\nPhone Number Length Is Not 10 Digits.\nPlease Re-Enter\n" RESET);
			sleep(1);
			printf("\nPhone-Number Of The Student: ");
		    scanf("%s",s[i].phone);
			while(1)
			{	
				break;
			}
		}

		printf("\nTotal Marks Scored By The Student: ");
		scanf("%f",&s[i].marks);

		printf("\nTotal Percentage: ");
		scanf("%f",&s[i].percent);

		fwrite(&s,sizeof(s),1,fp);
		printf(YELLOW "\nSTUDENT RECORD FOR %s ADDED SUCCESSFULLY\n" RESET,s[i].name);
		fclose(fp);
		sleep(2);
        
		printf("\nReturning To Main Menu.\n");
		system("clear");
	}
}

void found(char usn[15])
{
	struct student found;
	FILE *fr;
	int stu_found=0;

    fr=fopen("ani.txt","rb");

	while(fread(&found,sizeof(found),1,fr) == 1)
	{
        if(strcmp(usn,found.usn) == 0)
		{
            stu_found = 1;
            break;
        }
    }
    if(stu_found == 1)
	{
		printf(RED "\nStudent Record Of %s Is Already Present\n" RESET,usn);
		sleep(2);
		system("clear");
		main();
	}
}

void search()
{
    char search_usn[15];
    FILE *fr;
	int stu_found = 0;
    struct student info;
	char again;
    
	printf("\nPease Wait Connecting To DB.\n");
	sleep(1);

	fr=fopen("ani.txt","rb");

	if(fr==NULL)
	{
		printf(RED "\nFile Note Found.\n(Or) \nFile Is Not Placed In Required Path\n." RESET);
		sleep(2);
		main();
	}

    printf("\nEnter USN Of The Student To View Data: ");
    scanf("%s",search_usn);

    while(fread(&info,sizeof(info),1,fr) == 1)
	{
        if(strcmp(search_usn,info.usn) == 0)
		{
            stu_found = 1;
            break;
        }
    }
    if(stu_found == 1)
	{
		sleep(2);
        printf(WHITE "\nStudent Record Of '%s' Found\n\n",info.usn);
        printf("Student-USN:       %s\n",info.usn);
        printf("Student-Name:      %s\n",info.name);
        printf("Section:           %c\n",info.section);
		printf("Fees-Paid:         %f\n",info.fees_paid);
		printf("Fees-To-Be-Paid:   %f\n",info.fees_unpaid);
		printf("Marks Obtained:    %f\n",info.marks);
		printf("Total Percentage:  %f\n",info.percent);
        printf("Phone No:          %s\n",info.phone);
		sleep(2);
    }
	else
	{
        printf(RED "\nSorry, No record found in the database" RESET);
		sleep(2);
	}
	
	printf(RESET "\nDo You Want To Perform Another Search[y/n]: ");
	scanf(" %c",&again);

	if(again=='y')
	{
		search();
	}

	else if (again=='n')
	{
		system("clear");
		main();
	}

	else
	{
		printf(RED "\nUnknown Option Chosen.\nTaking You Back To Main Menu..\n" RESET);
		sleep(2);
		system("clear");
		main();
	}
}

void display_all()
{
	FILE *fp;
	char display_data,s;

	fp= fopen("ani.txt","rb+");
	display_data = fgetc(fp);
    
	printf(WHITE "\n\tDisplaying All Students Data\n" RESET);

	while(display_data!=EOF)
	{
		printf("%c",display_data);
		display_data = fgetc(fp);
	}

	fclose(fp);

	sleep(1);
	printf("\n\nPress Any Key To Continue..\n");
	scanf("%c",&s);
	getchar();

}

void delete_stu()
{
	char usn[15],k;
	FILE *fp, *temp;
	struct student ss;
	char cmd[100];

	printf("\nEnter USN Of The Student To Delete: ");
	scanf("%s",usn);

    fp = fopen("ani.txt","rb");
    temp = fopen("temp_ani.txt", "wb");

	if(temp!=NULL)
	{
		printf(YELLOW "\nPlease Wait Performing Necessary Operations\n" RESET);
		system("touch temp_ani.txt");
		sleep(2);
		printf(YELLOW "\nCreating A Back-Up File Please Wait..\n" RESET);
		system("cat ani.txt > ani.txt.bk");
		sleep(1);
		printf(YELLOW "\nBack-Up File Created Successfully As ani.txt.bk\n" RESET);
		fflush(stdin);
	}

	else if(temp==NULL)
	{
		printf("....");
		fflush(stdin);
	}

	else
	{
		printf(RED "Unknown Error Crashed The Current Operation\n" RESET);
		sleep(2);
		printf("\nReturning To Main Menu\n");
		fflush(stdin);
	}
	
    while(fread(&ss, sizeof(ss),1,fp)==1)
	{
        if(strcmp(usn,ss.usn) == 0)
		{
			fwrite(&ss,sizeof(ss),1,temp);
        }

    }
	
    fclose(fp);
    fclose(temp);
    remove("ani.txt");
    rename("temp_ani.txt","ani.txt");
    printf("\nStudent Data Of %s Has Been Deleted Successfully\n",usn);

	sleep(1);
	printf("\n\nPress Any Key To Continue..\n");
	scanf("%c",&k);
	getchar();

}

int main()
{
	int opt;
    system("clear");

    chk_compat();

	printf(YELLOW "\n\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * * *");
	printf("\n\t\t*             Student Database - SJBIT                *");
	printf("\n\t\t*        Project By Anirudh M P & Abhishek N          *");
	printf("\n\t\t*           USN: 1JB18CS015 & 1JB18CS005              *");
	printf("\n\t\t*             Special Thanks To: NONE                 *");
	printf("\n\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * * *\n" RESET);
	sleep(3);

	printf(RED "\n\t\t\t\tMenu\n" RESET);
	printf(BLUE "\n1.Add Student.\n2.Search Student Data\n3.Delete Student Data.\n4.Display All Student Data.\n5.Exit" RESET);
	printf(RED "\n\nYour Selection: " RESET);
	scanf("%d",&opt);
	
	switch(opt)
	{
		case 1:printf("\nYou Selected Add Student.\n");
			   system("echo Student Data Was Added @ `date` | cat >>log");
		       add();			   
			   printf("\nReturning To Main Menu.\n");
			   sleep(2);
			   main();

		case 2:printf("\nYou Selected Display Student Data.\n");
			   system("echo Student Data Was Searched @ `date` | cat >>log");
		       search();
			   printf("\nReturning To Main Menu.\n");
			   sleep(2);
			   main();
        
		case 3:printf("\nYou Selected Remove Student.\n");
			   system("echo Student Data Was Deleted @ `date` | cat >>log");
		       delete_stu();
			   printf("\nReturning To Main Menu.\n");
			   sleep(2);
			   main();

		case 4:printf("\nYou Selected Dislpay All Student Data.\n");
			   system("echo Student Data Was Displayed @ `date` | cat >>log");
		       display_all();			   
			   printf("\nReturning To Main Menu.\n");
			   sleep(2);
			   main();

		case 5:printf("\nQuitting The Interface\n");
		       system("echo User/Admin Quit The Script @ `date` | cat >>log");
		       sleep(3);
		       exit(1);

		default:printf("\nUnknown Option Selected.\n");
		        system("echo User/Admin Chose Unknown Option @ `date` | cat >>log");
		        break;
		        main();
	}

}
