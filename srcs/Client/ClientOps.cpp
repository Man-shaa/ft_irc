/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientOps.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:50:52 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/07/05 17:24:56 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"


void Client::addChannel(Channel& channel)
{
	_channels.push_back(&channel);
}

void Client::addInvitedChannel(std::string channelName)
{
	_invitedChannels.push_back(channelName);
}

void Client::removeChannel(const Channel& channel)
{
    for (std::vector<Channel*>::iterator it = _channels.begin(); it != _channels.end(); ++it) {
        if (*it == &channel) {
            _channels.erase(it);
			std::cout << "CLIENT: " << ORANGE << _nickName << " has removed the channel " << channel.getName() << " from his list\n" << CLOSE << std::endl;		
            break;
        }
    }
}

// Return 1 if the cliet has been ivited to [channelName] channel. 0 otherwise
int	Client::isClientInvited(std::string channelName) const
{
	for (std::vector<std::string>::const_iterator it = _invitedChannels.begin(); it != _invitedChannels.end(); ++it)
	{
		if (*it == channelName)
			return (1);
	}
	return (0);
}
