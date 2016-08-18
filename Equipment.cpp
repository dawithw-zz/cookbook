#include "COP3503su14_Proj3_Equipment_WoldegiorigsD.h"

// Constructor: Default
Equipment::Equipment()
{
	quantity = 1;
	silent = false;
}

// Constructor: Initialize name
Equipment::Equipment(std::string val)
{
	name = val;
	quantity = 1;
	silent = false;
}

// This function initializes the name
void Equipment::add(std::string new_name)
{
	name = new_name;
}

// This function returns the name
std::string Equipment::get_name()
{
	return name;
}

// This function retunrs the quantity
int Equipment::get_quantity()
{
	return quantity;
}

// This function prevents notification of negative quantity
void Equipment::ok_negative()
{
	silent = true;
}

// This function prints the Equipment to console
void Equipment::print()
{
	if (quantity == 1)
		std::cout << name << std::endl;
	else if (quantity > 1)
		std::cout << quantity << " " << name << std::endl;
}

// This function writes the Equipment to the output file stream parameter
void Equipment::save(std::ofstream &os)
{
	os << "<equipment>" << name << "</equipment>" << std::flush;
}

// This funtion writes the Equipment to the output file stream parameter, along with quantity -- inventory
void Equipment::save_inv(std::ofstream &os)
{
	for (int i = 0; i < quantity; ++i)
		os << "<equipment>" << name << "</equipment>" << std::endl; 
}

// Equality
bool Equipment::operator==(const Equipment &other)
{
	// compare names
	if (name == other.name)
		return true;

	return false;
}

// Addition
void Equipment::operator+=(const Equipment &addend)
{
	quantity += addend.quantity;
}

// Subtraction
void Equipment::operator-=(const Equipment &subtrahend)
{
	quantity -= subtrahend.quantity;
	if (quantity < 0)
	{	
		if (!silent)
			std::cerr << "WARNING: Negative value : Subtraction out of range" << std::endl;
		quantity = 0;
	}
}