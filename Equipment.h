#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <iostream>
#include <string>
#include <fstream>

class Equipment{
	private:
		std::string name;
		int quantity;
		bool silent;
	public:
		Equipment();
		Equipment(std::string val);
		void add(std::string new_name);
		std::string get_name();
		int get_quantity();
		void ok_negative();
		void print();
		void save(std::ofstream &os);
		void save_inv(std::ofstream &os);
		bool operator==(const Equipment &other);
		void operator+=(const Equipment &addend);
		void operator-=(const Equipment &subtrahend);
};

#endif
