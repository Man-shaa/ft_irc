/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSets.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:50:20 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/07/05 17:23:14 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

void	Client::setNickname(std::string name)
{
	_nickName = name;
}

void	Client::setFirstName(std::string name)
{
	_firstName = name;
}

void	Client::setLastName(std::string name)
{
	_lastName = name;
}

void	Client::setStatus(int status)
{
	_status = status;
}

void	Client::setUserName(std::string name)
{
	name = _userName;
}

void	Client::setModeLevel(int level)
{
	_modeLevel = level;
}
