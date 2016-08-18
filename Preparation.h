#ifndef PREP_H
#define PREP_H

#include "COP3503su14_Proj3_Equipment_WoldegiorigsD.h"
#include <vector>

class Step{
	private:
		std::string step_before;
		std::string step_after;
		Equipment equipment;
		bool equipment_added;
	public:
		Step();
		void add(std::string word);
		void add(Equipment item);
		bool has_equipment();
		Equipment get_equipment();
		void print();
		void save(std::ofstream &os);
};

class StepTime{
	public:
		std::string pcdata;
		std::string timeamt;
		std::string timeunit;
		std::string timetype;
	public:
		StepTime();
		void add(std::string value, int type);
		bool empty();
		void print();
		void save(std::ofstream &os);
};

class TimedStep{
	private:
		std::string pcdata;
		StepTime steptime;
		Step step;
	public:
		TimedStep();
		void add(Step item);
		void add(StepTime item);
		void add(std::string description);
		bool has_equipment();
		Equipment get_equipment();
		void print();
		void save(std::ofstream &os);
};

class Preparation{
	private:
		std::vector<Equipment> equipments;
		std::vector<Step> steps;
		std::vector<TimedStep> timedsteps;
	public:
		Preparation();
		void add(std::string line);
		void add(Equipment item);
		void add(Step step);
		void add(TimedStep step);
		std::vector<Equipment> get_equipments();
		void print();
		void save(std::ofstream &os);
};

#endif
