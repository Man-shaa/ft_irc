/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:30:41 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/08/06 02:42:29 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int Server::cmdPrivmsg(std::vector<std::string> args, Client &client)
{
	// cf. https://modern.ircdocs.horse/#privmsg-message
	for (int i = 0; _channels[i]; ++i)
	{
		if (_channels[i]->getName() == args[0])
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
