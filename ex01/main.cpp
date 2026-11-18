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

#include "Serializer.hpp"
#include <iostream>

int	main(void)
{
	Data		data;
	Data*		originalPtr;
	uintptr_t	raw;
	Data*		deserializedPtr;

	data.name = "Ayoub";
	data.level = 42;
	data.score = 19.95;
	originalPtr = &data;
	raw = Serializer::serialize(originalPtr);
	deserializedPtr = Serializer::deserialize(raw);
	std::cout << "Original pointer:     " << originalPtr << std::endl;
	std::cout << "Serialized uintptr_t: " << raw << std::endl;
	std::cout << "Deserialized pointer: " << deserializedPtr << std::endl;
	if (originalPtr == deserializedPtr)
		std::cout << "Pointers are equal." << std::endl;
	else
		std::cout << "Pointers are NOT equal." << std::endl;
	std::cout << "Data content: "
		<< deserializedPtr->name << ", "
		<< deserializedPtr->level << ", "
		<< deserializedPtr->score << std::endl;
	return (0);
}
