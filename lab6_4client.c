#include <netdb.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include <arpa/inet.h>
#include <string.h>

int main (int argc, char* argv[])
{
		if (argc < 2){
			puts("add DNS to programm call\n");
			return -1;
		}
		
        struct hostent *h;
        h=gethostbyname (argv[1]);

        if (NULL == h) {
                printf("Error of hostent\n");
                return -1;
        }

        int fd;
        char buffer[4096];
        memset(buffer, 0, 4096);
        char *fifo = "buffer_channel_4";

        mkfifo (fifo, 0666);

        if ((fd = open(fifo, O_WRONLY)) < 0) {
                fprintf (stderr, "Error of O_WRONLY\n");
                return -1;
        }

        printf ("Send...\n");

        int i=0;
        while (NULL != h->h_addr_list[i]){
                struct in_addr* tmp = (struct in_addr*) h->h_addr_list[i];
                strcat (buffer, inet_ntoa(*tmp));
                i++;
        }
        
        write (fd, buffer, 4096);

        close (fd);
        unlink (fifo);
        return 0;
}

