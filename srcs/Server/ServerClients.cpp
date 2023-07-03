/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerClients.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:55:37 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/07/03 15:44:53 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

// Add a new Client to [_client[]] in the server
void	Server::addClient(std::string nickname, int fd)
{
	for (int i = 0; i < MAX_CLIENTS; ++i)
	{
		if (_clients[i] == NULL)
		{
			_clients[i] = new Client(fd, nickname, i);
			break ;
		}
		if (i == MAX_CLIENTS - 1)
			std::cout << "Can not add more clients to the server" << std::endl;
	}
}

// Remove an existing client from [_clients[]] in the server
void	Server::removeClient(int fd)
{
	for (int i = 0; i < MAX_CLIENTS; ++i)
	{
		if (_clients[i] != NULL && _clients[i]->getSocket() == fd)
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
	for (int i = 0; i < MAX_CLIENTS; ++i)
	{
		if (_clients[i] != NULL)
			return ; //utile pour la fonction names sans arguments
	}
}

// Return a pointer to the client which have a [_socketFd] matching [fd]
Client	*Server::getClientByFd(int fd) const
{
	for (int i = 0; i < MAX_CLIENTS; ++i)
	{
		if (_clients[i] != NULL && _clients[i]->getSocket() == fd)
			return (_clients[i]);
	}
	return (NULL);
}

Client	*Server::getClientByName(std::string nickname) const
{
	for (int i = 0; i < MAX_CLIENTS; ++i)
	{
		if (_clients[i] != NULL && _clients[i]->getNickname() == nickname)
			return (_clients[i]);
	}
	return (NULL);
}
