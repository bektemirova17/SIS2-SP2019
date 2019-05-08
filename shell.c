#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>

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
int main(void) {
	command();
	return 0;
}

