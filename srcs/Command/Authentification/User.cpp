/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:29:10 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/08/06 04:08:18 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int		Server::cmdUser(std::vector<std::string> args, Client &client)
{
	//TODO Gérer le <realname> cf. https://modern.ircdocs.horse/#user-message
	if (client.getStatus() < PASSWORD)
		return (1);
	else if (client.getStatus() == CONNECT)
	{
		std::string	answer = "462 " + client.getBanger() + " :You may not reregister\r\n";
		send(client.getSocket(), answer.c_str(), answer.size(), 0);
	}
	if (args[0].empty())
		args[0] = "bob";
	if (args[0].size() > 12)
		args[0] = args[0].substr(0, 11);
	client.setUserName(args[0]);
	std::vector<std::string>::iterator it = (--args.end());
	client.setLastName(*it);
	--it;
	std::string firstName = (*it).substr(1, (*it).size() - 1);
	client.setFirstName(firstName);
	std::string answer = "001 " + args[0] + " :Welcome to the Internet Relay Network " + args[0] + "\r\n";
	send(client.getSocket(), answer.c_str(), answer.size(), 0);
	client.setStatus(CONNECT);
	return (0);
}
