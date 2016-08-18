#include "COP3503su14_Proj3_Recipe_WoldegiorigsD.h"

// ------------------------ RECIPEINFO ------------------------//
// Constructor: Default
RecipeInfo::RecipeInfo()
{
	no_info = true;
}

// This function adds a recipeinfo property
void RecipeInfo::add(std::string value, int type)
{
	switch(type)
	{
		// author
		case 1:
			author = value;
			no_info = false;
			return;
		// blurb
		case 2:
			blurb = value;
			no_info = false;
			return;
		// effort
		case 3:
			effort = value;
			no_info = false;
			return;
		// genre
		case 4:
			genre = value;
			no_info = false;
			return;
		// preptime
		case 5:
			preptime = value;
			no_info = false;
			return;
		// source
		case 6:
			source = value;
			no_info = false;
			return;
		// yield
		case 7:
			yield = value;
			no_info = false;
			return;
	}
}

// This function checks if any info is available
bool RecipeInfo::empty()
{
	return no_info;
}

// This function prints recipeinfo to console
void RecipeInfo::print()
{
	if (!author.empty())
		std::cout << "Author: " << author << std::endl;
	if (!blurb.empty())
		std::cout << blurb << std::endl;
	if (!effort.empty())
		std::cout << "Effort: " << effort << std::endl;
	if (!genre.empty())
		std::cout << "Genre: " << genre << std::endl;
	if (!preptime.empty())
		std::cout << "Time: " << preptime << std::endl;
	if (!source.empty())
		std::cout << "Source: " << source << std::endl;
	if (!yield.empty())
		std::cout << "Yield: " << yield << std::endl;
	std::cout << std::endl;
}

// This function writes the recipeinfo to the ofstream parameter
void RecipeInfo::save(std::ofstream &os)
{
	// start tag
	os << "<recipeinfo>" << std::endl;
	if (!author.empty())
		os << "<author>" << author << "</author>" << std::endl;
	if (!blurb.empty())
		os << "<blurb>" << blurb << "</blurb>" << std::endl;
	if (!effort.empty())
		os << "<effort>" << effort << "</effort>" << std::endl;
	if (!genre.empty())
		os << "<genre>" << genre << "</genre>" << std::endl;
	if (!preptime.empty())
		os << "<preptime>" << preptime << "</preptime>" << std::endl;
	if (!source.empty())
		os << "<source>" << source << "</source>" << std::endl;
	if (!yield.empty())
		os << "<yield>" << yield << "</yield>" << std::endl;
	// end tag
	os << "</recipeinfo>" << std::endl;
}

// -------------------------- RECIPE -------------------------- //

// Constructor: Default
Recipe::Recipe()
{}

// This function sets the title of the Recipe
void Recipe::add(std::string val, int type)
{
	switch(type)
	{
		// title
		case 1:
			title = val;
			return;
		// serving
		case 2:
			serving = val;
			return;
		// notes
		case 3:
			notes = val;
			return;
	}
}

// This function adds a recipe info
void Recipe::add(RecipeInfo item)
{	
	info = item;
}

// This function adds Ingredients to the vector ingredients
void Recipe::add(Ingredient item)
{
	ingredients.push_back(item);
}

// This function adds a list of Ingredients to the vector ingredients
void Recipe::add(std::vector<Ingredient> list)
{
	// call add(ingredient) on each ingredient in list
	for (auto i : list)
		add(i);
}

// This function adds Preparation to the Recipe
void Recipe::add(Preparation item)
{
	prep = item;
}

// This function returns the title of the Recipe
std::string Recipe::name()
{
	return title;
}

// This function returns the list of ingredients
std::vector<Ingredient> Recipe::get_ingredients()
{
	return ingredients;
}

// This function returns the list of equipments
std::vector<Equipment> Recipe::get_equipments()
{
	return prep.get_equipments();
}

// This function returns the Preparation
Preparation Recipe::get_prep()
{
	return prep;
}

// This function prints the Recipie to console
void Recipe::print()
{
	// title
	std::cout << "Title: "<< title << std::endl;
	std::cout << std::endl;
	// info
	if (!info.empty())
		info.print();
	// ingredientlist
	std::cout << "  Ingredients:" << std::endl;
	// print each ingredients in ingredientlist
	for (Ingredient i : ingredients)
	{
		i.print();
	}
	std::cout << std::endl;
	// preparation
	prep.print();	
	// serving
	if (!serving.empty())
		std::cout << "\nServing: " << serving << std::endl;
	// notes
	if (!notes.empty())
		std::cout << "\nNotes: " << notes << std::endl;
}

// This function writes the recipe to the ofstream parameter
void Recipe::save(std::ofstream &os)
{
	// start tag
	os << "<recipe>" << std::endl;
	os << "<title>" << title << "</title>" << std::endl;
	// recipe info
	if (!info.empty())
		info.save(os);
	// ingredientlist
	os << "<ingredientlist>" << std::endl;
	for (auto i : ingredients)
		i.save(os);
	os << "</ingredientlist>" << std::endl;
	// preparation
	prep.save(os);
	// serving
	if (!serving.empty())
		os << "<serving>" << serving << "</serving>" << std::endl;
	// notes
	if (!notes.empty())
		os << "<notes>" << notes << "</notes>" << std::endl;
	// end tag
	os << "</recipe>" << std::endl;
}

// Equality
bool Recipe::operator==(const Recipe &other)
{
	// compare titles
	if (title == other.title)
		return true;

	// failed condition
	return false;
}
