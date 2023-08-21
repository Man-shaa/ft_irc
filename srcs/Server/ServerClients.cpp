/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerClients.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:55:37 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/08/08 16:59:00 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

// Add a new Client to [_client[]] in the server
void	Server::addClient(std::string nickname, int fd)
{
	_clients.push_back(new Client(fd, nickname));
}

void	Server::addBot(std::string nickname, int fd)
{
	_clients.push_back(new Bot(fd, nickname));
}

// Remove an existing client from [_clients[]] in the server
void	Server::removeClient(int fd)
{
	for (size_t i = 0; i < _clients.size(); ++i)
	{
		if (_clients[i] && _clients[i]->getSocket() == fd)
		{
			_socketsToRemove.push_back(fd);
			delete(_clients[i]);
			_clients[i] = NULL;
			return ;
		}
	}
}

// Print all clients in server
void	Server::printAllClient() const
{
	for (size_t i = 0; i < _clients.size(); ++i)
	{
		std::cout << _clients[i]->getNickname() << std::endl;
		//utile pour la fonction names sans arguments
	}
}

// Return a pointer to the client which have a [_socketFd] matching [fd] or NULL
Client	*Server::getClientByFd(int fd) const
{
	for (size_t i = 0; i < _clients.size(); ++i)
	{
		if (_clients[i] && _clients[i]->getSocket() == fd)
			return (_clients[i]);
	}
	return (NULL);
}

// Return a pointer to the client which have a [_nickname] matching [nickname] or NULL
Client	*Server::getClientByName(std::string nickname) const
{
	for (size_t i = 0; i < _clients.size(); ++i)
	{
		if (_clients[i] && _clients[i]->getNickname() == nickname)
			return (_clients[i]);
	}
	return (NULL);
}

// Bot	*Server::getBot() const	{
// 	for (size_t i = 0; i < _clients.size(); ++i)
// 	{
// 		if (_clients[i] && _clients[i]->getNickname() == "bot")
// 			return (_clients[i]);
// 	}
// 	return (NULL);
// }
