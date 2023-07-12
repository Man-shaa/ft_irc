/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:41:05 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/07/12 17:16:44 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

#define VALID_CHAR "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz-_"

void	Server::initCmd()
{
	_mapFcts["PASS"] = &Server::cmdPass;
	_mapFcts["NICK"] = &Server::cmdNick;
	_mapFcts["USER"] = &Server::cmdUser;
	_mapFcts["JOIN"] = &Server::cmdJoin;
	_mapFcts["PART"] = &Server::cmdPart;
	_mapFcts["MODE"] = &Server::cmdMode;
	_mapFcts["PING"] = &Server::cmdPing;
	_mapFcts["TOPIC"] = &Server::cmdTopic;
	_mapFcts["WHO"] = 	&Server::cmdWho;
	_mapFcts["PRIVMSG"] = &Server::cmdPrivmsg;
	_mapFcts["INVITE"] = &Server::cmdInvite;
	_mapFcts["OPER"] = &Server::cmdOper;
	_mapFcts["KICK"] = &Server::cmdKick;
	_mapFcts["KILL"] = &Server::cmdKill;
}
