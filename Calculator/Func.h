#pragma once

#include <iostream>
#include <map>
#include <string>
#include <memory>

#include "global.h"
#include "Token.h"
#include "Property.h"

using FuncPtr = std::shared_ptr<class Func>;
using FuncCPtr = std::shared_ptr<const class Func>;

class Func : public std::enable_shared_from_this<Func>
{
private:
	Func(const std::string& funcInf = "");
public:
	~Func() = default;

    static FuncPtr makeFunc(const std::string& funcInf = "") noexcept;
    static FuncPtr makeFunc(FuncCPtr func) noexcept;

	bool isComplete() const noexcept;

	const std::string& getInf() const noexcept;
	std::string getPost() const noexcept;

	void retranslate() noexcept;

	FuncPtr derivative(const std::string& var) const noexcept;
	void setDerivative(const std::string& var) noexcept;

	double calculate(const Properties& props = {}) const noexcept;

	FuncPtr fragmentate() const noexcept;

	double operator()(const Properties& props = {}) const noexcept;
	operator std::string() const noexcept;

	friend FuncPtr sin(FuncPtr f);
	friend FuncPtr cos(FuncPtr f);
	friend FuncPtr tg(FuncPtr f);
	friend FuncPtr ctg(FuncPtr f);
	friend FuncPtr sqrt(FuncPtr f);
	friend FuncPtr abs(FuncPtr f);
	friend FuncPtr round(FuncPtr f);
	friend FuncPtr ceil(FuncPtr f);
	friend FuncPtr floor(FuncPtr f);
	friend FuncPtr asin(FuncPtr f);
	friend FuncPtr acos(FuncPtr f);
	friend FuncPtr atg(FuncPtr f);
	friend FuncPtr actg(FuncPtr f);
	friend FuncPtr ln(FuncPtr f);
	friend FuncPtr log(FuncPtr f);

	friend FuncPtr operator +(FuncCPtr f1, FuncCPtr f2);
	friend FuncPtr operator -(FuncCPtr f1, FuncCPtr f2);
	friend FuncPtr operator *(FuncCPtr f1, FuncCPtr f2);
	friend FuncPtr operator /(FuncCPtr f1, FuncCPtr f2);
	friend FuncPtr operator ^(FuncCPtr f1, FuncCPtr f2);

	static int countFragments(FuncCPtr func) noexcept;

private:
	std::string funcInf;
	std::vector<Token> tokensInf;
	std::vector<Token> tokensPost;

	friend class Translator;
	friend class Calculator;
	friend class FuncFragmentator;
	friend class DerivativeCalculator;
};
