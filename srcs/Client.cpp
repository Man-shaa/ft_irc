/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:42:20 by msharifi          #+#    #+#             */
/*   Updated: 2023/06/20 15:48:56 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(void) : _socketFd(-1), _nickName(""), _id(-1), _channels(0)
{
	return ;
}

Client::Client(int socketFd, std::string nickname, int id) : _socketFd(socketFd), _nickName(nickname), _id(id), _channels(0)
{
	_fds_clt.fd = socketFd;
	_fds_clt.events = POLLIN;
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

int	Client::getId() const
{
	return (_id);
}

pollfd	Client::getPollStrc() const
{
	return (_fds_clt);
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

void	Client::printInfo() const
{
	std::cout << "socket fd : " << _socketFd << std::endl;
	std::cout << "nickname : [" << _nickName << "]" << std::endl;
	std::cout << "channels : " << std::endl;
	for (std::vector<std::string>::const_iterator it = _channels.begin(); it != _channels.end(); ++it)
		std::cout << "	- " << *it << std::endl;
	std::cout << std::endl;
}

void	Client::setNickName(std::string &name)
{
	// std::string nickName(name);
	// if (nickName.empty() == false)
		_nickName = name;
}

int	Client::getSocketFd() const
{
	return (_socketFd);
}