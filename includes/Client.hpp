/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:39:05 by msharifi          #+#    #+#             */
/*   Updated: 2023/07/01 18:08:00 by ccheyrou         ###   ########.fr       */
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
		int							_id;
		std::vector<Channel*>		_channels;
		struct 						pollfd _fds_clt;
		

	public:

		Client(void);
		Client(int soketFd, std::string nickName, int id);
		~Client(void);

		bool 	operator==(const Client& other) const;
			
		int								getSocket() const;
		const std::string				&getNickname() const;
		pollfd							getPollStrc() const;
		void							addChannel(Channel& channel);
		void							removeChannel(const Channel& channel);
		void							setNickName(std::string &name);
		int								getSocketFd() const;
		int								getId() const;

		void							printAllClientChannel() const;
		int								isClientInChannel(std::string channel) const;

		void	printInfo() const;
};

#endif
