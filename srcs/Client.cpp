/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:42:20 by msharifi          #+#    #+#             */
/*   Updated: 2023/06/17 15:59:09 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(void) : _socketFd(-1), _nickName(""), _channels(0)
{
	return ;
}

Client::Client(int socketFd, std::string nickname) : _socketFd(socketFd), _nickName(nickname), _channels(0)
{
	return ;
}

Client::~Client(void)
{
	return ;
}

int	Client::getSocket() const
{
	return (_socketFd);
}

const std::string	&Client::getNickname() const
{
	return (_nickName);
}

const std::vector<std::string>	&Client::getChannels() const
{
	return (_channels);
}

void Client::addChannel(const std::string& channel)
{
	_channels.push_back(channel);
}

void Client::removeChannel(const std::string& channel)
{
	_channels.erase(std::remove(_channels.begin(), _channels.end(), channel), _channels.end());
}
