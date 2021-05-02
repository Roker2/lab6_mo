#pragma once

#include <vector>
#include <string>

#include "Property.h"

class Func
{
public:
	Func(const std::string& str);
	~Func() = default;

	inline bool isComplete() const noexcept { return !funcPost.empty(); }

	double operator()(const std::vector<Property> props = {});
	operator std::string() const noexcept;

private:
	std::string funcInf;
	std::string funcPost;

	friend class Translator;
};

