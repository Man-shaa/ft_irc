/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:14:51 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/06/20 16:45:18 by msharifi         ###   ########.fr       */
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
		sockaddr_in 		_serverAddress;
		sockaddr_in 		_clientAddress;
		std::vector<int> 	_sockets;
		std::vector<int> 	_socketsToRemove;
		Client				*_clients[MAX_CLIENTS];
		struct 				pollfd _fds_srv;
		int           		_ret;
		int					_fd;
		int					_port;
		std::string			_password;

	public:
		Server(void);
		~Server(void);

		int		start(int port, std::string password);
		int		createSocket();
		int		listenSocket();
		int 	linkSocketServer();
		void	serverInfo();
		int		acceptConnexions();
		void	manageClientMsg();
		void	socketToRemove();
		int		serverManagement();
		int		dataManagement();
		void	addClient(std::string nickname, int fd);
		Client	*getClientByFd(int fd) const;

		void	printAllClient() const;
};

#endif