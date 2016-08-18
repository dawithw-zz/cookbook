#ifndef COOKBOOK_H
#define COOKBOOK_H

#include "COP3503su14_Proj3_Recipe_WoldegiorigsD.h"
#include "COP3503su14_Proj3_Inventory_WoldegiorigsD.h"


// -------------- SECTION ------------- //

class Section{
	private:
		std::string title;
		std::vector<Recipe> recipes;
	public:
		Section();
		void add(std::string name);
		void add(Recipe item);
		void save(std::ofstream &os);
		void print();
};

// -------------- COOKBOOK ------------- //

class Cookbook{
	private:
		std::string title;
		std::vector<Section> sections;
		std::vector<Recipe> recipes;
	public:
		Cookbook();
		void add(std::string name);
		void add(Section item);
		void add(Recipe item);
		bool find(std::string recipe);
		Recipe get(std::string recipe);
		void print();
		void save(std::ofstream &os);
		void operator+=(const Cookbook &addend);
};

// -------------- MENU ------------- //

class Menu{
	private:
		std::vector<Recipe> recipes;
		std::vector<Ingredient> ingredients;
		std::vector<Equipment> equipments;
	public:
		Menu();
		void add(Recipe item);
		void add(Ingredient item);
		void add(Equipment item);
		void remove(std::string title);
		bool find(std::string title);
		Inventory get();
		void print();
		void reset();
		void save(std::ofstream &os);
};

#endif
