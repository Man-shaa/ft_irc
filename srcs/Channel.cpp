/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:22:39 by ajeanne           #+#    #+#             */
/*   Updated: 2023/06/21 18:04:52 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel() : _name("default"), _logMsg("default"), _topic("default"), _password("default"), _secured(false), _owner(0){

	return;	
}

Channel::Channel(std::string name, Client& owner) : _name(name), _logMsg("toto"), _topic("TURLUTUTU"), _password("toor"), _secured(false), _owner(owner.getSocket()){

	addModo(owner);
	addUser(owner);
	return;	
}

Channel::~Channel(void)	{
	return;
}

std::string	Channel::getName(void) const	{
	
	return (_name);
}

std::string	Channel::getTopic(void) const	{
	
	return (_topic);
}

std::vector<std::string> Channel::getUsrList(void) const	{
	std::vector<std::string> usrNames;
	
	for (std::map<int, Client*>::const_iterator it = _usrList.begin(); it != _usrList.end(); ++it)
	{
		usrNames.push_back((it->second)->getNickname());
	}
	
	return (usrNames);
}

void	Channel::setLogMsg(std::string logMsg) {
	_logMsg = logMsg;	
}

void	Channel::setTopic(std::string topic) {
	_topic = topic;
}

void	Channel::setPassword(std::string password) {
	_password = password;
}

void	Channel::setSecured(bool secured) {
	_secured = secured;
}

void	Channel::addUser(Client &user)	{
	_usrList[user.getSocket()] = &user;

	return;
}

void	Channel::addModo(Client &user)	{
	_modoList[user.getSocket()] = &user;

	return;
}

void	Channel::remUser(Client &user)	{
    for (std::map<int, Client*>::iterator it = _usrList.begin(); it != _usrList.end(); ++it)
	{
        if (it->first != user.getSocket())
		{
            _usrList.erase(it);
            break;
		}
	}
			
	return ;
}

void	Channel::remModo(Client &user)	{
    for (std::map<int, Client*>::iterator it = _modoList.begin(); it != _modoList.end(); ++it)
	{
        if (it->first != user.getSocket())
		{
            _modoList.erase(it);
            break;
		}
	}
			
	return ;
}

// void	Channel::sendMsg(std::string msg, Client &user) const	{
// 	for (std::vector<std::string>::const_iterator it = _usrList.begin(); it != _usrList.end(); ++it)	{
// 		if (*it != user.getNickname())
// 			send(it->getSocket(), msg.c_str(), msg.size(), 0);
// 	}

// 	return;
// }
