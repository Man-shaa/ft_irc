/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kill.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 19:28:47 by msharifi          #+#    #+#             */
/*   Updated: 2023/08/06 04:57:30 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int	Server::cmdKillErrorHandling(std::vector<std::string> args, Client &client)
{
	if (client.getModeLevel() != MODO)
	{
		std::string answer = "481 " + client.getBanger() + " :Permission Denied- You're not an IRC operator\r\n"; // ERR_NOPRIVILEGES
		send(client.getSocket(), answer.c_str(), answer.size(), 0);
		removeClient(client.getSocket());
		return (1);
	}
	else if (args.size() < 2)
	{
		std::string answer = "461 " + client.getBanger() + " KILL :Not enough parameters\r\n"; // ERR_NEEDMOREPARAMS
		send(client.getSocket(), answer.c_str(), answer.size(), 0);
		removeClient(client.getSocket());
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
	std::cout << "Rentre dans cmdKill" << std::endl;
	if (cmdKillErrorHandling(args, client))
		return (1);
	std::cout << "Passe parsing cmdKILL" << std::endl;
	std::string answer = ":" + client.getBanger() + " KILL " + args[0] + " :User has been killed\r\n";
	std::vector<Channel *> channelList = getClientByName(args[0])->getChannelList();
	for (std::vector<Channel *>::iterator it = channelList.begin(); it != channelList.end(); ++it)
	{
		std::string answer = ":" + client.getBanger() + " KILL " + args[0] + " :User has been killed\r\n";
		(*it)->sendMsgToChannel(answer);
	}
	Client	*target = getClientByName(args[0]);
	answer = ":" + target->getBanger() + " QUIT " + args[1] + "\r\n";
	send(target->getSocket(), answer.c_str(), answer.size(), 0);
	return (0);
}