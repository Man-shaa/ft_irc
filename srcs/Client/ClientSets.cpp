/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSets.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:50:20 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/07/02 16:51:22 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

void	Client::setNickname(std::string &name)
{
	_nickName = name;
}

void	Client::setFirstName(std::string &name)
{
	_firstName = name;
}

void	Client::setLastName(std::string &name)
{
	_lastName = name;
}

void	Client::setStatus(int status)
{
	_status = status;
}
