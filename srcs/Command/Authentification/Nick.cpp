/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:27:54 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/07/05 19:56:19 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int	Server::parseNickname(std::string &name) const
{
	int	nameSize = name.size();
	for (int i = 0; i < nameSize; ++i)
	{
		if (!isalnum((int)name[i]) && !strchr("{}()[]\\|", name[i]))
			return (1);
	}
	return (0);
}

// Returns 1 if [name] is already used by another user, 0 if not
int	Server::usedNickname(std::string name) const
{
	for (int i = 0; i < MAX_CLIENTS; ++i)
	{
		if (_clients[i] && _clients[i]->getNickname() == name)
			return (1);
	}
	return (0);
}

int	Server::cmdNickErrorHandling(std::vector<std::string> args, Client &client)
{
	if (client.getStatus() < PASSWORD)
	{
		std::string answer = "461 " + client.getNickname() + " PASS :Not enough parameters\r\n"; // ERR_NEEDMOREPARAMS
		send(client.getSocket(), answer.c_str(), answer.size(), 0);
		removeClient(client.getSocket());
		return (1);
	}
	if (parseNickname(args[0]))
	{
		std::string answer = "432 " + client.getNickname() + " " + args[0] + " :Erroneus nickname\r\n"; // ERR_ERRONEUSNICKNAME
		send(client.getSocket(), answer.c_str(), answer.size(), 0);
		return (1);
	}
	// else if (usedNickname(args[0]))
	// {
	// 	std::string answer = "433 " + client.getNickname() + " " + args[0] + " :Nickname is already in use\r\n"; // ERR_ERRONEUSNICKNAME
	// 	send(client.getSocket(), answer.c_str(), answer.size(), 0);
	// 	return (1);
	// }
	return (0);
}

int		Server::cmdNick(std::vector<std::string> args, Client &client)
{
	if (cmdNickErrorHandling(args, client))
		return (1);
	std::string answer = ":" + client.getNickname() + " NICK " + args[0] + "\r\n";
	send(client.getSocket(), answer.c_str(), answer.size(), 0);
	client.setNickname(args[0]);
	return (0);
}
