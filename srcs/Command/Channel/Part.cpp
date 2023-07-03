/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 17:01:12 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/07/02 21:45:53 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

std::vector<std::string>	Server::listChannels(std::string chans)
{
	std::vector<std::string> listChannel;
	std::istringstream iss(chans);
	std::string token;

	if (std::getline(iss, token, ','))
        listChannel.push_back(token);
		
	while (std::getline(iss, token, ','))
		listChannel.push_back(token);

	return (listChannel);
}

int	Server::cmdPart(std::vector<std::string> args, Client &client)
{
	//Si le channel n'est pas precisé
	if (args.size() < 1)
	{
		std::string ERR_NEEDMOREPARAMS = "461 " + client.getNickname() + " PART :Not enough parameters\r\n";
		send(client.getSocket(), ERR_NEEDMOREPARAMS.c_str(), ERR_NEEDMOREPARAMS.size(), 0);
		return (1);	
	}
	
	std::vector<std::string> listChannel = listChannels(args[0]);
	std::string reason;
	int 		i;
	
	if (args.size() >= 2 && !args[1].empty())
		reason = args[1];

	for (std::vector<std::string>::const_iterator it = listChannel.begin(); it != listChannel.end(); ++it)
	{
		bool 		channelExist = false;
		for (i = 0; _channels[i]; ++i)
		{
			if (_channels[i]->getName() == *it)
			{
				channelExist = true;
				break;
			}
		}
		//Si le channel n'existe pas, on retourne un msg d'erreur
		if (!channelExist)
		{
			std::string ERR_NOSUCHCHANNEL = "403 " + client.getNickname() + " :No such channel\r\n";
			send(client.getSocket(), ERR_NOSUCHCHANNEL.c_str(), ERR_NOSUCHCHANNEL.size(), 0);
			return (1);
		}
		//Si le channel existe, mais que l'utilisateur n'en fait pas parti
		if (!client.isClientInChannel(_channels[i]->getName()))
		{
			std::string ERR_NOTONCHANNEL = "442 " + client.getNickname() + " " + _channels[i]->getName() + " :You're not on that channel\r\n";
			send(client.getSocket(), ERR_NOTONCHANNEL.c_str(), ERR_NOTONCHANNEL.size(), 0);
			return (1);
		}
		//L'utilisateur est supprime du channel (NB: Obliger de mettre @localhost sinon ca bug)
		std::string PART = ":" + client.getNickname() + "@localhost PART " + _channels[i]->getName() + " " + reason + "\r\n";
		send(client.getSocket(), PART.c_str(), PART.size(), 0);
		client.removeChannel(*_channels[i]);
		//TODO:NE MARCHE PAS
		if (_channels[i]->remUser(client))
			delChannel(*it);
	}
	return (0);	
}
