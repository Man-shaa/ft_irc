/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:39:05 by msharifi          #+#    #+#             */
/*   Updated: 2023/06/23 17:07:29 by msharifi         ###   ########.fr       */
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
	PASSWORD,
	REGISTER,
	CONNECT,
	DELETE
};

class Channel;

class Client
{
	private:
		int							_socketFd;
		std::string					_nickName;
		int							_status;
		int							_id;
		std::vector<Channel*>		_channels;
		struct 						pollfd _fds_clt;
		

	public:

		Client(void);
		Client(int soketFd, std::string nickName, int id);
		~Client(void);

		int								getSocket() const;
		int								getStatus() const;
		const std::string				&getNickname() const;
		pollfd							getPollStrc() const;
		int								getId() const;
		int								getSocketFd() const;

		void							setNickname(std::string &name);
		void							setStatus(int status);
	
		void							removeChannel(const Channel& channel);
		void							addChannel(Channel& channel);
		

		void	printInfo() const;
};

#endif
