/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelaou <aybelaou@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 19:00:00 by aybelaou          #+#    #+#             */
/*   Updated: 2026/04/20 19:00:00 by aybelaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Identify.hpp"
#include <iostream>

int	main(void)
{
	Base*	randomClass;
	int		i;

	i = 0;
	while (i < 10)
	{
		randomClass = generate();
		std::cout << "identify(Base*): ";
		identify(randomClass);
		std::cout << "identify(Base&): ";
		identify(*randomClass);
		delete randomClass;
		std::cout << "-----" << std::endl;
		++i;
	}
	return (0);
}
