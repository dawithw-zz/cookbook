#include "COP3503su14_Proj3_Inventory_WoldegiorigsD.h"

// Constructor: Default
Inventory::Inventory()
{}

// This function adds an Equipment to the Inventory
void Inventory::add(Equipment item)
{
	// check for duplicates
	for (int i = 0; i < equipments.size(); ++i)
		if (equipments[i] == item)
		{
			equipments[i] += item;
			return;
		}
	// add new equipment
	equipments.push_back(item);
}

// This funtion adds an Ingredient to the Inventory
void Inventory::add(Ingredient item)
{
	// check for duplicates
	for (int i = 0; i < ingredients.size(); ++i)
		if (ingredients[i] == item)
		{
			ingredients[i] += item;
			return;
		}
	// add new ingredient
	ingredients.push_back(item);	
}

// This function adds an ingredientslist to the current Inventory
void Inventory::add(std::vector<Ingredient> list)
{
	for (auto i : list)
		add(i);
}

// This function adds an equipmentlist to the current Inventory
void Inventory::add(std::vector<Equipment> list)
{
	for (auto e : list)
		add(e);
}

// This function removes the selected Equipment from current Inventory
void Inventory::remove(Equipment item)
{
	for (int i = 0; i < equipments.size(); ++i)
		if (equipments[i] == item)
		{
			equipments.erase(equipments.begin() + i);
			return;
		}
}

// This function prints the list of items in Inventory
void Inventory::print(int type)
{
	switch(type)
	{
		// ingredientlist
		case 1:
			std::cout << "Ingredients:" << std::endl;
			for (auto i : ingredients)
			{
				std::cout << " " << std::flush;
				i.print();
			}
			return;
		// equipmentlist
		case 2:
			std::cout << "Equipments:" << std::endl;
			for (auto e : equipments)
			{
				std::cout << " " << std::flush;
				e.print();
			}
			return;
	}
}

// This function writes the Inventory to output file stream parameter
void Inventory::save(std::ofstream &os, int type)
{
	
	// ingredientslist
	if (type == 1)
	{
		os << "<ingredientlist>" << std::endl;
		for (auto i : ingredients)
			i.save(os);
		os << "</ingredientlist>" << std::endl;
	}

	// equipmentslist
	if (type == 2)
	{
		os << "<equipmentlist>" << std::endl;
		for (auto e : equipments)
			e.save(os);
		os << "</equipmentlist>" << std::endl;
	}

}

// Addition
void Inventory::operator+=(const Inventory &addend)
{
	// add ingredients
	for (auto i : addend.ingredients)
		add(i);
	// add equipments
	for (auto e : addend.equipments)
		add(e);
}

// Subtraction 
void Inventory::operator-=(const Inventory &subtrahend)
{
	// reduce ingredients
	for (auto item : subtrahend.ingredients)
		for (int i = 0; i < ingredients.size(); ++i)
			if (ingredients[i] == item)
			{
				ingredients[i] -= item;
				// quantity = 0
				if (ingredients[i].get_quantity().empty())
					ingredients.erase(ingredients.begin() + i);
			}
	// reduce equipments
	for (auto item : subtrahend.equipments)
		for (int i = 0; i < equipments.size(); ++i)
			if (equipments[i] == item)
			{
				equipments[i] -= item;
				// quantity = 0
				if (equipments[i].get_quantity() == 0)
					equipments.erase(equipments.begin() + i);
			}
}

// Subtract ingredient from inventory
void Inventory::operator-=(const Ingredient &subtrahend)
{
	for (int i = 0; i < ingredients.size(); ++i)
		if (ingredients[i] == subtrahend)
		{
			ingredients[i] -= subtrahend;
			// quantity = 0
			if (ingredients[i].get_quantity().empty())
				ingredients.erase(ingredients.begin() + i);
		}
}