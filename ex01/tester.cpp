/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelaou <aybelaou@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 19:00:00 by aybelaou          #+#    #+#             */
/*   Updated: 2026/04/20 19:00:00 by aybelaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"
#include <iostream>

static void	expect(bool condition, const char* message, int& failures)
{
	if (condition)
		std::cout << "[OK] " << message << std::endl;
	else
	{
		std::cout << "[KO] " << message << std::endl;
		++failures;
	}
}

int	main(void)
{
	int			failures;
	Data		stackData;
	Data*		stackPtr;
	uintptr_t	stackRaw;
	Data*		stackBack;
	Data*		heapData;
	uintptr_t	heapRaw;
	Data*		heapBack;
	uintptr_t	nullRaw;
	Data*		nullBack;

	failures = 0;
	stackData.name = "stack";
	stackData.level = 1;
	stackData.score = 42.42;
	stackPtr = &stackData;
	stackRaw = Serializer::serialize(stackPtr);
	stackBack = Serializer::deserialize(stackRaw);
	expect(stackBack == stackPtr, "Stack pointer round-trip", failures);
	expect(stackBack->name == "stack", "Stack data name preserved", failures);
	expect(stackBack->level == 1, "Stack data level preserved", failures);
	expect(stackBack->score == 42.42, "Stack data score preserved", failures);
	heapData = new Data;
	heapData->name = "heap";
	heapData->level = 99;
	heapData->score = -1.5;
	heapRaw = Serializer::serialize(heapData);
	heapBack = Serializer::deserialize(heapRaw);
	expect(heapBack == heapData, "Heap pointer round-trip", failures);
	expect(heapBack->name == "heap", "Heap data name preserved", failures);
	expect(heapBack->level == 99, "Heap data level preserved", failures);
	expect(heapBack->score == -1.5, "Heap data score preserved", failures);
	delete heapData;
	nullRaw = Serializer::serialize(NULL);
	nullBack = Serializer::deserialize(nullRaw);
	expect(nullBack == NULL, "NULL pointer round-trip", failures);
	std::cout << "Result: " << (failures == 0 ? "all tests passed." : "test failure(s).")
		<< std::endl;
	return (failures == 0 ? 0 : 1);
}
