/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:39:05 by msharifi          #+#    #+#             */
/*   Updated: 2023/07/05 19:43:26 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef CLIENT_HPP
# define CLIENT_HPP

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
#include <map>
#include "Channel.hpp"

enum ClientStatus
{
	ACCEPT,
	PASSWORD,
	REGISTER,
	CONNECT,
	DELETE
};

enum ModeratorLevel
{
	USER,
	OPERATOR
};

# define ORANGE "\033[33m"
# define GREEN "\033[32m"
# define RED "\033[31m"
# define CLOSE "\033[0m"

class Channel;

class Client
{
	private:
		int							_socketFd;
		std::string					_nickName;
		std::string					_firstName;
		std::string					_lastName;
		std::string					_userName;
		int							_status;
		int							_modeLevel;
		int							_id;
		std::vector<Channel*>		_channels;
		std::vector<std::string>	_invitedChannels;
		struct 						pollfd _fds_clt;
		

	public:

		Client(void);
		Client(int soketFd, std::string nickName, int id);
		~Client(void);

		int					getSocket() const;
		int					getStatus() const;
		const std::string	&getNickname() const;
		std::string			getFirstName() const;
		std::string			getLastName() const;
		std::string			getUserName() const;
		pollfd				getPollStrc() const;
		int					getId() const;
		int					getModeLevel() const;
		std::string			getModeLevelStr() const;
		std::vector<Channel*> getClientChannels() const;

		void				setNickname(std::string name);
		void				setFirstName(std::string name);
		void				setLastName(std::string name);
		void				setUserName(std::string name);
		void				setStatus(int status);
		void				setModeLevel(int status);
	
		void				addChannel(Channel& channel);
		void				addInvitedChannel(std::string channelName);
		void				removeChannel(const Channel& channel);
		int					isClientInvited(std::string channelName) const;

		void							printAllClientChannel() const;
		int								isClientInChannel(std::string channel) const;

};

#endif
