#ifndef SOCKET_H
#define SOCKET_H

#define SOCKET_BUFFER_SIZE 4096

typedef struct Socket
{
	int forward [2];
	int backward[2];
	
	char   *buffer;
	size_t  length;
} Socket;

typedef enum SocketDirection
{
	DIRECTION_FORWARD  = 0,
	DIRECTION_BACKWARD = 1,
} SocketDirection;

typedef enum SocketDirector
{
	DIRECTOR_FORWARD  = 0,
	DIRECTOR_BACKWARD = 1,
} SocketDirector;


Socket *create_socket ( void);
void    release_socket( Socket *const socket);

ssize_t write_socket( Socket *const socket, const SocketDirection direction);
ssize_t read_socket ( Socket *const socket, const SocketDirection direction);

void configure_socket( const Socket *const socket, const SocketDirector director);

#endif // SOCKET_H
