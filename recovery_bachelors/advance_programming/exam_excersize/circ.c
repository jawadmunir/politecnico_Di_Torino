#include "circ.h"

GATE *search(char *name,GATE *head){
while(head!=NULL)
  {
  if(strcmp(head->name,name)==0)
	 return head;
  head=head->next;
  }
return NULL;
}

GATE *search_inp(char *input,GATE *head){
int s;
while(head!=NULL)
  {
  for(s=0;s<head->inp;s++)
	 {
	 if(strcmp(head->inputs[s],input)==0)
		return head;
	 }
  head=head->next;
  }
return NULL;
}

GATE *readfile(char *text){
FILE *fp;
int s;
GATE *data,*head=NULL;
char buffer[21];
if((fp=fopen(text,"r"))==NULL)
  {
  printf("Error reading the source file");
  return NULL;
  }
while(feof(fp)==0)
  {
  data=(GATE*)malloc(sizeof(struct vertex));
  fscanf(fp,"%s",buffer);
  data->name=(char*)malloc((strlen(buffer)+1)*sizeof(char));
  strcpy(data->name,buffer);
  fscanf(fp,"%s",buffer);
  data->logic_gate=(char*)malloc((strlen(buffer)+1)*sizeof(char));
  strcpy(data->logic_gate,buffer);
  fscanf(fp,"%d %d",&(data->inp),&(data->outp));
  data->inputs=(char**)malloc(data->inp*sizeof(char*));
  for(s=0;s<data->inp;s++)
	 {
	 fscanf(fp,"%s",buffer);
	 data->inputs[s]=(char*)malloc((strlen(buffer)+1)*sizeof(char));
	 strcpy(data->inputs[s],buffer);
	 }
  data->outputs=(char**)malloc(data->outp*sizeof(char*));
  for(s=0;s<data->outp;s++)
	 {
	 fscanf(fp,"%s",buffer);
	 data->outputs[s]=(char*)malloc((strlen(buffer)+1)*sizeof(char)+1);
	 strcpy(data->outputs[s],buffer);
	 }
  fscanf(fp,"%d",&(data->delay));
  strcpy(data->parent,"none");
  data->weight=0;
  data->next=head;
  head=data;
  }
return head;
}

void critical_path(GATE *head){
GATE *temp,*b,*cont;
int i,max;
cont=head;
while(cont!=NULL)
  {
  temp=head;
  while(temp!=NULL)
	 {
	 for(i=0;i<temp->outp;i++)
		{
		b=head;

		while(b!=NULL)
		  {
		  b=search_inp(temp->outputs[i],b);
		  if(b!=NULL)
			 {
			 if(b->weight<temp->weight+temp->delay)
				{
				b->weight=temp->weight+temp->delay;
				strcpy(b->parent,temp->name);
				}
			 b=b->next; // I have put this segment here in the case the search_inp function returns a NULL
			 }
		  }
		}
	 temp=temp->next;
	 }
  cont=cont->next;
  }
temp=head;
max=0;
b=NULL;
while(temp!=NULL)
  {
  if(strcmp(temp->logic_gate,"OUTPUT")==0)
	 {
	 if(temp->weight+temp->delay>max)
		{
		max=temp->weight+temp->delay;
		b=temp;
		}
	 }
  temp=temp->next;
  }
printf("The critical path is: ");
while(b!=NULL)
  {
  printf(" %s  ",b->name);
  b=search(b->parent,head);
  }
printf("with a delay: %d",max);
}
