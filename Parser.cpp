#include "COP3503su14_Proj3_Parser_WoldegiorigsD.h"

using namespace std;

// Constructor: Initializes ifstream by filename specified in parameter
Parser::Parser(string filename)
{
	temp_file = "temp.parser";
	is.open(filename.c_str());
	// failed to open file
	if (is.fail())
	{
		cerr << "ERROR -- Failed to read file " << filename << endl;
	}
	reformat();
}

// This function creates a temporary file with a reformatted arrangement.
void Parser::reformat()
{
	// open temporary file
	os.open(temp_file.c_str());
	// fail to open file
	if (os.fail())
	{
		cerr << "INTERNAL ERROR: Unable to create temporary file for parsing." << endl;
	}

	read_write('<');

	// close files
	is.close();
	os.close();
}

// This function proceeds recursively. Line upto delimiter is read word by
// word, and written to output file in required format. Tags and tag contents
// are printed on separate lines.
void Parser::read_write(char delimiter)
{
	string word;

	// Read line upto delimiter
	if (getline(is, line, delimiter))
	{
		// read line into string stream
		istringstream str_reader(line);

		// wirte first word to file -- eliminate space from the beginning of lines
		if (str_reader >> word)
		{
			if (delimiter == '>' && isinvalid(word))
			{
				cerr << "WARNING: Unidentified tag: <" << line << "> is misplaced/unknown." << endl; 
				os << "unknown";
			}
			else
			{
				os << word;
				// read and write following words if available, separated by space
				while (str_reader >> word)
				{
					os << " " << word;
				}
			}
		}
		// new line
		os << endl;

		// change delimiter
		if (delimiter == '<')
			delimiter = '>';
		else 
			delimiter = '<';

		// repeat
		read_write(delimiter);
	}
	// end tag file
	return;	
}

bool Parser::isinvalid(string word)
{
	vector<string> valid = {"cookbook","title","section","recipe","recipeinfo","author","blurb","effort","genre","preptime","source","yield","ingredient","ingredientlist","fooditem","quantity","unit","equipmentlist","inventory","preparation","timeamt","timeunit","timetype","steptime","timedstep","step","equipment","serving","notes","/cookbook","/title","/section","/recipe","/recipeinfo","/author","/blurb","/effort","/genre","/preptime","/source","/yield","/ingredient","/ingredientlist","/fooditem","/quantity","/unit","/equipmentlist","/inventory","/preparation","/timeamt","/timeunit","/timetype","/steptime","/timedstep","/step","/equipment","/serving","/notes","?xml","!DOCTYPE"};
	for (auto v : valid)
		if (v == word)
			return false;
	return true;
}

// This function builds a Cookbook object
Cookbook Parser::build_cookbook()
{
	Cookbook book;
	bool in_cookbook = false;

	// open reformatted file
	is.open(temp_file.c_str());

	// read lines
	while(getline(is, line))
	{
		// skip and continue
		if (line == "cookbook")
		{
			in_cookbook = true;
			continue;
		}
		// build recipe and add to cookbook
		else if (line == "recipe")
		{
			Recipe r = build_recipe();
			book.add(r);
		}
		// set title
		else if (line == "title" && in_cookbook)
		{
			// get next line
			getline(is, line);
			// end tag title
			if (line == "/title")
				continue;
			// set title
			book.add(line);
		}
		// build section and add to cookbook
		else if (line == "section" && in_cookbook)
		{
			Section s = build_section();
			book.add(s);
		}
		else if (line == "/cookbook" && in_cookbook)
			in_cookbook = false;
		else if (line == "inventory")
			cerr << "NOTE: Inventory files should be separate from Recipe files. Check User documentation on proper file format." << endl;
	}
	// close and remove temporary file
	is.close();
	remove(temp_file.c_str());
	return book;
}

// This funtions builds the Inventory structure
Inventory Parser::build_inventory()
{
	Inventory inventory;
	bool in_inventory = false;
	
	// open reformatted file
	is.open(temp_file.c_str());

	// read lines
	while(getline(is, line))
	{
		// skip tag and continue
		if (line == "inventory")
		{
			in_inventory = true;
			continue;
		}
		// create and ingredientlist and add to inventory
		if (line == "ingredientlist" && in_inventory)
			inventory.add(build_ingredientlist());
		// create an equipmentlist and add to inventory
		else if (line == "equipmentlist" && in_inventory)
			inventory.add(build_equipmentlist());
		// end tag inventory
		else if (line == "/inventory" && in_inventory)
		{
			in_inventory = false;
			break;
		}
		else if (line == "recipe" || line == "cookbook")
			cerr << "NOTE: Recipe files should be separate from Recipe files. Check User documentation on proper file format." << endl;
	}  
	// close and remove temporary file
	is.close();
	remove(temp_file.c_str());
	return inventory;
}

// This function builds a Section object
Section Parser::build_section()
{
	Section section;

	// read lines
	while(getline(is, line))
	{
		// end tag section
		if (line == "/section")
			break;
		// create section title
		else if (line == "title")
		{
			// get next line
			getline(is, line);
			// end tag title
			if (line == "/title")
				continue;
			// set title
			section.add(line);
		}
		else if (line == "recipe")
		{
			Recipe r = build_recipe();
			section.add(r);
		}
	}
	return section;
}

// This function builds a Recipe object
Recipe Parser::build_recipe()
{
	Recipe recipe;

	// read lines
	while(getline(is, line))
	{
		// end tag recipe
		if (line == "/recipe")
			break;
		// create recipe title
		else if (line == "title")
		{
			// get next line
			getline(is, line);
			// end tag title
			if (line == "/title")
			{
				cerr << "WARNING: Recipe title empty. Access to recipe will not be available" << endl;
				continue;
			}
			// set title
			recipe.add(line, 1);
		}
		// recipe info
		else if (line == "recipeinfo")
			recipe.add(build_recipeinfo());
		// add ingredients
		else if (line == "ingredientlist")
			recipe.add(build_ingredientlist());
		// add prep
		else if (line == "preparation")
			recipe.add(build_prep());
		// serving
		else if (line == "serving")
		{
			getline(is, line);
			if (line == "/serving")
				continue;
			recipe.add(line, 2);
		}
		// notes
		else if (line == "notes")
		{
			getline(is, line);
			if (line == "/notes")
				continue;
			recipe.add(line, 3);
		}
	}
	return recipe;
}

// This function builds a RecipeInfo object
RecipeInfo Parser::build_recipeinfo()
{
	RecipeInfo info;

	while(getline(is, line))
	{
		// end tag
		if (line == "/recipeinfo")
			break;
		// author
		else if (line == "author")
		{
			// get next line
			getline(is, line);
			// end tag
			if (line == "/author")
				continue;
			// set author
			info.add(line, 1);
		}
		// blurb
		else if (line == "blurb")
		{
			// get next line
			getline(is, line);
			// end tag
			if (line == "/blurb")
				continue;
			// set blurb
			info.add(line, 2);
		}
		// effort
		else if (line == "effort")
		{
			// get next line
			getline(is, line);
			// end tag
			if (line == "/effort")
				continue;
			// set effort
			info.add(line, 3);
		}
		// genre
		else if (line == "genre")
		{
			// get next line
			getline(is, line);
			// end tag
			if (line == "/genre")
				continue;
			// set genre
			info.add(line, 4);
		}
		// preptime
		else if (line == "preptime")
		{
			// get next line
			getline(is, line);
			// end tag
			if (line == "/preptime")
				continue;
			// set preptime
			info.add(line, 5);
		}
		// source
		else if (line == "source")
		{
			// get next line
			getline(is, line);
			// end tag
			if (line == "/source")
				continue;
			// set author
			info.add(line, 6);
		}
		// yield
		else if (line == "yield")
		{
			// get next line
			getline(is, line);
			// end tag
			if (line == "/yield")
				continue;
			// set yield
			info.add(line, 7);
		}
	}
	return info;
}

// This function builds an Ingredient object
Ingredient Parser::build_ingredient()
{
	Ingredient ingredient;
	Quantity q;
	
	// read lines
	while(getline(is, line))
	{
		// end tag ingredient
		if (line == "/ingredient")
			break;
		// add quantity to ingredient
		else if (line == "quantity")
		{
			getline(is, line);
			// end tag quantity
			if (line == "/quantity")
				continue;
			q.add(line, 1);
			ingredient.add(q);
		}
		// add unit to ingredient
		else if (line == "unit")
		{
			getline(is, line);
			// end tag unit
			if (line == "/unit")
				continue;
			q.add(line, 2);
			ingredient.add(q);
		}
		// add fooditem to ingredient
		else if (line == "fooditem")
		{
			getline(is, line);
			// end tag fooditem
			if (line == "/fooditem")
				continue;
			ingredient.add(line, 1);
		}
		// description
		else
		{
			// not end tag of ingredient property
			if (line != "/quantity" && line != "/unit" && line != "/fooditem")
				ingredient.add(line, 0);
		}
	}
	return ingredient;
}

// This function builds a Preparation object
Preparation Parser::build_prep()
{
	Preparation prep;
	Step step;

	// read lines
	while(getline(is, line))
	{
		// end tag prep
		if (line == "/preparation")
		{
			prep.add(step);
			break;
		}
		// add equipment
		else if (line == "equipment")
		{
			getline(is, line);
			if (line == "/equipment")
				continue;
			// create an equipment and add to inventory
			Equipment e (line);
			prep.add(e);
			// create step for undefined steps
			step.add(e);
			prep.add(step);
			step = *new Step();
		}
		// add step
		else if (line == "step")
			prep.add(build_step());
		// add timedstep
		else if (line == "timedstep")
			prep.add(build_timedstep());
		else if (line != "/equipment")
			// create step
			step.add(line);
	}
	return prep;
}

// This function builds a Step object
Step Parser::build_step()
{
	Step step;

	// read lines
	while(getline(is, line))
	{
		// end tag step
		if (line == "/step")
			break;
		// add equipment
		else if (line == "equipment")
		{
			getline(is, line);
			// end tag equipment
			if (line == "/equipment")
				continue;
			// create an Equipment and add to step
			step.add(*new Equipment(line));
		}
		else if (line != "/equipment")
				step.add(line);
	}
	return step;
}

// This function builds a TimedStep object
TimedStep Parser::build_timedstep()
{
	TimedStep timedstep;
	StepTime steptime;

	// read lines
	while(getline(is, line))
	{
		// end tag
		if (line == "/timedstep")
			break;
		// add step
		else if (line == "step")
			timedstep.add(build_step());
		// add steptime
		else if (line == "steptime")
		{
			while(getline(is, line))
			{
				if (line == "/steptime")
					break;
				else if (line == "timeamt")
				{	
					getline(is, line);
					if (line == "/timeamt")
						continue;
					steptime.add(line, 1);
				}
				else if (line == "timeunit")
				{	
					getline(is, line);
					if (line == "/timeunit")
						continue;
					steptime.add(line, 2);
				}
				else if (line == "timetype")
				{	
					getline(is, line);
					if (line == "/timetype")
						continue;
					steptime.add(line, 3);
				}
			}
			timedstep.add(steptime);
		}
	}
	return timedstep;
}

// This function builds and returns an ingredientlist
std::vector<Ingredient> Parser::build_ingredientlist()
{
	vector<Ingredient> ingredients;

	// read lines
	while(getline(is, line))
	{
		// end tag ingredientlist 
		if (line == "/ingredientlist")
			break;
		// create an ingredient and add to inventory
		else if (line == "ingredient")
		{
			Ingredient ing = build_ingredient();
			for (int i = 0; i < ingredients.size(); ++i)
				if (ingredients[i] == ing)
				{
					ingredients[i] += ing;
					continue;
				}
			ingredients.push_back(ing);
		}
	}
	return ingredients;
}

// This function builds and returns an equipmentlist
std::vector<Equipment> Parser::build_equipmentlist()
{
	vector<Equipment> equipments;

	while(getline(is, line))
	{
		// end tag equipmentlist
		if (line == "/equipmentlist")
			break;
		// add equipment
		else if (line == "equipment")
		{
			getline(is, line);
			if (line == "/equipment")
				continue;
			// create an equipment and add to inventory
			Equipment e (line);
			for (int i = 0; i < equipments.size(); ++i)
				if (equipments[i] == e)
				{
					equipments[i] += e;
					continue;
				}
			equipments.push_back(e);
		}
	}
	return equipments;
}
