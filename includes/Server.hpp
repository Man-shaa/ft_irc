/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:14:51 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/06/19 17:48:44 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <cstdlib>
# include <cstring>
# include <sstream>
# include <cstdio>
# include <netdb.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <fcntl.h>
# include <poll.h>
# include <errno.h>
# include <signal.h>
# include <sys/stat.h>
# include <algorithm>
# include <iostream>
# include <vector>
# include <map>

# include "Client.hpp"

# define MAX_CLIENTS 10
# define BUFFER_SIZE 4096

class Server
{
	private:
		std::string 		_serverName;
		int 				_listenSocket;
		sockaddr_in 		_serverAddress;
		sockaddr_in 		_clientAddress;
		std::vector<int> 	_Sockets;
		std::vector<int> 	_socketsToRemove;
		Client				*_client[MAX_CLIENTS];
		struct 				pollfd _fds;
		int           		_ret;
		int					_client;
		int					_port;

	
public:

	Server( void );
	~Server( void );
	
	int		start(int port);
	int		createSocket();
	int		listenSocket();
	int 	link_SocketServer();
	void	serverInfo();
	int		acceptConnexions();
	void	manageClientMsg();
	void	socketToRemove();
	int		serverManagement();
	int		dataManagement();
	void	addClient(int clientSocket);
	Client	*getClientByFd(int fd) const;

	void	printAllClient() const;
};

#endif