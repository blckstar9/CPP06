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

#include "ScalarConverter.hpp"
#include <iostream>
#include <sstream>
#include <string>

struct t_test_case
{
	const char*	input;
	const char*	expected;
};

static std::string	captureConvert(const std::string& input)
{
	std::ostringstream	buffer;
	std::streambuf*		oldBuffer;

	oldBuffer = std::cout.rdbuf(buffer.rdbuf());
	ScalarConverter::convert(input);
	std::cout.rdbuf(oldBuffer);
	return (buffer.str());
}

static bool	runTestCase(const t_test_case& testCase, int index)
{
	std::string	output;

	output = captureConvert(testCase.input);
	if (output == testCase.expected)
	{
		std::cout << "[OK] test #" << index << " -> \"" << testCase.input << "\""
			<< std::endl;
		return (true);
	}
	std::cout << "[KO] test #" << index << " -> \"" << testCase.input << "\""
		<< std::endl;
	std::cout << "Expected:" << std::endl << testCase.expected;
	std::cout << "Got:" << std::endl << output;
	return (false);
}

int	main(void)
{
	t_test_case	tests[] = {
		{"0", "char: Non displayable\nint: 0\nfloat: 0.0f\ndouble: 0.0\n"},
		{"a", "char: 'a'\nint: 97\nfloat: 97.0f\ndouble: 97.0\n"},
		{"42.0f", "char: '*'\nint: 42\nfloat: 42.0f\ndouble: 42.0\n"},
		{"nan", "char: impossible\nint: impossible\nfloat: nanf\ndouble: nan\n"},
		{"nanf", "char: impossible\nint: impossible\nfloat: nanf\ndouble: nan\n"},
		{"+inf", "char: impossible\nint: impossible\nfloat: +inff\ndouble: +inf\n"},
		{"-inff", "char: impossible\nint: impossible\nfloat: -inff\ndouble: -inf\n"},
		{"1.5", "char: Non displayable\nint: 1\nfloat: 1.5f\ndouble: 1.5\n"},
		{"1.5f", "char: Non displayable\nint: 1\nfloat: 1.5f\ndouble: 1.5\n"},
		{"65", "char: 'A'\nint: 65\nfloat: 65.0f\ndouble: 65.0\n"},
		{"127", "char: Non displayable\nint: 127\nfloat: 127.0f\ndouble: 127.0\n"},
		{"2147483648", "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible\n"},
		{"42f", "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible\n"},
		{".", "char: '.'\nint: 46\nfloat: 46.0f\ndouble: 46.0\n"},
		{"'7'", "char: '7'\nint: 55\nfloat: 55.0f\ndouble: 55.0\n"},
		{"16777217.0f", "char: impossible\nint: 16777216\nfloat: 1.67772e+07f\ndouble: 1.67772e+07\n"},
		{"16777217.0", "char: impossible\nint: 16777217\nfloat: 1.67772e+07f\ndouble: 1.67772e+07\n"},
		{"2147483647.0f", "char: impossible\nint: impossible\nfloat: 2.14748e+09f\ndouble: 2.14748e+09\n"},
		{"2147483647.9", "char: impossible\nint: 2147483647\nfloat: 2.14748e+09f\ndouble: 2.14748e+09\n"},
		{"-2147483648.9", "char: impossible\nint: -2147483648\nfloat: -2.14748e+09f\ndouble: -2.14748e+09\n"},
		{"127.9", "char: Non displayable\nint: 127\nfloat: 127.9f\ndouble: 127.9\n"},
		{"-.5f", "char: Non displayable\nint: 0\nfloat: -0.5f\ndouble: -0.5\n"},
		{"42.", "char: '*'\nint: 42\nfloat: 42.0f\ndouble: 42.0\n"},
		{"1e3", "char: impossible\nint: 1000\nfloat: 1000.0f\ndouble: 1000.0\n"},
		{"4.2E+1f", "char: '*'\nint: 42\nfloat: 42.0f\ndouble: 42.0\n"},
		{"-inf", "char: impossible\nint: impossible\nfloat: -inff\ndouble: -inf\n"},
		{"+inff", "char: impossible\nint: impossible\nfloat: +inff\ndouble: +inf\n"},
		{"1e39", "char: impossible\nint: impossible\nfloat: impossible\ndouble: 1e+39\n"},
		{"1e-40f", "char: Non displayable\nint: 0\nfloat: 9.99995e-41f\ndouble: 9.99995e-41\n"},
		{"-0.0f", "char: Non displayable\nint: 0\nfloat: -0.0f\ndouble: -0.0\n"},
		{"", "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible\n"},
		{"abc", "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible\n"},
		{"42abc", "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible\n"},
		{" 42", "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible\n"},
		{"42 ", "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible\n"},
		{"1.2.3", "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible\n"},
		{"++42", "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible\n"},
		{"--42", "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible\n"},
		{"1e", "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible\n"},
		{"1e+", "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible\n"},
		{".e2", "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible\n"},
		{"42ff", "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible\n"},
		{"0x2a", "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible\n"},
		{"0x1.2p3", "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible\n"},
		{"nan(payload)", "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible\n"},
		{"2147483649", "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible\n"},
		{"-2147483649", "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible\n"},
		{"999999999999999999999999999999999999", "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible\n"},
		{"1e39f", "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible\n"},
		{"-1e39f", "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible\n"},
		{"1e309", "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible\n"},
		{"-1e309", "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible\n"},
		{"\n", "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible\n"}
	};
	int			totalTests;
	int			i;
	int			passed;

	totalTests = static_cast<int>(sizeof(tests) / sizeof(tests[0]));
	i = 0;
	passed = 0;
	while (i < totalTests)
	{
		if (runTestCase(tests[i], i + 1))
			++passed;
		++i;
	}
	std::cout << "Result: " << passed << "/" << totalTests
		<< " tests passed." << std::endl;
	return (passed == totalTests ? 0 : 1);
}
