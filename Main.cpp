#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include "COP3503su14_Proj3_Parser_WoldegiorigsD.h"

using namespace std;

// Declarations
int command_line_parameters(int argc, char* argv[], Cookbook &book, Inventory &inventory);
void print (int type);
string get_name();
bool input_ing(Ingredient &i);

const int SILENT = 0;
const int NORMAL = 1;
const int VERBOSE = 2;
const int HELP = 3;

int main(int argc, char* argv[])
{
	Cookbook book;
	Inventory inventory;
	Inventory menu_inv;
	Menu menu;
	string input;
	int option = -1;
	int mode;
	
	mode = command_line_parameters(argc, argv, book, inventory);

	// print startup menu
	if (mode == NORMAL)
		print(NORMAL);
	else if (mode == VERBOSE)
		print(VERBOSE);

	// User interface
	while(option)
	{
		cin >> option;
		input = "";
		// 0. exit
		if (option == 0)
		{
			// verbose mode: print exit message.
			if (mode == VERBOSE)
				cout << "Goodbye." << endl;
			continue;
		}

		// 1. input recipie file 
		else if (option == 1)
		{
			// prompt
			if (mode == VERBOSE)
				cout << "Recipe file: " << flush;
			// user input: file
			cin >> input;
			// parse file and create cookbook; combine with current cookbook
			Parser p(input);
			Cookbook temp = p.build_cookbook();
			book += temp;
		}

		// 2. input inventory file
		else if (option == 2)
		{
			// prompt
			if (mode == VERBOSE)
				cout << "Inventory file:" << flush;
			// user input: file
			cin >> input;
			// parse file and create inventory; combine with current inventory
			Parser p(input);
			inventory += p.build_inventory();
		}

		// 3. subtract inventory
		else if (option == 3)
		{
			// prompt
			if (mode == VERBOSE)
				cout << "Inventory file:" << flush;
			// user input: file
			cin >> input;
			// parse file and create inventory; subtract from current inventory
			Parser p(input);
			inventory -= p.build_inventory();
		}
		
		// 4.	add recipe -- menu
		else if (option == 4)
		{
			// prompt
			if (mode == VERBOSE)
				cout << "Recipe name: " << flush;
			// user input: recipe name
			input = get_name();
			// check for recipe in cookbook; create a recipe and add to menu
			if (book.find(input))
			{
				Recipe r = book.get(input);
				menu.add(r);
				// update menu inventory;
				menu_inv = menu.get();
				if (mode)
					cout << "Recipe " << input << " added to menu." << endl;
			}
			else
				cerr << "Recipe " << input << " not found." << endl;
		}

		// 5.	remove recipe -- menu
		else if (option == 5)
		{
			// prompt
			if (mode == VERBOSE)
				cout << "Recipe name: " << flush;
			// user input: recipe name
			input = get_name();
			// check for recipe in menu;
			if (menu.find(input))
			{
				menu.remove(input);
				// update menu inventory;
				menu_inv = menu.get();
				// completion message
				if (mode)
					cout << "Recipe " << input << " deleted from menu." << endl;
 			}
			else
				cerr << "Recipe " << input << " not found." << endl;
		}

		// 6.	reset current menu
		else if (option == 6)
		{
			menu.reset();
			if (mode)
				cout << "Menu emptied." << endl;
		}

		// 7.	save to file
		else if (option == 7)
		{
			// prompt
			if (mode == VERBOSE)
				cout << "Save to (include extension): " << flush;
			cin >> input;
			ofstream os;
			os.open(input.c_str());
			if (os.fail())
				cerr << "Unable to save to " << input << endl;
			menu.save(os);
			os.close();
		}
		// 8.	print menu to console
		else if (option == 8)
		{
			menu.print();
		}

		// 9.	print recipe
		else if (option == 9)
		{
			// prompt
			if (mode == VERBOSE)
				cout << "Recipe name: " << flush;
			// user input: recipe name
			input = get_name();
			// check if recipe in cookbook
			if (book.find(input))
			{
				Recipe r = book.get(input);
				r.print();
			}
			else
				cerr << "Recipe " << input << " not found." << endl;
		}

		// 10. increase ingredient - inventory
		else if (option == 10)
		{
			Ingredient i;
			// prompt
			if (mode == VERBOSE)
				cout << "Ingredient:" << endl;
			bool success = input_ing(i);
			if (success)
				inventory.add(i);
		}

		// 11. reduce ingredient - inventory
		else if (option == 11)
		{
			Ingredient i;
			// prompt
			if (mode == VERBOSE)
				cout << "Ingredient:" << endl;
			bool success = input_ing(i);
			if (success)
				inventory -= i;
		}

		// 12. insert equipment - inventory
		else if (option == 12)
		{
			// prompt
			if (mode == VERBOSE)
				cout << "Equipment:" << endl;
			input = get_name();
			Equipment e(input);
			inventory.add(e);
		}
		// 13. delete equipment - inventory
		else if (option == 13)
		{
			// prompt
			if (mode == VERBOSE)
				cout << "Equipment:" << endl;
			input = get_name();
			Equipment e(input);
			inventory.remove(e);
		}
		// 14. print ingredient - inventory
		else if (option == 14)
			inventory.print(1);

		// 15. print equipment - inventory
		else if (option == 15)
			inventory.print(2);

		// 16. print ingredients - menu
		else if (option == 16)
			menu_inv.print(1);

		// 17. print ingredients shopping list
		else if (option == 17)
		{
			menu_inv -= inventory;
			cout << "Shopping list " << flush;
			menu_inv.print(1);
		}

		// 18. save ingredients shopping list to file
		else if (option == 18)
		{
			// prompt
			if (mode == VERBOSE)
				cout << "Save to (include extension): " << flush;
			cin >> input;
			ofstream os;
			os.open(input.c_str());
			if (os.fail())
				cerr << "Unable to save to " << input << endl;
			menu_inv.save(os, 1);
			os.close();
		}

		// 19. print equipments - menu
		else if (option == 19)
			menu_inv.print(2);

		// 20. print equipment shopping list
		else if (option == 20)
		{
			Inventory menu_inv = menu.get();
			menu_inv -= inventory;
			cout << "Shopping list " << flush;
			menu_inv.print(2);
		}
		
		// 21. save equipment shopping list to file
		else if (option == 21)
		{
			// prompt
			if (mode == VERBOSE)
				cout << "Save to (include extension): " << flush;
			cin >> input;
			ofstream os;
			os.open(input.c_str());
			if (os.fail())
				cerr << "Unable to save to " << input << endl;
			menu_inv.save(os, 2);
			os.close();
		}

		// 22. help menu
		else if (option == 22)
		{
			print(HELP);
		}
		// Invalid input
		else
		{
			cerr << option << ": invalid option." << endl;
			option = -1;
			if (mode == VERBOSE)
				cout << "See list of available commands." << endl;
			print(VERBOSE);
			continue;
		}
		if (mode == VERBOSE)
			print(VERBOSE);
	}
}

// This function takes in all the command line parameters and returns the mode
// specified -- default mode, if not specified
int command_line_parameters(int argc, char* argv[], Cookbook &book, Inventory &inventory)
{
	// default mode
	int mode = NORMAL;

	// List of available command line parameters
	string args[] = {"-s", "-v", "-r", "-i"};

	// Check command line arguments
	for (int i = 1; i < argc; ++i)
	{
		// silent mode
		if (argv[i] == args[0])
			mode = SILENT;

		// verbose mode
		else if (argv[i] == args[1])
			mode = VERBOSE;

		// input recipe file
		else if (argv[i] == args[2])
		{
			// exists additional parameter
			if (argv[i+1])
			{
				// parse file
				Parser p(argv[i+1]);
				// create cookbook and add combine with current book
				Cookbook temp = p.build_cookbook();
				book += temp;
			}
			// file name not specified
			else
			{
				cerr << "Unspecified parameter for " << args[2] << endl 
						 << "Usage: "<< args[2] << " [filename]" << endl;
			}
		}

		// input inventory file
		else if (argv[i] == args[3])
		{
			// exists additional parameter
			if (argv[i+1])
			{
				// parse file
				Parser p(argv[i+1]);
				// create a temporary inventory and add to current inventory
				inventory += p.build_inventory();
			}
			// file name not specified
			else
			{
				cerr << "Unspecified parameter for " << args[3] << endl 
						 << "Usage: " << args[3] << " [filename]" << endl;
			}
		}

		// unknown parameter
		else
		{
			// not file name of -i or -r parameters
			if (!(argv[i-1] == args[2] || argv[i-1] == args[3]))
				cerr << "ERROR: " << argv[i] << " not a valid argument." << endl;
		}
	}

	return mode;
}

// This function opens and prints the contents of the file associated with the
// menu specified for printing.
void print (int type)
{
	// file stream
	ifstream is;
	string line;
	string file;

	switch(type)
	{
		case NORMAL:
			file = "normal.menu";
			break;
		case VERBOSE:
			file = "verbose.menu";
			break;
		case HELP:
			file = "help.menu";
			break;
	}
	is.open(file.c_str());
	// fail to open menu file
	if (is.fail())
		cerr << "INTERNAL ERROR: Unable to locate/open " << file << endl;
	// print line to console
	while(getline(is, line))
	{
		cout << line << endl;
	}
	// close file
	is.close();
}

// This function takes a sequence of inputs from cin until newline
// encountered. The use of cin along with getline() prevents the necessity of
// having the user enter name right away, as would happen if only getline()
// was used.
string get_name()
{
	string name;
	string input; 

	// read name
	cin >> name;
	// if name is more than one word, append the remaining words to name
	if (getline(cin, input) && input != " ")
		name += input;

	return name;
}

// This function converts user input into an ingredient
bool input_ing(Ingredient &i)
{
	Quantity q;
	string line;
	string name;
	string word;

	// name
	cin >> name;
	// more stuff
	if (getline(cin, line) && line != " ")
	{
		istringstream read(line);
		// set amount
		while (read >> word)
		{
			if (isdigit(word[0]))
			{
				// check if amount has only digits or /
				for (auto c : word)
					if (!isdigit(c) && c != '/')
					{
						cerr << "Invalid amount: Amount must be a positive number. Operation stopped." << endl;
						return false;
					}
				q.add(word, 1);
				// set unit
				if(read >> word)
					q.add(word, 2);
			}	
			// add more to name
			else
				name = (name + " " + word);
		}
	}
	// default quantity -- 1 unitless
	else
		q.add("1", 1);
	
	// add name and quantity to ingredient
	i.add(name, 1);
	i.add(q);
	return true;
}