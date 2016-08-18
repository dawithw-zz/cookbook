#ifndef PARSER_H
#define PARSER_H

#include "COP3503su14_Proj3_Cookbook_WoldegiorigsD.h"
#include "COP3503su14_Proj3_Inventory_WoldegiorigsD.h"
#include <stdio.h>
#include <sstream>

class Parser{
	private:
		std::ifstream is;
		std::ofstream os;
		std::string line;
		std::string temp_file;
		// -- helper functions --
		void reformat();
		void read_write(char delimiter);
		bool isinvalid(std::string word);
		Section build_section();
		Recipe build_recipe();
		RecipeInfo build_recipeinfo();
		Ingredient build_ingredient();
		Preparation build_prep();
		Step build_step();
		TimedStep build_timedstep();
		std::vector<Ingredient> build_ingredientlist();
		std::vector<Equipment> build_equipmentlist();
	
	public:
		Parser(std::string filename);
		Cookbook build_cookbook();
		Inventory build_inventory();	
};

#endif