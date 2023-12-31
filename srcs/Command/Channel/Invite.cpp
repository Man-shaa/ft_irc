/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 20:52:40 by msharifi          #+#    #+#             */
/*   Updated: 2023/08/08 19:15:33 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int	Server::cmdInviteErrorHandling(std::vector<std::string> args, Client &client)
{
	if (args.size() < 2)
	{
		std::string answer = "461 " + client.getBanger() + " INVITE :not enough parameters\r\n"; // ERR_NEEDMOREPARAMS
		send(client.getSocket(), answer.c_str(), answer.size(), 0);
		return (1);
	}
	else if (!getClientByName(args[0]))
	{
		std::string answer = "401 " + client.getBanger() + " " + args[0] + " :No such nick\r\n"; // ERR_NOSUCHNICK
		send(client.getSocket(), answer.c_str(), answer.size(), 0);
		return (1);
	}
	else if (!doesChannelExist(args[1]))
	{
		std::string answer = "403 " + client.getBanger() + " " + args[1] + " :No such channel\r\n"; // ERR_NOSUCHCHANNEL
		send(client.getSocket(), answer.c_str(), answer.size(), 0);
		return (1);
	}
	else if (!isUserInChannel(client.getNickname(), args[1]))
	{
		std::string answer = "442 " + client.getBanger() + " " + args[1] + " :You're not on that channel\r\n"; // ERR_NOTONCHANNEL
		send(client.getSocket(), answer.c_str(), answer.size(), 0);
		return (1);
	}
	else if (isUserInChannel(args[0], args[1]))
	{
		std::string answer = "443 " + client.getBanger() + " " + args[0] + " " + args[1] + " :is already on channel\r\n"; // ERR_USERONCHANNEL
		send(client.getSocket(), answer.c_str(), answer.size(), 0);
		return (1);
	}
	Channel *channel = getChannelByName(args[1]);
	if (channel->isChannelInviteOnly())
	{
		if (!channel->clientIsOp(client.getSocket()))
		{
			std::string answer = "482 " + client.getBanger() + " " + args[1] + " :You're not channel operator\r\n"; // ERR_CHANOPRIVSNEEDED
			send(client.getSocket(), answer.c_str(), answer.size(), 0);
			return (1);
		}
		getClientByName(args[0])->addInvitedChannel(args[1]);
	}
	return (0);
}

int	Server::cmdInvite(std::vector<std::string> args, Client &client)
{
	if (cmdInviteErrorHandling(args, client))
		return (1);
	std::string answer = "341 " + client.getBanger() + " " + args[0] + " " + args[1] + "\r\n"; // RPL_INVITING
	Client	*c = getClientByName(args[0]);
	send(client.getSocket(), answer.c_str(), answer.size(), 0);
	answer = ":" + client.getBanger() + " INVITE " + args[0] + " " + args[1] + "\r\n"; // RPL_INVITING
	send(c->getSocket(), answer.c_str(), answer.size(), 0);
	return (0);
}
