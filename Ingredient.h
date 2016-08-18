#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

class Unit{
	private:
		std::string unit;
		static const int tsp = 1;
		static const int tbsp = 3;
		static const int oz = 6;
		static const int c = 48;
		static const int pt = 96;
		static const int qt = 192;
		static const int gal = 768;
	public:
		Unit();
		void set(std::string type);
		int get();
		std::string name();
		bool known();
		void simplify();
		bool empty();
		void save(std::ofstream &os);
		bool operator==(const Unit &other);
};

class Quantity{
	private:
		std::string quantity;
		Unit unit;
		int whole;
		int numerator;
		int denominator;
		bool fraction;
		bool mixed;
		bool silent;
	public:
		Quantity();
		void add(std::string value, int type);
		int bad();
		void to_number();
		int create(int upper, int lower);
		int convert(char c);
		void convert_unit();
		void ok_negative();
		void update();
		bool empty();
		void print();
		void save(std::ofstream &os);
		void add_fraction(const Quantity &addend);
		void sub_fraction(const Quantity &subtrahend);
		void simplify();
		bool operator==(const Quantity& other);
		void operator+=(const Quantity& addend);
		void operator-=(const Quantity& subtrahend);
		void operator=(const Quantity& other);
};

class Ingredient{
	private:
		Quantity quantity;
		std::string name;
		std::string state;
	public:
		Ingredient();
		void add(std::string value, int type);
		void add(Quantity amount);
		Quantity get_quantity();
		std::string get_name();
		void print();
		void save(std::ofstream &os);
		bool operator==(const Ingredient &other);
		void operator+=(const Ingredient &addend);
		void operator-=(const Ingredient &subtrahend);
};

#endif
