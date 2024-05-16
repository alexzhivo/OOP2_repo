#include <memory>
#include <string>
#include <iostream>
#include <cstdlib> // for system()
#include <cstdint> // for uint32_t
#include <chrono>  // for currentYear() implementation

//------------------- User includes ----------------------------

// A class that represents a form.
// As you will see below: many fields and many validators can be added to the form
#include "Form.h"

// A class that represents a field. 
// As you will see below: (at least) one validator can be added to each field 
#include "Field.h"

// A class that represents a range validator.
// It validates if a field value is in some range.
// The type used as template parameter must implement < and > operators.
#include "RangeValidator.h"

// A class that represents a regex validator.
// It validates whether a field value matches a specific format.
// The type used as template parameter must implement < and > operators.
#include "RegexValidator.h"

// A class that represents an ID validator.
// ID validation is done using the control digit.
// Works only on the type 'uint32_t'.
#include "IdValidator.h"

// A class that represents a value and his name.
// The class must override the << and >> operators.
// >> operator reads an int and << operator prints destination name if the value is
// valid and if not - the number.
// include "ValuesToNames.h"

// A class that defines Date
#include "Date.h"

// A class that keeps the mail format
#include "MailPattern.h"

// A class that keeps the address format
#include "AddressPattern.h"

// A class that keeps the name format
#include "NamePattern.h"

// A class that keeps the names of the different income options
// include "IncomeOptions.h"

// A class that keeps the names of the different other incomes options
// #include "OtherIncomes.h"

// A class that keeps the names of the tax credits options
// #include "TaxCredits.h"

// A class that represents a incomes-vs.-other incomes validator.
// It checks if reports matches each other.
// The types used as template parameter must be Field.
// #include "IncomesAndOtherIncomesValidator.h"

// A class that represents a other incomes-vs.-tax credits validator.
// It checks if the reports matches each other.
// The types used as template parameter must be Field.
// #include "OtherIncomesAndTaxCreditsValidator.h"

//------------------- Function declarations ----------------------------

// Gets the welcome message
std::string getWelcomeMessage();

// Gets the goodbye message
std::string getGoodbyeMessage();

// Gets the error message
std::string getErrorMessage();

// Utility function for clearing the terminal screen
void clearScreen();

// Utility function for getting current year from computer clock
Date currentDate();

// Utility function for getting current year from computer clock
int currentYear();

//------------------- consts --------------------------

constexpr int MIN_AGE = 16;
constexpr int MAX_AGE = 67;

//------------------- main ----------------------------

int main()
{
	// Creating the form fields
	auto nameField = std::make_unique<Field<std::string>>("What is your name?");
	auto idField = std::make_unique<Field<uint32_t>>("What is your ID?");
	auto mailField = std::make_unique<Field<std::string>>("What is your mail?");
	auto addressField = std::make_unique<Field<std::string>>("What is your address?");
	auto dateOfBirthField = std::make_unique<Field<Date>>("What is your date of birth? (YYYY-MM-DD)");
	auto startDateTaxYearField = std::make_unique<Field<Date>>("Date of beginning work in the tax year? (YYYY-MM-DD)");
	//auto incomeOptions = ValuesToNames<IncomeOptions>();
	//auto incomeField = std::make_unique<Field<ValuesToNames<IncomeOptions>>> ("Details of my income from this employer: I receive:\n" + incomeOptions.valuesAndNames());
	//auto otherIncomes = ValuesToNames<OtherIncomes>();
	//auto otherIncomesField = std::make_unique<Field<ValuesToNames<OtherIncomes>>>("Details of other incomes:\n" + otherIncomes.valuesAndNames());
	//auto taxCredits = ValuesToNames<TaxCredits>();
	//auto taxCreditsField = std::make_unique<Field<ValuesToNames<TaxCredits>>>("Receives tax credits at other income:\n" + taxCredits.valuesAndNames());

	// Creating the field validators
	auto nameValidator = std::make_unique<RegexValidator>(NamePattern::getPattern());
	auto idValidator = std::make_unique<IdValidator>();
	auto mailValidator = std::make_unique<RegexValidator>(MailPattern::getPattern());
	auto addressValidator = std::make_unique<RegexValidator>(AddressPattern::getPattern());
	auto ageValidator = std::make_unique<RangeValidator<Date>>(currentDate() - MAX_AGE, currentDate() - MIN_AGE);
	auto startDateTaxYearValidator = std::make_unique<RangeValidator<Date>>(currentYear(), currentDate());
	//auto incomeValidator = std::make_unique<RangeValidator<ValuesToNames<IncomeOptions>>>(1, 4);
	//auto otherIncomeValidator = std::make_unique<RangeValidator<ValuesToNames<OtherIncomes>>>(1, 6);
	//auto taxCreditsValidator = std::make_unique<RangeValidator<ValuesToNames<TaxCredits>>>(1, 3);
	
	// Adding the validators to the fields
	nameField->addValidator(nameValidator.get());
	idField->addValidator(idValidator.get());
	mailField->addValidator(mailValidator.get());
	addressField->addValidator(addressValidator.get());
	dateOfBirthField->addValidator(ageValidator.get());
	startDateTaxYearField->addValidator(startDateTaxYearValidator.get());
	//incomeField->addValidator(incomeValidator.get());	
	//otherIncomesField->addValidator(otherIncomeValidator.get());
	//taxCreditsField->addValidator(taxCreditsValidator.get());

	// Creating form validators
	//auto incomesAndOtherIncomesValidator
	//	= std::make_unique<IncomesAndOtherIncomesValidator>(incomeField.get(), otherIncomesField.get());
	//auto otherIncomesAndTaxCreditsValidator
	//	= std::make_unique<OtherIncomesAndTaxCreditsValidator>(otherIncomesField.get(), taxCreditsField.get());

	// Creating the form and adding the fields to it
	auto myForm = Form();
	myForm.addField(nameField.get());
	myForm.addField(idField.get());
	myForm.addField(mailField.get());
	myForm.addField(addressField.get());
	myForm.addField(dateOfBirthField.get());	
	myForm.addField(startDateTaxYearField.get());
	//myForm.addField(incomeField.get());
	//myForm.addField(otherIncomesField.get());
	//myForm.addField(taxCreditsField.get());

	// Adding form validators
	//myForm.addValidator(incomesAndOtherIncomesValidator.get());
	//myForm.addValidator(otherIncomesAndTaxCreditsValidator.get());

	// Getting the information from the user
	clearScreen();
	std::cout << getWelcomeMessage();

	// Get the input only for empty or not valid fields
	myForm.fillForm();

	// Validation loop
	for (auto formIsCorrect = myForm.validateForm(); !formIsCorrect; formIsCorrect = myForm.validateForm())
	{
		// Displays all form fields with value (and error if not valid)
		clearScreen();
		std::cout << getErrorMessage();
		std::cout << myForm << '\n';

		myForm.fillForm();
	}

	clearScreen();
	std::cout << getGoodbyeMessage();
	std::cout << myForm << '\n';
	return 0;
}

std::string getWelcomeMessage()
{
	return "+----------------------------------------------------------+\n"
		"|                  Hello and welcome!                      |\n"
		"|           Please fill the following 101 form             |\n"
		"+----------------------------------------------------------+\n";
}

std::string getErrorMessage()
{
	return "+----------------------------------------------------------+\n"
		"|     There was an error in at least one of the fields!    |\n"
		"|                Please correct the error(s)               |\n"
		"+----------------------------------------------------------+\n";
}

std::string getGoodbyeMessage()
{
	return "+----------------------------------------------------------+\n"
		"|                      Thank you!                          |\n"
		"|               This is the data you sent:                 |\n"
		"+----------------------------------------------------------+\n";
}

void clearScreen()
{
	system("cls");
}

Date currentDate()
{
	namespace ch = std::chrono;
	auto ymd = ch::year_month_day(ch::floor<ch::days>(ch::system_clock::now()));
	return Date(static_cast<unsigned>(static_cast<int>(ymd.year())), static_cast<unsigned>(ymd.month()), static_cast<unsigned>(ymd.day()));
}
int currentYear()
{
	namespace ch = std::chrono;
	auto ymd = ch::year_month_day(ch::floor<ch::days>(ch::system_clock::now()));
	return static_cast<int>(ymd.year());
}