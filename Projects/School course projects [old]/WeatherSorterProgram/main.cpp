#include <utility>

#include "pch.h"
#include "HelperFunctions.h"

/* For this project I heavily relied on support from the internet, documentation and the C&C++ Together community on discord asking questions non-stop.
 * I don't know how terrible or good this is, but it's here and it works. The program is in Swedish and I may update it for English however due to time
 * It is not high on my priority list right now.
 */

//  Mainly used to correctly display "åäö" in the program.
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX 1
#include <windows.h>
bool isRunning = true;

void enableANSI() {
    auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD current_mode{};
    GetConsoleMode(handle, &current_mode);
    SetConsoleMode(handle, current_mode | ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}
#endif

bool isRunning = true;
class CityAndTemperature {
private:
    int temperature = 0;
    std::string cityName;

public:
    // constructor CLion suggested using nodiscard i simply obliged
    CityAndTemperature(std::string name, int temp) : cityName(std::move(name)), temperature(temp) {
    }

    [[nodiscard]] int getTemperature() const { return temperature; }

    [[nodiscard]] std::string getCityName() const { return cityName; }

    [[nodiscard]] std::string toString() const {
        return "I staden " + cityName + ", är det:" + std::to_string(temperature) + " grader";
    }
};

std::vector<CityAndTemperature> cities;

std::vector<CityAndTemperature> registerCitiesAndTemperature(int numCities) {
    std::vector<CityAndTemperature> cities;

    for (int i = 0; i < numCities; ++i) {
        std::string cityName;
        int temperature;

        std::cout << "Ange stad #" << (i + 1) << ": ";
        std::getline(std::cin, cityName);

        std::cout << "Ange stadens temperatur: " << cityName << ": ";
        temperature = getValidInput<int>("", -50, 50, "Ogiltig temperatur! Ange ett värde mellan -50 och 50.");

        cities.emplace_back(cityName, temperature);
    }
    return cities;
}

void sortCityByTemperature(std::vector<CityAndTemperature> &cities) {
    std::sort(cities.begin(), cities.end(), [](const CityAndTemperature &a, const CityAndTemperature &b) {
        return a.getTemperature() < b.getTemperature();
    });
}

bool findCityByTemperature(const std::vector<CityAndTemperature> &cities, int temperature) {
    auto it = std::lower_bound(cities.begin(), cities.end(), temperature, [](const CityAndTemperature &city, int temp) {
        return city.getTemperature() < temp;
    });

    if (it != cities.end() && it->getTemperature() == temperature) {
        std::cout << "Hittade stad: " << it->getCityName() << "\n";
        return true;
    } else {
        std::cout << "Ingen stad hittad med angiven temperatur: " << temperature << "\n";
        return false;
    }
}

void mainMenu() {
    // Anger alternativ till användaren
    std::cout << "Välkommen till Väderkollen användare!\n";
    std::cout << "Vad önskar du göra?\n";
    std::cout << "\n1. Registrera städer och deras temperatur.\n";
    std::cout << "2. avregistrera städer.\n";
    std::cout << "3. Sortera temperatur högst till lägst.\n";
    std::cout << "4. Varmaste staden!\n";
    std::cout << "5. Kallaste staden!\n";
    std::cout << "6. Sök efter stad med temperatur.\n";
    std::cout << "7. Avsluta program.\n";

    auto mainMenuChoice = getValidInput<int>(
        "\nAnge ditt val: ",
        1, 7,
        "Felaktig inmatning! Ange ett nummer mellan 1 - 7."
    ); // Initierar mainMenuChoice och ser till att inmatning blir rätt

    // Switch som ansvarar för menyval
    switch (mainMenuChoice) {
        case 1: {
            // registrera städer
            int numCities = getValidInput<int>("Hur många städer vill du registrera? (max 100) ", 1, 100,
                                               "Ange ett giltigt antal (1-100).");

            auto newCities = registerCitiesAndTemperature(numCities);
            cities.insert(cities.end(), newCities.begin(), newCities.end());
            std::cout << "Städer registrerade!\n";
            break;
        }
        case 2: {
            // avregistrera städer
            std::string cityName;
            std::cout << "Ange namnet på staden du vill ta bort: ";
            std::getline(std::cin, cityName);

            auto it = std::remove_if(cities.begin(), cities.end(),
                                     [&cityName](const CityAndTemperature &city) {
                                         return city.getCityName() == cityName;
                                     });
            if (it != cities.end()) {
                cities.erase(it, cities.end());
                std::cout << "Staden '" << cityName << "' togs bort.\n";
            } else {
                std::cout << "Ingen stad med namnet '" << cityName << "' hittades.\n";
            }
            break;
        }
        case 3: {
            // Sortera städer genom temperatur
            if (cities.empty()) {
                std::cout << "Inga städer att sortera.\n";
                break;
            }

            sortCityByTemperature(cities);
            std::reverse(cities.begin(), cities.end());

            std::cout << "Temperaturer sorterade i fallande ordning:\n";
            for (const auto &city: cities) {
                std::cout << city.toString() << '\n';
            }
            break;
        }
        case 4: {
            // Varmaste staden
            if (cities.empty()) {
                std::cout << "Inga städer är registrerade.\n";
                break;
            }
            auto warmest = *std::max_element(cities.begin(), cities.end(),
                                             [](const CityAndTemperature &a, const CityAndTemperature &b) {
                                                 return a.getTemperature() < b.getTemperature();
                                             });
            std::cout << "Den varmaste staden är " << warmest.getCityName()
                    << " med en temperatur på " << warmest.getTemperature() << " grader.\n";
            break;
        }
        case 5: {
            // Kallaste staden
            if (cities.empty()) {
                std::cout << "Inga städer är registrerade.\n";
                break;
            }
            auto coldest = *std::min_element(cities.begin(), cities.end(),
                                             [](const CityAndTemperature &a, const CityAndTemperature &b) {
                                                 return a.getTemperature() < b.getTemperature();
                                             });
            std::cout << "Den kallaste staden är " << coldest.getCityName()
                    << " med en temperatur på " << coldest.getTemperature() << " grader.\n";
            break;
        }
        case 6: {
            // Kallar till sortering innan sökning sker.
            // Sök efter stad med temperatur
            if (cities.empty()) {
                std::cout << "Inga registrerade städer hittade!\n";
                break;
            }

            sortCityByTemperature(cities);

            int searchTemp = getValidInput<int>("Ange sök temperatur: ", -50, 50,
                                                "Ange en temperatur mellan -50 och 50.");
            if (!findCityByTemperature(cities, searchTemp)) {
                std::cout << "Sökning avslutad. Ingen stad med angiven temperatur hittades.\n";
            }

            break;
        }

        case 7: {
            // Avsluta
            quitProgram();
            return;
        }
        default: {
            std::cout << "Ogiltigt val! Försök igen.\n";
            break;
        }
    }
    waitForEnter();
}

int main() {
#ifdef _WIN32
    enableANSI();
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif

    while (isRunning) {
        mainMenu();
    }
    isRunning = false;
    return 0;
}
