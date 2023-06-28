/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:22:39 by ajeanne           #+#    #+#             */
/*   Updated: 2023/06/28 19:48:39 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel() : _name("default"), _logMsg("default"), _topic("default"), _password("default"), _secured(false), _owner(0){
	return;	
}

Channel::Channel(std::string name, Client& owner) : _name(name), _logMsg("toto"), _topic("TURLUTUTU"), _password("toor"), _secured(false), _owner(owner.getSocket()){

	addModo(owner);
	addUser(owner);
	
	_mode['i'] = true;
	_mode['t'] = false;
	_mode['k'] = false;
	_mode['o'] = false;

	std::stringstream ss;
	std::time_t now = std::time(0);
    ss << now;
	_creationTime = ss.str();
	std::cout << _creationTime << std::endl;
}

Channel::~Channel(void)	{
	return;
}

std::string	Channel::getCreationTime(void) const	{
	
	return (_creationTime);
}

std::string	Channel::getName(void) const	{
	
	return (_name);
}

int	Channel::getOwner(void) const	{
	
	return (_owner);
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

void	Channel::setLogMsg(std::string logMsg) {
	_logMsg = logMsg;	
}

void	Channel::setTopic(std::string topic, Client &user) 
{
	std::vector<std::string> modes;
	
	for (std::map<char, bool>::const_iterator it = _mode.begin(); it != _mode.end(); ++it)
	{
		if ((it->first) == 't' && it->second == false)
			_topic = topic;
		else if ((it->first) == 't' && it->second == true)
		{
			if (user.getSocketFd() == _owner)
				_topic = topic;
		}
	}
}

void	Channel::setPassword(std::string password) {
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

void	Channel::sendMsg(std::string msg, Client &user) const
{
    for (std::map<int, Client*>::const_iterator it = _usrList.begin(); it != _usrList.end(); ++it)
	{
		if (it->first != user.getSocket())
		{
			if (send(it->second->getSocket(), msg.c_str(), msg.size(), 0) == -1)
			{
				std::string ERR_CANNOTSENDTOCHAN = "404 " + user.getNickname() + " " + _name + " :Cannot send to channel\r\n";
				send(user.getSocket(), ERR_CANNOTSENDTOCHAN.c_str(), ERR_CANNOTSENDTOCHAN.size(), 0);
			}
		}	
	}

	return ;
}

void	Channel::sendMode(std::string msg, Client &user) const
{
	(void)user;
	std::string MODE_COMMAND = "MODE " + _name + " " + msg + "\r\n";
	std::cout << MODE_COMMAND << std::endl;
    for (std::map<int, Client*>::const_iterator it = _usrList.begin(); it != _usrList.end(); ++it)
	{
		send(it->second->getSocket(), MODE_COMMAND.c_str(), MODE_COMMAND.size(), 0);
	}

	return ;
}