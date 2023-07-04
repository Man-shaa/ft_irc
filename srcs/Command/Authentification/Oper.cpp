/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Oper.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:22:26 by msharifi          #+#    #+#             */
/*   Updated: 2023/07/04 15:56:23 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int	Server::cmdOperErrorHandling(std::vector<std::string> args, Client &client)
{
	// if (args[0] != client.getNickname())
	// {
	// 	std::string answer = "502 " + client.getNickname() + " :Cant change mode for other users\r\n"; // ERR_USERSDONTMATCH
	// 	send(client.getSocket(), answer.c_str(), answer.size(), 0);
	// 	return (1);
	// }
	if (args.size() < 2 || args[0].empty() == true)
	{
		std::string answer = "461 " + client.getNickname() + " OPER :Not enough parameters\r\n"; // ERR_NEEDMOREPARAMS
		send(client.getSocket(), answer.c_str(), answer.size(), 0);
		return (1);
	}
	else if (args[0] != OPERNAME || args[1] != OPERPASS)
	{
		std::string answer = "464 " + client.getNickname() + " :Password incorrect\r\n"; // ERR_PASSWDMISMATCH
		send(client.getSocket(), answer.c_str(), answer.size(), 0);
		return (1);
	}
	return (0);
}

int	Server::cmdOper(std::vector<std::string> args, Client &client)
{
	if (cmdOperErrorHandling(args, client))
		return (1);
	std::string answer = "381 " + client.getNickname() + " :You are now an IRC operator\r\n"; // RPL_YOUREOPER
	send(client.getSocket(), answer.c_str(), answer.size(), 0);
	answer = ":" + client.getNickname() + "@localhost MODE " + client.getNickname() + " +o\r\n"; // RPL_YOUREOPER
	send(client.getSocket(), answer.c_str(), answer.size(), 0);
	return (0);
}
