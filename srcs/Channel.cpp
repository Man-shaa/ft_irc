/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:22:39 by ajeanne           #+#    #+#             */
/*   Updated: 2023/06/20 23:57:39 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(void)	{

}

Channel::Channel(std::string name, Client &owner) : _name(name), _logMsg("toto"), _topic("TURLUTUTU"), _password("toor"), _secured(false), _owner(&owner)	{
	addModo(owner);
	addUser(owner);

	return;	
}

Channel::~Channel(void)	{
	delete _owner;

	return;
}

std::string	Channel::getName(void) const	{
	
	return _name;
}

std::vector<client>	Channel::getUsrList(void) const	{
	return _usrList;
}

void	Channel::setLogMsg(std::string logMsg) : _logMsg(logMsg)	{
	
}

void	Channel::setTopic(std::string topic) : _topic(topic)	{
	
}

void	Channel::setPassword(std::string password) : _password(password)	{
	
}

void	Channnel::setSecured(bool secured) : _secured(secured)	{
	
}

void	Channel::addUser(Client &user)	{
	_usrList.push_back(user);

	return;
}

void	Channel::addModo(Client &user)	{
	_modoList.push_back(user);

	return;
}

void	Channel::remUser(Client &user)	{
	_usrList.erase(std::remove(_usrList.begin(), _usrList.end(), user), _usrList.end());
	
	return;
}

void	Channel::remModo(Client &user)	{
	_modoList.erase(std::remove(_modoList.begin(), _modoList.end(), user), _modoList.end());

	return;
}

void	Channel::sendMsg(std::string msg, const Client &user) const	{
	for (std::vector<std::string>::const_iterator it = _usrList.begin(); it != _usrList.end(); ++it)	{
		if (*it != user)
			send(*it.getSocket(), msg.c_str(), msg.size(), 0);
	}

	return;
}
