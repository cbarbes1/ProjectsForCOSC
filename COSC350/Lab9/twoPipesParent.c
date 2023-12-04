#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#define WRITE_END 1
#define READ_END 0

int main()
{
	int data_processed;
	int file_pipes[2];
	int oth_pipes[2];
	const char some_data[] = "Hi there, Kiddo";
	char buffer[BUFSIZ + 1], buf1[BUFSIZ+1], buf2[BUFSIZ+1], buf3[BUFSIZ+1];
	pid_t fork_result;

	memset(buffer, '\0', sizeof(buffer));
	memset(buf1, '\0', sizeof(buf1));
	memset(buf2, '\0', sizeof(buf2));
	memset(buf3, '\0', sizeof(buf2));

	if (pipe(file_pipes) == 0 && pipe(oth_pipes)== 0) {
		fork_result = fork();
		if (fork_result == (pid_t)-1) {
			fprintf(stderr, "Fork failure");
			exit(EXIT_FAILURE);
		}

		if (fork_result == 0) {
			sprintf(buffer, "%d", file_pipes[READ_END]);
			sprintf(buf1, "%d", file_pipes[WRITE_END]);
			sprintf(buf2, "%d", oth_pipes[READ_END]);
			sprintf(buf3, "%d", oth_pipes[WRITE_END]);
			
			(void)execl("twoPipesChild", "twoPipesChild", buffer, buf1, buf2, buf3, (char *)0);
			exit(EXIT_FAILURE);
		}
		else {
			char buff[BUFSIZ];
			close(file_pipes[READ_END]);
			close(oth_pipes[WRITE_END]);
			data_processed = write(file_pipes[1], some_data, strlen(some_data));
			printf("%d - wrote %d bytes: %s\n", getpid(), data_processed, some_data);
			
			data_processed = read(oth_pipes[READ_END], buff, BUFSIZ);
			printf("%d - read %d bytes: %s\n", getpid(), data_processed, buff);	
		}
	}
	exit(EXIT_SUCCESS);
}
