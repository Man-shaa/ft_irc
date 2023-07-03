/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientOps.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:50:52 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/07/02 21:21:29 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"


void Client::addChannel(Channel& channel)
{
	_channels.push_back(&channel);
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
