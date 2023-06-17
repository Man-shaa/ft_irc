/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:39:05 by msharifi          #+#    #+#             */
/*   Updated: 2023/06/17 18:15:12 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

class Client
{
	private:
		int							_socketFd;
		std::string					_nickName;
		std::vector<std::string>	_channels;

	public:

		Client(void);
		Client(int soketFd, std::string nickName);
		~Client(void);

		int								getSocket() const;
		const std::string				&getNickname() const;
		const std::vector<std::string>	&getChannels() const;
		void							addChannel(const std::string& channel);
		void							removeChannel(const std::string& channel);
		void							setNickName(std::string &name);
		int								getSocketFd() const;

		void	printInfo() const;
};

#endif
