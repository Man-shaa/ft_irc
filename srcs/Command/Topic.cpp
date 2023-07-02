/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 15:48:38 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/07/02 15:53:01 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int		Server::cmdTopic(std::vector<std::string> args, Client &client)
{
	bool 	channelExist = false;
	int		i;
	
	for (i = 0; _channels[i]; ++i)
	{
		if (_channels[i]->getName() == args[0])
		{
			channelExist = true;
			break;
		}
	}
	if (!channelExist)
	{
		std::string ERR_NOSUCHCHANNEL = "403 " + client.getNickname() + " :No such channel\r\n";
		send(client.getSocket(), ERR_NOSUCHCHANNEL.c_str(), ERR_NOSUCHCHANNEL.size(), 0);
		return (0);
	}
	if (!client.isClientInChannel(args[0]))
	{
		std::string ERR_NOTONCHANNEL = "442 " + client.getNickname() + " " + args[0] + " :You're not on that channel\r\n";
		send(client.getSocket(), ERR_NOTONCHANNEL.c_str(), ERR_NOTONCHANNEL.size(), 0);
		return (1);
	}
	if (args.size() == 1)
	{
		if (!_channels[i]->getTopic().empty())
		{
			std::string RPL_NOTOPIC = "331 " + client.getNickname() + " " + args[0] + " :No topic is set\r\n";
			send(client.getSocket(), RPL_NOTOPIC.c_str(), RPL_NOTOPIC.size(), 0);				
		}
		else
		{
			std::string RPL_TOPIC = "332 " + client.getNickname() + " " + args[0] + " :" + _channels[i]->getTopic() + "\r\n";
			send(client.getSocket(), RPL_TOPIC.c_str(), RPL_TOPIC.size(), 0);						
			//topictime
		}
	}
	if (args.size() == 2)
	{
		if (_channels[i]->setTopic(args[1], client))
			_channels[i]->sendTopic(args[1]);
		else
		{
			std::string ERR_CHANOPRIVSNEEDED = "482 " + client.getNickname() + " :You're not channel operator\r\n";
			send(client.getSocket(), ERR_CHANOPRIVSNEEDED.c_str(), ERR_CHANOPRIVSNEEDED.size(), 0);
		}
	}
	return(0);
}
