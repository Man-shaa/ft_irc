/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:14:51 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/08/08 18:56:06 by ccheyrou         ###   ########.fr       */
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
# include <csignal>
# include "Client.hpp"
# include "Bot.hpp"

# define BLUE "\033[34m"
# define ORANGE "\033[33m"
# define GREEN "\033[32m"
# define RED "\033[31m"
# define CLOSE "\033[0m"

# define BUFFER_SIZE 4096

# define OPERPASS	"Admin1234!"
# define OPERNAME	"admin"
# define SERVERNAME "server.name"

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
		std::vector<Client*>				_clients;
		std::vector<Channel*>				_channels;
		struct 								pollfd _fds_srv;
		int           						_ret;
		int									_fd;
		int									_port;
		std::string							_password;
		std::map<std::string, cmdFct>		_mapFcts;
		std::map<char, modeFct>				_modeFcts;
		std::string 						_IP;
		std::string 						_params_mode;
		int									_flag;

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
		void		removeExit();

		// void	removeSocketByFd(int socketFd);
		int			serverManagement();
		int			dataManagement();

		//BOT
		int 		simulBot();

		//CLIENT MANAGEMENT
		int			acceptConnexions();
		Client		*getClientByFd(int fd) const;
		Client		*getClientByName(std::string nickname) const;
		void		addClient(std::string nickname, int fd);
		void		addBot(std::string nickname, int fd);
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
		void		initCmd();

		// NICK
		int			parseNickname(std::string &name) const;
		int			usedNickname(std::string name) const;
		int			cmdNickErrorHandling(std::vector<std::string> args, Client &client);
		int			cmdNick(std::vector<std::string> args, Client &client);

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
		bool		isDigits(const std::string& str);

		void		mode_K(Client &client, std::string param, std::string &validModes, int i, bool change);
		void		mode_T(Client &client, std::string param, std::string &validModes, int i, bool change);
		void		mode_I(Client &client, std::string param, std::string &validModes, int i, bool change);
		void		mode_O(Client &client, std::string param, std::string &validModes, int i, bool change);
		void		mode_L(Client &client, std::string param, std::string &validModes, int i, bool change);
		void		mode_B(Client &client, std::string param, std::string &validModes, int i, bool change);
		std::string	toggleChannelMode(Client &client, char mode, std::string param, int i, bool change);
		std::string	channelMode(Client &client, std::map<std::string, std::string> args, int i);
		bool		isSign(char c);
		bool    	isValidChanMode(std::string mode);
		bool    	isParNeededMode(std::string mode);
		std::string	parseMode(std::string mode);
		std::string	checkArg(Client &client, std::vector<std::string> args, int i);
		int			cmdMode(std::vector<std::string> args, Client &client);

		int			handleModeUser(std::vector<std::string> args, Client &client);

		std::vector<std::string>	listChannels(std::string chans);
		int							cmdPart(std::vector<std::string> args, Client &client);

		// TOPIC
		int			cmdTopic(std::vector<std::string> args, Client &client);

		//NOTICE
		int			cmdNotice(std::vector<std::string> args, Client &client);
		
		// PRIVMSG
		int			cmdPrivmsg(std::vector<std::string> args, Client &client);
		void		privMsgChannel(std::vector<std::string> args, Client &client, std::string name);
		void		privMsgChannelBot(std::vector<std::string> args, Client &client, std::string name);
		void		privMsgChannelOps(std::vector<std::string> args, Client &client, std::string name);
		void		privMsgUser(std::vector<std::string> args, Client &client);
		
		// KILL
		int			cmdKillErrorHandling(std::vector<std::string> args, Client &client);
		int			cmdKill(std::vector<std::string> args, Client &client);

		// OPER
		int			cmdOperErrorHandling(std::vector<std::string> args, Client &client);
		int			cmdOper(std::vector<std::string> args, Client &client);

		// PING
		int			cmdPing(std::vector<std::string> args, Client &client);

		//UTILS
		void		printAllClient() const;
		void		printAllChannel() const;
};

#endif
