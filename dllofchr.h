#pragma once
#include <stdio.h>
#include<conio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
struct tabs {
	char *currH[20];	//	To maintain the current tab history
	int currP;			//	Pointing to the current tab history.
	int size;
	struct tabs *tnext;
	struct tabs *tprev;
};
//this link always point to first Link
struct tabs *thead = NULL;
//keeps track of current node we are on
struct tabs *tcurrent = NULL;
//this link always point to last Link 
struct tabs *ttail = NULL;

//is list empty
bool tisEmpty() {
	return thead == NULL;
}
//total no of tabs
int tlength() {
	int length1 = 0;
	struct tabs *temp1;

	for (temp1 = thead; temp1 != NULL; temp1 = temp1->tnext) {
		length1++;
	}

	return length1;
}

//save file name
void saveStat(char *ch)
{
	if (tcurrent->size > tcurrent->currP)//maintaining history
	{
		int i;
		for (i = tcurrent->currP + 1; i <= tcurrent->size; i++)//freeing used memory
		{
			free(tcurrent->currH[i]);
		}
		tcurrent->size = tcurrent->currP;
	}

	tcurrent->size++;
	tcurrent->currP = tcurrent->size;
	tcurrent->currH[tcurrent->currP] = ch;
}


//display current page
void displayCurr(char *temp)
{
#pragma warning(disable : 4996)//removing warning error
	FILE *fp;//points to the first character in the file
	char ch;
	if (strcmp(temp, "New Tab"))//if not new tab
	{
		fp = fopen(temp, "r");
		if (fp == NULL)//if can't open the file
		{
			printf("\nWebpage is not availabe\n");
		}
		else
		{
			while (1)
			{
				ch = fgetc(fp);
				if (ch == EOF)
					break;
				printf("%c", ch);
			}
			fclose(fp);
		}
	}
}

//display the list in from first to last
void displayAll() {

	//start from the beginning
	struct tabs *tptr = ttail;
	system("cls");
	//navigate till the end of the list
	while (tptr != NULL) {//giving browser a proper view
		printf("| ");
		if (tptr==tcurrent)
		{
			printf("\033[0;34m");
			fputs(tptr->currH[tptr->currP], stdout);//prints string without new line
			printf("\033[0m");
		}
		else
		{
			fputs(tptr->currH[tptr->currP], stdout);//prints string without new line
		}
		printf(" \\       ");
		tptr = tptr->tprev;

	}
	printf("\n");
	displayCurr(tcurrent->currH[tcurrent->currP]);
}

//create a new tab
void createTab()
{
	//create a link
	struct tabs *tlink = (struct tabs*) malloc(sizeof(struct tabs));
	tlink->tnext = NULL;
	tlink->tprev = NULL;
	tlink->size = 0;
	tlink->currP = 0;
	tlink->currH[tlink->currP] = "New Tab";
	if (tisEmpty()) {
		//make it the last link
		ttail = tlink;
	}
	else {
		//update first prev link
		thead->tprev = tlink;
	}

	//point it to old first link
	tlink->tnext = thead;

	//point first to new first link
	thead = tlink;
	tcurrent = tlink;
	displayAll();
}

//search 
void search(char *temp)
{
	int i = 0;
	while (1)//putting input in a proper format
	{
		if (temp[i] == '\n')
		{
			temp[i] = '.';
			break;
		}
		i++;
	}

	strcat(temp, "txt");
	saveStat(temp);
	displayAll();
}

//move b/w tabs
void movNext()
{
	if (tcurrent == thead)
	{
		printf("nothing more to show next.....\n");
	}
	else
	{
		tcurrent = tcurrent->tprev;
	}
	displayAll();
}
void movPrev()
{
	if (tcurrent == ttail)
	{
		printf("nothing more to show next.....\n");
	}
	else
	{
		tcurrent = tcurrent->tnext;
		displayAll();
	}
	
}

// to mov between current tab history
void movForward()
{
	if (tcurrent->currP == tcurrent->size)
	{
		printf("can't move forward!!");
	}
	else
	{
		tcurrent->currP++;
		displayAll();
	}
}
void movBack()
{
	if (tcurrent->currP == 0)
	{
		printf("can't move back!!");
	}
	else
	{
		tcurrent->currP--;
		displayAll();
	}
}

void destructor();

//delete the current tab
void deleteTab()
{
	int i;
	for ( i = 1; i <= tcurrent->size; i++)//freeing current history
	{
		free(tcurrent->currH[i]);
	}
	if (thead == ttail)//if there's only one tab
	{
		tcurrent->size = 0;
		destructor();
		exit(i);
	}
	else//freeing space taken by tab
	{
		struct tabs *temp;
		if (tcurrent->tnext == NULL)//if no next tab
		{
			temp = ttail;
			ttail = ttail->tprev;
			ttail->tnext = NULL;
			movNext();
		}
		else if (tcurrent->tprev == NULL)//if no previous tab
		{
			temp = thead;
			thead = thead->tnext;
			thead->tprev = NULL;
			movPrev();
		}
		else//if both next and previous tabs
		{
			temp = tcurrent;
			(tcurrent->tprev)->tnext = tcurrent->tnext;
			(tcurrent->tnext)->tprev = tcurrent->tprev;
			movNext();
		}
		free(temp);
		
	}

}

//history
void history()
{
	if (strcmp(tcurrent->currH[tcurrent->currP], "New Tab"))//if not a new tab
	{
		createTab();
		tcurrent->currH[tcurrent->currP] = "history.txt";//new tab will open as history
		displayAll();
	}
	else//if new tab
	{
		char *sm = (char*)malloc(20);
		strcpy(sm , "history.txt");
		tcurrent->currH[tcurrent->currP] = sm;
		displayAll();
	}
}

//instruction menual
void iMenu()
{
	if (strcmp(tcurrent->currH[tcurrent->currP], "New Tab"))//if not a new tab
	{
		createTab();
		tcurrent->currH[tcurrent->currP] = "imenu.txt";//new tab will open as menu
		displayAll();
	}
	else//if new tab
	{
		char *sm = (char*)malloc(20);
		strcpy(sm, "imenu.txt");
		tcurrent->currH[tcurrent->currP] = sm;
		displayAll();
	}
}

//incognito mode
void incognito()
{

		if (strcmp(tcurrent->currH[tcurrent->currP], "New Tab"))//if not a new tab
		{
			createTab();
			tcurrent->currH[tcurrent->currP] = "Incognito.txt";//new tab will open as menu
			displayAll();
		}
		else//if new tab
		{
			char *sm = (char*)malloc(20);
			strcpy(sm, "Incognito.txt");
			tcurrent->currH[tcurrent->currP] = sm;
			displayAll();
		}
}

//a destructor
void destructor()
{
	struct tabs *tptr;
	while (ttail!=NULL)
	{
		tptr = ttail;
		int i;
		for (i = 1; i <= tptr->size; i++)//freeing current history
		{
			free(tptr->currH[i]);
		}
		ttail = ttail->tprev;
		free(tptr);
	}
}
