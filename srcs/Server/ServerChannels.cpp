/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerChannels.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:54:41 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/07/25 15:49:00 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::createChannel(std::string channelName, Client &client)
{
	_channels.push_back(new Channel(channelName, client));
}

// Return 1 if the channel exist, 0 otherwise
int	Server::doesChannelExist(std::string &name) const
{
	for (size_t i = 0; i < _channels.size(); ++i)
	{
		if (_channels[i] != NULL && _channels[i]->getName() == name)
			return (1);
	}
	return (0);
}

// Return the channel [name] if it exist in server::_channels[MAX_CLIENTS] or NULL if it doesn't
Channel	*Server::getChannelByName(std::string name) const
{
	for (size_t i = 0; i < _channels.size(); ++i)
	{
		if (_channels[i] != NULL && _channels[i]->getName() == name)
			return (_channels[i]);
	}
	return (NULL);
}

// Return 1 if the client [clientName] is in the channel [channelName], 0 otherwise
int	Server::isUserInChannel(std::string clientName, std::string channelName) const
{
	Channel	*channel = this->getChannelByName(channelName);
	if (!channel)
		return (0);
	std::vector<std::string> usrList = channel->getUsrList();
	for (std::vector<std::string>::const_iterator it = usrList.begin(); it != usrList.end(); ++it)
	{
		std::string	opeName = "@" + clientName;
		if (clientName == *it || opeName == *it)
			return (1);
	}
	return (0);
}

void Server::delChannel(std::string channelName)
{
	for (size_t i = 0; i < _channels.size(); ++i)
	{
		if (_channels[i] != NULL && _channels[i]->getName() == channelName)
		{
			delete _channels[i];
			_channels[i] = NULL;
			std::cout << "SERVER: " << RED << channelName << " deleted\n" << CLOSE << std::endl;
			break ;
		}
	}
}

// Print all channels in server
void	Server::printAllChannel() const
{
	for (size_t i = 0; i < _channels.size(); ++i)
	{
		if (_channels[i] != NULL)
		{
			std::cout << _channels[i]->getName() << std::endl;
			break;
		}
	}
}

void	Server::deleteUnusedChannel()
{
	for (size_t i = 0; i < _channels.size(); ++i)
	{
		if (_channels[i] && _channels[i]->getUserNumber() == 0)
		{
			delete _channels[i];
			_channels[i] = NULL;
		}
	}
}
