#include "COP3503su14_Proj3_Preparation_WoldegiorigsD.h"

// ----------------------- STEP ----------------------- //

// Constructor: Default
Step::Step()
{
	equipment_added = false;
}

// This function adds a word to the step.
void Step::add(std::string word)
{
	if (equipment_added)
		step_after += word;
	else
		step_before += word;
}

// This function sets the equipment to an Equipment item 
void Step::add(Equipment item)
{
	equipment = item;
	equipment_added = true;
}

// This function retunrs a boolean value that determines if there is an
// equipment used in the Step
bool Step::has_equipment()
{
	return equipment_added;
}

// This function returns the equipment used in step.
Equipment Step::get_equipment()
{
	return equipment;
}

// This function prints the step to the console
void Step::print()
{
	if (equipment_added)
	{
		if (!step_after.empty())
			std::cout << step_before << " " << equipment.get_name() << " " << step_after << std::endl;
		else
			std::cout << step_before << " " << equipment.get_name() << std::endl;
	}
	else
		std::cout << step_before << std::endl;	
}

// This function writes the step to an output file stream parameter
void Step::save(std::ofstream &os)
{
	// start tag
	os << "<step>" << step_before << std::flush;
	// equipment
	if (equipment_added)
	{
		equipment.save(os);
		// more step
		if (!step_after.empty())
			os << step_after << std::flush;
	}
	// end tag
	os << "</step>" << std::endl;
}

// ------------------- TIMEDSTEP ------------------- //

// Constructor: Default
TimedStep::TimedStep()
{}

// This function adds a Step item
void TimedStep::add(Step item)
{
	step = item;
}

// This function adds a StepTime item
void TimedStep::add(StepTime item)
{
	steptime = item;
}

// This function adds additional description
void TimedStep::add(std::string description)
{
	pcdata = description;
}

// This function determines if step has an equipment
bool TimedStep::has_equipment()
{
	return step.has_equipment();
}

// This function returns the equipment used in step.
Equipment TimedStep::get_equipment()
{
	return step.get_equipment();
}

// This function prints TimedStep to console
void TimedStep::print()
{
	step.print();
	if (!steptime.empty())
		steptime.print();
	if (!pcdata.empty())
		std::cout << "	" << pcdata << std::endl;
	else
		std::cout << std::endl;
}

// This function saves TimedStep to console
void TimedStep::save(std::ofstream &os)
{
	// start tag
	os << "<timedstep>" << std::endl;
	step.save(os);
	if (!steptime.empty())
		steptime.save(os);
	if (!pcdata.empty())
		os << pcdata << std::endl;
	// end tag
	os << "</timedstep>" << std::endl;
}

// ------------------- STEPTIME ------------------- //

// Constructor: Default
StepTime::StepTime()
{}

// This function adds the properties of StepTime
void StepTime::add(std::string value, int type)
{
	switch(type)
	{
		// pcdata
		case 0:
			pcdata = value;
			return;
		// time amount
		case 1:
			timeamt = value;
			return;
		// time unit
		case 2:
			timeunit = value;
			return;
		// time type
		case 3:
			timetype = value;
			return;
	}
}

// This function checks if StepTime is empty
bool StepTime::empty()
{
	if (pcdata.empty() && timeamt.empty() && timetype.empty() && timeunit.empty())
		return true;
	return false;
}

// This function prints the StepTime to console
void StepTime::print()
{
	// indent
	std::cout << " " << std::flush;
	if (!pcdata.empty())
		std::cout << " " << pcdata << std::flush;
	if (!timeamt.empty())
		std::cout << " " << timeamt << std::flush;
	if (!timeunit.empty())
		std::cout << " " << timeunit << std::flush;
	if (!timetype.empty())
		std::cout << " " << timetype << std::flush;
	std::cout << std::endl;
}

// This function writes StepTime to the output file stream parameter
void StepTime::save(std::ofstream &os)
{
	// start tag
	os << "<steptime>" << std::endl;
	if (!pcdata.empty())
		os << pcdata << std::flush;
	if (!timeamt.empty())
		os << "<timeamt>" << timeamt << "</timeamt>" << std::flush;
	if (!timeunit.empty())
		os << "<timeunit>" << timeunit << "</timeunit>" << std::flush;
	if (!timetype.empty())
		os << "<timetype>" << timetype << "</timetype>" << std::flush;
	// endtag
	os << "\n</steptime>" << std::endl;
}

// ----------------------- PREPARATION ----------------------- //

// Constructor: Default
Preparation::Preparation()
{}

// This function adds an Equipment to the preparation
void Preparation::add(Equipment item)
{
	for (int i = 0; i < equipments.size(); ++i)
	{
		if (equipments[i] == item)
			equipments[i] += item;
	}
}
// This function adds a Step to the steps
void Preparation::add(Step step)
{
	steps.push_back(step);
	if (step.has_equipment())
	{
		for (int i = 0; i < equipments.size(); ++i)
		{
			if (equipments[i] == step.get_equipment())
				equipments[i] += step.get_equipment();
		}
		equipments.push_back(step.get_equipment());
	}
}

// This function adds a TimedStep to the timedsteps
void Preparation::add(TimedStep step)
{
	timedsteps.push_back(step);
	if (step.has_equipment())
	{
		for (int i = 0; i < equipments.size(); ++i)
		{
			if (equipments[i] == step.get_equipment())
				equipments[i] += step.get_equipment();
		}
		equipments.push_back(step.get_equipment());
	}
}

// This function returns the vector containing the list of equipments used
std::vector<Equipment> Preparation::get_equipments()
{
	return equipments;
}

// This function prints Preparation to console
void Preparation::print()
{
	std::cout << "  Preparation:" << std::endl;
	// print steps
	for (auto s : steps)
		s.print();
	for (auto t : timedsteps)
		t.print();
}

// This function writes Perparation to the ofstream parameter
void Preparation::save(std::ofstream &os)
{
	// start tag
	os << "<preparation>" << std::endl;
	// steps
	for (auto s : steps)
		s.save(os);
	// timedsteps
	for (auto t : timedsteps)
		t.save(os);
	//end tag
	os << "</preparation>" << std::endl;
}