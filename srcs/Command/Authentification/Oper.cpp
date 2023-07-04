/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Oper.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:22:26 by msharifi          #+#    #+#             */
/*   Updated: 2023/07/04 14:24:38 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int	Server::cmdOper(std::vector<std::string> args, Client &client)
{
	if (!usedNickname(args[0]))
	{
		std::string answer = "401 " + client.getNickname() + " " + client.getNickname() + " :No such nick/channel\r\n"; // ERR_NOSUCHNICK
		send(client.getSocket(), answer.c_str(), answer.size(), 0);
		return (1);
	}
	else if (args[0] != client.getNickname())
	{
		std::string answer = "502 " + client.getNickname() + " :Cant change mode for other users\r\n"; // ERR_USERSDONTMATCH
		send(client.getSocket(), answer.c_str(), answer.size(), 0);
		return (1);
	}
	if (args.size() == 1)
	{
		std::string answer = "221 " + client.getNickname() + " " + client.getModeLevelStr() + "\r\n"; // RPL_UMODEIS
		send(client.getSocket(), answer.c_str(), answer.size(), 0);
	}
	else if (args.size() == 2)
	{
		int	n = -1;
		if (args[1] == "+r")
			n = USER;
		else if (args[1] == "+o")
			n = OPERATOR;
		if (n == USER || n == OPERATOR)
		{
			client.setModeLevel(n);
			std::string answer = "MODE " + client.getNickname() + " " + args[1] + "\r\n";
			send(client.getSocket(), answer.c_str(), answer.size(), 0);
		}
		else
		{
			std::string answer = "501 " + client.getNickname() + " :Unknown MODE flag\r\n"; // ERR_UMODEUNKNOWNFLAG
			send(client.getSocket(), answer.c_str(), answer.size(), 0);
			// return (1); // utile ?
		}
	}
	return (0);
}
