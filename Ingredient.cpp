#include "COP3503su14_Proj3_Ingredient_WoldegiorigsD.h"


// ----------------------- INGREDIENT ----------------------- //

// Constructor: Default
Ingredient::Ingredient()
{}

// This function sets an Ingredient property
void Ingredient::add(std::string value, int type)
{
	switch(type)
	{
		// fooditem
		case 1:
			name = value;
			return;
		// description
		case 0:
			state = value;
			return;
	}
}

// This function adds a Quantity to the ingredient
void Ingredient::add(Quantity amount)
{
	quantity = amount;
}

// This function returns the quantity of the Ingredient
Quantity Ingredient::get_quantity()
{
	return quantity;
}

// This funciton returns the name of the Ingredient
std::string Ingredient::get_name()
{
	return name;
}

// This function prints the Ingredient to console
void Ingredient::print()
{
	quantity.print();

	// check for description
	if (state.empty())
		std::cout << name << std::endl;
	else
		std::cout << name << " " << state << std::endl;
}

// This function writes Ingredient to an open file stream
void Ingredient::save(std::ofstream &os)
{
	os << "<ingredient>" << std::endl;
	quantity.save(os);
	os << "<fooditem>" << name << "</fooditem>" << state << std::endl;
	os << "</ingredient>" << std::endl;
}

// Equivalency
bool Ingredient::operator==(const Ingredient &other)
{
	if (name == other.name && state == other.state && quantity == other.quantity)
		return true;
	return false;
}

// Addition
void Ingredient::operator+=(const Ingredient &addend)
{
	quantity += addend.quantity;
}

// Subtraction
void Ingredient::operator-=(const Ingredient &subtrahend)
{
	quantity -= subtrahend.quantity;
}

// ----------------------- QUANTITY ----------------------- //

// Constructor: Default
Quantity::Quantity()
{
	whole = 0;
	numerator = 0;
	denominator = 1;
	fraction = false;
	mixed = false;
	silent = false;
}

// This function initializes the amount or unit of the quantity
void Quantity::add(std::string value, int type)
{
	if (type == 1)
	{
		quantity = value;
		int fail = bad();
		if (fail)
		{
			quantity = "1";
			switch(fail)
			{
				case 1:
					std::cerr << "Illegal character: Quantity must be a number or fraction" << std::endl;
					break;
				case 2:
					std::cerr << "Illegal spacing: Mixed fraction must be of format -- <whole_number> <numerator>/<denominator>" << std::endl;
					break;
				case 3:
					std::cerr << "Illegal division: Fraction must be of format -- <numerator>/<denominator>" << std::endl;
					break;
			}
		}
		to_number();
		return;
	}
	else if (type == 2)
	{
		unit.set(value);
		return;
	}
}

// This function checks for bad formatting
// 0: Valid
// 1: Invalid character
// 2: Illegal spacing
// 3: Illegal division
int Quantity::bad()
{
	// first character must be a digit
	if (!isdigit(quantity[0]))
		return 1;
	for (auto c : quantity)
	{
		// space for mixed fraction
		if (c == ' ')
		{
			if (!mixed)
				mixed = true;
			else
				return 2;
		}
		// fraction
		else if (c == '/')
		{
			if (!fraction)
				fraction = true;
			else
				return 3;	
		}
		// other non-digit characters
		else if (!isdigit(c))
			return 1;
	}
	// check if mixed number has fractional part
	if (mixed && !fraction)
		return 2;
	// good
	return 0;
}

// This function converts string amount to number
void Quantity::to_number()
{
	// positions
	int space = 0;
	int division = 0;

	// find space and division location
	for (int i = 0; i < quantity.size(); ++i)
	{
		if (quantity[i] == '/')
				division = i;
		else if (quantity[i] == ' ')
			space = i;
	}

	// whole number
	if (!fraction)
	{
		whole = create(quantity.size(), 0);
		return;
	}
	// simple fraction
	else if (fraction && !mixed)
	{
		numerator = create(division, 0);
		denominator = create(quantity.size(), division+1);
	}
	// mixed fraction
	else if (mixed && fraction)
	{
		whole = create(space, 0);
		numerator = create(division, space+1);
		denominator = create(quantity.size(), division+1);
	}
}

// This function converts characters in a string to numbers. 
// Lower: inclusive, Upper limit: not inclusive
int Quantity::create(int upper, int lower)
{
	int number = 0;
	int j = 0;

	// make upper inclusive
	upper --;

	for(int i = upper; i >= lower; --i)
	{
		if (i == upper)
			number += convert(quantity[i]);
		else
			number += (convert(quantity[i]) * pow(10,j));

		++j;
	}
	return number;
}

// This function converts number character to integer
int Quantity::convert(char c)
{
	int ascii = (int)c;
	switch(ascii)
	{
		case 48:
			return 0;
		case 49:
			return 1;
		case 50:
			return 2;
		case 51:
			return 3;
		case 52:
			return 4;
		case 53:
			return 5;
		case 54:
			return 6;
		case 55:
			return 7;
		case 56:
			return 8;
		case 57:
			return 9;
	}
}

// This function converts a known unit to most suitable form
void Quantity::convert_unit()
{
	if (!unit.known())
		return;

	if (whole >= 768)
	{
		numerator += (whole * denominator);
		denominator *= 768;
		simplify();
		unit.set("gal");
	}
	else if (whole >= 192)
	{
		numerator += (whole * denominator);
		denominator *= 192;
		simplify();
		unit.set("qt");
	}
	else if (whole >= 96)
	{
		numerator += (whole * denominator);
		denominator *= 96;
		simplify();
		unit.set("pt");
	}
	else if (whole >= 48)
	{
		numerator += (whole * denominator);
		denominator *= 48;
		simplify();
		unit.set("c");
	}
	else if (whole >= 6)
	{
		numerator += (whole * denominator);
		denominator *= 6;
		simplify();
		unit.set("oz");
	}
	else if (whole >= 3)
	{
		numerator += (whole * denominator);
		denominator *= 3;
		simplify();
		unit.set("tbsp");
	}
}

// This function sets silent to true : prevents error message from displaying
// when subtraction yeilds negative results.
void Quantity::ok_negative()
{
	silent = true;
}
// This function updates the state of quantity
void Quantity::update()
{
	convert_unit();
	
	// negative values
	if (whole < 0 || numerator < 0)
	{
		// warning
		if (!silent)
			std::cout << "WARNING: Negative value : Subtraction out of range" << std::endl;

		whole = 0;
		numerator = 0;
	}

	// simple fraction
	if (!whole && numerator)
	{
		fraction = true;
		mixed = false;
	}
	// mixed fraction
	else if (whole && numerator)
	{
		fraction = true;
		mixed = true;
	}
	// whole number
	else if (whole && !numerator)
	{	
		fraction = false;
		mixed = false;	
	}
}

// This function determines if amount is empty
bool Quantity::empty()
{
	if (!whole && !numerator)
		return true;
	return false;
}

// Prints the quantity
void Quantity::print()
{
	// no quantity
	if (empty())
		return;
	
	// whole number
	if (whole && !numerator)
		std::cout << whole << " " << std::flush;
	// simple fraction
	else if (numerator && !whole)
		std::cout << numerator << "/" << denominator << " " << std::flush;
	// mixed
	else if (mixed)
		std::cout << whole << " " << numerator << "/" << denominator << " " << std::flush;

	// unit
	if (!unit.empty())
		std::cout << unit.name() << " " << std::flush;
}

// This function writes the Quantity to an open file stream
void Quantity::save(std::ofstream &os)
{
	if (empty())
		return;
	os << "<quantity>";
	if (whole && numerator)
		os << whole << " " << numerator << "/" << denominator;
	else if (whole && !numerator)
		os << whole;
	else if (!whole && numerator)
		os << numerator << "/" << denominator;
	os << "</quantity>" << std::flush;

	if (!unit.empty())
		unit.save(os); 
}

// This function computes the numerator and denominator for sum of fractions
void Quantity::add_fraction(const Quantity &addend)
{
	// to simple fraction
	int a_numerator = addend.numerator;
	a_numerator += (addend.whole * addend.denominator);
	numerator += (whole * denominator);

	Unit a = addend.unit;
	// using units
	if (unit.known() && a.known())
	{
		numerator *= unit.get();
		a_numerator *= a.get();
	}

	// used up
	whole = 0;
	
	// same denominators
	if (denominator == addend.denominator)
	{
		numerator += addend.numerator;
	}
	// different denominators
	else
	{
		numerator = (numerator * addend.denominator) + (a_numerator * denominator);
		denominator = (denominator * addend.denominator);
	}
	simplify();
}

// This function computes the numerator and denominator for difference of fractions
void Quantity::sub_fraction(const Quantity &addend)
{
	// to simple fraction
	int a_numerator = addend.numerator;
	a_numerator += (addend.whole * addend.denominator);
	numerator += (whole * denominator);
	
	Unit a = addend.unit;
	// using units
	if (unit.known() && a.known())
	{
		numerator *= unit.get();
		a_numerator *= a.get();
	}

	// used up
	whole = 0;
	
	// same denominators
	if (denominator == addend.denominator)
	{
		numerator -= addend.numerator;
	}
	// different denominators
	else
	{
		numerator = (numerator * addend.denominator) - (a_numerator * denominator);
		denominator = (denominator * addend.denominator);
	}

	if (!empty())
		simplify();
}

// Checks if two quantites can be computed
bool Quantity::operator==(const Quantity& other)
{
	Unit temp = other.unit;

	if (unit.known() && temp.known())
		return true;
	else if (unit == temp)
		return true;

	return false;
}

// This function simplifies a fraction to its lowest term
void Quantity::simplify()
{
	// negative
	if (numerator < 0)
	{
		numerator = 0;
		denominator = 1;
	}
	// numerator equals denominator
	else if (numerator == denominator)
	{
		whole = 1;
		numerator = 0;
		denominator = 1;
	}
	// denominator factor of numerator
	else if (numerator > denominator && numerator%denominator == 0)
	{
		whole = numerator/denominator;
		numerator = 0;
		denominator = 1;
	}
	// numerator factor of denominator
	else if (numerator < denominator && denominator%numerator == 0)
	{
		numerator = 1;
		denominator = denominator/numerator;
	}
	// common factors
	else
	{
		while (numerator%2 == 0 && denominator%2 == 0)
		{
			numerator = numerator/2;
			denominator = denominator/2;
		}
		while (numerator%3 == 0 && denominator%3 == 0)
		{
			numerator = numerator/3;
			denominator = denominator/3;
		}
		while (numerator%5 == 0 && denominator%5 == 0)
		{
			numerator = numerator/5;
			denominator = denominator/5;
		}
		while (numerator%7 == 0 && denominator%7 == 0)
		{
			numerator = numerator/7;
			denominator = denominator/7;
		}
		// end of factoring
		if (numerator != 1)
		{
			whole = (numerator - (numerator%denominator))/denominator;
			if (whole)
				numerator = numerator%denominator;
		}
	}
}

// Addition
void Quantity::operator+=(const Quantity& addend)
{
	// adding whole number
	if (addend.fraction == false)
	{
		Unit temp_u = addend.unit;
		int temp_w = addend.whole;
		if (unit.known() && temp_u.known())
		{
			whole *= unit.get();
			temp_w *= temp_u.get();
		}
		whole += temp_w;
	}
	// adding fraction
	else 
		add_fraction(addend);

	update();
}

// Subtraction
void Quantity::operator-=(const Quantity& subtrahend)
{
	// subtracting whole number
	if (subtrahend.fraction == false)
	{
		Unit temp_u = subtrahend.unit;
		int temp_w = subtrahend.whole;
		if (unit.known() && temp_u.known())
		{
			whole *= unit.get();
			temp_w *= temp_u.get();
		}
		whole -= temp_w;
	}
	// subtracting fraction
	else 
		sub_fraction(subtrahend);

	update();
}

// Make equal to
void Quantity::operator=(const Quantity& other)
{
	quantity = other.quantity;
	unit = other.unit;
	whole = other.whole;
	numerator = other.numerator;
	denominator = other.denominator;
	fraction = other.fraction;
	mixed = other.mixed;
}

// ----------------------- UNIT ----------------------- //

// Constructor: Default
Unit::Unit()
{}

// This function initializes unit
void Unit::set(std::string type)
{
	unit = type;
}

std::string Unit::name()
{
	return unit;
}

// This function returns the value of unit in tsp
int Unit::get()
{
	if (unit == "tsp" || unit == "teaspoon")
		return tsp;
	else if (unit == "tbsp" || unit == "tablespoon")
		return tbsp;
	else if (unit == "oz" || unit == "ounce")
		return oz;
	else if (unit == "c" || unit == "cup")
		return c;
	else if (unit == "pt" || unit == "pint")
		return pt;
	else if (unit == "qt" || unit == "quart")
		return qt;
	else if (unit == "g" || unit == "gal" || unit == "gallon")
		return gal;
}

// This function checks if unit is one of the convertible types
bool Unit::known()
{
	// known units
	if (unit == "tsp" || unit == "teaspoon" || unit == "tbsp" || unit == "tablespoon" || unit == "oz" || unit == "ounce" || unit == "c" || unit == "cup" || unit == "pt" || unit == "pint" || unit == "qt" || unit == "quart" || unit == "g" || unit == "gal" || unit == "gallon")
		return true;
	else
		return false;
}

// This function converts the unit for easier processing -- to lower case;
// remove period at the end
void Unit::simplify()
{
	// convert unit to lowercase letters
	for (int i = 0; i < unit.size(); ++i)
		unit[i] = tolower(unit[i]);

	// remove last character of unit if is '.'
	if (unit[unit.size()-1] == '.')
		unit.erase(unit.size()-1);
}

// This function check's if unit is initialized
bool Unit::empty()
{
	if (unit.empty())
		return true;
	return false;
}

// This function writes the unit to the open file stream parameter
void Unit::save(std::ofstream &os)
{
	os << "<unit>" << unit << "</unit>" << std::flush;
}

// Equality
bool Unit::operator==(const Unit &other)
{
	if(unit == other.unit)
		return true;
	return false;
}
