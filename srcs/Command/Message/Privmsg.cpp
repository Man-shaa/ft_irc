/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:30:41 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/08/07 18:58:55 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int Server::cmdPrivmsg(std::vector<std::string> args, Client &client)
{
	//cf. https://modern.ircdocs.horse/#privmsg-message
	std::string	name = args[0];
	
	if (name[0] == '#')
		privMsgChannel(args, client, name);
	else if (name[0] == '%' && name[1] == '#')	{
		name.erase(0,1);
		privMsgChannelOps(args, client, name);
	}
	else if	(name[0] == '@' && name[1] == '%' && name[2] == '#')	{
		name.erase(0,2);
		privMsgChannelOps(args, client, name);
	}
	else if (getClientByName(args[0]))	{
		privMsgUser(args, client);
	}
	else	{
		std::string answer = "401 " + client.getBanger() + " " + args[0] + " :No such nick\r\n"; // ERR_NOSUCHNICK
		send(client.getSocket(), answer.c_str(), answer.size(), 0);
	}
	return (0);
}

void	Server::privMsgChannel(std::vector<std::string> args, Client &client, std::string name)	{
	for (size_t i = 0; i < _channels.size(); ++i) 
	{
		if (_channels[i] && _channels[i]->getName() == name)
		{
			std::string msg = ":" + client.getNickname() + " PRIVMSG " + name;
			for (std::vector<std::string>::const_iterator it = args.begin() + 1; it != args.end(); ++it)
			{
				msg += " " + *it;
			}
			msg += "\r\n";
			_channels[i]->sendMsg(msg, client);
			break;
		}
	}
}

void	Server::privMsgChannelOps(std::vector<std::string> args, Client &client, std::string name)	{
	for (size_t i = 0; i < _channels.size(); ++i) 
	{
		if (_channels[i] && _channels[i]->getName() == name)
		{
			std::string msg = ":" + client.getNickname() + " PRIVMSG " + name;
			for (std::vector<std::string>::const_iterator it = args.begin() + 1; it != args.end(); ++it)
			{
				msg += " " + *it;
			}
			msg += "\r\n";
			_channels[i]->sendMsgOpe(msg, client);
			break;
		}
	}
}

void	Server::privMsgUser(std::vector<std::string> args, Client &client)	{
	std::string msg = ":" + client.getNickname() + " PRIVMSG " + args[0];
	for (std::vector<std::string>::const_iterator it = args.begin() + 1; it != args.end(); ++it)
	{
		msg += " " + *it;
	}
	msg += "\r\n";
	send(getClientByName(args[0])->getSocket(), msg.c_str(), msg.size(), 0);
}