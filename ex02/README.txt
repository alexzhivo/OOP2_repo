oop2_ex02
=====================================================================
		ex02
=====================================================================

	Author: Alex Zhivotovsky.
	ID: Alex - 319257903.

=====================================================================
		Description
===================================================================== 	 

	In this exercise, we will build a terminal application (Terminal, Console)
	that is used to fill out form 101 for the current tax year.
	specificly we have given a main.cpp file and we needed to create the header files
	for the program so it will compile and work.

=====================================================================
		Included files
=====================================================================

the files added inside include directory:

	- Form.h
	- Field.h
	- Date.h
	- MailPattern.h
	- AddressPattern.h
	- NamePattern.h
	- Validator.h
	- RegexValidator.h
	- RangeValidator.h
	- IdValidator.h
	- ValuesToNames.h (not working)
	- IncomeOptions.h (not working)

the files added inside src directory:

	- main.cpp

=====================================================================
                          Data Structures
=====================================================================

	when i used Data Structures i mainly used Vectors.

=====================================================================
                     Algorithms worth mention
=====================================================================
	
	i used the regex library for c++ for regex stuff.

=====================================================================
                              Design
=====================================================================
	
	Validator is used as an abstruct class for RangeValidator,
	RegexValidator, IdValidator to inherit from.
	
	Form consists of Fields thus Form object holds a vector of Field class objects.

=====================================================================
                            Known bugs
=====================================================================

	the program is not working for everything that involves with ValuesToNames class.
	(7,8,9 - fields do not work)

=====================================================================
                             Comments
=====================================================================

	Unfortunately I couldn't get ValuesToNames to work so I got stuck on it for a long
	time in the exercise so I didn't have time to finish it.