/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kill.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 19:28:47 by msharifi          #+#    #+#             */
/*   Updated: 2023/08/06 18:52:05 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int	Server::cmdKillErrorHandling(std::vector<std::string> args, Client &client)
{
	if (client.getModeLevel() != MODO)
	{
		std::string answer = "481 " + client.getBanger() + " :Permission Denied- You're not an IRC operator\r\n"; // ERR_NOPRIVILEGES
		send(client.getSocket(), answer.c_str(), answer.size(), 0);
		return (1);
	}
	else if (args.size() < 2)
	{
		std::string answer = "461 " + client.getBanger() + " KILL :Not enough parameters\r\n"; // ERR_NEEDMOREPARAMS
		send(client.getSocket(), answer.c_str(), answer.size(), 0);
		return (1);
	}
	else if (!getClientByName(args[0]))
	{
		std::string answer = "401 " + client.getBanger() + " " + args[0] + " :No such nick/channel\r\n"; // ERR_NOSUCHNICK
		send(client.getSocket(), answer.c_str(), answer.size(), 0);
		return (1);
	}
	return (0);
}

int	Server::cmdKill(std::vector<std::string> args, Client &client)
{
	if (cmdKillErrorHandling(args, client))
		return (1);
	std::string	reason = args[1];
	for (size_t i = 2; i < args.size(); ++i)
		reason += " " + args[i];
	std::vector<Channel *> channelList = getClientByName(args[0])->getChannelList();
	Client	*target = getClientByName(args[0]);
	for (std::vector<Channel *>::iterator it = channelList.begin(); it != channelList.end(); ++it)
	{
		std::string answer = target->getNickname() + " QUIT " + reason + "\r\n";
		// std::string answer = ":" + client.getBanger() + " KILL " + args[0] + " " + reason + "\r\n";
		(*it)->sendMsgToChannel(answer);
	}
	std::string answer = ":" + client.getBanger() + " KILL " + args[0] + " " + reason + "\r\n";
	send(target->getSocket(), answer.c_str(), answer.size(), 0);
	_socketsToRemove.push_back(target->getSocket());
	removeClient(target->getSocket());
	return (0);
}