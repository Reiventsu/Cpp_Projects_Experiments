#include "pch.h"
// Ovan länkar till pch.h som innehåller mina headers
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

void cleanConsole() {
#define ESC "\x1b"
    std::cout << ESC "[2J" ESC "[H";
}

const double MAX_WEIGHT = 700.0;
const double MAX_HEIGHT = 300.0;
const int MAX_AGE = 120;

double getValidWeight() {
    double weight;
    while (true) {
        std::cout << "Ange din vikt i kilogram: ";
        std::cin >> weight;

        // Kollar om inmatning är acceptabel.
        if (std::cin.fail() || weight <= 0 || weight > MAX_WEIGHT) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Kastar felaktig inmatning.
            std::cout << "Felaktig vikt! Ange ett positivt tal under 700 kg.\n";
        } else {
            return weight;
        }
    }
}

double getValidHeight() {
    double height;
    while (true) {
        std::cout << "Ange din längd i centimeter (t.ex 171): ";
        std::cin >> height;

        // Kollar om inmatning är acceptabel.
        if (std::cin.fail() || height <= 0 || height > MAX_HEIGHT) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Felaktig läng! Ange ett positivt tal under 300 cm.\n";
        } else {
            return height;
        }
    }
}

void waitForEnter() {
    std::cin.clear(); // itifall det finns något i input buffern så borde det rensas här.
    std::cout << "\nTryck 'Enter' för att återgå till menyn...";
    std::cin.get();
    cleanConsole();
}

int menu() {
    // skapar ett heltal här för att använda i en 'meny' baserat på användarens val.
    int choice = 0;

    while (true) {
        std::cout << "Vad önskar du göra härnäst?\n";
        std::cout << "\n1. Beräkna BMI\n";
        std::cout << "2. Beräkna BMR\n";
        std::cout << "3. Avsluta\n";
        std::cout << "\nAnge ett val (1-3): ";
        std::cin >> choice;

        // Validerar att användare har angett acceptabel inmatning.
        if (std::cin.fail() || choice < 1 || choice > 3) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            return choice;
        }
    }
}

void calcBMI() {
    double weight = getValidWeight(); //hämtar vikt
    double height = getValidHeight() / 100; // hämtar angiven vikt i cm och flyttar decimalen frammåt.


    double bmi = weight / (height * height);

    std::cout << "\nDin BMI är: " << bmi << '\n';

    //använder mig av tabellen skriven i inlämnings uppgift 1 för att uppfölja på användarens BMI resultat.
    if (bmi < 18.5) {
        std::cout << "Du är undervikt.\n";
    } else if (bmi >= 18.5 && bmi < 24.9) {
        std::cout << "Din vikt är sund och normal.\n";
    } else if (bmi >= 25.0 && bmi < 29.9) {
        std::cout << "Du är övervikt.\n";
    } else if (bmi >= 30 && bmi < 39.9) {
        std::cout << "Du är kraftigt övervikt.\n";
    } else {
        std::cout << "Du är extremt övervikt.\n";
    }

    // Inväntar användarens godkännande att återgå till menyn.
    waitForEnter();
    cleanConsole();
}

void calcBMR() {
    double weight = getValidWeight();
    double height = getValidHeight();
    int age;
    char sex;

    // Hämta ålder, har redan gjort en massa sådana här så måste inte kommentera men det är en enkel inmatnings check så att fel inmatning inte ges.
    while (true) {
        std::cout << "ange din ålder i år: ";
        std::cin >> age;

        if (std::cin.fail() || age <= 0 || age > MAX_AGE) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Felaktig ålder! Ange ett positivt tal under 120 år.\n";
        } else {
            break;
        }
    }

    // Hämtar användarens kön
    while (true) {
        std::cout << "Ange ditt kön (M/K): ";
        std::cin >> sex;
        sex = std::tolower(sex);
        // Här undrade jag om det fanns ett bättre sätt än att skriva ( == 'M' == 'm' osv.) och det visar sig att det gör det. Nu behöver bara 'm' och 'k' kollas.

        if (sex == 'm' || sex == 'k') {
            break;
        } else {
            std::cout << "Felaktig inmatning! Ange 'M' för man eller 'K' för kvinna.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    double bmr = 0.00; // Använder Harris-Benedict ekvationen
    // Om kön är man
    if (sex == 'm') {
        bmr = 66.47 + (13.75 * weight) + (5.003 * height) - (6.755 * age);
    } else {
        // Om kön är kvinna
        bmr = 655.1 + (9.563 * weight) + (1.85 * height) - (4.676 * age);
    }

    // Utmatning av resultat.
    int activityLevel = 0;
    double multiplierAcLvlBMR = 1.0;

    while (true) {
        std::cout << "\nHur aktiv är du?\n";
        std::cout << "\n1. Stillasittande (ingen ansträngande aktivitet)\n";
        std::cout << "2. Lätt aktivitet (lätt ansträngning 1-3 dagar i veckan) \n";
        std::cout << "3. Lagom aktiv (Lagom ansträngning 3-5 dagar i veckan)\n";
        std::cout << "4. Väldigt aktiv (Ansträngande träning 6-7 dagar i veckan)\n";
        std::cout << "5. Extremt aktiv (Krävande fysisk aktivitet eller träning 2 gånger per dag)\n";
        std::cout << "\nAnge ett val (1-5): ";
        std::cin >> activityLevel;

        if (std::cin.fail() || activityLevel < 1 || activityLevel > 5) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ogiltigt val! Ange ett nummer mellan 1 och 5.\n";
        } else {
            break;
        }
    }

    switch (activityLevel) {
        case 1:
            multiplierAcLvlBMR = 1.2; // Stillasittande
            break;
        case 2:
            multiplierAcLvlBMR = 1.375; // Lätt aktiv
            break;
        case 3:
            multiplierAcLvlBMR = 1.55; // Lagom aktiv
            break;
        case 4:
            multiplierAcLvlBMR = 1.725; // Väldigt aktiv
            break;
        case 5:
            multiplierAcLvlBMR = 1.9; // Extremt aktiv
            break;
    }

    // Räknar ihop BMR och aktivitetsnivå.
    double totalBMR = bmr * multiplierAcLvlBMR;

    // Informerar användaren om resultatet.
    std::cout << "\nDin BMR är: " << totalBMR << " kalorier per dag.\n";

    // Kallar funktionen för att invänta användarens godkännande att återgå till menyn.
    waitForEnter();
    cleanConsole();
}

// Skapade en funktion för att avsluta programmet snyggt jag googlade bara hur man gjorde detta, jag vet att sleep inte är en bra idé i vissa fall eftersom den fryser hela tråden.
// I detta fall är det okej eftersom programmet ska avslutas sa min kompis.
void quitProgram() {
    cleanConsole(); // Kallar cleanConsole funtkionen för att sopa rent i fönstret innan avslutning.
    std::cout << "Avslutar programmet. Hej då!" << std::endl;
    //använder endl; då jag inte förväntar mig inmatning från användaren eller vidare interaktion.
    std::this_thread::sleep_for(std::chrono::seconds(2));
    // Pausar programmer i 2 sekunder för att se till att användaren ser avslutnings meddelandet.
}

void greeting() {
    while (true) {
        int choice = menu(); // Kallar efter meny funktionen.

        switch (choice) {
            case 1:
                cleanConsole();
                calcBMI();
                break;
            case 2:
                cleanConsole();
                calcBMR();
                break;
            case 3:
                quitProgram();
                return;
        }
    }
}

int main() {
#ifdef _WIN32
	enableANSI();
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
#endif
    greeting(); // Kallar funktionen som startar programmets flöde.
    return 0;
}
