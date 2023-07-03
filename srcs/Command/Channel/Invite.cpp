/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 20:52:40 by msharifi          #+#    #+#             */
/*   Updated: 2023/07/03 22:31:32 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int	Server::cmdInvite(std::vector<std::string> args, Client &client)
{
	std::cout << "ARGS0 : " << args[0] << std::endl;
	std::cout << "ARGS1 : " << args[1] << std::endl;
	if (args.size() < 2)
	{
		std::cout << "NIQUE TON PERE ++" << std::endl;
		std::string answer = "461 :" + client.getNickname() + "@localhost INVITE :not enough parameters\r\n"; // ERR_NEEDMOREPARAMS
		send(client.getSocket(), answer.c_str(), answer.size(), 0);
		return (1);
	}
	else if (!doesChannelExist(args[1]))
	{
		std::cout << "NIQUE TON FRERE ++" << std::endl;
		std::string answer = "403 :" + client.getNickname() + "@localhost " + args[1] + " :No such channel\r\n"; // ERR_NOSUCHCHANNEL
		send(client.getSocket(), answer.c_str(), answer.size(), 0);
		return (1);
	}
	else if (!isUserInChannel(client.getNickname(), args[1]))
	{
		std::cout << "NIQUE TA SOEUR ++" << std::endl;
		std::string answer = "442 :" + client.getNickname() + "@localhost " + args[1] + " :You're not on that channel\r\n"; // ERR_NOTONCHANNEL
		send(client.getSocket(), answer.c_str(), answer.size(), 0);
		return (1);
	}
	else if (isUserInChannel(args[0], args[1]))
	{
		std::cout << "NIQUE TON CHIEN ++" << std::endl;
		std::string answer = "443 :" + client.getNickname() + "@localhost " + args[0] + " " + args[1] + " :is already on channel\r\n"; // ERR_USERONCHANNEL
		send(client.getSocket(), answer.c_str(), answer.size(), 0);
		return (1);
	}
	else
	{
		std::cout << "NIQUE TA MERE ++" << std::endl;
		std::string answer = "341 :" + client.getNickname() + "@localhost " + args[0] + " " + args[1] + "\r\n"; // RPL_INVITING
		Client	*c = getClientByName(args[0]);
		send(client.getSocket(), answer.c_str(), answer.size(), 0);
		answer = ":" + client.getNickname() + "@localhost INVITE " + args[0] + " " + args[1] + "\r\n"; // RPL_INVITING
		send(c->getSocket(), answer.c_str(), answer.size(), 0);
	}
	std::cout << "----			FIN				---" << std::endl;
	return (0);
}
