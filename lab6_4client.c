#include <netdb.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include <arpa/inet.h>
#include <string.h>

int main (int argc, char *argv[])
{
	if(argc < 2)
	{
		fprintf(stderr, "Add DNS\n");
		return -1;
	}

	struct hostent *host;
	host = gethostbyname (argv[1]);
	if(!host)
	{
		fprintf(stderr, "Error of getHostByName\n");
		return -1;
	}

	struct sockaddr_in remoteDB;
	inet_aton("127.0.0.1", &remoteDB.sin_addr);
	remoteDB.sin_port = htons(3000);
	remoteDB.sin_family = AF_INET;

	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if(fd < 0)
	{
		fprintf(stderr, "Error of Socket\n");
		return -1;
	}
	if(connect(fd, (struct sockaddr*)&remoteDB, sizeof(remoteDB)) == -1)
	{
		fprintf(stderr, "Error of Connect\n");
		return -1;
	}
	
	char buffer[4096];
	int i=0;
	memset(buffer, 0, 4096);
	strcat(buffer, argv[1]);

	while(host->h_addr_list[i])
	{
		struct in_addr *tmp = (struct in_addr*) host->h_addr_list[i];
		strcat(buffer, inet_ntoa(*tmp));
		buffer[strlen(buffer)] = '\n';
		i++;
	}
	write(fd, buffer, 4096);
	close(fd);
	return 0;
}

