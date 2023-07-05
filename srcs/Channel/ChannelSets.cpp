/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelSets.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:44:42 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/07/04 22:56:01 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

void	Channel::setLogMsg(std::string logMsg) {
	_logMsg = logMsg;	
}

int	Channel::setTopic(std::string topic, Client &user) 
{	
	if (_mode['t'] == false || (clientIsOp(user.getSocket()) && _mode['t'] == true ))
		return(_topic = topic, 1);
	else
		return (0);
}

void	Channel::setPassword(std::string password, bool change)
{
	if (change == false)
		_password = "";
	else
		_password = password;
}

int	Channel::setMaxUsr(int maxUsr, bool change)
{
	if (change == false)
		return (_maxUsr = 0, 0);
	else
		return (_maxUsr = maxUsr, 1);
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
