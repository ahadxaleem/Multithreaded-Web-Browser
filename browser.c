#include<stdio.h>
#include<conio.h>
#include<string.h>
#include"dllofchr.h"

void main()
{
	createTab();
	char op[10], sinput[20];
	while (1)
	{
		printf("\nEnter operation :");	//	Operation you want to perform
		fgets(op, sizeof(op), stdin);
		if (!strcmp(op, "search\n"))	//	Comparing strings
		{
			FILE *fp=NULL;
			printf("Search Bar :");
			fgets(sinput, sizeof(sinput), stdin);
			if (strcmp(tcurrent->currH[tcurrent->currP], "Incognito.txt"))//if not incognito save history
			{
				fp = fopen("history.txt", "a");//opening file  
				fprintf(fp, sinput);//writing data into file
				fclose(fp);
			}
			char *sm = (char*)malloc(20);//avoiding a major error of all arrays pointing at same location
			strcpy(sm, sinput);
			search(sm);
		}
		else if (!strcmp(op, "ctab\n"))
		{
			createTab();
		}
		else if (!strcmp(op, "ntab\n"))
		{
			movNext();
		}
		else if (!strcmp(op, "ptab\n"))
		{
			movPrev();
		}
		else if (!strcmp(op, "mfwd\n"))
		{
			movForward();
		}
		else if (!strcmp(op, "mback\n"))
		{
			movBack();
		}
		else if (!strcmp(op, "dtab\n"))
		{
			deleteTab();
		}
		else if (!strcmp(op, "close\n"))
		{
			destructor();
			break;
		}
		else if (!strcmp(op, "history\n"))
		{
			history();
		}
		else if (!strcmp(op, "imenu\n"))
		{
			iMenu();
		}
		else if (!strcmp(op, "incog\n"))
		{
			incognito();
		}
		else
		{
			printf("function not exist\n");
		}
	}
}
