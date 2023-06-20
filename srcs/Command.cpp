/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:41:05 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/06/20 19:27:23 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::initCmd()
{
	_mapFcts["USER"] = &Server::cmdUser;
}


int		Server::cmdUser(std::string & arg1)
{
	std::string answer = "001 " + arg1 + " :Welcome to the Internet Relay Network " + arg1 + "\r\n";
	_clients[getClientByFd(_fd)->getId()]->setNickName(arg1);
	send(_fd, answer.c_str(), answer.size(), 0);
	return (0);
}