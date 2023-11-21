#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#define READ_END 0
#define WRITE_END 1
#define FIFO "task4_fifo"

int main()
{
	umask(0000);
	int ffd;
	ffd = mkfifo("/tmp/task4_fifo", 0777);

	int data_processed;
	int fd;
	const char some_data[] = "123";
	char *buffer = (char*)calloc(strlen(some_data)+1, sizeof(char));

	buffer[strlen(some_data)] = '\0';

	// open for read and write fifo
	if((fd=open("/tmp/task4_fifo", O_RDWR))<0){
		printf("Error opening fifo\n");
		exit(1);
	}

	data_processed = write(fd, some_data, strlen(some_data));
	printf("Wrote %d bytes\n", data_processed);

	// open read only fifo
	data_processed = read(fd, buffer, data_processed);
	printf("Read %d bytes: %s\n", data_processed, buffer);
	// close fifo
	close(fd);

	// free the memory
	free(buffer);

	//exit
	exit(EXIT_SUCCESS);
}
