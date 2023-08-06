/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelGets.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 20:54:57 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/08/06 17:49:54 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

std::string	Channel::getCreationTime(void) const	{
	
	return (_creationTime);
}

std::string	Channel::getSetat(void) const	{
	
	return (_setat);
}

std::string	Channel::getName(void) const	{
	
	return (_name);
}

int	Channel::getOwner(void) const	{
	
	return (_owner);
}

int	Channel::getMaxUsr(void) const	{
	
	return (_maxUsr);
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

std::vector<std::string> Channel::getOpeList(void) const
{
	std::vector<std::string> modoNames;
	
	for (std::map<int, Client*>::const_iterator it = _OpeList.begin(); it != _OpeList.end(); ++it)
	{
		modoNames.push_back((it->second)->getNickname());
	}
	
	return (modoNames);
}

std::vector<std::string> Channel::getUsrList(void)
{
	std::vector<std::string> usrNames;
	
	for (std::map<int, Client*>::const_iterator it = _usrList.begin(); it != _usrList.end(); ++it)
	{
		if (clientIsOp(it->first))
			usrNames.push_back("@" + (it->second)->getNickname());
		else
			usrNames.push_back((it->second)->getNickname());
	}
	
	return (usrNames);
}

std::map<int, Client*>Channel::getUsrListMap(void)
{
	return (_usrList);
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

int	Channel::getUserNumber(void) const
{
	return (_usrList.size());
}

int	Channel::getOpNumber(void) const
{
	return (_OpeList.size());
}
