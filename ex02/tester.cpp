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

#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include "Identify.hpp"
#include <iostream>
#include <sstream>
#include <string>

static std::string	captureIdentifyPointer(Base* p)
{
	std::ostringstream	buffer;
	std::streambuf*		oldBuffer;

	oldBuffer = std::cout.rdbuf(buffer.rdbuf());
	identify(p);
	std::cout.rdbuf(oldBuffer);
	return (buffer.str());
}

static std::string	captureIdentifyReference(Base& p)
{
	std::ostringstream	buffer;
	std::streambuf*		oldBuffer;

	oldBuffer = std::cout.rdbuf(buffer.rdbuf());
	identify(p);
	std::cout.rdbuf(oldBuffer);
	return (buffer.str());
}

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

static bool	isKnownOutput(const std::string& output)
{
	return (output == "A\n" || output == "B\n" || output == "C\n");
}

int	main(void)
{
	int			failures;
	A			a;
	B			b;
	C			c;
	Base		unknown;
	bool		validPointers;
	bool		validTypes;
	bool		matchingTypes;
	Base*		randomPtr;
	std::string	pOut;
	std::string	rOut;
	int			i;
	int			seenA;
	int			seenB;
	int			seenC;

	failures = 0;
	expect(captureIdentifyPointer(&a) == "A\n", "identify(Base*) -> A", failures);
	expect(captureIdentifyPointer(&b) == "B\n", "identify(Base*) -> B", failures);
	expect(captureIdentifyPointer(&c) == "C\n", "identify(Base*) -> C", failures);
	expect(captureIdentifyReference(a) == "A\n", "identify(Base&) -> A", failures);
	expect(captureIdentifyReference(b) == "B\n", "identify(Base&) -> B", failures);
	expect(captureIdentifyReference(c) == "C\n", "identify(Base&) -> C", failures);
	expect(captureIdentifyPointer(NULL) == "Unknown\n", "identify(Base*) -> NULL", failures);
	expect(captureIdentifyPointer(&unknown) == "Unknown\n",
		"identify(Base*) -> Base", failures);
	expect(captureIdentifyReference(unknown) == "Unknown\n",
		"identify(Base&) -> Base", failures);
	validPointers = true;
	validTypes = true;
	matchingTypes = true;
	seenA = 0;
	seenB = 0;
	seenC = 0;
	i = 0;
	while (i < 300)
	{
		randomPtr = generate();
		validPointers = validPointers && randomPtr != NULL;
		if (randomPtr != NULL)
		{
			pOut = captureIdentifyPointer(randomPtr);
			rOut = captureIdentifyReference(*randomPtr);
			validTypes = validTypes && isKnownOutput(pOut);
			matchingTypes = matchingTypes && pOut == rOut;
			if (pOut == "A\n")
				++seenA;
			else if (pOut == "B\n")
				++seenB;
			else if (pOut == "C\n")
				++seenC;
			delete randomPtr;
		}
		++i;
	}
	expect(validPointers, "generate() returned 300 valid pointers", failures);
	expect(validTypes, "All generated types are A/B/C", failures);
	expect(matchingTypes, "Pointer and reference identifications match", failures);
	expect(seenA > 0, "generate() produced A at least once", failures);
	expect(seenB > 0, "generate() produced B at least once", failures);
	expect(seenC > 0, "generate() produced C at least once", failures);
	std::cout << "Seen counts -> A: " << seenA << ", B: " << seenB
		<< ", C: " << seenC << std::endl;
	std::cout << "Result: " << (failures == 0 ? "all tests passed." : "test failure(s).")
		<< std::endl;
	return (failures == 0 ? 0 : 1);
}
