/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerChannels.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:54:41 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/07/03 22:14:04 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::createChannel(std::string channelName, Client &client)
{
	for (int i = 0; i < MAX_CHANNEL; ++i)
	{
		if (_channels[i] == NULL)
		{
			_channels[i] = new Channel(channelName, client);
			break ;
		}
		if (i == MAX_CHANNEL - 1)
			std::cout << "Can not add more channels to the server" << std::endl;
	}
}

// Return 1 if the channel exist, 0 otherwise
int	Server::doesChannelExist(std::string &name) const
{
	for (int i = 0; i < MAX_CLIENTS; ++i)
	{
		if (_channels[i] != NULL && _channels[i]->getName() == name)
			return (1);
	}
	std::cout << "RETURN 0 dans fonction doesChannelExist" << std::endl;
	return (0);
}

// Return the channel [name] if it exist in server::_channels[MAX_CLIENTS] or NULL if it doesn't
Channel	*Server::getChannelByName(std::string &name) const
{
	for (int i = 0; i < MAX_CLIENTS; ++i)
	{
		if (_channels[i] != NULL && _channels[i]->getName() == name)
			return (_channels[i]);
	}
	return (NULL);
}

// Return 1 if the client [clientName] is in the channel [channelName], 0 otherwise
int	Server::isUserInChannel(std::string clientName, std::string &channelName) const
{
	Channel	*channel = getChannelByName(channelName);
	if (!channel)
		return (0);
	std::vector<std::string> usrList = channel->getUsrList();
	for (std::vector<std::string>::const_iterator it = usrList.begin(); it != usrList.end(); ++it)
	{
		std::cout << *it << std::endl;
		std::string	opeName = "@" + clientName;
		if (clientName == *it || opeName == *it)
			return (1);
	}
	return (0);
}

// Print all channels in server
void	Server::printAllChannel() const
{
	for (int i = 0; i < MAX_CHANNEL; ++i)
	{
		if (_channels[i] != NULL)
		{
			std::cout << _channels[i]->getName() << std::endl;
			break;
		}
	}
}
