/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:58:39 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/08/01 16:28:44 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

//TODO:https://modern.ircdocs.horse/#who-message
int		Server::cmdWho(std::vector<std::string> args, Client &client)
{
	std::string channel;
	//A channel name
	if (args[0][0] == '#' || args[0][0] == '&' || args[0][0] == '+')
	{
		std::string channel = args[0];
		std::map<int, Client*> _usrList = getChannelByName(channel)->getUsrListMap();
		for (std::map<int, Client*>::const_iterator it = _usrList.begin(); it != _usrList.end(); ++it)
		{
			std::string RPL_WHOREPLY = "352 " \
			+ channel + " " + (it->second)->getNickname() + " " + _IP + " " + SERVERNAME + " " +(it->second)->getNickname() + " H :1 " \
			+ (it->second)->getFirstName() + " " + (it->second)->getLastName() + "\r\n";
			std::cout << RPL_WHOREPLY << std::endl;
			send(client.getSocket(), RPL_WHOREPLY.c_str(), RPL_WHOREPLY.size(), 0);
			
			std::string RPL_ENDOFWHO = "315 " + (it->second)->getNickname() +  " " + channel + " :End of WHO list\r\n";
			send(client.getSocket(), RPL_ENDOFWHO.c_str(), RPL_ENDOFWHO.size(), 0);
		}
	}
	else
	{
		//An exact nickname
		if (!getClientByName(args[0]))
			return (1);
		client.getChannelList().empty() ? channel = "*" : channel = client.getChannelList()[0]->getName();

		//TODO:gerer <flags> H ou G 
		std::string RPL_WHOREPLY = "352 " \
		+ channel + " " + getClientByName(args[0])->getUserName() + " " + _IP + " " + SERVERNAME + " " + getClientByName(args[0])->getNickname() + " H :1 " \
		+ getClientByName(args[0])->getFirstName() + " " + getClientByName(args[0])->getLastName() + "\r\n";
		std::cout << RPL_WHOREPLY << std::endl;
		send(client.getSocket(), RPL_WHOREPLY.c_str(), RPL_WHOREPLY.size(), 0);
		
		std::string RPL_ENDOFWHO = "315 " + client.getNickname() + " " + channel + " :End of WHO list\r\n";
		send(client.getSocket(), RPL_ENDOFWHO.c_str(), RPL_ENDOFWHO.size(), 0);
	}
	
	return (0);
}