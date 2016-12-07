#pragma once
#include <string>


int getNum(const std::string& prompt);	// Gets an integer through cin
										// Handles if User enters a character/ string
										// Throws runtime_error() if "End of Input" is encountered

int getPositiveNum(const std::string& prompt);	// Returns a number >= 0
												// Calls getNum() for input


std::string getString(const std::string& prompt);	// Reads a string from cin through getline()
													// Throws runtime_error() if "End of Input" is encountered

char getChar(const std::string& prompt);	// Returns a char, reading from cin
											// Throws runtime_error() if "End of Input" is encountered