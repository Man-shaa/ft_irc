/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:30:02 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/09/06 22:47:16 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int		Server::cmdJoinRPL(std::string channel, Client &client, int i)
{
	//JOIN sent to client
	std::string JOIN = ":" + client.getBanger() + " JOIN " + channel + "\r\n";
	_channels[i]->sendMsgToChannel(JOIN);

	//RPL_TOPIC sent to client
	std::string RPL_TOPIC =  "332 " + client.getBanger() + " " + channel + " :" + _channels[i]->getTopic() + "\r\n";
	send(client.getSocket(), RPL_TOPIC.c_str(), RPL_TOPIC.size(), 0);

	std::string RPL_TOPICWHOTIME =  "333 " + client.getBanger() + " " + channel + " " + client.getNickname() + " " + _channels[i]->getSetat() + "\r\n";
	send(client.getSocket(), RPL_TOPICWHOTIME.c_str(), RPL_TOPICWHOTIME.size(), 0);

	//RPL_NAMREPLY sent to client
	std::vector<std::string> listUsr = _channels[i]->getUsrList();
	std::string RPL_NAMREPLY = "353 " + client.getBanger() + " = " + channel + " :";
	for (std::vector<std::string>::const_iterator it = listUsr.begin(); it != listUsr.end(); ++it)
	{
		if (it == listUsr.begin())
			RPL_NAMREPLY += *it;
		else
			RPL_NAMREPLY += " " + *it;
	}
	RPL_NAMREPLY += "\r\n";
	_channels[i]->sendMsgToChannel(RPL_NAMREPLY);
	std::cout << RPL_NAMREPLY << std::endl;
	//RPL_ENDOFNAMES sent to client
	std::string RPL_ENDOFNAMES = "366 " + client.getBanger() + " " + channel + " :End of NAMES list\r\n";
	_channels[i]->sendMsgToChannel(RPL_ENDOFNAMES);
	
	client.addChannel(*_channels[i]);
	return (0);
}

int		Server::cmdJoin(std::vector<std::string> args, Client &client)
{
	bool channelExist = false;
	size_t i;
	
	std::vector<std::string> listChannel = listChannels(args[0]);
	std::vector<std::string> listPassword;
	
	if (args.size() == 2)
		listPassword = listChannels(args[1]);
		
	std::map<std::string, std::string> channels;
	
	std::vector<std::string>::iterator password = listPassword.begin();

	for (std::vector<std::string>::const_iterator channelName = listChannel.begin(); channelName != listChannel.end(); ++channelName)
	{
		if (!listPassword.empty() && password != listPassword.end())
		{
			channels[*channelName] = *password;
			password++;
		}
		else
			channels[*channelName] = "";
	}
	
	for (std::map<std::string, std::string>::const_iterator it = channels.begin(); it != channels.end(); ++it)
	{
		for (i = 0; i < _channels.size(); ++i)
		{
			if (_channels[i] && _channels[i]->getName() == it->first)
			{
				channelExist = true;
				//The channel is password-protected and the user does not give or returns a wrong password 
				if ((_channels[i]->getSecured() == true && (it->second == "" || it->second != _channels[i]->getPassword())))
				{
					std::string ERR_BADCHANNELKEY = "475 " + client.getBanger() + " " + it->first + " :Cannot join channel (+k)\r\n";
					send(client.getSocket(), ERR_BADCHANNELKEY.c_str(), ERR_BADCHANNELKEY.size(), 0);
					break;
				}
				//The channel has a user limit and cannot add a new user
				if (_channels[i]->getMaxUsr() != 0 && _channels[i]->getUserNumber() >= _channels[i]->getMaxUsr())
				{
					std::string ERR_CHANNELISFULL = "471 " + client.getBanger() + " " + it->first + " :Cannot join channel (+l)\r\n";
					send(client.getSocket(), ERR_CHANNELISFULL.c_str(), ERR_CHANNELISFULL.size(), 0);
					break;
				}
				if (_channels[i]->getModeChannel().find("i") != std::string::npos && !client.isClientInvited(it->first))
				{
					std::string ERR_INVITEONLYCHAN = "473 " + client.getBanger() + " " + it->first + " :Cannot join channel (+i)\r\n";
					send(client.getSocket(), ERR_INVITEONLYCHAN.c_str(), ERR_INVITEONLYCHAN.size(), 0);
					break;
				}
				_channels[i]->addUser(client);
				cmdJoinRPL(it->first, client, i);
				std::cout << BLUE << client.getBanger() << " intègre le channel déjà existant " << CLOSE << it->first << std::endl;
			}
		}
		
		if (!channelExist)
		{
			createChannel(it->first, client);
			std::cout << "CLIENT: " << GREEN << client.getBanger() << " a crée un nouveau channel " << CLOSE << it->first << "\n" << std::endl;
			cmdJoinRPL(it->first, client, i);
			_channels[i]->addUser(*getClientByName("bot"));
			cmdJoinRPL(it->first, *getClientByName("bot"), i);
		}
	}

	//TEST voir les channels du client
	client.printAllClientChannel();
	return (0);
}
