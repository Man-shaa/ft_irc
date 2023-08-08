/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 19:28:11 by msharifi          #+#    #+#             */
/*   Updated: 2023/08/08 19:18:43 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int	Server::cmdKickErrorHandling(std::vector<std::string> args, Client &client)
{
	if (args.size() < 2)
	{
		std::string answer = "461 " + client.getBanger() + " KICK :not enough parameters\r\n"; // ERR_NEEDMOREPARAMS
		send(client.getSocket(), answer.c_str(), answer.size(), 0);
		return (1);
	}
	else if (!doesChannelExist(args[0]))
	{
		std::string answer = "403 " + client.getBanger() + " " + args[0] + " :No such channel\r\n"; // ERR_NOSUCHCHANNEL
		send(client.getSocket(), answer.c_str(), answer.size(), 0);
		return (1);
	}
	else if (!isUserInChannel(client.getNickname(), args[0]))
	{
		std::string answer = "442 " + client.getBanger() + " " + args[0] + " :You're not on that channel\r\n"; // ERR_NOTONCHANNEL
		send(client.getSocket(), answer.c_str(), answer.size(), 0);
		return (1);
	}
	else if (!isUserInChannel(args[1], args[0]))
	{
		std::string answer = "441 " + client.getBanger() + " " + args[1] + " " + args[0] + " :They aren't on that channel\r\n"; // ERR_USERNOTINCHANNEL
		send(client.getSocket(), answer.c_str(), answer.size(), 0);
		return (1);
	}
	else if (!getChannelByName(args[0])->clientIsOp(client.getSocket()))
	{
		std::string answer = "482 " + client.getBanger() + " " + args[0] + " :You're not channel operator\r\n"; // ERR_CHANOPRIVSNEEDED
		send(client.getSocket(), answer.c_str(), answer.size(), 0);
		return (1);
	}
	return (0);
}

int	Server::cmdKick(std::vector<std::string> args, Client &client)
{
	if (cmdKickErrorHandling(args, client) || getClientByName(args[1])->getSocket() == 4)
		return (1);
	std::string answer = ":" + getClientByName(args[1])->getBanger() + " PART " + args[0] + "\r\n";
	send(getClientByName(args[1])->getSocket(), answer.c_str(), answer.size(), 0);
	if (args[2].size() != 1)
	{
		std::string	argsStr;
		for (std::vector<std::string>::iterator it = args.begin() + 2; it != args.end(); ++it)
			argsStr += *it + " ";
		answer = ":" + client.getBanger() + " KICK " + args[0] + " " + args[1] + " :" + argsStr.substr(1, argsStr.size() - 2) + "\r\n"; // ERR_NOTONCHANNEL
	}
	else
	{
		answer = ":" + client.getBanger() + " KICK " + args[0] + " " + args[1] + " :Unknown reason\r\n"; // ERR_NOTONCHANNEL
	}
	getChannelByName(args[0])->sendMsgToChannel(answer);

	Channel	*channel = getChannelByName(args[0]);
	Client	*target = getClientByName(args[1]);
	target->removeChannel(*channel);
	if (channel->remUser(*target))
		delChannel(args[0]);
	return (0);
}
