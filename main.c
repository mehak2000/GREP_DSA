#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include "grep.h"
#include<string.h>
//#include "open.c"
#define REG 10
#define UNMATCH 2
#define WHOLEWORDS 3
#define COUNT 4
#define INSENSITIVE 5
#define MAXIMUM 6
#define RECURSION 101
#define FILENAME 8
#define LINENUMBER 9
#define QUIET 100
#define COUNTUNMATCH 56
#define COUNTINSENSITIVE 102
#define COUNTWHOLEWORDS 45
#define CASEINSENSITIVEWHOLE 432
# define PURPLE "\x1b[35m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"
int openfile(char *,int,char * ,int ,int,int);
int modecheck(char,int );
void recursion(int ,char *, char *, int );
int main(int argc,char * argv[]){
   int static flag=0;
   int static type=0;
   int i=0;
   int num;
    if( argc< 3 && strcmp(argv[1],"--help")!=0 && strcmp(argv[1],"--version")!=0){
		printf("Usage: grep [OPTION]... PATTERN [FILE]...\n Try './grep --help' for more information.");
		return 0;
    }
    else if(strcmp(argv[1],"--help")==0){		
printf("Usage: grep [OPTION]... PATTERN [FILE]...\n Search for PATTERN in each FILE.\n Example: grep -i &apos;hello world&apos; menu.h main.c \n Pattern selection and interpretation: \n -e, --regexp=PATTERN      use PATTERN for matching \n -i, --ignore-case         ignore case distinctions \n -w, --word-regexp         force PATTERN to match only whole words \n Miscellaneous: \n -v, --invert-match        select non-matching lines \n Output control: \n -m, --max-count=NUM       stop after NUM selected lines \n -n, --line-number         print line number with output lines \n -H, --with-filename       print file name with output lines \n -h, --no-filename         suppress the file name prefix on output \n -o, --only-matching       show only the part of a line matching PATTERN \n -r, --recursive           like --directories=recurse \n -l, --files-with-matches  print only names of FILEs with selected lines \n -c, --count               print only a count of selected lines per FILE \n \n When FILE is &apos;-&apos;, read standard input.  With no FILE, read &apos;.&apos; if \n recursive, &apos;-&apos; otherwise.  With fewer than two FILEs, assume -h. \n Exit status is 0 if any line is selected, 1 otherwise; \n if any error occurs and -q is not given, the exit status is 2.");
	}
    else{ 
  	if (argv[1][0]!='-'){	
		if(argc==3){
			flag=0;
			i=2;
			type=REG; 
			openfile(argv[i],type,argv[1],flag,num,0);
		}
		else if(argc>3){
			flag=1;
			//printf("HI");
			i=2;
			type=REG; 
			while(i<argc){
				openfile(argv[i],type, argv[1],flag,num,0);
				i++;							
			}
		}
	}
	else if (argv[1][0]=='-' && argv[1][1]!='m' && argv[1][1]!='r' && (strcmp(argv[1],"-e")!=0) && (strcmp(argv[2],"-e")!=0) && argv[1][1]!='l' && strcmp(argv[2],"-H")!=0 && strcmp(argv[2],"-h")!=0 && strcmp(argv[1],"-n")!=0 && strcmp(argv[2],"-n")!=0 && strcmp(argv[1],"-q")!=0 && (strcmp(argv[1],"-ci")!=0) && (strcmp(argv[1],"-cv")!=0) && (strcmp(argv[1],"-vi")!=0) && (strcmp(argv[1],"-cvi")!=0) && (strcmp(argv[1],"-vw")!=0) && (strcmp(argv[1],"-cvw")!=0) && (strcmp(argv[1],"-cw")!=0) && (strcmp(argv[1],"-iw")!=0) && (strcmp(argv[1],"-h")!=0) && (strcmp(argv[1],"-H")!=0) && (strcmp(argv[3],"*.")!=0)) {
		
			if(argc>4){
				//printf("2");
				i=3;
				flag=1;
				while(i<argc){
					type=modecheck(argv[1][1],type);
					openfile(argv[i],type, argv[2], flag,num,0);
					i++;							
				}
			}
			else if(argc==4){
				//flag =0;
				//printf("1");
				type=modecheck(argv[1][1],type);
				i=3;
				//printf("%d",type);
				openfile(argv[i],type, argv[2], flag,num,0);
			}
		
	}
	else if((strcmp(argv[1],"-h")==0) || (strcmp(argv[1],"-H")==0)){
			if(strcmp(argv[1],"-h")==0) 
				flag=0;
			else 
				flag=1;
			if(argc==4){
				i=3;
				type=REG; 
				openfile(argv[i],type,argv[2],flag,num,0);
			}
		
		else if(argc>4){
			if(strcmp(argv[1],"-h")==0) 
				flag=0;
			else 
				flag=1;
			i=3;
			type=REG; 
			while(i<argc){
				openfile(argv[i],type, argv[2],flag,num,0);
				i++;							
			}
		}
	}		
	else if(argv[1][0]=='-' && argv[1][1]=='m' && (strcmp(argv[3],"-e")!=0)){
		if(strcmp(argv[3],"-H")==0){
			if (argc==6){
				//printf("hi");
				flag=1;
				type=modecheck(argv[1][1],type);
				i=5;
				openfile(argv[i],type,argv[4],flag,atoi(argv[2]),0);
			}
			else{
				flag=1;
				i=5;
				while(i<argc){
					type=modecheck(argv[1][1],type);
					openfile(argv[i],type,argv[4],flag,atoi(argv[2]),0);
					i++;							
				}
			}
			//continue;
		}
		if(strcmp(argv[3],"-h")==0){
			if (argc==6){
				//printf("hi");
				flag=0;
				type=modecheck(argv[1][1],type);
				i=5;
				openfile(argv[i],type,argv[4],flag,atoi(argv[2]),0);
			}
			else{
				
				flag=0;
				i=5;
				while(i<argc){
					type=modecheck(argv[1][1],type);
					openfile(argv[i],type,argv[4],flag,atoi(argv[2]),0);
					i++;							
				}
			}
			//continue;
		}
		if (argc==5 && strcmp(argv[3],"-H")!=0 && (strcmp(argv[3],"-h")!=0)){
			flag=0;
			type=modecheck(argv[1][1],type);
			i=4;
			openfile(argv[i],type,argv[3],flag,atoi(argv[2]),0);
		}
		else if((strcmp(argv[3],"-H")!=0) && argc>5 && (strcmp(argv[3],"-h")!=0) &&(strcmp(argv[3],"-n")!=0) ){
			flag=1;
			i=4;
			while(i<argc){
				type=modecheck(argv[1][1],type);
				openfile(argv[i],type,argv[3],flag,atoi(argv[2]),0);
				i++;							
			}
		}
		else if((strcmp(argv[3],"-n")==0) && (strcmp(argv[4],"-h")!=0) && (strcmp(argv[4],"-H")!=0)){
			 int type1=LINENUMBER;
			if (argc==6){
				type=modecheck(argv[1][1],type);
				openfile(argv[5],type,argv[4],0,atoi(argv[2]),type1);
			}
			else{
				i=5;
				while(i<argc){
					type=modecheck(argv[1][1],type);
					openfile(argv[i],type,argv[4],1,atoi(argv[2]),type1);
					i++;							
				}
			}
		}
		else if((strcmp(argv[3],"-n")==0) && (strcmp(argv[4],"-h")==0)){
			//printf("2");
			int type1=LINENUMBER;
			if (argc==7){
				type=modecheck(argv[1][1],type);
				openfile(argv[6],type,argv[5],0,atoi(argv[2]),type1);
			}
			else{
				i=6;
				while(i<argc){
					type=modecheck(argv[1][1],type);
					openfile(argv[i],type,argv[5],0,atoi(argv[2]),type1);
					i++;							
				}
			}
		
		}
		else if((strcmp(argv[3],"-n")==0) && (strcmp(argv[4],"-H")==0)){
			//printf("3");
			int type1=LINENUMBER;
			if (argc==7){
				type=modecheck(argv[1][1],type);
				openfile(argv[6],type,argv[5],1,atoi(argv[2]),type1);
			}
			else{
				i=6;
				while(i<argc){
					type=modecheck(argv[1][1],type);
					openfile(argv[i],type,argv[5],1,atoi(argv[2]),type1);
					i++;							
				}
			}
		}		
	}
	else if((strcmp(argv[1],"-m")==0)||(strcmp(argv[1],"-e")==0)||(strcmp(argv[2],"-e")==0)){
		//printf("hi");
		if((strcmp(argv[1],"-e")==0)){
			if (argc==4){
				flag=0;
				i=3;
				type=REG;
				openfile(argv[i],type,argv[2],flag,0,0);
			}
			if(argc>4 ){
				int j;
				flag=1;
				type=REG;
				i=3;
				j=2;
				while(i<argc+1){
					openfile(argv[i],type,argv[j],flag,0,0);
					i=i+3;
					j=j+3;
				}
			}
		}
		else if (strcmp(argv[2],"-e")==0){
				
				if (argc==5){
					flag=0;
					i=4;
					type=modecheck(argv[1][1],type);
					openfile(argv[i],type,argv[3],flag,0,0);
				}
				if(argc>5 ){
					int j,k=1;
					flag=1;
					i=4;
					j=3;
				
					
					while(i<argc){
						//printf("%s",argv[j]);
						type=modecheck(argv[k][1],type);
						if(k>1 && type==MAXIMUM)
							openfile(argv[i],type,argv[j],flag,argv[k][2],0);
						else{
							openfile(argv[i],type,argv[j],flag,0,0);
						}
						i=i+4;
						j=j+4;
						k=k+4;
					
						
				}
				
			}
		}
		else if(strcmp(argv[1],"-m")==0 && (strcmp( argv[3],"-n")!=0)){
			
			if(argc==6){
				type=MAXIMUM;
				openfile(argv[5],type,argv[4],flag,atoi(argv[2]),0);
			}
			if(argc>6){
				int j,k=6;
				flag=1;
				i=5;
				j=4;
				type=MAXIMUM;
				openfile(argv[5],type,argv[4],flag,atoi(argv[2]),0);
				
				while(i<argc-1){
					
					i=i+4;
					j=j+4;
					type=modecheck(argv[k][1],type);
					openfile(argv[i],type,argv[j],flag,0,0);
					k=k+4;
					
			}
			}
		}
		
	}
	else if(argv[2][0]=='-' && argv[2][1]=='H'){
		int type1=0;
		if(argc==5){
			if(strcmp(argv[1],"-n")==0){
				type1=LINENUMBER;
				type=REG;
			}
			else{
			type=modecheck(argv[1][1],type);
			}
			openfile(argv[4],type,argv[3],1,0,type1);
		}
		if(argc>5){
			flag=1;
			i=4;
			
			if(strcmp(argv[1],"-n")==0){
				type1=LINENUMBER;
				type=REG;
			}
			else{
			type=modecheck(argv[1][1],type);
			}
			while(i<argc){
				
				openfile(argv[i],type,argv[3],flag,0,type1);
				i++;							
			}
		}
	}
	else if(argv[2][0]=='-' && argv[2][1]=='h'){
		int type1=0;
		if(argc==5){
			//printf("hi");
			if(strcmp(argv[1],"-n")==0){
				type1=LINENUMBER;
				type=REG;
			}
			else{
			type=modecheck(argv[1][1],type);
			}
			openfile(argv[4],type,argv[3],0,0,type1);
		}
		if(argc>5){
			flag=0;
			i=4;
			
			if(strcmp(argv[1],"-n")==0){
				type1=LINENUMBER;
				type=REG;
			}
			else{
			type=modecheck(argv[1][1],type);
			}
			while(i<argc){
				
				openfile(argv[i],type,argv[3],flag,0,type1);
				i++;							
			}
		}
	}
	
	else if(((strcmp(argv[1],"-n")==0) && argv[2][0]=='-')||((strcmp(argv[2],"-n")==0) && argv[1][0]=='-')){
		int type1=LINENUMBER;
		if(strcmp(argv[2],"-h")==0){
			//printf("hi");
			if(argc==5){			
				if(strcmp(argv[1],"-n")==0){
					
					openfile(argv[5],REG,argv[3],0,0,type1);
				}
				
			}
			if(argc>5){
				i=4;
				while(i<argc){
					if(strcmp(argv[1],"-n")==0){
						openfile(argv[i],REG,argv[3],0,0,type1);
					}
					i++;
				}
			}
		}
		
		if(strcmp(argv[3],"-h")==0){
			if(argc==6){			
				if(strcmp(argv[1],"-n")==0){
					type=modecheck(argv[2][1],type);
					openfile(argv[5],type,argv[4],0,0,type1);
				}
				else if(strcmp(argv[2],"-n")==0){
					type=modecheck(argv[1][1],type);
					openfile(argv[5],type,argv[4],0,0,type1);
				}
			}
		if(argc>6){
				i=5;
				while(i<argc){
					if(strcmp(argv[1],"-n")==0){
						type=modecheck(argv[2][1],type);
						openfile(argv[i],type,argv[4],0,0,type1);
					}
					else if(strcmp(argv[2],"-n")==0){
						type=modecheck(argv[1][1],type);
						openfile(argv[i],type,argv[4],0,0,type1);
					}
					i++;
				}
			}
		}
		else if(strcmp(argv[3],"-H")==0){
			if(argc==6){
				if(strcmp(argv[1],"-n")==0){
					type=modecheck(argv[2][1],type);
					openfile(argv[5],type,argv[4],1,0,type1);
				}
				else if(strcmp(argv[2],"-n")==0){
					type=modecheck(argv[1][1],type);
					openfile(argv[5],type,argv[4],1,0,type1);
				}
			}
		else if(argc>6){
				i=5;
				while(i<argc){
					if(strcmp(argv[1],"-n")==0){
						type=modecheck(argv[2][1],type);
						openfile(argv[i],type,argv[4],1,0,type1);
					}
					else if(strcmp(argv[2],"-n")==0){
						type=modecheck(argv[1][1],type);
						openfile(argv[i],type,argv[4],1,0,type1);
					}
					i++;
					
				}
			} 
			
			}
		if (argc==5){
			//printf("HI");
			flag=0;
			if(strcmp(argv[1],"-n")==0){
				type=modecheck(argv[2][1],type);
				openfile(argv[4],type,argv[3],0,0,type1);
			}
			else if(strcmp(argv[2],"-n")==0){
				type=modecheck(argv[1][1],type);
				openfile(argv[4],type,argv[3],0,0,type1);
			}
		}
			if(argc>5 && (strcmp(argv[3],"-h")!=0) && (strcmp(argv[3],"-H")!=0)){
				flag =1;
				i=4;
				while(i<argc){
					if(strcmp(argv[1],"-n")==0){
						type=modecheck(argv[2][1],type);
					}
					else if(strcmp(argv[2],"-n")==0){
						type=modecheck(argv[1][1],type);
					}
					openfile(argv[i],type,argv[3],flag,0,type1);
					i++;
				}
			}
	}
		else if(strcmp(argv[1],"-n")==0 && (strcmp(argv[3],"-h")!=0)){
			int type1=LINENUMBER;
			if (argc==4){
				flag=0;
				i=3;
				type=REG;
				openfile(argv[i],type,argv[2],0,0,type1);
			}
			if (argc>4){
				flag =1;
				i=3;
				type=REG;	
				while(i<argc){
					openfile(argv[i],type,argv[2],flag,0,type1);
					i++;
				}
			}
		}
	else if((strcmp(argv[1],"-ci")==0)|| (strcmp(argv[1],"-cv")==0)){
		//printf("9");
		int type1;
		if(argv[1][2]=='i'){
				//printf("hello");
				type1=COUNTINSENSITIVE;
				type=INSENSITIVE;
			}
		else if( argv[1][2]=='v'){
				//printf("hello");
				type1=COUNTUNMATCH;
				type=UNMATCH;
			}
		else{
				type1=COUNTWHOLEWORDS;
				type=WHOLEWORDS;
		}
		if (argc==4){
			openfile(argv[3],type, argv[2],0,num,type1);
		}
		else if(argc>4){
			i=3;
			while(i<argc){
				openfile(argv[i],type,argv[2],1,num,type1);
				i++;
			}
		}
	}
	else if(strcmp(argv[1],"-vi")==0||strcmp(argv[1],"-cvi")==0){
		//printf("10");
		type=UNMATCH;
		int type1=INSENSITIVE;
		if(argv[1][1]=='c'){
				num=1;
			}
		if (argc==4){			
			openfile(argv[3],type, argv[2],0,num,type1);
		}
		else if(argc>4){
			flag=1;
			i=3;
			while(i<argc){
				openfile(argv[i],type,argv[2],flag,num,type1);
				i++;
			}
		}
	}
	else if(strcmp(argv[1],"-cvw")==0){
		//printf("10");
		type=UNMATCH;
		int type1=WHOLEWORDS;
		if(argv[1][1]=='c'){
				num=1;
			}
		if (argc==4){			
			openfile(argv[3],type, argv[2],0,num,type1);
		}
		else if(argc>4){
			flag=1;
			i=3;
			while(i<argc){
				openfile(argv[i],type,argv[2],flag,num,type1);
				i++;
			}
		}
	}
	else if(strcmp(argv[1],"-iw")==0){
		type=CASEINSENSITIVEWHOLE;
		if (argc==4){
			openfile(argv[3],type, argv[2],0,0,0);
		}
		else if(argc>4){
			i=3;
			while(i<argc){
				openfile(argv[i],type,argv[2],1,0,0);
				i++;
			}
		}
	}
	else if((strcmp(argv[1],"-r")==0) || (strcmp(argv[1],"-l")==0)){
		if(argv[2][0]=='-'){
		
		type=modecheck(argv[2][1],type);
		recursion( type,argv[3],".",0);
     		}
		else{
			type=modecheck(argv[1][1],type);
			recursion( type,argv[2],".",0);
		}		
	}

	}
}								  
int openfile( char *filename,int type,char *pattern,int flag,int num,int type1){
	    int j=0,k=0,l=0,m=0,n=0,z=0,f=0;
	    char ch;
	    line l1;
	    init(&l1);
	    FILE * fp;
	    int boolean=0,count=0,flag1=0,boolean1=0;
	    fp=fopen(filename,"r+");
	    if (fp==NULL){
		perror("Invalid file argument");
		exit(0); 
    		}
	   else{
		while((ch = getc(fp)) != EOF ){
				if (ch!='\n' && ch !='\0'){
					insert(&l1,ch);
				}
				else{
					k++;
					if (type==REG || type==RECURSION || type==FILENAME){
						boolean=matchpattern(l1,pattern);
						if(boolean){	
							if(flag){					
								if(type==FILENAME && num ==1){
									printf( PURPLE "%s \n" RESET,filename);
									num++;
									continue;
								}
								if(type!=FILENAME && flag==1)
									printf( PURPLE "%s:" RESET,filename);
							}
							if(type1==LINENUMBER)
								printf( CYAN "%d :" RESET , k);
							
							if(type!=FILENAME)
								traverse(l1); 
						}	
				}
					else if (type==UNMATCH && type1!=INSENSITIVE && type1!=WHOLEWORDS){
							boolean=donotmatchpattern( l1, pattern);
							if(boolean){
								if(type1==COUNTUNMATCH)			
									m++;			
								if(flag && type1!=COUNTUNMATCH){					
									printf(PURPLE "%s :" RESET,filename);
								}
								if(type1==LINENUMBER)
									printf( CYAN "%d :" RESET , k);
								if(type1!=COUNTUNMATCH)
									traverse(l1); 
							}
						}
						else if(type==WHOLEWORDS){
							boolean=matchwholewords( l1, pattern);
							if(boolean){		
								if(type1==COUNTWHOLEWORDS)
									f++;				
								if(flag && type1!=COUNTWHOLEWORDS){					
									printf(PURPLE "%s :" RESET,filename);
								}
								if(type1==LINENUMBER)
									printf( CYAN "%d :" RESET , k);
								if(type1!=COUNTWHOLEWORDS)
									traverse(l1); 
							}
						}
						else if (type==COUNT){
							boolean=matchpattern(l1,pattern);
							if(boolean){
								count=count+1;
							}
						}
						else if(type==INSENSITIVE){	
							boolean=caseinsensitive(l1,pattern);
							if(boolean){
								l++;
								if(flag && type1!=COUNTINSENSITIVE){					
									printf(PURPLE "%s :" RESET,filename);
								}
								if(type1==LINENUMBER)
						
									printf( CYAN "%d :" RESET , k);
								if(type1!=COUNTINSENSITIVE)
									traverse(l1);
							}
						}
						else if(type==MAXIMUM){
							//printf("%d",num);
							boolean=matchpattern(l1,pattern);
							if(boolean && j<num && j!=num){
								if(flag){					
									printf(PURPLE "%s :" RESET,filename);
								}
								if(type1==LINENUMBER)
									printf( CYAN "%d :" RESET , k);
								//printf("%d",j);
								traverse(l1);
							}
							if(boolean){
								//printf("%d",j);
								j++;
							}
						}
						else if(type==UNMATCH && type1== INSENSITIVE){
							
							boolean1=caseinsensitive(l1,pattern);
							if(!boolean1 ){
								if(num==1)
									n++;
								if(flag && num!=1){					
									printf(PURPLE "%s :" RESET,filename);
								}
								if(num!=1)
								traverse(l1);
							}
						}
						else if(type==UNMATCH && type1==WHOLEWORDS){
							//printf("--------------------");
							boolean1=matchwholewords(l1,pattern);
							if(!boolean1){
								if(num==1)
									z++;
								if(flag && num!=1){					
									printf(PURPLE "%s :" RESET,filename);
								}
								if(num!=1)
								traverse(l1);
							}
						}
						else if(type==CASEINSENSITIVEWHOLE){
							boolean=caseinsensitiveandwholeword(l1,pattern);
							if(boolean){	
								if(flag){					
									
										printf( PURPLE "%s:" RESET,filename);
								}
								traverse(l1); 
							}
						}	
					destroyLine(&l1);
					init(&l1);
				}
				}
				fclose(fp);
  	if(type==COUNT && flag==0)
			printf("%d\n",count);
	else if(type==COUNT && flag==1){
			printf( PURPLE "%s:  " RESET,filename);
			printf("%d \n",count);
	}
	else if((type1==COUNTINSENSITIVE && flag==0))
			printf("%d\n",l);
	else if((type1==COUNTWHOLEWORDS && flag==0))
			printf("%d\n",f);
	else if((type1==COUNTUNMATCH && flag==0))
			printf("%d\n",m);
	else if((type1==COUNTINSENSITIVE && flag==1)){
			printf( PURPLE "%s:  " RESET,filename);
			printf("%d \n",l);
	}	
	else if((type1==COUNTUNMATCH && flag==1)){
		printf( PURPLE "%s:  " RESET,filename);
		printf("%d \n",m);	
	}
	else if((type1==COUNTWHOLEWORDS && flag==1)){
			printf( PURPLE "%s:  " RESET,filename);
			printf("%d \n",f);
	}	
	else if(type1==INSENSITIVE && num==1 && flag==1){
		//printf("hi");
		printf( PURPLE "%s:  " RESET,filename);
		printf("%d \n",n);
	}
	else if(type1==INSENSITIVE && num==1 && flag==0)
		printf("%d \n",n);
	else if(type1==WHOLEWORDS && num==1 && flag==1){
		//printf("hi");
		printf( PURPLE "%s:  " RESET,filename);
		printf("%d \n",z);
	}
	else if(type1==WHOLEWORDS && num==1 && flag==0)
		printf("%d \n",z);
	if(type1==FILENAME)
			printf( CYAN "%d :" RESET , k);
	}
	return 0;
}
void recursion(int type,char *pattern,char *name, int indent){    
   char path1[1024];
   int static flag1;
    DIR *dir;
    struct dirent *entry;
   if (!(dir = opendir(name)))
        return;
   while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            char path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
           snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
	   strcpy(path1,path);
	   flag1=1;
           recursion(type,pattern,path,indent + 2);
        } else {
		if(strcmp(entry->d_name,"grep")!=0){
		    if(flag1!=1){
			openfile(entry->d_name,type,pattern, 1,1,0);
		    }
		    else{
			snprintf(path1, sizeof(path1), "%s/%s", name, entry->d_name);
			
			openfile(path1,type,pattern, 1,1,0);		
		  }
		}
        }
   }
    closedir(dir);
}
int modecheck(char  mode,int type){
		if(mode=='v'){
			type=UNMATCH;
		}
		else if(mode=='w'){
			type=WHOLEWORDS;
		}
		else if (mode=='c'){
			type=COUNT;
		}
		else if(mode=='i'){
			type=INSENSITIVE;
		}
		else if(mode=='m'){
			type=MAXIMUM;
		}	
		else if(mode=='r'){
			type=RECURSION;
		}
		else if(mode=='l'){
			type=FILENAME;
		}
		else if(mode=='e'){
			type=REG;
		}
		else if(mode=='n'){
			type=LINENUMBER;
		}
		return type;
}
