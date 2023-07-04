/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 19:28:11 by msharifi          #+#    #+#             */
/*   Updated: 2023/07/04 23:09:03 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int	Server::cmdKickErrorHandling(std::vector<std::string> args, Client &client)
{
	if (args.size() < 2)
	{
		std::string answer = "461 " + client.getNickname() + "@localhost KICK :not enough parameters\r\n"; // ERR_NEEDMOREPARAMS
		send(client.getSocket(), answer.c_str(), answer.size(), 0);
		return (1);
	}
	else if (!doesChannelExist(args[0]))
	{
		std::string answer = "403 " + client.getNickname() + "@localhost " + args[0] + " :No such channel\r\n"; // ERR_NOSUCHCHANNEL
		send(client.getSocket(), answer.c_str(), answer.size(), 0);
		return (1);
	}
	
	
	
	
	
	
	
	// ICI
	if (!getChannelByName(args[0])->clientIsOp(client.getSocket()))
	{
		std::string answer = "482 " + client.getNickname() + "@localhost " + args[0] + " :You're not channel operator\r\n"; // ERR_CHANOPRIVSNEEDED
		send(client.getSocket(), answer.c_str(), answer.size(), 0);
		return (1);
	}
	else if (!isUserInChannel(args[1], args[0]))
	{
		std::string answer = "441 " + client.getNickname() + "@localhost " + args[1] + " " + args[0] + " :They aren't on that channel\r\n"; // ERR_USERNOTINCHANNEL
		send(client.getSocket(), answer.c_str(), answer.size(), 0);
		return (1);
	}
	else if (!isUserInChannel(client.getNickname(), args[0]))
	{
		std::string answer = "442 " + client.getNickname() + "@localhost " + args[0] + " :You're not on that channel\r\n"; // ERR_NOTONCHANNEL
		send(client.getSocket(), answer.c_str(), answer.size(), 0);
		return (1);
	}
	return (0);
}

int	Server::cmdKick(std::vector<std::string> args, Client &client)
{
	if (cmdKickErrorHandling(args, client))
		return (1);
	// for (std::vector<std::string>::iterator it = args.begin(); it != args.end(); ++it)
	// 	std::cout << *it << std::endl;
	std::string answer = ":" + args[1] + "@localhost PART " + args[0] + "\r\n";
	send(getClientByName(args[1])->getSocket(), answer.c_str(), answer.size(), 0);
	if (args[2].size() != 1)
	{
		std::string	argsStr;
		for (std::vector<std::string>::iterator it = args.begin() + 2; it != args.end(); ++it)
			argsStr += *it + " ";
		answer = ":" + client.getNickname() + "@localhost KICK " + args[0] + " " + args[1] + " :" + argsStr.substr(1, argsStr.size() - 2) + "\r\n"; // ERR_NOTONCHANNEL
	}
	else
	{
		answer = ":" + client.getNickname() + "@localhost KICK " + args[0] + " " + args[1] + " :Unknown reason\r\n"; // ERR_NOTONCHANNEL
	}
	getChannelByName(args[0])->sendMsgToChannel(answer);
	// send(client.getSocket(), answer.c_str(), answer.size(), 0);

	Channel	*channel = getChannelByName(args[0]);
	client.removeChannel(*channel);
	if (channel->remUser(client))
		delChannel(args[0]);
	return (0);
}
