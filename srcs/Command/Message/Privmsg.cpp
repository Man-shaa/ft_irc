/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:30:41 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/07/02 16:30:54 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int		Server::cmdPrivmsg(std::vector<std::string> args, Client &client)
{
	//cf. https://modern.ircdocs.horse/#privmsg-message
	for (int i = 0; _channels[i]; ++i) 
	{
		if (_channels[i]->getName() == args[0])
		{
			std::string msg = ":" + client.getNickname() + " PRIVMSG " + args[0] + " " + args[1] + "\r\n";
			_channels[i]->sendMsg(msg, client);
			break;
		}
	}
	return (0);
}
