/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientGets.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:50:00 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/07/05 19:44:50 by msharifi         ###   ########.fr       */
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

int	Client::getId() const
{
	return (_id);
}

int	Client::getStatus() const
{
	return (_status);
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
