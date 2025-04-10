#pragma once

#include <iostream> // väsentlig 
#include <cmath> // för BMI och BMR
#include <cstdlib> //används av min 'cleanConsole' funktion
#include <locale> // används i 'greeting'för att se till att bokstäver i konsol-rutan ser rätt ut.
#include <chrono> // används för 'chrono::seconds' i quitProgram funktionen
#include <thread> // för 'sleep_for' i quitProgram funktionen
#include <limits> // nyttjas av std::tolower
#include <cctype> // för std::numeric_limits