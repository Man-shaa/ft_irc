/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelSets.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:44:42 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/07/04 12:25:09 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

void	Channel::setLogMsg(std::string logMsg) {
	_logMsg = logMsg;	
}

int	Channel::setTopic(std::string topic, Client &user) 
{	
	for (std::map<char, bool>::const_iterator it = _mode.begin(); it != _mode.end(); ++it)
	{
		if ((it->first) == 't' && it->second == false)
		{
			_topic = topic;
			break;
		}
		else if ((it->first) == 't' && it->second == true)
		{
			if (user.getSocket() == _owner)
			{
				_topic = topic;
				break;
			}
			else
				return (0);
		}
	}
	return (1);
}

void	Channel::setPassword(std::string password, bool change)
{
	if (change == false)
		_password = "";
	else
		_password = password;
}

void	Channel::setSecured(bool secured) {
	_secured = secured;
}

void	Channel::setMode(bool active, char i) {
	
	for (std::map<char, bool>::iterator it = _mode.begin(); it != _mode.end(); ++it)
	{
		if ((it->first) == i)
		{
			if (active == true)
				it->second = true;
			else
				it->second = false;
		}
	}
}
