#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int fd;

void Stop (int signalno)
{
		close(fd);
        exit(0);
}

int main (int argc, char *argv[])
{
	printf("%d\n", getpid());

	struct sockaddr_in local;
	inet_aton("127.0.0.1", &local.sin_addr);
	local.sin_port = htons(3000);
	local.sin_family = AF_INET;

	int fd = socket(AF_INET, SOCK_STREAM, 0);
	
	if(fd < 0)
	{
		fprintf(stderr, "Error of Socket\n");
		return -1;
	}
	if(bind(fd, (struct sockaddr*)&loc, sizeof(loc)) < 0)
	{
		fprintf(stderr, "Error of bind()\n");
		return -1;
	}

	listen (fd, 10);
	char buffre[4096];

	signal(SIGTERM, Stop);
	
	while(1)
	{
		given = accept (fd, NULL, NULL);
		if(read(given, buffer, 4096))
		{
			output = fopen("storage", "a+");
			printf("%s\n", buffer);
			fprintf(output, "%s\n", buffer);
			
			fclose(output);
		}
	}
	return 0;
}
