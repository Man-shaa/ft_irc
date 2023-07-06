/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kill.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 19:28:47 by msharifi          #+#    #+#             */
/*   Updated: 2023/07/05 20:00:17 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int	Server::cmdKillErrorHandling(std::vector<std::string> args, Client &client)
{
	if (client.getModeLevel() != MODO)
	{
		std::string answer = "481 " + client.getNickname() + " :Permission Denied- You're not an IRC operator\r\n"; // ERR_NEEDMOREPARAMS
		send(client.getSocket(), answer.c_str(), answer.size(), 0);
		removeClient(client.getSocket());
		return (1);
	}
	else if (args.size() < 2)
	{
		std::string answer = "461 " + client.getNickname() + " KILL :Not enough parameters\r\n"; // ERR_NEEDMOREPARAMS
		send(client.getSocket(), answer.c_str(), answer.size(), 0);
		removeClient(client.getSocket());
		return (1);
	}
	else if (!getClientByName(args[0]))
	{
		std::string answer = "401 " + client.getNickname() + "@localhost " + args[0] + " :No such nick\r\n"; // ERR_NOSUCHNICK
		send(client.getSocket(), answer.c_str(), answer.size(), 0);
		return (1);
	}
	return (0);
}

int	Server::cmdKill(std::vector<std::string> args, Client &client)
{
	if (cmdKillErrorHandling(args, client))
		return (1);
	std::vector<Channel *> channelList = getClientByName(args[0])->getChannelList();
	for (std::vector<Channel *>::iterator it = channelList.begin(); it != channelList.end(); ++it)
	{
		std::string answer = ":" + _serverName + " KILL " + args[0] + " :User has been killed\r\n";
		(*it)->sendMsgToChannel(answer);
	}
	return (0);
}