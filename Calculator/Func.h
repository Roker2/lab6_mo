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

	inline bool isComplete() const noexcept { return !tokensPost.empty(); }

	const std::string& getInf() const noexcept;
	std::string getPost() const noexcept;

	void retranslate() noexcept;

	FuncPtr derivative(const std::string& var) const noexcept;
	void setDerivative(const std::string &var) noexcept;

	double calculate(const Properties& props = {}) const noexcept;

    std::vector<FuncPtr> fragmentate() const noexcept;

	double operator()(const Properties& props = {}) const noexcept;
	operator std::string() const noexcept;

private:
	std::string funcInf;
	std::vector<Token> tokensInf;
	std::vector<Token> tokensPost;

	friend class Translator;
	friend class Calculator;
	friend class FuncFragmentator;
};
