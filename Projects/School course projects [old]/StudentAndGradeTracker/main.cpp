#include "pch.h"

/* Förord.
 * Det kommer finnas en del funktioner osv i detta program som jag endast förklarar vad dom gör alltså nödvändig dokumentation
 * det är onödigt för mig att förklara hur jag gjorde dessa funktioner då de alla är plundrade från mitt tidigare program, inför nästa arbete jag gör kommer jag nog att skapa
 * en fil med utility funktioner och stoppa allt där i så att jag enkelt kan använda det över mina projekt.
 * I detta projekt försöker jag använda struct och klass.
 * Jag försökte även tänka på hur man borde kommentera ett projekt men kan det kanske också betyder att jag har kommenterat det dåligt
 * när det gäller betygsättning då jag kanske förklarar mindre varför jag väljer att göra vissa saker.
 * Om du vill att jag ska gå igenom och kommentera mer så säg bara till.
 */

// Håller programmet igång via loopen i main() tills falskt av quitProgram()
bool isRunning = true;

// Detta är bara klipp och klistrad kod från mitt tidigare program då jag finner funktionerna väldigt nyttiga att ha.
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX 1
#include <windows.h>

// Funktion för att aktivera ANSI-kodning på Windows
void enableANSI() {
    auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD current_mode{};
    GetConsoleMode(handle, &current_mode);
    SetConsoleMode(handle, current_mode | ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}
#endif

// Rensar konsolen genom att använda ANSI-sekvenser
void cleanConsole() {
#define ESC "\x1b"
    std::cout << ESC "[2J" ESC "[H"; // Rensar skärmen och placerar markören i det övre vänstra hörnet
}

// Tidigare använd mall för att validera användarens inmatning
template<typename T>
T getValidInput
(const std::string &prompt, T min = std::numeric_limits<T>::lowest(), T max = std::numeric_limits<T>::max(),
 const std::string &errorMessage = "") {
    T input;
    while (true) {
        std::cout << prompt; // Fråga som visas till användaren
        std::cin >> input;

        if (std::cin.fail() || input < min || input > max) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (!errorMessage.empty()) {
                // Om felmeddelande är specificerat, visa det annars visas ospecifikt felmeddelande.
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

// Funktion för att kontrollera ja/nej-svar från användaren
bool isValidYesNo() {
    std::string isValidYesNoStr;
    while (true) {
        std::getline(std::cin, isValidYesNoStr);

        if (isValidYesNoStr.length() != 1) {
            std::cout << "Felaktigt val! Ange endast en bokstav. (j/n)\n";
            continue;
        }

        // Konverterat givet svar till liten bokstav så jag inte behöver kolla både 'J' och 'j' till exempel.
        if (char isValidYesNoChar = static_cast<char>(std::tolower(isValidYesNoStr[0])); isValidYesNoChar == 'j') {
            return true;
        } else if (isValidYesNoChar == 'n') {
            return false;
        } else {
            std::cout << "Felaktigt val! Ange 'j' för ja eller 'n' för nej.\n";
        }
    }
}

// Funktion för att säkerställa att användaren inte lämnar ett tomt textfält
std::string getValidString(const std::string &prompt, const std::string &errorMessage = "") {
    std::string input;
    while (true) {
        std::cout << prompt; // Fråga som visas till användaren
        std::getline(std::cin, input);
        if (!input.empty()) {
            return input;
        } else {
            std::cout << (errorMessage.empty() ? "Felaktig inmatning! Försök igen.\n" : errorMessage + '\n');
        }
    }
}

// Variabler för att hålla information om betyg och ämnen
std::string grades[5]{"Matematik", "Svenska", "Engelska", "Historia", "Fysik"};
int gradePoints[5];
char gradeLetters[5];

// Struct för att lagra personliga detaljer om en student
// Försöker använda struct här för att lära mig hur jag integrerar det i ettt program
struct StudentPersonalDetails {
    std::string firstName;
    std::string lastName;
    int age{};
};

// Klass för att hantera studentens betyg
// att lära mig hur man använder klasser har varit kul och hoppas snart att jag kan få arbeta med minne för som jag förstår det om man skulle vilka skapa en lista med flera studenter
// att kolla emellan så behöver man skapa flera olika student "objekt" för att göra något sådant, jag googlade bara lite kort för
class StudentGrades {
private:
    StudentPersonalDetails details; // Personliga detaljer
    int gradePoints[5] = {0}; // Array för att lagra betygspoäng
    char gradeLetters[5] = {' '}; // Array för att lagra betyg (bokstäver)
    const std::string grades[5] = {"Matematik", "Svenska", "Engelska", "Historia", "Fysik"}; // Lista av ämnen

public:
    // Konstruktor som sätter standardvärden för att undvika att kompilatorn bestämmer sina egna.
    StudentGrades()
        : details(), gradePoints{0}, gradeLetters{' '},
          grades{"Matematik", "Svenska", "Engelska", "Historia", "Fysik"} {
        details.age = 18; // Sätter en standardålder
    }

    // Funktion för att registrera studentens personliga detaljer.
    void setDetails() {
        details.firstName = getValidString("Förnamn: ", "Namnet får inte lämnas tomt!");
        details.lastName = getValidString("Efternamn: ", "Efternamnet får inte lämnas tomt!");
        details.age = getValidInput<int>("Ålder: ", 1, 100, "Ogiltig ålder! Ange ett heltal mellan 1 och 100.");
    }

    // Läser in betygspoäng från användaren
    // Lärde mig om hur man kunde "rotera" igenom en array med en for-loop och bara använda ++ för att gå ett steg fram med varje iteration.
    void readScores() {
        std::cout << "Ange betygspoäng för varje ämne (0-100):\n";
        for (int i = 0; i < 5; i++) {
            gradePoints[i] = getValidInput<int>(
                grades[i] + ": ", 0, 100, "Ogiltig poängtal! Ange ett värde mellan 0 och 100."
            );
        }
    }

    // Konverterar poäng till bokstavsbetyg
    void convertScoresToGrades() {
        for (int i = 0; i < 5; ++i) {
            if (gradePoints[i] >= 100) gradeLetters[i] = 'A';
            else if (gradePoints[i] >= 50) gradeLetters[i] = 'C';
            else gradeLetters[i] = 'F';
        }
    }

    // Skriver ut studentens betyg
    // Detta var lite krångligt och tog mig ett par försök att få snyggt
    void printGrades() const {
        std::cout << "\nStudent: " << details.firstName << " " << details.lastName
                << ", Ålder: " << details.age << "\n";
        for (int i = 0; i < 5; ++i) {
            std::cout << grades[i] << ": " << gradePoints[i]
                    << " (" << gradeLetters[i] << ")\n";
        }
    }

    // Funktion för att rensa studentens data
    // Då jag inte hanterar objektminne eller så, bestämde jag bara mig för att låta dig nolla data så programmet kan återanvändas utan att behöva startas om.
    // Man kan bara fortsätta att registrera studenter om och om igen och den kommer bara skriva över det som tidigare angetts men jag ville ändå ge valet
    void reset() {
        details = {};
        for (int i = 0; i < 5; ++i) {
            gradePoints[i] = 0;
            gradeLetters[i] = ' ';
        }
        std::cout << "Studentens data har rensats.\n";
    }
};

// Väntar på att användaren trycker på Enter tagen från mitt förra program
void waitForEnter() {
    std::cin.clear();
    std::cout << "\nTryck 'Enter' för att återgå till menyn...";
    std::cin.get();
    cleanConsole();
}

// Funktion för att avsluta programmet taget från mitt förra program
void quitProgram() {
    while (true) {
        std::cout << "Vill du avsluta programmet? (j/n): ";

        if (bool isQuitChoice = isValidYesNo(); isQuitChoice) {
            cleanConsole();
            std::cout << "Avslutar programmet.\n" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            isRunning = false;
            return;
        } else {
            std::cout << "Återgår till menyn!\n";
            waitForEnter();
            break;
        }
    }
}

// Huvudmeny Jag tog denna från förra programmet också och bara skrev om den lite.
void mainMenu(StudentGrades &student) {
    std::cout << "Välkommen användare!\n";
    std::cout << "\nVad vill du göra?\n";
    std::cout << "\n1. Registrera student.\n";
    std::cout << "2. Registrera/Uppdatera betyg.\n";
    std::cout << "3. Skriv ut betygsrapport.\n";
    std::cout << "4. Avsluta student.\n";
    std::cout << "5. Avsluta program.\n";

    auto mainMenuChoice = getValidInput<int>(
        "\nAnge ditt val: ",
        1, 5,
        "Felaktig inmatning! Ange ett nummer mellan 1 - 5."
    );

    switch (mainMenuChoice) {
        case 1:
            cleanConsole();
            student.setDetails();
            std::cout << "Student registrerad!\n";
            waitForEnter();
            break;
        case 2:
            cleanConsole();
            student.readScores();
            student.convertScoresToGrades();
            std::cout << "Betyg uppdaterade!\n";
            waitForEnter();
            break;
        case 3:
            cleanConsole();
            student.printGrades();
            waitForEnter();
            break;
        case 4:
            cleanConsole();
            student.reset();
            waitForEnter();
            break;
        case 5:
            quitProgram();
            return;
        default:
            cleanConsole();
            std::cout << "Ogiltigt val. Försök igen.\n";
    }
}

// Main som egentligen bara ser till att programmet återvänder till mainMenu tills användaren avslutar programmet
int main() {
#ifdef _WIN32
    enableANSI(); // Aktiverar ANSI-stöd för Windows
    SetConsoleCP(CP_UTF8); // Ställer in UTF-8 för konsolen
    SetConsoleOutputCP(CP_UTF8);
#endif

    StudentGrades student;

    while (isRunning) {
        mainMenu(student);
    }
    isRunning = false;
    return 0;
}
