/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:42:20 by msharifi          #+#    #+#             */
/*   Updated: 2023/07/01 18:24:23 by ccheyrou         ###   ########.fr       */
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

void Client::addChannel(Channel& channel)
{
	if (_channels.size() > CHANLIMIT)
	{
		std::string ERR_TOOMANYCHANNELS = "405 " + _nickName + " " + channel.getName() + ":You have joined too many channels\r\n";
		send(_socketFd, ERR_TOOMANYCHANNELS.c_str(), ERR_TOOMANYCHANNELS.size(), 0);
	}
	else
		_channels.push_back(&channel);
}

void Client::removeChannel(const Channel& channel)
{
    for (std::vector<Channel*>::iterator it = _channels.begin(); it != _channels.end(); ++it) {
        if (*it == &channel) {
            _channels.erase(it);
            break; // Sortie de la boucle après avoir trouvé et supprimé l'objet Channel
        }
    }
}

void	Client::printInfo() const
{
	std::cout << "socket fd : " << _socketFd << std::endl;
	std::cout << "nickname : [" << _nickName << "]" << std::endl;
	std::cout << "channels : " << std::endl;
	for (std::vector<Channel*>::const_iterator it = _channels.begin(); it != _channels.end(); ++it)
		std::cout << "	- " << (*it)->getName() << std::endl;
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

void	Client::printAllClientChannel() const
{
	std::stringstream ss;
    ss << _channels.size();
	
	std::string listChannels = _nickName + " fait partie de " + ss.str() + " channel(s) : " ;
	for (std::vector<Channel*>::const_iterator it = _channels.begin(); it != _channels.end(); ++it)
		listChannels += (*it)->getName() + " ";
	std::cout << ORANGE << listChannels << CLOSE << std::endl;
}

int	Client::isClientInChannel(std::string channel) const
{
	printf("OK\n");
	for (std::vector<Channel*>::const_iterator it = _channels.begin(); it != _channels.end(); ++it)
		if ((*it)->getName() == channel)
			return (1);
	printf("KO\n");
	return (0);
}