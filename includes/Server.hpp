/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:14:51 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/06/23 18:22:45 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <cstdlib>
# include <cstring>
# include <string>
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

# define BLUE "\033[34m"
# define ORANGE "\033[33m"
# define GREEN "\033[32m"
# define RED "\033[31m"
# define CLOSE "\033[0m"

# define MAX_CLIENTS 10
# define MAX_CHANNEL 10
# define BUFFER_SIZE 4096

class Client;
class Channel;

class Server
{
	typedef int (Server::*cmdFct)(std::vector<std::string>, Client &);
	
	private:
		std::string 						_serverName;
		sockaddr_in 						_serverAddress;
		sockaddr_in 						_clientAddress;
		std::vector<int> 					_sockets;
		std::vector<int> 					_socketsToRemove;
		Client								*_clients[MAX_CLIENTS];
		Channel								*_channels[MAX_CLIENTS];
		struct 								pollfd _fds_srv;
		int           						_ret;
		int									_fd;
		int									_port;
		std::string							_password;
		std::map<std::string, cmdFct>		_mapFcts;

	public:
		Server(void);
		~Server(void);

		//SERVER MANAGEMENT
		int		start(int port, std::string password);
		int		createSocket();
		int		listenSocket();
		int 	linkSocketServer();
		void	serverInfo();
		void	socketToRemove();
		int		serverManagement();
		int		dataManagement();

		//CLIENT MANAGEMENT
		int							acceptConnexions();
		Client						*getClientByFd(int fd) const;
		Client						*getClientByName(std::string nickname) const;
		void						addClient(std::string nickname, int fd);
		void						manageClientMsg();
		void						executeCommand(std::string newcmd);

		//CHANNEL MANAGEMENT
		void 	createChannel(std::string channelName, Client &client);

		//COMMAND MANAGEMENT
		void	initCmd();
		int		cmdNick(std::vector<std::string> args, Client &client);
		int		cmdUser(std::vector<std::string> args, Client &client);
		int		cmdJoin(std::vector<std::string> args, Client &client);
		int		cmdJoinRPL(std::string channel, Client &client, int index);
		int		cmdMode(std::vector<std::string> args, Client &client);
		int		cmdPing(std::vector<std::string> args, Client &client);
		int		cmdPrivmsg(std::vector<std::string> args, Client &client);

		//UTILS
		void	printAllClient() const;
		void	printAllChannel() const;
};

#endif