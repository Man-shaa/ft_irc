/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:51:24 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/07/03 15:43:15 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

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
