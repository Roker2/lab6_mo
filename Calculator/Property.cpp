#include "Property.h"

Property::Property(const std::string &var, double value)
	: var(var), value(value)
{}

Property::Property(std::string &&var, double &&value)
	: var(std::move(var)), value(std::move(value))
{}
