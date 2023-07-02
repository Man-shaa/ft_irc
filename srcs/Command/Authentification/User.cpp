/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:29:10 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/07/02 16:29:42 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int		Server::cmdUser(std::vector<std::string> args, Client &client)
{
	//TODO Gérer le <realname> cf. https://modern.ircdocs.horse/#user-message
	//TODO Gérer le ERR_ALREADYREGISTERED :  "<client> :You may not reregister"
	//TODO Tronquer le username si il dépasse la taille de USERLEN = 12
	// if ( == NULL)
	// 	return (1);
	if (args[0].empty())
		args[0] = "bob";
	std::vector<std::string>::iterator it = (--args.end());
	client.setLastName(*it);
	--it;
	std::string firstName = (*it).substr(1, (*it).size() - 1);
	client.setFirstName(firstName);
	std::string answer = "001 " + args[0] + " :Welcome to the Internet Relay Network " + args[0] + "\r\n";
	send(client.getSocket(), answer.c_str(), answer.size(), 0);
	return (0);
}
