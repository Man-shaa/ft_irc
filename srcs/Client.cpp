/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:42:20 by msharifi          #+#    #+#             */
/*   Updated: 2023/06/29 16:58:35 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(void) : _socketFd(-1), _nickName(""), _status(PASSWORD), _id(-1), _channels(0)
{
	return ;
}

Client::Client(int socketFd, std::string nickname, int id) : _socketFd(socketFd), _nickName(nickname), _status(PASSWORD), _id(id), _channels(0)
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

int	Client::getStatus() const
{
	return (_status);
}

const std::string	&Client::getNickname() const
{
	return (_nickName);
}

std::string	Client::getFirstName() const
{
	return (_firstName);
}

std::string	Client::getLastName() const
{
	return (_lastName);
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

void	Client::setNickname(std::string &name)
{
	_nickName = name;
}

void	Client::setFirstName(std::string &name)
{
	_firstName = name;
}

void	Client::setLastName(std::string &name)
{
	_lastName = name;
}

void	Client::setStatus(int status)
{
	_status = status;
}

int	Client::getSocketFd() const
{
	return (_socketFd);
}
