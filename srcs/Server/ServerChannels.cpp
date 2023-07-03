/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerChannels.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:54:41 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/07/02 21:57:23 by ccheyrou         ###   ########.fr       */
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

void Server::delChannel(std::string channelName)
{
	for (int i = 0; i < MAX_CHANNEL; ++i)
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
	for (int i = 0; i < MAX_CHANNEL; ++i)
	{
		if (_channels[i] != NULL)
		{
			std::cout << _channels[i]->getName() << std::endl;
			break;
		}
	}
}
