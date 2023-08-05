/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:42:20 by msharifi          #+#    #+#             */
/*   Updated: 2023/08/05 17:11:49 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(void) : _socketFd(-1), _nickName(""), _status(ACCEPT), _channels(0)
{
	return ;
}

Client::Client(int socketFd, std::string nickname) : _socketFd(socketFd), _nickName(nickname), _banger(nickname), _status(ACCEPT), _channels(0)
{
	_fds_clt.fd = socketFd;
	_fds_clt.events = POLLIN;
	return ;
}

Client::~Client(void)
{
	return ;
}
