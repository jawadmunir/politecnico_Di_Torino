/* Name: Munir, jawad
matr no: 158385 
This program is done by reading the file in a character array of 1000 elements  */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <conio.h>
#define MAX 1000

void printdescendingorder(char *[],int [],int);// function to sort in descending order w.r.t votes  
void swap(char **p, char **q);// fuction to swap will call by printdecendingorder.


int main()
{
	 char *candidate[MAX],*ck;// to read the line from file
	 char buffer[30]; 
	 char command;
	 char cname[30]; // for getting a string from stdin
	 int i,j=0,quit=0,n=0,ch=0,chk=0,qt,count=0;
	 int votecount[MAX];// to account for the votes got by each canidate.
	 FILE *fp;
     char *space;
	 // dynamically allocating the memory for the array of pionters
	 for(i=0; i<MAX; i++){
	 candidate[i]=(char *)malloc(sizeof(char)*30);
	 votecount[i]=0;// initializing with zero all the votes.
	 }
	 printf("\n\n\n ******************************************************\n");
	 printf(" *             VOTING SYSTEM                          *\n");
	 printf(" ******************************************************\n\n");
	 // reading file
	 if((fp= fopen("candidate.txt","r"))==NULL)
	 {
			printf("file could not open\n");
			}
	 else{
	 while(fgets(buffer,29,fp)!=NULL && j<MAX){
          //if(  ( space=strchr(buffer,'\n')) !=NULL)
			//			  *space='\0';
                                     
      strcpy(candidate[j],buffer);
      
	 
	 count++;// This is used to account for knowing that how many lines are their in the file which was read.

	  printf( "the name of %d canidate is %s \n",j+1,candidate[j]);

	  //z=strlen(candidate[j]);
	 // printf("\n The size of %d condidate is %d\n",j+1,z);
		j++;
       // printf("count is %d\n",count);
		
		}// while
	 //file check, so their is no duplicates
     //printf("count is %d\n",count); 

	 for(i=0;i<count;i++)
	 {
		 for(j=0;j<count;j++)
		 {
			 if((strcmp(candidate[i],candidate[j])==0))
			{
				 if(i!=j)
			quit++;
			}//end if
			}// end for "j"
			}// end for "i"
			if( quit>=1){
			printf("the file doesnot fulfill requirements abort execution\n");
			//exit (1);
			}
			else
			{
			printf("\nBEFORE ENTERING THE VOTE READ THE MENU \n");
			printf(">>\n");
			printf("  enter\n <V> for writing the complete name of the canidate\n <S> for entering first characters of canidate name\n");
			printf(" <Q> for finishing the reading of vote\n");



			do
			{
			qt=1;
			
			scanf("%c",&command);
			/*if(command=="\n"){
			scanf("%c",&command);
			}*/

			command=toupper(command);

			switch(command)
			{
                           ch=0;
			              // chk=0;
                           
					 case'V':
								printf("enter the canidate full name\n");
								fflush(stdin);
								//scanf("%s",cname);
								fgets(cname,29,stdin);
			for(i=0;i<count;i++)
			{
				if((strcmp(cname,candidate[i])==0))
				{
					  ++votecount[i];
					  ch++;
				}// if
			}// for
				 if(ch==0)
				 {
				 printf("The canidate name not found, enter the command and type the name agian to vote\n");
				 	break;
				 }
		break;

					 case'S':
                             chk=0;
			printf("Enter the first characters you remember of the canidate's name: \n");
								fflush(stdin);
                                //scanf("%s",cname);
								
								fgets(cname,29,stdin);
								  if (   (ck=strchr(cname,'\n') )!=NULL )
								       *ck='\0';
			                    n=strlen(cname);// to read no of characters enter by the user
			                   // printf("the no charaters in cname%d\n",n);
			                   // printf("the string read is %s\n ",cname);
			for(i=0;i<count;i++){
                                 //printf("the canidate name is : %s\n",candidate[i]);
				  if((strncmp(candidate[i],cname,n-1))==0){
				 // ++votecount[i];
				  chk++;
				  }// if
			}// for
				 if(chk==1){
                   for(i=0;i<count;i++){
                        if((strncmp(cname,candidate[i],n))==0){
                                 ++votecount[i];
                                      break;
                  }//if
                }//for
             }//if
            // printf("the value of chk:%d\n",chk);
                  if(chk>1){
				 printf("The vote given is Ambigious,please by giving the command agian enter your vote:\n");
				 printf("The characters that you have given refers to %d candidates\n",ch);
				 printf("type more characters to be paticular about your candidate by entering the command and the name agian:\n");
				 break;
				 }//end if*/
                 if(chk==0){
		             printf( "candidate name not found , your vote is ignored ,please by giving the command agian enter you vote agian:\n");
											 //scanf("%s",cname);
											 break;
						 }
				 
				 
                                       
				 //printf("the canidate name not found, enter the name agian\n");
				 //scanf("%s",cname);
				 break;
						case'Q':
						// printing the names and the vote the canidate got
						for(i=0;i<count;i++)
						printf("The canidate name %s , The votes that they got: %d \n",candidate[i],votecount[i]);
						printdescendingorder(candidate,votecount,count);
						qt=0;

						free(candidate);
						break;
						//default:
									//printf("Wrong command\n");
									//break;
						}
						}
						while(qt);


}
}
system("PAUSE");
 return 0;
}

// function definations

void printdescendingorder(char *candidate[],int votecount[],int x)
{
	  int switched =1;
	  int hold=0;
	  int i=0,j=0;
	  for(i=0;i<x && switched;i++)
	  {
		switched=0;
		for(j=0;j<x;j++)
		{
			if(votecount[j]<votecount[j+1])
			{
			switched=1;
			hold=votecount[j];
			votecount[j]=votecount[j+1];
			votecount[j+1]=hold;
			swap(&candidate[j],&candidate[j+1]);
			}//end if
		  }//for j
		}// for i
		  printf("The list sorted with votes given is as follows\n\n");
		  for(i=0;i<x;i++){
        //printf("the sorted list: %d\n",votecount[i]);
        if(votecount[i] > 0)
		  printf("The canidates name is %s,votes that they got is: %d \n",candidate[i],votecount[i]);
}

	  } // end funtion

void swap(char **p, char **q){
	  char *temp;
	  temp= *p;
	  *p=*q;
	  *q=temp;
	  }
	 
