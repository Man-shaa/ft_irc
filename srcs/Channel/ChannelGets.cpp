/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelGets.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:44:05 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/07/03 21:23:30 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

std::string	Channel::getCreationTime(void) const	{
	
	return (_creationTime);
}

std::string	Channel::getName(void) const	{
	
	return (_name);
}

int	Channel::getOwner(void) const	{
	
	return (_owner);
}

bool	Channel::getSecured(void) const	{
	
	return (_secured);
}

std::string	Channel::getPassword(void) const	{
	
	return (_password);
}

std::string	Channel::getTopic(void) const	{
	
	return (_topic);
}

std::vector<std::string> Channel::getUsrList(void) const
{
	std::vector<std::string> usrNames;
	
	for (std::map<int, Client*>::const_iterator it = _usrList.begin(); it != _usrList.end(); ++it)
	{
		if ((it->first) == _owner)
		{
			usrNames.push_back("@" + (it->second)->getNickname());
		}
		else
			usrNames.push_back((it->second)->getNickname());
	}
	
	return (usrNames);
}

std::string Channel::getModeChannel(void) const
{
	std::string modes;
	
	for (std::map<char, bool>::const_iterator it = _mode.begin(); it != _mode.end(); ++it)
	{
		if ((it->second) == true)
			modes += it->first;
	}
	return (modes);
}
