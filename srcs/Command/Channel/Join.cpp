/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:30:02 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/07/05 18:27:32 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int		Server::cmdJoinRPL(std::string channel, Client &client, int i)
{
	//JOIN sent to client
	std::string JOIN = ":" + client.getNickname() + " JOIN " + channel + "\r\n";
	send(client.getSocket(), JOIN.c_str(), JOIN.size(), 0);

	//RPL_RPL_TOPIC sent to client
	std::string RPL_TOPIC =  "332 " + client.getNickname() + " " + channel + " :" + _channels[i]->getTopic() + "\r\n";
	send(client.getSocket(), RPL_TOPIC.c_str(), RPL_TOPIC.size(), 0);

	std::string RPL_TOPICWHOTIME =  "333 " + client.getNickname() + " " + channel + " " + client.getNickname() + " " + _channels[i]->getSetat() + "\r\n";
	send(client.getSocket(), RPL_TOPICWHOTIME.c_str(), RPL_TOPICWHOTIME.size(), 0);

	//RPL_NAMREPLY sent to client
	std::vector<std::string> listUsr = _channels[i]->getUsrList();
	std::string RPL_NAMREPLY = "353 " + client.getNickname() + " = " + channel + " :";
	for (std::vector<std::string>::const_iterator it = listUsr.begin(); it != listUsr.end(); ++it)
	{
		if (it == listUsr.begin())
			RPL_NAMREPLY += *it;
		else
			RPL_NAMREPLY += " " + *it;
	}
	RPL_NAMREPLY += "\r\n";
	std::cout << RPL_NAMREPLY << std::endl;
	send(client.getSocket(), RPL_NAMREPLY.c_str(), RPL_NAMREPLY.size(), 0);
	
	//RPL_ENDOFNAMES sent to client
	std::string RPL_ENDOFNAMES = "366 " + client.getNickname() + " " + channel + " :End of NAMES list\r\n";
	send(client.getSocket(), RPL_ENDOFNAMES.c_str(), RPL_ENDOFNAMES.size(), 0);
	
	client.addChannel(*_channels[i]);
	return (0);
}

int		Server::cmdJoin(std::vector<std::string> args, Client &client)
{
	//TODO Servers MAY restrict the number of channels a client may be joined to at one time cf. https://modern.ircdocs.horse/#chanlimit-parameter
	//TODO Definir le type de channel accepte cf.https://modern.ircdocs.horse/#chantypes-parameter
	bool channelExist = false;
	int i;
	
	for (std::vector<std::string>::const_iterator it = args.begin(); it != args.end(); ++it)
	{
		// std::cout << _channels[i]->getModeChannel().find("i") << std::endl;
		for (i = 0; _channels[i]; ++i)
		{
			if (_channels[i]->getName() == *it)
			{
				channelExist = true;
				//The channel is password-protected and the user does not give or returns a wrong password 
				if ((_channels[i]->getSecured() == true && (args.size() == 1 || args[1] != _channels[i]->getPassword())))
				{
					std::string ERR_BADCHANNELKEY = "475 " + client.getNickname() + " " + args[0] + " :Cannot join channel (+k)\r\n";
					send(client.getSocket(), ERR_BADCHANNELKEY.c_str(), ERR_BADCHANNELKEY.size(), 0);
					return (1);
				}
				//The channel has a user limit and cannot add a new user
				if (_channels[i]->getMaxUsr() != 0 && _channels[i]->getUserNumber() >= _channels[i]->getMaxUsr())
				{
					std::string ERR_CHANNELISFULL = "471 " + client.getNickname() + " " + args[0] + " :Cannot join channel (+l)\r\n";
					send(client.getSocket(), ERR_CHANNELISFULL.c_str(), ERR_CHANNELISFULL.size(), 0);
					return (1);
				}
				if (_channels[i]->getModeChannel().find("i") != std::string::npos && !client.isClientInvited(args[0]))
				{
					std::string ERR_INVITEONLYCHAN = "473 " + client.getNickname() + " " + args[0] + " :Cannot join channel (+i)\r\n";
					send(client.getSocket(), ERR_INVITEONLYCHAN.c_str(), ERR_INVITEONLYCHAN.size(), 0);
					return (1);
				}
				_channels[i]->addUser(client);
				cmdJoinRPL(*it, client, i);
				std::cout << BLUE << client.getNickname() << " intègre le channel déjà existant " << CLOSE << *it << std::endl;
			}
		}
		
		if (!channelExist)
		{
			createChannel(*it, client);
			std::cout << "CLIENT: " << GREEN << client.getNickname() << " a crée un nouveau channel " << CLOSE << *it << "\n" << std::endl;
			cmdJoinRPL(*it, client, i);
		}
	}

	//TEST voir les channels du client
	client.printAllClientChannel();
	return (0);
}
