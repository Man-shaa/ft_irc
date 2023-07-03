/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:42:20 by msharifi          #+#    #+#             */
/*   Updated: 2023/07/02 16:51:42 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(void) : _socketFd(-1), _nickName(""), _id(-1), _channels(0)
{
	return ;
}

Client::Client(int socketFd, std::string nickname, int id) : _socketFd(socketFd), _nickName(nickname), _id(id), _channels(0)
{
	_fds_clt.fd = socketFd;
	_fds_clt.events = POLLIN;
	return ;
}

Client::~Client(void)
{
	return ;
}
