#pragma once

#include <map>
#include <string>

#include "Token.h"
#include "Property.h"

class Func
{
public:
	Func(const std::string& funcInf = "");
	~Func() = default;

	inline bool isComplete() const noexcept { return !tokensPost.empty(); }

	std::string getPost() const noexcept;

	void retranslate() noexcept;

	double operator()(const Properties& props = {});
	operator std::string() const noexcept;

private:
	std::string funcInf;
	std::vector<Token> tokensInf;
	std::vector<Token> tokensPost;

	friend class Translator;
	friend class Calculator;
};

