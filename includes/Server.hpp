/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:14:51 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/06/16 15:02:22 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <cstdio>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <errno.h>
#include <signal.h>
#include <sys/stat.h>
#include <algorithm>
#include <iostream>
#include <vector>

#define MAX_CLIENTS 10
#define BUFFER_SIZE 4096

class Server
{
private:
	std::string 		_serverName;
	int 				_listenSocket;
	sockaddr_in 		_serverAddress;
	std::vector<int> 	_clientSockets;
	sockaddr_in 		_clientAddress;
	std::vector<int> 	_socketsToRemove;

	
public:

	Server( void );
	~Server( void );
	
	int		start(int port);
	int		createSocket();
	int		listenSocket();
	int 	link_SocketServer();
	void	serverInfo(int port);
	void	acceptConnexions();
	void	manageClientMessage();
	void	socketToRemove();


};

#endif