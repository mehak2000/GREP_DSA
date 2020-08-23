#include "grep.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

//to initialize the line
void init (line *l){
	l->head=NULL;
	l->tail=NULL;
}

//to insert the node
void insert(line *l,char  character){
	node *newnode=(node *)malloc (sizeof(node));
	if(!newnode){
		return;
	}
	newnode->next=NULL;
	newnode->prev=NULL;
	newnode->ch[0]=character;
	newnode->ch[1]='\0';
	if(l->head==NULL && l->tail==NULL){
		l->head=newnode;
		l->tail=newnode;
		return;	
	}
	else{
		newnode->prev=l->tail;
		l->tail->next=newnode;
		l->tail=newnode;
		newnode->next=NULL;
	}
	return;
}

//to print the list
void traverse(line l){
	node *ptr;
	ptr=l.head;
	while(ptr->next){
		printf("%c",ptr->ch[0]);
		ptr=ptr->next;
	}
	if(ptr==l.tail){
		printf("%c \n",ptr->ch[0]);
	}
	return;
}

//to remove a node
void destroyLine(line *l){
	node *temp;
	if (l->head==NULL && l->tail ==NULL){
		return;
	}
	else{
		while(l->tail !=l->head){
			temp=l->tail;
			l->tail=temp->prev;
			l->tail->next=NULL;
			temp->prev=NULL;
			free(temp);
		}
		if(l->tail==l->head){
			temp=l->tail;
			l->tail=NULL;
			l->head=NULL;
			free(temp);
		}
	}
}

//to lower the string 
void lower_string(char * s){
	   int i = 0;
           for(i=0;i<=strlen(s);i++){
                 if(s[i]>=65&&s[i]<=90)
                  s[i]=s[i]+32;
   }
	return ;
}

int caseinsensitive(line l, char *pattern){
	char word[100];	
	strcpy(word,pattern);
	line l1;
	init(&l1);
	node *ptr;
	if (l.head==NULL){
		return 0;
	}
	ptr=l.head;
	while(ptr->next){
		insert(&l1,ptr->ch[0]);
		ptr=ptr->next;
	}
	if(ptr==l.tail){
		insert(&l1,ptr->ch[0]);
	}
	lower_string(word);
	node *ptr1;
	ptr1=l1.head;
	while(ptr1->next){
		lower_string(ptr1->ch);
		ptr1=ptr1->next;
	}
	if(ptr1->next==NULL){
		lower_string(ptr1->ch);
	}	
	int i=0;
	ptr1=l1.head;
	while((ptr1->next)  && (word[i]!='\0')){ 
		if(word[i]==ptr1->ch[0] ){
				ptr1=ptr1->next;
				i++;
				continue;
			}
			else{ 	
			      if(i!=0){
					i=0;
				}
				else{
					ptr1=ptr1->next;
				}
			}
		}
	if(ptr1==l1.tail){
		if(word[i]==ptr1->ch[0])
				i++;
		
	}
	 if(word[i]=='\0'){
			return 1;
		}
		else{
			return 0;
		}
}

int donotmatchpattern(line l, char *pattern){
	char word[100];	
	strcpy(word,pattern);
	line l1;
	init(&l1);
	node *ptr;
	if (l.head==NULL){
		return 0;
	}
	ptr=l.head;
	while(ptr->next){
		insert(&l1,ptr->ch[0]);
		ptr=ptr->next;
	}
	if(ptr==l.tail){
		insert(&l1,ptr->ch[0]);
	}
	node *ptr1;
	int i=0;
	ptr1=l1.head;
	while((ptr1->next)  && (word[i]!='\0')){ 
		if(word[i]==ptr1->ch[0] ){
				ptr1=ptr1->next;
				i++;
				continue;
			}
			else{ 	
			      if(i!=0){
					i=0;
				}
				else{
					ptr1=ptr1->next;
				}
			}
		}
	if(ptr1==l1.tail){
		if(word[i]==ptr1->ch[0])
				i++;
	}
	 if(word[i]=='\0'){
			return 0;
		}
		else{
			return 1;
		}
}

int matchwholewords(line l, char *pattern){
	char word[100];	
	strcpy(word,pattern);
	line l1;
	init(&l1);
	if (l.head==NULL){
		return 0;
	}
	node *ptr;
	ptr=l.head;
	while(ptr->next){
		insert(&l1,ptr->ch[0]);
		ptr=ptr->next;
	}
	if(ptr==l.tail){
		insert(&l1,ptr->ch[0]);
	}
	node *ptr1;
	int i=0;
	ptr1=l1.head;
	while((ptr1->next)  && (word[i]!='\0')){ 
		if(word[i]==ptr1->ch[0] ){
				ptr1=ptr1->next;
				i++;
				continue;
			}
			else{ 	
			      if(i!=0){
					i=0;
				}
				else{
					ptr1=ptr1->next;
				}
			}
		}
	if(ptr1==l1.tail){
		if(word[i]==ptr1->ch[0])
				i++;
	}
	  if((word[i]=='\0')&&((ptr1->ch[0]==' ') || (ptr1->ch[0]=='(') || (ptr1->ch[0]=='/') || ptr1->ch[0]==')'|| ptr1->ch[0]=='<'|| ptr1->ch[0]=='>'|| ptr1->ch[0]=='!'|| ptr1->ch[0]=='-'||ptr1->ch[0]=='*'||ptr1->ch[0]==','||ptr1->ch[0]=='"'||ptr1->ch[0]==';'||ptr1->ch[0]==':'|| ptr1->ch[0]=='\0')){
			return 1;
		}
		else{
			return 0;
		}
}

 int matchpattern(line l, char *pattern){
	char word[100];	
	strcpy(word,pattern);
	if (l.head==NULL){
		return 0;
	}
	line l1;
	init(&l1);
	node *ptr;
	ptr=l.head;
	while(ptr->next){
		insert(&l1,ptr->ch[0]);
		ptr=ptr->next;
	}
	if(ptr==l.tail){
		insert(&l1,ptr->ch[0]);
	}
	node *ptr1;
	int i=0;
	ptr1=l1.head;
	while((ptr1->next)  && (word[i]!='\0')){ 
		if(word[i]==ptr1->ch[0]){
				ptr1=ptr1->next;
				i++;	
				continue;
		}
		else{ 	
			      if(i!=0){
					i=0;
				}
				else{
					ptr1=ptr1->next;
					
				}
			}
		}
	if(ptr1==l1.tail){
			if(word[i]==ptr1->ch[0])
				i++;
	}
	 if(word[i]=='\0'){
			return 1;
		}
		else{
			return 0;
		}
}

int caseinsensitiveandwholeword(line l, char *pattern){
	char word[100];	
	strcpy(word,pattern);
	line l1;
	init(&l1);
	node *ptr;
	if (l.head==NULL){
		return 0;
	}
	ptr=l.head;
	while(ptr->next){
		insert(&l1,ptr->ch[0]);
		ptr=ptr->next;
	}
	if(ptr==l.tail){
		insert(&l1,ptr->ch[0]);
	}
	lower_string(word);
	node *ptr1;
	ptr1=l1.head;
	while(ptr1->next){
		lower_string(ptr1->ch);
		ptr1=ptr1->next;
	}
	if(ptr1->next==NULL){
		lower_string(ptr1->ch);
	}	
	int i=0;
	ptr1=l1.head;
	while((ptr1->next)  && (word[i]!='\0')){ 
		if(word[i]==ptr1->ch[0] ){
				ptr1=ptr1->next;
				i++;
				continue;
			}
			else{ 	
			      if(i!=0){
					i=0;
				}
				else{
					ptr1=ptr1->next;
				}
			}
		}
	if(ptr1==l1.tail){
		if(word[i]==ptr1->ch[0])
				i++;
		
	}
	 if((word[i]=='\0')&&((ptr1->ch[0]==' ') || (ptr1->ch[0]=='(') || (ptr1->ch[0]=='/') || ptr1->ch[0]==')'|| ptr1->ch[0]=='<'|| ptr1->ch[0]=='>'|| ptr1->ch[0]=='!'|| ptr1->ch[0]=='-'||ptr1->ch[0]=='*'||ptr1->ch[0]==','||ptr1->ch[0]=='"'||ptr1->ch[0]==';'||ptr1->ch[0]==':' || ptr1->ch[0]=='\0')){
			return 1;
		}
		else{
			return 0;
		}
}
