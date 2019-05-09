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

			/*create directory  */
			if(strcmp(com,"mkdir") == 0)
				mkdir(pathname, S_IRWXG | S_IROTH | S_IXOTH);
			/* delete directory */
			if(strcmp(com,"rmdir") == 0)
				rmdir(pathname);
			/* change  directory path */
			if(strcmp(com,"chdir") == 0)
				chdir(pathname);
			/* get current working directory */
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
				FILE *fp;
				fp = fopen(pathname,"w");
			}
			/* remove file */
			if(strcmp(com,"rm") == 0)
			{
				remove(pathname);
            }
	}
}

void printFirst(const char *argv[], char line[MAXLINE]) {
    	char commandChoice[MAXLINE+1]; //will contain user input
	char numBytes[MAXLINE+1]; //will hold user inputted number as a char
	int numberOfBytesToPrint; //will hold user inputted number as int
	FILE *readFile; //will hold the opened file
	char holdFile[MAXLINE+1]; //will hold contents of file
	int fileSize; //will hold size of file being read
	readFile = fopen(argv[1], "r"); //opens file
        if (readFile == NULL) { //checks that the file exists 
		printf("%s does not exist.\n", argv[1]); 
		return;
        }
        else { //if the file exists
        	fread(holdFile, 1, MAXLINE+1, readFile); //store file in holdFile
		if (line[1] == ' ') { //checks that there is a space between command and number
			//stores the command and number
                	sscanf(line, "%s %s", commandChoice, numBytes);
       			if (!(isdigit(numBytes[0]))) { //validates that numBytes is an integer
                		printf("Not numeric: %s\n", numBytes);
                	}
                	else {
                		numberOfBytesToPrint = atoi(numBytes); //changes numBytes to an int
                        	fseek(readFile, 0, SEEK_END); //finds the end of the file
                        	fileSize = ftell(readFile); //sets fileSize to the size of the file
                        	fseek(readFile, 0, SEEK_SET); //goes back to the beginning of file
                        	if (fileSize < numberOfBytesToPrint) { 
                        		printf("File %s is only %d bytes, not %d\n", argv[1], fileSize, numberOfBytesToPrint);
                        	} //prints error message if file is smaller than number of bytes to print
                        	else {
                        		for (int i = 0; i < numberOfBytesToPrint; i++) { 
                        	        	printf("%c", holdFile[i]);
                        	        } //prints the requested number of characters
                        	        printf("\n");
                        	}  
			}
		}
		else { //if there is no space after command
			printf("Invalid input\n");
		}
	}
	fclose(readFile); //closes the file
}

void printLast(const char *argv[], char line[MAXLINE]) {
	char commandChoice[MAXLINE+1]; //will contain user input
        char numBytes[MAXLINE+1]; //will hold user inputted number as a char
        int numberOfBytesToPrint; //will hold user inputted number as int
        FILE *readFile; //will hold the opened file
        char holdFile[MAXLINE+1]; //will hold contents of file
        int fileSize; //will hold size of file being read
        readFile = fopen(argv[1], "r"); //opens file
        if (readFile == NULL) { //checks that the file exists
                printf("%s does not exist.\n", argv[1]);
        }
        else { //if the file exists
                fread(holdFile, 1, MAXLINE+1, readFile); //reads file into holdFile
                if (line[1] == ' ') { //checks there is a space after command
                        sscanf(line, "%s %s", commandChoice, numBytes); //reads user input
                        if (!(isdigit(numBytes[0]))) { 
                                printf("Not numeric: %s\n", numBytes);
                        } //prints error message if user didn't input an integer
                        else { //if user did input an integer
                                numberOfBytesToPrint = atoi(numBytes); //converts numBytes to an integer
                                fseek(readFile, 0, SEEK_END); //goes to end of file
                                fileSize = ftell(readFile); //gets file size
                                fseek(readFile, 0, SEEK_SET); //goes to beginning of file
                                if (fileSize < numberOfBytesToPrint) {
                                        printf("File %s is not long enough\n", argv[1]);
                                } //prints error message if file is smaller than number of bytes to print
                                else { //if file is big enough
                                        for (int i = 0; i < numberOfBytesToPrint; i++) {
                                                printf("%c", holdFile[i+fileSize-numberOfBytesToPrint]);
                                        } //prints requested characters
                                        printf("\n");
                                }
                        }
                }
                else { //if there wasn't a space after the command
                        printf("Invalid input\n");
                }
        }
        fclose(readFile); //closes the file
} 

void printUI(const char *argv[], char line[MAXLINE]) {
	char commandChoice[MAXLINE+1]; //will contain user input
        char numBytes[MAXLINE+1]; //will hold user inputted number as a char
        int numberOfBytesToPrint; //will hold user inputted number as int
        FILE *readFile; //will hold the opened file
        char holdFile[MAXLINE+1]; //will hold contents of file
        int fileSize; //will hold size of file being read
        readFile = fopen(argv[1], "r"); //opens file
        if (readFile == NULL) {
                printf("%s does not exist.\n", argv[1]);
        } //checks that the file exists
        else { //if the file exists
                fread(holdFile, 1, MAXLINE+1, readFile); //reads the file
                if (line[1] == ' ') { //checks that there is a space after command
                        sscanf(line, "%s %s", commandChoice, numBytes); //reads user input
                        if (!(isdigit(numBytes[0]))) { //checks that user inputted an integer
                                printf("Not numeric: %s\n", numBytes);
                        }
                        else { //if user inputted an integer
                                numberOfBytesToPrint = atoi(numBytes); //convers numBytes to an integer
                                fseek(readFile, 0, SEEK_END); //goes to end of file
                                fileSize = ftell(readFile); //stores file size
                                fseek(readFile, 0, SEEK_SET); //goes to beginning of file
				//fileSize/4 is the most bytes possible to print
                                if ((fileSize/4) < numberOfBytesToPrint) { 
                                	printf("File %s is not long enough\n", argv[1]);
				} //prints error message if file is not long enough
				 else { //if file is long enough
					/* Professor Paul Linton helped me with the next part of this 
					function. I was struggling on this section of the project and 
					discussed with me the best ways to go about it. He also helped 
					me understand the XOR part of the next function */
					union {
						unsigned char tempChar[4];
						unsigned int result;
					}charToInt; //tempChar and result share the same memory
                                        for (int i = 0; i < numberOfBytesToPrint*4; i+=4) {
                                                charToInt.tempChar[0] = holdFile[i];
						charToInt.tempChar[1] = holdFile[i+1];
						charToInt.tempChar[2] = holdFile[i+2];
						charToInt.tempChar[3] = holdFile[i+3];
						printf("%d ", charToInt.result);
                                        } //fills tempChar with 4 bytes from file and prints them 
					  // as an unsigned integer
                                        printf("\n");
                                }
                        }
                }
                else { //if there is no space after command
                        printf("Invalid input\n");
                }
        }
        fclose(readFile); //closes file
}

void printXOR(const char *argv[], char line[MAXLINE]) {
        char commandChoice[MAXLINE+1]; //will contain user input
        char numBytes[MAXLINE+1]; //will hold user inputted number as a char
        int numberOfBytesToPrint; //will hold user inputted number as int
        FILE *readFile; //will hold the opened file
        char holdFile[MAXLINE+1]; //will hold contents of file
        int fileSize; //will hold size of file being read
        readFile = fopen(argv[1], "r"); //opens file
        if (readFile == NULL) { 
                printf("%s does not exist.\n", argv[1]);
        } //prints error message if file does not exist
        else {
                fread(holdFile, 1, MAXLINE+1, readFile); //reads in the file
                if (line[1] == ' ') { //verifies there is a space after command
                        sscanf(line, "%s %s", commandChoice, numBytes); //stores user input
                        if (!(isdigit(numBytes[0]))) {
                                printf("Not numeric: %s\n", numBytes);
                        } //prints error message if user doesn't enter integer
                        else { //if user does enter an integer
                                numberOfBytesToPrint = atoi(numBytes); //convers numBytes to an integer
                                fseek(readFile, 0, SEEK_END); //goes to end of file
                                fileSize = ftell(readFile); //stores file size
                                fseek(readFile, 0, SEEK_SET); //goes to beginning of file
                                if (fileSize < numberOfBytesToPrint) {
                                        printf("File %s is not long enough\n", argv[1]);
                                } //checks if the file is smaller than number of bytes to print
                                else { //if file is larger
					char tempChar = holdFile[0]; 
					if (numberOfBytesToPrint == 0) {
						printf("%03o\n", 0);
					} //prints 000 if user enters 0
					else { //user wants to print more than 0 bytes
                                        	for (int i = 0; i < numberOfBytesToPrint-1; i++) {
                                               		tempChar = tempChar^holdFile[i+1];
                                        	} //XOR's the bytes together into tempChar
                                        	printf("%03o\n", tempChar); //prints tempChar
					}
                                }
                        }
                }
                else { //if there is no space afte case 's': command(); break;
                        printf("Invalid input\n"); case 's': command(); break;
                }
        }
        fclose(readFile); //closes the file
}

void handleCommands(const char *argv[]) {
	char line[MAXLINE];
	while (1) { // each command
		(void) fgets(line, MAXLINE, stdin);
		switch (line[0]) {
                        case 's': command(); break;
                        case 'q': exit(0); break;
			case 'e': printf("%s\n", argv[0]); break;
			case 'p': printFirst(argv, line); break;
			case 'L': printLast(argv, line); break;
			case 'i': printUI(argv, line); break;
			case 'x': printXOR(argv, line); break;
                        default: printf("Unrecognized command %s", line); //if the command isn't listed above

		} // switch line[0]
	} // each command
} // handleCommands

int main(int argc, const char *argv[]) {
	handleCommands(argv);
} // main
