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

int main (int argc, char* argv[])
{
        printf("%d\n", getpid());

        char buffer[4096];
        char *fifo = "buffer_channel_4";

        mkfifo (fifo, 0666);

        while (1)
        {
                signal (SIGUSR1, Stop);
                fd = open(fifo, O_RDONLY);
                printf("Massage:\n");
                read (fd, &buffer, 4096);
                printf("%s\n", buffer);
        }
		return 0;
}
