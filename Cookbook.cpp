#include "COP3503su14_Proj3_Cookbook_WoldegiorigsD.h"

// -------------- SECTION ------------- //

// Constructor: Default
Section::Section()
{}

// This function initializes the title
void Section::add(std::string name) 
{
	title = name;
}

// This function adds a Recipe object to the recipes vector
void Section::add(Recipe item)
{
	recipes.push_back(item);
}

// This function writes the section to the output stream parameter
void Section::save(std::ofstream &os)
{
	// start tag
	os << "<section>" << std::endl;
	
	// title
	if (!title.empty())
		os << "<title>" << title << "</title>" << std::endl;

	// call save function of each recipe in recipes vector
	for (auto r : recipes)
		r.save(os);

	// end tag
	os << "</section>" << std::endl;
}

// This function prints the Section to console
void Section::print()
{
	// print title
	std::cout << "SECTION: " << title << std::endl << std::endl;
	
	// print Recipes
	for (Recipe r : recipes)
		r.print();
	std::cout << "****************************\n" << std::endl;
}


// -------------- COOKBOOK ------------- // 

// Constructor: Default
Cookbook::Cookbook()
{}

// This function initializes the cookbook title
void Cookbook::add(std::string name)
{
	title = name;
}

// This function adds a Section to the sections vector
void Cookbook::add(Section item)
{
	sections.push_back(item);
}

// This function adds a Recipe to the recipes vector
void Cookbook::add(Recipe item)
{
	recipes.push_back(item);
}

// This function checks if a recipe in the recipes list has a similar name to
// the string parameter
bool Cookbook::find(std::string recipe)
{
	for (int i = 0; i < recipes.size(); ++i)
	{
		if (recipes[i].name() == recipe)
			return true;
	}
	return false;
}

// This function returns a Recipe with the name of the string parameter
Recipe Cookbook::get(std::string recipe)
{
	for (int i = 0; i < recipes.size(); ++i)
	{
		if (recipes[i].name() == recipe)
			return recipes[i];
	}
}

// This function prints the Cookbook to console
void Cookbook::print()
{
	// print title
	if (!title.empty())
		std::cout << "===============\n" 
							<< "COOKBOOK: " << title 
							<< "\n===============\n" << std::endl;

	// Condition: Cookbook has no sections
	if (sections.empty())
	{
		for (Recipe r : recipes)
			r.print();
	}
	// condition failed
	else
	{
		for (Section s : sections)
			s.print();
	}
}

// This function writes the cookbook to the parameter output file stream
void Cookbook::save(std::ofstream &os)
{
	// start tag
	os << "<cookbook>" << std::endl;

	// title
	if (!title.empty())
		os << "<title>" << title << "</title>" << std::endl;

	// sections
	if (!sections.empty())
		for (auto s : sections)
			s.save(os);

	// recipes
	if (!recipes.empty())
		for (auto r : recipes)
			r.save(os);

	// end tag
	os << "</cookbook>" << std::endl;
}

// Addition: Merge cookbooks
void Cookbook::operator+=(const Cookbook &addend)
{
	// sections available
	if (!addend.sections.empty())
		for (auto s : addend.sections)
			sections.push_back(s);

	// recipes available
	if (!addend.recipes.empty())
		for (auto r : addend.recipes)
			recipes.push_back(r);
}


// -------------- MENU ------------- //

// Constructor: Default
Menu::Menu()
{}

// This function adds a recipe to recipes
void Menu::add(Recipe item)
{
	// check duplicates
	for (auto r : recipes)
		if (r == item)
		{
			std::cerr << "Warning: Possible Duplicate Recipe: " << item.name() << " already on Menu." << std::endl;
		}

	// add item to recipes
	recipes.push_back(item);
	// add item's ingredients
	std::vector<Ingredient>temp_ing = item.get_ingredients();
	for (auto i : temp_ing)
		add(i);
	// add item's equipments
	std::vector<Equipment>temp_eqp = item.get_equipments();
	for (auto e : temp_eqp)
		add(e);
}

// This function adds an ingredient to the ingredients list
void Menu::add(Ingredient item)
{
	Quantity temp;
	for (int i = 0; i < ingredients.size(); ++i)
	{
		// set quantity to silent mode
		temp = ingredients[i].get_quantity();
		temp.ok_negative();
		ingredients[i].add(temp);

		if (ingredients[i] == item)
		{
			ingredients[i] += item;
			return;
		}
	}
	ingredients.push_back(item);
}

// This function adds an equipment to the equipments list
void Menu::add(Equipment item)
{
	for (int i = 0; i < equipments.size(); ++i)
	{
		equipments[i].ok_negative();
		if (equipments[i] == item)
		{
			equipments[i] += item;
			return;
		}
	}
	equipments.push_back(item);
}

// This function finds and removes a recipe from the Menu
void Menu::remove(std::string title)
{
	for (int i = 0; i < recipes.size(); ++i)
		if (recipes[i].name() == title)
			recipes.erase(recipes.begin() + i);
}

// This function determines if a recipe with name of parameter exists in the
// recipes list
bool Menu::find(std::string title)
{
	for (auto r : recipes)
		if (r.name() == title)
			return true;
	return false;
}

// This function retunrs an inventory of menu ingredients and equipments
Inventory Menu::get()
{
	Inventory menu;
	menu.add(ingredients);
	menu.add(equipments);
	return menu;
}

// This function prints a list of all recipes in menu
void Menu::print()
{
	
	std::cout << "========\n" 
						<< "MENU:\n" 
						<< "========" << std::endl;
	for (auto r : recipes)
		std::cout << r.name() << std::endl;
	return;
}

// This function erases all recipe from menu
void Menu::reset()
{
	recipes.clear();
	ingredients.clear();
	equipments.clear();
}

// This function writes all recipes to the output file stream parameter
void Menu::save(std::ofstream &os)
{
	for (auto r : recipes)
		r.save(os);
}
