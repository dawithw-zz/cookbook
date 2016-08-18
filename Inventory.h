#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include "COP3503su14_Proj3_Ingredient_WoldegiorigsD.h"
#include "COP3503su14_Proj3_Equipment_WoldegiorigsD.h"

class Inventory{
	private:
		std::vector<Ingredient> ingredients;
		std::vector<Equipment> equipments;
	public:
		Inventory();
		void add(Equipment item);
		void add(Ingredient item);
		void add(std::vector<Ingredient> list);
		void add(std::vector<Equipment> list);
		void remove(Equipment item);
		void print(int type);
		void save(std::ofstream &os, int type);
		void operator+=(const Inventory &addend);
		void operator-=(const Inventory &subtrahend);
		void operator-=(const Ingredient &subtrahend);
};

#endif
