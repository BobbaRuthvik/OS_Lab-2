#include<bits/stdc++.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>
#include<errno.h>
extern int errno;
using namespace std;


int getWords(char *base, char target[1024][1024]){
	int n = 0, i, j = 0;
	for(i=0; 1; i++){
		if(base[i] != ' '){
			target[n][j++] = base[i];
		}
		else{
			target[n][j++] = '\0'; //insert NULL
			n++;
			j = 0;
		}
		if(base[i] == '\0')
			break;
	}
	return n;
}

int compare(char a[], char b[]){
	int flag = 0, i = 0;
	while(a[i] != '\0' && b[i] != '\0'){
		if(a[i]!=b[i]){
			flag = 1;
			break;
		}
		i++;
	}
	if(flag==0) return 0;
	else return 1;
}

int main(){
	//char terminal_buffer[100];
	char command[100];
	char *username = getlogin();
	printf("Username: %s\n", username);
	strcpy(command, "groups ");
	int idx = 7;
	
	char pc[1024];
	char words[1024][1024];
	char student[100] = "S";
	char teacher[100] = "F";
	char admin[100] = "A";
	char sheet[100] = "H";
		int ret = 0;
		char cmd1[100];
		sprintf(cmd1, "echo %s | sudo -S chmod 666 marksheet.txt", username);
		ret = system(cmd1);
		if(ret==0)
			printf("Read permission given to marksheet.txt\n");
		else
			printf("Unable to give read permission to marksheet.txt\n");

		int fd2;
		if((fd2 = open("marksheet.txt", O_RDONLY)) == -1){
			printf("Error Number %d\n", errno);
			perror("Couldn't open file marksheet.txt\n");
			exit(1);
		}
		char c;
		int len = 0;
		int line = 0;
		int count_line = 0;
		char score[1024][1024];
		while(read(fd2, &c, 1) == 1){
			if(c == '\n'){
				score[line][len] = '\0';
				count_line++;
				//printf("%s\n", score[line]);
				line++;
				len = 0;
			}
			else{
				score[line][len++] = c;
			}
		}
		if(close(fd2) < 0){
			printf("Error Number %d\n", errno);
			perror("Unable to close file marksheet.txt\n");
			exit(1);
		}
			
			if(compare(username, admin) == 0){
				printf("iam admin\n");
				for(int i=0; i<count_line; i++){
					printf("%s\n", score[i]);
				}
				system("vim marksheet.txt");
				//printf("X: %s\n",score[0][0]);
			}
			else if(compare(username, student)==0){
				printf("Iam student\n");
				printf("X: %s\n", score[0]);
			}
			else if(compare(username, teacher) == 0){
				printf("Iam teacher\n");
				printf("Y: %s\n", score[1]);
			}
			else if(compare(username, sheet)==0){
				printf("Iam in view mode\n");
				printf("X: %s\n", score[0]);
				printf("Y: %s\n", score[1]);
				printf("Z: %s\n", score[2]);
			}
		
		char cmd2[100];	
                sprintf(cmd2, "echo %s | sudo -S chmod 600 marksheet.txt", username);
		ret = system(cmd2);
                if(ret==0)
                	printf("Permissions of read removed from marksheet.txt\n");
                else
                	printf("Unable to remove read permissions to marksheet.txt\n");


	return 0;
}
