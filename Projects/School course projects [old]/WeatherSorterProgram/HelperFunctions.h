//
// Created by Rei on 2024-12-18.
//

#pragma once
#include "pch.h"

// En standard input validation template, highly reusable.
template<typename T>
T getValidInput
(const std::string &prompt, T min = std::numeric_limits<T>::lowest(), T max = std::numeric_limits<T>::max(),
 const std::string &errorMessage = "") {
    T input;
    while (true) {
        std::cout << prompt;
        std::cin >> input;

        if (std::cin.fail() || input < min || input > max) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (!errorMessage.empty()) {
                // Använder '!' här då om jag specifierat 'std::string& errorMessage' finns det text som borde visas, annars visas ospecifikt felmeddelande.
                std::cout << errorMessage << '\n';
            } else {
                std::cout << "Ospecifikt Fel! Vänligen försök igen.\n";
            }
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return input;
        }
    }
}

inline void cleanConsole() {
#define ESC "\x1b"
    std::cout << ESC "[2J" ESC "[H";
}

inline void waitForEnter() {
    std::cin.clear(); // itifall det finns något i input buffern så borde det rensas här.
    std::cout << "\nTryck 'Enter' för att återgå till menyn...";
    std::cin.get();
    cleanConsole();
}

inline bool isValidYesNo() {
    std::string isValidYesNoStr;
    while (true) {
        std::getline(std::cin, isValidYesNoStr);

        if (isValidYesNoStr.length() != 1) {
            std::cout << "Felaktigt val! Ange endast en bokstav. (j/n)\n";
            continue;
        }

        // Tidigare så användes 'char isValidYesNoChar = std::tolower(isValidYesNoStr[0]);'
        // Men min IDE Clion varnade "Clang-Tidy: Narrowing conversion from 'int' to signed type 'char' is implementation-defined"
        // Så jag googlade hur man löser det och lärde mig om 'static_cast<char>' https://en.cppreference.com/w/cpp/language/static_cast

        char isValidYesNoChar = static_cast<char>(std::tolower(isValidYesNoStr[0]));

        if (isValidYesNoChar == 'j') {
            return true;
        } else if (isValidYesNoChar == 'n') {
            return false;
        } else {
            std::cout << "Felaktigt val! Ange 'j' för ja eller 'n' för nej.\n";
        }
    }
}
extern bool isRunning;

inline void quitProgram() {
    while (true) {
        std::cout << "Vill du avsluta programmet? (j/n): ";

        if (bool isQuitChoice = isValidYesNo(); isQuitChoice) {
            // Om användaren skrev 'J' eller 'j' så kommer detta vara sant
            cleanConsole();
            std::cout << "Tack för att du använder Väderkollen. Hej då!\n" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            isRunning = false;
            return;
        } else {
            // Om användaren skrev 'N' eller 'n' så kommer detta vara falskt och därför gå vidare till 'else'
            std::cout << "Återgår till menyn!\n";
            waitForEnter();
            break;
        }
    }
}