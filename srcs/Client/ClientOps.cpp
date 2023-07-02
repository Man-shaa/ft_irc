/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientOps.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:50:52 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/07/02 16:51:05 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

void Client::addChannel(Channel& channel)
{
	_channels.push_back(&channel);
}

void Client::removeChannel(const Channel& channel)
{
    for (std::vector<Channel*>::iterator it = _channels.begin(); it != _channels.end(); ++it) {
        if (*it == &channel) {
            _channels.erase(it);
            break; // Sortie de la boucle après avoir trouvé et supprimé l'objet Channel
        }
    }
}
