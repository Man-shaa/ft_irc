/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 15:48:38 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/08/06 04:34:39 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int		Server::cmdTopic(std::vector<std::string> args, Client &client)
{
	bool 	channelExist = false;
	size_t	i;

	std::cout << "rentre dans cmdTopic" << std::endl;
	for (i = 0; i < _channels.size(); ++i)
	{
		if (_channels[i]->getName() == args[0])
		{
			channelExist = true;
			break;
		}
	}
	if (!channelExist)
	{
		std::string ERR_NOSUCHCHANNEL = "403 " + client.getBanger() + " " + args[0] + " :No such channel\r\n";
		send(client.getSocket(), ERR_NOSUCHCHANNEL.c_str(), ERR_NOSUCHCHANNEL.size(), 0);
		return (0);
	}
	if (!client.isClientInChannel(args[0]))
	{
		std::string ERR_NOTONCHANNEL = "442 " + client.getBanger() + " " + args[0] + " :You're not on that channel\r\n";
		send(client.getSocket(), ERR_NOTONCHANNEL.c_str(), ERR_NOTONCHANNEL.size(), 0);
		return (1);
	}
	std::string	msg;
	if (args.size() <= 1)
		msg = args[0];
	else
	{
		for (std::vector<std::string>::iterator it = args.begin() + 1; it != args.end(); ++it)
		{
			if (it == args.begin() + 1)
				msg = (*it).erase(0,1);
			else
				msg += " " + *it;
		}
	}
	msg += "\r\n";
	if (_channels[i]->setTopic(msg, client))
		_channels[i]->sendTopic(msg, client);
	else
	{
		std::cout << "Rentre dans not channel operator !" << std::endl;
		std::string ERR_CHANOPRIVSNEEDED = "482 " + client.getBanger() + " :You're not channel operator\r\n";
		send(client.getSocket(), ERR_CHANOPRIVSNEEDED.c_str(), ERR_CHANOPRIVSNEEDED.size(), 0);
	}
	return(0);
}
