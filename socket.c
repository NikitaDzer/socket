#include <stdlib.h>

#include <unistd.h>
#include <fcntl.h>

#include "socket.h"


Socket *create_socket( void)
{
	Socket *const socket = (Socket *)calloc( 1, sizeof(Socket));
	if ( socket == NULL )
	{
		return NULL;
	}

	socket->buffer = (char *)calloc( SOCKET_BUFFER_SIZE, sizeof(char));
	if ( socket->buffer == NULL )
	{
		free( socket);

		return NULL;
	}
	
	pipe( socket->forward);
	pipe( socket->backward);

	return socket;
}

void release_socket( Socket *const socket)
{
	close( socket->forward[0]);
	close( socket->forward[1]);

	close( socket->backward[0]);
	close( socket->backward[1]);

	free( socket->buffer);
	free( socket);
}

ssize_t write_socket( Socket *const socket, const SocketDirection direction)
{
	int fd = 0;

	switch ( direction )
	{
	    case DIRECTION_FORWARD:
		    fd = socket->forward[1];
		    break;

	    case DIRECTION_BACKWARD:
		    fd = socket->backward[1];
		    break;

	    default:
		    break;
	}

	return write( fd, socket->buffer, socket->length);
}

ssize_t read_socket( Socket *const socket, const SocketDirection direction)
{	
	int fd = 0;

	switch ( direction )
	{
	    case DIRECTION_FORWARD:
		fd = socket->forward[0];
		break;

	    case DIRECTION_BACKWARD:
		fd = socket->backward[0];
		break;

	    default:
		break;
	}

	return socket->length = read( fd, socket->buffer, SOCKET_BUFFER_SIZE);
}

void configure_socket( const Socket *const socket, const SocketDirector director)
{
	switch ( director )
	{
	    case DIRECTOR_FORWARD:
		close( socket->forward [0]);
		close( socket->backward[1]);
		break;

	    case DIRECTOR_BACKWARD:
		close( socket->forward [1]);
		close( socket->backward[0]);
		break;

	    default:
		break;	
	}
}
