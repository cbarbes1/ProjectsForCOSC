#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define READ_END 0
#define WRITE_END 1

int main(int argc, char *argv[])
{
	int data_processed;
	char buffer[BUFSIZ + 1];
	char some_data[] = "Hi, Mom";
	int fd[2], fd2[2];

	memset(buffer, '\0', sizeof(buffer));
	sscanf(argv[1], "%d", &fd[READ_END]);
	sscanf(argv[2], "%d", &fd[WRITE_END]);
	sscanf(argv[3], "%d", &fd2[READ_END]);
	sscanf(argv[4], "%d", &fd2[WRITE_END]);

	close(fd[WRITE_END]);
	close(fd2[READ_END]);

	data_processed = read(fd[READ_END], buffer, BUFSIZ);
	printf("%d - read %d bytes: %s\n", getpid(), data_processed, buffer);

	data_processed = write(fd2[WRITE_END], some_data, strlen(some_data));
	printf("%d - wrote %d bytes: %s\n", getpid(), data_processed);

	exit(EXIT_SUCCESS);
}
