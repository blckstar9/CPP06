/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelaou <aybelaou@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 19:00:00 by aybelaou          #+#    #+#             */
/*   Updated: 2026/04/20 19:00:00 by aybelaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <iostream>
#include <limits>
#include <cstdlib>
#include <cctype>
#include <sstream>
#include <cmath>
#include <cerrno>

namespace
{
	enum t_literal_type
	{
		TYPE_INVALID,
		TYPE_CHAR,
		TYPE_INT,
		TYPE_FLOAT,
		TYPE_DOUBLE
	};

	bool	isNan(double value)
	{
		return (value != value);
	}

	bool	isPosInf(double value)
	{
		return (value == std::numeric_limits<double>::infinity());
	}

	bool	isNegInf(double value)
	{
		return (value == -std::numeric_limits<double>::infinity());
	}

	bool	isPseudoFloatLiteral(const std::string& literal)
	{
		return (literal == "nanf" || literal == "+inff" || literal == "-inff");
	}

	bool	isPseudoDoubleLiteral(const std::string& literal)
	{
		return (literal == "nan" || literal == "+inf" || literal == "-inf");
	}

	bool	isCharLiteral(const std::string& literal)
	{
		return ((literal.length() == 1
			&& std::isprint(static_cast<unsigned char>(literal[0]))
			&& !std::isdigit(static_cast<unsigned char>(literal[0])))
			|| (literal.length() == 3 && literal[0] == '\''
				&& literal[2] == '\''
				&& std::isprint(static_cast<unsigned char>(literal[1]))));
	}

	bool	isIntLiteral(const std::string& literal)
	{
		std::size_t	i;

		if (literal.empty())
			return (false);
		i = 0;
		if (literal[i] == '+' || literal[i] == '-')
			++i;
		if (i == literal.length())
			return (false);
		while (i < literal.length())
		{
			if (!std::isdigit(static_cast<unsigned char>(literal[i])))
				return (false);
			++i;
		}
		return (true);
	}

	bool	isDecimalCore(const std::string& value)
	{
		std::size_t	i;
		bool		hasDot;
		bool		hasDigit;

		i = 0;
		if (i < value.length() && (value[i] == '+' || value[i] == '-'))
			++i;
		hasDot = false;
		hasDigit = false;
		while (i < value.length())
		{
			if (std::isdigit(static_cast<unsigned char>(value[i])))
				hasDigit = true;
			else if (value[i] == '.' && !hasDot)
				hasDot = true;
			else
				break ;
			++i;
		}
		if (!hasDigit)
			return (false);
		if (i < value.length() && (value[i] == 'e' || value[i] == 'E'))
		{
			++i;
			if (i < value.length() && (value[i] == '+' || value[i] == '-'))
				++i;
			hasDigit = false;
			while (i < value.length()
				&& std::isdigit(static_cast<unsigned char>(value[i])))
			{
				hasDigit = true;
				++i;
			}
			return (hasDigit && i == value.length());
		}
		return (hasDot && i == value.length());
	}

	bool	isFloatLiteral(const std::string& literal)
	{
		if (literal.length() < 2 || literal[literal.length() - 1] != 'f')
			return (false);
		return (isDecimalCore(literal.substr(0, literal.length() - 1)));
	}

	bool	isDoubleLiteral(const std::string& literal)
	{
		return (isDecimalCore(literal));
	}

	t_literal_type	detectType(const std::string& literal)
	{
		if (isCharLiteral(literal))
			return (TYPE_CHAR);
		if (isIntLiteral(literal))
			return (TYPE_INT);
		if (isPseudoFloatLiteral(literal) || isFloatLiteral(literal))
			return (TYPE_FLOAT);
		if (isPseudoDoubleLiteral(literal) || isDoubleLiteral(literal))
			return (TYPE_DOUBLE);
		return (TYPE_INVALID);
	}

	bool	parseInt(const std::string& literal, double& value)
	{
		char*	end;
		long	raw;
		int		parsed;

		end = NULL;
		errno = 0;
		raw = std::strtol(literal.c_str(), &end, 10);
		if (*end != '\0' || errno == ERANGE)
			return (false);
		if (raw < std::numeric_limits<int>::min()
			|| raw > std::numeric_limits<int>::max())
			return (false);
		parsed = static_cast<int>(raw);
		value = static_cast<double>(parsed);
		return (true);
	}

	bool	parseDouble(const std::string& literal, double& value)
	{
		char*	end;

		end = NULL;
		value = std::strtod(literal.c_str(), &end);
		return (*end == '\0' && !isPosInf(value) && !isNegInf(value));
	}

	double	pseudoToDouble(const std::string& literal)
	{
		if (literal == "nan" || literal == "nanf")
			return (std::numeric_limits<double>::quiet_NaN());
		if (literal == "+inf" || literal == "+inff")
			return (std::numeric_limits<double>::infinity());
		return (-std::numeric_limits<double>::infinity());
	}

	bool	parseLiteral(const std::string& literal, t_literal_type type,
		double& value)
	{
		float	asFloat;

		if (type == TYPE_CHAR)
		{
			value = static_cast<double>(literal[literal.length() == 3 ? 1 : 0]);
			return (true);
		}
		if (type == TYPE_INT)
			return (parseInt(literal, value));
		if (isPseudoFloatLiteral(literal) || isPseudoDoubleLiteral(literal))
			value = pseudoToDouble(literal);
		else if (type == TYPE_FLOAT)
		{
			if (!parseDouble(literal.substr(0, literal.length() - 1), value)
				|| value > std::numeric_limits<float>::max()
				|| value < -std::numeric_limits<float>::max())
				return (false);
		}
		else if (!parseDouble(literal, value))
			return (false);
		if (type == TYPE_FLOAT)
		{
			asFloat = static_cast<float>(value);
			value = static_cast<double>(asFloat);
		}
		return (true);
	}

	void	printImpossible(void)
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
	}

	std::string	withDecimalPoint(const std::string& value)
	{
		if (value.find_first_of(".eE") == std::string::npos)
			return (value + ".0");
		return (value);
	}

	std::string	formatFloat(double value)
	{
		std::ostringstream	out;

		if (isNan(value))
			return ("nanf");
		if (isPosInf(value))
			return ("+inff");
		if (isNegInf(value))
			return ("-inff");
		if (value > std::numeric_limits<float>::max()
			|| value < -std::numeric_limits<float>::max())
			return ("impossible");
		out << static_cast<float>(value);
		return (withDecimalPoint(out.str()) + "f");
	}

	std::string	formatDouble(double value)
	{
		std::ostringstream	out;

		if (isNan(value))
			return ("nan");
		if (isPosInf(value))
			return ("+inf");
		if (isNegInf(value))
			return ("-inf");
		out << value;
		return (withDecimalPoint(out.str()));
	}
}

void	ScalarConverter::convert(const std::string& literal)
{
	t_literal_type	type;
	double			value;
	int				asInt;
	char			asChar;
	double			intPart;

	type = detectType(literal);
	if (type == TYPE_INVALID || !parseLiteral(literal, type, value))
	{
		printImpossible();
		return ;
	}
	// Floating-to-integer casts truncate before the range check applies.
	std::modf(value, &intPart);
	if (isNan(value) || isPosInf(value) || isNegInf(value)
		|| intPart < std::numeric_limits<char>::min()
		|| intPart > std::numeric_limits<char>::max())
		std::cout << "char: impossible" << std::endl;
	else
	{
		asChar = static_cast<char>(value);
		if (!std::isprint(static_cast<unsigned char>(asChar)))
			std::cout << "char: Non displayable" << std::endl;
		else
			std::cout << "char: '" << asChar << "'" << std::endl;
	}
	if (isNan(value) || isPosInf(value) || isNegInf(value)
		|| intPart < std::numeric_limits<int>::min()
		|| intPart > std::numeric_limits<int>::max())
		std::cout << "int: impossible" << std::endl;
	else
	{
		asInt = static_cast<int>(value);
		std::cout << "int: " << asInt << std::endl;
	}
	std::cout << "float: " << formatFloat(value) << std::endl;
	std::cout << "double: " << formatDouble(value) << std::endl;
}
