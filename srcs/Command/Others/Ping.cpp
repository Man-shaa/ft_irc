/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:31:08 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/07/05 18:50:18 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int		Server::cmdPing(std::vector<std::string> args, Client &client)
{
	std::string pong = "PONG :server.name " + args[0] + "\r\n";
	send(client.getSocket(), pong.c_str(), pong.size(), 0);
	_IP = args[0];
	
	return (0);
}
