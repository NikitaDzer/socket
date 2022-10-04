#include <stdio.h>
#include <stdbool.h>
#include <errno.h>

#include <fcntl.h>
#include <unistd.h>

#include "socket.h"


int main( const int argc, const char *argv[])
{
	const int CORRECT_ARGC = 3;

	if ( argc != CORRECT_ARGC)
	{
		return 1;
	}

	Socket *const socket = create_socket();
	if ( socket == NULL )
	{
		return 1;
	}

	const pid_t pid = fork();
	if ( pid == -1 )
	{
		release_socket( socket);
		
		return 1;	
	}

	if ( pid == 0 )
	{
		configure_socket( socket, DIRECTOR_BACKWARD);

		while ( true )
		{
			 read_socket( socket, DIRECTION_FORWARD);
			write_socket( socket, DIRECTION_BACKWARD);
		
			if ( (ssize_t)socket->length <= 0 )
				break;
		}

		return 0;
	}
	else
	{
		configure_socket( socket, DIRECTOR_FORWARD);

		const int fd_input  = open( argv[1], O_RDONLY | 0666);
		const int fd_output = open( argv[2], O_RDWR   | 0666);

		while ( true )
		{
			socket->length = read( fd_input, socket->buffer, SOCKET_BUFFER_SIZE);

			if ( (ssize_t)socket->length <= 0 )
				break;

			write_socket( socket, DIRECTION_FORWARD);
			 read_socket( socket, DIRECTION_BACKWARD);

			write( fd_output, socket->buffer, socket->length);	
		}

		release_socket( socket);

		close( fd_input);
		close( fd_output);

		return 0;
	}
}

