#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> 
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>

#define MAXLINE 100

uid_t getuid_byName(const char *name)
{
    if(name) {
        struct passwd *pwd = getpwnam(name);
        if(pwd) return pwd->pw_uid;
    }
  return -1;
}

void p_print(const char *argv[], char line[MAXLINE]) {
    	char commands[MAXLINE+1]; 
	char numBytes[MAXLINE+1]; 
	int numBytesToPrint; 
	FILE *fp; 
	char holdFile[MAXLINE+1];
	int fileSize; 
	fp = fopen(argv[1], "r"); 
        if (fp == NULL) { 
		printf("%s does not exist.\n", argv[1]); 
		return;
        }
        else { 
        	fread(holdFile, 1, MAXLINE+1, fp);
		if (line[1] == ' ') { 
                	sscanf(line, "%s %s", commands, numBytes);
       			if (!(isdigit(numBytes[0]))) { 
                		printf("Not numeric: %s\n", numBytes);
                	}
                	else {
                		numBytesToPrint = atoi(numBytes); 
                        	fseek(fp, 0, SEEK_END); 
                        	fileSize = ftell(fp); 
                        	fseek(fp, 0, SEEK_SET); 
                        	if (fileSize < numBytesToPrint) { 
                        		printf("File %s is only %d bytes, not %d\n", argv[1], fileSize, numBytesToPrint);
                        	} 
                        	else {
                        		for (int i = 0; i < numBytesToPrint; i++) { 
                        	        	printf("%c", holdFile[i]);
                        	        } 
                        	        printf("\n");
                        	}  
			}
		}
		else {
			printf("Invalid input\n");
		}
	}
	fclose(fp); 
}

void l_print(const char *argv[], char line[MAXLINE]) {
	char commands[MAXLINE+1]; 
        char numBytes[MAXLINE+1]; 
        int numBytesToPrint; 
        FILE *fp; 
        char holdFile[MAXLINE+1]; 
        int fileSize; 
        fp = fopen(argv[1], "r"); 
        if (fp == NULL) { 
                printf("%s does not exist.\n", argv[1]);
        }
        else { 
                fread(holdFile, 1, MAXLINE+1, fp); 
                if (line[1] == ' ') { 
                        sscanf(line, "%s %s", commands, numBytes); 
                        if (!(isdigit(numBytes[0]))) { 
                                printf("Not numeric: %s\n", numBytes);
                        } 
                        else { 
                                numBytesToPrint = atoi(numBytes); 
                                fseek(fp, 0, SEEK_END); 
                                fileSize = ftell(fp); 
                                fseek(fp, 0, SEEK_SET); 
                                if (fileSize < numBytesToPrint) {
                                        printf("File %s is not long enough\n", argv[1]);
                                } 
                                else {
                                        for (int i = 0; i < numBytesToPrint; i++) {
                                                printf("%c", holdFile[i+fileSize-numBytesToPrint]);
                                        } 
                                        printf("\n");
                                }
                        }
                }
                else { 
                        printf("Invalid input\n");
                }
        }
        fclose(fp); 
} 

void i_print(const char *argv[], char line[MAXLINE]) {
	char commands[MAXLINE+1]; 
        char numBytes[MAXLINE+1];
        int numBytesToPrint; 
        FILE *fp; 
        char holdFile[MAXLINE+1]; 
        int fileSize; 
        fp = fopen(argv[1], "r"); 
        if (fp == NULL) {
                printf("%s does not exist.\n", argv[1]);
        } 
        else { 
                fread(holdFile, 1, MAXLINE+1, fp); 
                if (line[1] == ' ') { 
                        sscanf(line, "%s %s", commands, numBytes); 
                        if (!(isdigit(numBytes[0]))) { 
                                printf("Not numeric: %s\n", numBytes);
                        }
                        else { 
                                numBytesToPrint = atoi(numBytes); 
                                fseek(fp, 0, SEEK_END); 
                                fileSize = ftell(fp); 
                                fseek(fp, 0, SEEK_SET); 
                                if ((fileSize/4) < numBytesToPrint) { 
                                	printf("File %s is not long enough\n", argv[1]);
				} 
				 else { 
					union {
						unsigned char tempChar[4];
						unsigned int result;
					}charToInt; 
                                        for (int i = 0; i < numBytesToPrint*4; i+=4) {
                                                charToInt.tempChar[0] = holdFile[i];
						charToInt.tempChar[1] = holdFile[i+1];
						charToInt.tempChar[2] = holdFile[i+2];
						charToInt.tempChar[3] = holdFile[i+3];
						printf("%d ", charToInt.result);
                                        } 
                                        printf("\n");
                                }
                        }
                }
                else { 
                        printf("Invalid input\n");
                }
        }
        fclose(fp); 
}

void x_print(const char *argv[], char line[MAXLINE]) {
        char commands[MAXLINE+1]; 
        char numBytes[MAXLINE+1]; 
        int numBytesToPrint; 
        FILE *fp; 
        char holdFile[MAXLINE+1]; 
        int fileSize; 
        fp = fopen(argv[1], "r"); 
        if (fp == NULL) { 
                printf("%s does not exist.\n", argv[1]);
        } 
        else {
                fread(holdFile, 1, MAXLINE+1, fp); 
                if (line[1] == ' ') { 
                        sscanf(line, "%s %s", commands, numBytes); 
                        if (!(isdigit(numBytes[0]))) {
                                printf("Not numeric: %s\n", numBytes);
                        } 
                        else { 
                                numBytesToPrint = atoi(numBytes);
                                fseek(fp, 0, SEEK_END);
                                fileSize = ftell(fp); 
                                fseek(fp, 0, SEEK_SET); 
                                if (fileSize < numBytesToPrint) {
                                        printf("File %s is not long enough\n", argv[1]);
                                } 
                                else { 
					char tempChar = holdFile[0]; 
					if (numBytesToPrint == 0) {
						printf("%03o\n", 0);
					} 
					else { 
                                        	for (int i = 0; i < numBytesToPrint-1; i++) {
                                               		tempChar = tempChar^holdFile[i+1];
                                        	} 
                                        	printf("%03o\n", tempChar); 
					}
                                }
                        }
                }
                else { 
                        printf("Invalid input\n");
                }
        }
        fclose(fp);
}

void command(){
	char com[30];
	char pathname[30];
	char username[30];
	char cwd[1024];
	struct dirent *pDirent;
	DIR *pDir;

	while(1){
			printf(">");
			scanf("%s",com);
			scanf("%s",pathname);

		
			if(strcmp(com,"mkdir") == 0)
				mkdir(pathname, S_IRWXG | S_IROTH | S_IXOTH);
		
			if(strcmp(com,"rmdir") == 0)
				rmdir(pathname);
		
			if(strcmp(com,"chdir") == 0)
				chdir(pathname);
			
			if(strcmp(com,"pwd") == 0){
				getcwd(cwd, sizeof(cwd));
				printf("Current working dir:%s\n",cwd);
			}
			if(strcmp(com,"ls") == 0)
			{
				pDir = opendir(pathname);
				while((pDirent = readdir(pDir)) != NULL)
				{
					printf("[%s]\n", pDirent->d_name);
				}
			}
			if (strcmp(com, "chown") == 0)
            {
                printf("New user login: ");
                scanf("%s", username);
                uid_t newId = getuid_byName(username);
                if (newId != -1){
                    int status = chown(pathname, newId, -1);
                    /*if (errno == EROFS){
                        printf("erofs");
                    }
                    if (errno == EPERM)
                        printf("eperm");
                    if (errno == EINVAL)
                        printf("einval");
                    if (errno == EACCES)
                        printf("eacces");*/
                    printf("%d, %i\n", status, newId);
                }else{
                    printf("No user %i\n", newId);
                }
            }

			if(strcmp(com,"touch") == 0)
			{
				fopen(pathname,"w");
			}
			if(strcmp(com,"rm") == 0)
			{
				remove(pathname);
            }
	}
}

void handleCommands(const char *argv[]) {
	char line[MAXLINE];
	while (1) { 
		(void) fgets(line, MAXLINE, stdin);
		switch (line[0]) {
			case 'q': exit(0); break;
			case 'e': printf("%s\n", argv[0]); break;
			case 'p': p_print(argv, line); break;
			case 'l': l_print(argv, line); break;
			case 'i': i_print(argv, line); break;
			case 'x': x_print(argv, line); break;
                        case 'm': command(); break;
			default: printf("Unrecognized command %s", line); 

		} 
	} 
} 

int main(int argc, const char *argv[]) {
	handleCommands(argv);
} 
