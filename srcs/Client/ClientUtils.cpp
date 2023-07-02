/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:51:24 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/07/02 16:51:49 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

void	Client::printInfo() const
{
	std::cout << "socket fd : " << _socketFd << std::endl;
	std::cout << "nickname : [" << _nickName << "]" << std::endl;
	std::cout << "channels : " << std::endl;
	for (std::vector<Channel*>::const_iterator it = _channels.begin(); it != _channels.end(); ++it)
		std::cout << "	- " << (*it)->getName() << std::endl;
	std::cout << std::endl;
}

int	Client::isClientInChannel(std::string channel) const
{
	for (std::vector<Channel*>::const_iterator it = _channels.begin(); it != _channels.end(); ++it)
		if ((*it)->getName() == channel)
			return (1);
	return (0);
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
