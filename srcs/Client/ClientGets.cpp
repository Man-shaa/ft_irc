/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientGets.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:50:00 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/08/05 16:27:32 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

int	Client::getSocket() const
{
	return (_socketFd);
}

const std::string	&Client::getNickname() const
{
	return (_nickName);
}

int	Client::getStatus() const
{
	return (_status);
}

std::string	Client::getBanger() const
{
	return (_banger);
}

pollfd	Client::getPollStrc() const
{
	return (_fds_clt);
}

int	Client::getModeLevel() const
{
	return (_modeLevel);
}

std::string	Client::getModeLevelStr() const
{
	std::string	str;
	if (_modeLevel == USER)
		str = "+r";
	else if (_modeLevel == MODO)
		str = "+o";
	return (str);
}

std::vector<Channel *>	Client::getChannelList() const
{
	return (_channels);
}

std::string			Client::getFirstName() const
{
	return (_firstName);
}

std::string			Client::getLastName() const
{
	return (_lastName);
}

std::string			Client::getUserName() const
{
	return (_userName);	
}
