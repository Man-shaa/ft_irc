/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:30:41 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/08/06 04:24:53 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int Server::cmdPrivmsg(std::vector<std::string> args, Client &client)
{
	for (size_t i = 0; i < _channels.size(); ++i) 
	{
		if (_channels[i] && _channels[i]->getName() == args[0])
		{
			std::string msg = ":" + client.getNickname() + " PRIVMSG " + args[0];
			for (std::vector<std::string>::const_iterator it = args.begin() + 1; it != args.end(); ++it)
			{
				msg += " " + *it;
			}
			msg += "\r\n";
			_channels[i]->sendMsg(msg, client);
			break;
		}
	}
	return (0);
}
