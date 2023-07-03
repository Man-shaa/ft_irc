/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelOps.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:45:29 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/07/02 21:53:03 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"


//MEMBER MANAGEMENT

void	Channel::addUser(Client &user)	{
	_usrList[user.getSocket()] = &user;

	return;
}

void	Channel::addModo(Client &user)	{
	_modoList[user.getSocket()] = &user;

	return;
}

int	Channel::remUser(Client &user)	
{
    for (std::map<int, Client*>::iterator it = _usrList.begin(); it != _usrList.end(); ++it)
	{
        if (it->first == user.getSocket())
		{
            _usrList.erase(it);
			std::cout << "CHANNEL: " << ORANGE << user.getNickname() << " has been removed from the channel " << _name << "\n" << CLOSE << std::endl;		
            break;
		}
	}
	
	//Supprime l'instance si il n'y a plus d'utilisateur
	if (_usrList.empty())
		return (1);
	return (0);
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


//MESSAGE MANAGEMENT

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

void	Channel::sendMode(std::string msg) const
{
	if (!msg.empty())
	{
		std::string MODE_COMMAND = "MODE " + _name + " " + msg + "\r\n";
		std::cout << MODE_COMMAND << std::endl;
		for (std::map<int, Client*>::const_iterator it = _usrList.begin(); it != _usrList.end(); ++it)
		{
			send(it->second->getSocket(), MODE_COMMAND.c_str(), MODE_COMMAND.size(), 0);
		}
	}

	return ;
}

void	Channel::sendTopic(std::string msg, Client &user) const
{
	if (!msg.empty())
	{
		std::string TOPIC_COMMAND = ":" + user.getNickname() + " TOPIC " + _name + " " + msg + "\r\n";
		std::cout << TOPIC_COMMAND << std::endl;
		for (std::map<int, Client*>::const_iterator it = _usrList.begin(); it != _usrList.end(); ++it)
		{
			send(it->second->getSocket(), TOPIC_COMMAND.c_str(), TOPIC_COMMAND.size(), 0);
		}
	}

	return ;
}
