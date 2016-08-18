#ifndef RECIPE_H
#define RECIPE_H

//Note: class string, vector, and iostream included in the header(s)
#include "COP3503su14_Proj3_Ingredient_WoldegiorigsD.h"
#include "COP3503su14_Proj3_Equipment_WoldegiorigsD.h"
#include "COP3503su14_Proj3_Preparation_WoldegiorigsD.h"

class RecipeInfo{
	private:
		std::string author;
		std::string blurb;
		std::string effort;
		std::string genre;
		std::string preptime;
		std::string source;
		std::string yield;
		bool no_info;
	public:
		RecipeInfo();
		void add(std::string value, int type);
		bool empty();
		void print();
		void save(std::ofstream &os);
};



class Recipe{
	private:
		std::string title;
		std::string serving;
		std::string notes;
		RecipeInfo info;
		std::vector<Ingredient> ingredients;
		Preparation prep;
	public:
		Recipe();
		void add(std::string val, int type);
		void add(RecipeInfo item);
		void add(Ingredient item);
		void add(std::vector<Ingredient> list);
		void add(Preparation item);
		std::string name();
		std::vector<Ingredient> get_ingredients();
		std::vector<Equipment> get_equipments();
		Preparation get_prep();
		void print();
		void save(std::ofstream &os);
		bool operator==(const Recipe &other);
};

#endif
