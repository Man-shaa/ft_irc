/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:14:51 by ccheyrou          #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2023/07/05 15:26:27 by msharifi         ###   ########.fr       */
=======
/*   Updated: 2023/07/03 17:56:37 by msharifi         ###   ########.fr       */
>>>>>>> 572949c ([WIP] Mode User (deso j'avais pas vu que je suis sur le main UwU))
=======
/*   Updated: 2023/07/04 23:23:20 by ccheyrou         ###   ########.fr       */
>>>>>>> 404ad83 ([WIP] Mode l)
=======
/*   Updated: 2023/07/05 16:13:37 by ccheyrou         ###   ########.fr       */
>>>>>>> 11634f3 ([MERGE] mode OLI)
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

# define OPERPASS	"Admin1234!"
# define OPERNAME	"admin"

class Client;
class Channel;

class Server
{
	typedef int (Server::*cmdFct)(std::vector<std::string>, Client &);
	typedef void (Server::*modeFct)(Client &, std::string, std::string &, int, bool);

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
		std::map<char, modeFct>		_modeFcts;

	public:
		Server(void);
		~Server(void);

		//SERVER MANAGEMENT
		int			start(int port, std::string password);
		int			createSocket();
		int			listenSocket();
		int 		linkSocketServer();
		void		serverInfo();
		void		socketToRemove();
		void		deleteUnusedChannel();

		// void	removeSocketByFd(int socketFd);
		int			serverManagement();
		int			dataManagement();

		//CLIENT MANAGEMENT
		int			acceptConnexions();
		Client		*getClientByFd(int fd) const;
		Client		*getClientByName(std::string nickname) const;
		void		addClient(std::string nickname, int fd);
		void		removeClient(int fd);
		int			manageClientMsg();
		int			executeCommand(std::string newcmd);

		//CHANNEL MANAGEMENT
		void 		createChannel(std::string channelName, Client &client);
		void		delChannel(std::string channelName);
		int			doesChannelExist(std::string &name) const;
		Channel		*getChannelByName(std::string name) const;
		int			isUserInChannel(std::string clientName, std::string channelName) const;

		//COMMAND MANAGEMENT
<<<<<<< HEAD
		void		initCmd();

		// NICK
		int			parseNickname(std::string &name) const;
		int			usedNickname(std::string name) const;
		int			cmdNickErrorHandling(std::vector<std::string> args, Client &client);
		int			cmdNick(std::vector<std::string> args, Client &client);

		// OPER
		int			cmdOperErrorHandling(std::vector<std::string> args, Client &client);
		int			cmdOper(std::vector<std::string> args, Client &client);

		// PASS
		int			cmdPass(std::vector<std::string> args, Client &client);

		// USER
		int			cmdUser(std::vector<std::string> args, Client &client);

		// INVITE
		int			cmdInviteErrorHandling(std::vector<std::string> args, Client &client);
		int			cmdInvite(std::vector<std::string> args, Client &client);

		// JOIN
		int			cmdJoin(std::vector<std::string> args, Client &client);
		int			cmdJoinRPL(std::string channel, Client &client, int index);

		// KICK
		int			cmdKickErrorHandling(std::vector<std::string> args, Client &client);
		int			cmdKick(std::vector<std::string> args, Client &client);

		// MODE
		void		initMode();
		bool 		containsUppercase(const std::string& param);
		void		mode_K(Client &client, std::string param, std::string &validModes, int i, bool change);
		void		mode_T(Client &client, std::string param, std::string &validModes, int i, bool change);
		void		mode_I(Client &client, std::string param, std::string &validModes, int i, bool change);
		void		mode_O(Client &client, std::string param, std::string &validModes, int i, bool change);
		void		mode_L(Client &client, std::string param, std::string &validModes, int i, bool change);
		std::string	toggleChannelMode(Client &client, char mode, std::string param, int i, bool change);
		std::string	channelMode(Client &client, std::map<std::string, std::string> args, int i);
		bool		isSign(char c);
		bool    	isValidChanMode(std::string mode);
		bool    	isParNeededMode(std::string mode);
		std::string	parseMode(std::string mode);
<<<<<<< HEAD
		std::string	checkArg(Client &client, std::vector<std::string> args, int i);
		int			cmdMode(std::vector<std::string> args, Client &client);

		// PART
		std::vector<std::string>	listChannels(std::string chans);
		int							cmdPart(std::vector<std::string> args, Client &client);

		// TOPIC
		int			cmdTopic(std::vector<std::string> args, Client &client);

		// PRIVMSG
		int			cmdPrivmsg(std::vector<std::string> args, Client &client);

		// PING
		int			cmdPing(std::vector<std::string> args, Client &client);
=======
		void	initCmd();
		int		cmdNick(std::vector<std::string> args, Client &client);
		int		cmdUser(std::vector<std::string> args, Client &client);
		int		cmdJoin(std::vector<std::string> args, Client &client);
		int		cmdJoinRPL(std::string channel, Client &client, int index);
		int		cmdPing(std::vector<std::string> args, Client &client);
		int		cmdPass(std::vector<std::string> args, Client &client);
		
		int		parseNickname(std::string &name) const;
		int		usedNickname(std::string &name) const;
		int		cmdPrivmsg(std::vector<std::string> args, Client &client);
		int		cmdTopic(std::vector<std::string> args, Client &client);
	
		//MODE CMD
		int			cmdMode(std::vector<std::string> args, Client &client);
		void		initMode();
		std::string	toggleChannelMode(Client &client, std::vector<std::string> args, unsigned long pos, int i, bool change);
		std::string	channelMode(Client &client, std::vector<std::string> args, int i);
		void		mode_K(Client &client, std::vector<std::string> args, std::string &validModes, int i, bool change);
		void		mode_T(Client &client, std::vector<std::string> args, std::string &validModes, int i, bool change);
		void		mode_I(Client &client, std::vector<std::string> args, std::string &validModes, int i, bool change);
		void		mode_O(Client &client, std::vector<std::string> args, std::string &validModes, int i, bool change);

		int			handleModeUser(std::vector<std::string> args, Client &client);
>>>>>>> 572949c ([WIP] Mode User (deso j'avais pas vu que je suis sur le main UwU))

		//UTILS
		void		printAllClient() const;
		void		printAllChannel() const;
=======
		bool 		containsUppercase(const std::string& param);
		bool 		isDigits(const std::string& str);


		std::vector<std::string>	listChannels(std::string chans);


		//UTILS
		void	printAllClient() const;
		void	printAllChannel() const;
>>>>>>> 404ad83 ([WIP] Mode l)
};

#endif