#include "pch.h"
// Include för precompiled header (älskar prcompiled headers)

// Använder inte 'using namespace std;' då som tidigare förklarat av mig anses det bra att undvika att använda namespaces
// då det kan skapa mer problem än det är värt i ett storskaligt projekt.

// Den här biten gavs till mig av en användare på en discord server.
// Den kollar först om koden körs på windows om den gör det så inkluderar den windows.h för vissa funktioner.
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN // Minskar vad som hämtas från windows.h
#define NOMINMAX 1 // Ser till att windows.h inte får definiera min eller max så det inte skapar konflikt med standardbiblioteket.


#include <windows.h> // Använder detta för några funktioner så som koden precis under denna kommentar och för UTF-8

void enableANSI() {
    auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD current_mode{};
    GetConsoleMode(handle, &current_mode);
    SetConsoleMode(handle, current_mode | ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}
#endif

// En liten funktion för att ge mig möjligheten att rensa konsol-fönstret när jag vill.
// Denna funktion brukade använda 'system("cls");' och 'system("clear");' senare användes 'std::cout << "\033c";'
// nu används ANSI argument, som än en gång jag fick hjälp med att lära mig av användare på nätet. I detta projekt har jag försökt utmana mig på många nivåer.
void cleanConsole() {
#define ESC "\x1b"
    std::cout << ESC "[2J" ESC "[H";
}

/*
Jag gillar när jag inte behöver skriva om samma kod flera gånger och därav letade jag efter en lösning till det på nätet och då lärde jag mig att
C++ har något som kallas 'templates' alltså mallar, jag ska nu använda detta för att skapa en generisk funktion som förmodligen kommer användas ofta.
Detta var blod, svett och tårar att lära mig men jag är glad att jag gjorde det.s
Exempel på användning: 'getValidInput<double>("Enter amount: ", 0.0, 1000.0, "Error");'
getValidInput<type>("", min, max,"");
*/

double balance = 0.0; // Globalt definierad double ändras under programmets livstid.
bool isRunning = true;
//då jag använder en while loop för att se till att programmet återgår till menyn så använder jag en bool som ett styrvärde som nyttjas i quitProgram(); även.

template<typename T>
T getValidInput
(const std::string &prompt, T min = std::numeric_limits<T>::lowest(), T max = std::numeric_limits<T>::max(),
 const std::string &errorMessage = "") {
    T input; //Detta skapar 'input' som är det som återges när allt blivit kontrollerat.
    while (true) {
        std::cout << prompt; // Så här är den del av mallen 'std::string& prompt,'
        std::cin >> input;

        // validerar om inmatning är acceptabel baserad på en vanlig funktionjag använt ofta
        // den ska tillåta mig att specififera ett felmedelande när kallad annars ger den ett ospecifikt fel.
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

/* Jag hittade ett fel där felmeddelandet repeterades ett antal gång lika med hur många felskrivna karaktärer gavs då jag använde 'char' för valideing.
 * Exempel "243" skulle få 3 felmeddelanden att bli utskrivna. Nu ignorerar koden allt efter första karaktären i detta fall.
 * Jag diskuterade detta länge och fick en snilleblixt då en nämde att "jqwdshfgjh" hade varit en acceptabel inmatning eftersom
 * den börjar med 'j' så jag ändrade min approach. Jag börade med att utesluta ett av problemen, att jag använde char då om användaren skrev som exemepl
 * "243" så går den igenom hela valideringsprocessen för alla 3 i rad så skapades problemet med repeterande felmeddelanden.
 * Nästa problem var som påpekat "nytrewuqyt" är tekniskt sagt acceptabelt, men det är löjligt så jag ändrade om hur jag gjorde saker.
 * Skapade då en validering som ser till att endast en bokstav ges och implementerade den i två funktioner som sedan flyttades till sin egna funktion för att bli kallad istället.
 */

// Jag lärde mig nyligen om regeln "Single-responsibility principle" av Robert C. Martin som då sa: "A module should be responsible to one, and only one, actor."
// Jag bestämde mig då för att flytta detta till en funktion då den tidigare repeterades två gånger i quitProgram(); och bankSavingsInterest();
bool isValidYesNo() {
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

// en funktion som inväntar att användaren trycket 'Enter' jag hittade hur man gör den här på något forum
// den funkar genom att invänta att användaren startar en ny rad.
void waitForEnter() {
    std::cin.clear(); // itifall det finns något i input buffern så borde det rensas här.
    std::cout << "\nTryck 'Enter' för att återgå till menyn...";
    std::cin.get();
    cleanConsole();
}

void bankDeposit() {
    // Använder min mall jag skapade tidigare för att snabbt och enkelt felkorrigera inmatning specifierar att negativa tal inte accepteras
    // och kontrollerar att talet inte överskrider vad som kan hanteras.
    // 'auto' används då det ser bättre ut occh förebygger probelm i framtiden om jag skulle ändra något i min mall som på något vis skulle påverka om jag överspecifierade typen.
    // Anses vara good practice när man använder mallar.
    std::cout << "Du har valt att sätta in pengar.\n";

    auto depositAmount = getValidInput<double>(
        "\nAnge belopp att sätta in: ",
        0.01, std::numeric_limits<double>::max(),
        "Felaktigt belopp. Ange ett positivt värde. (t.ex 50 eller 25.5)"
    );

    balance += depositAmount;
    // lägger ihop valörerna och ger totalet till 'balance' så vi kan hålla reda på saldot i programmet.
    std::cout << "\nDu har satt in " << depositAmount << " kr. Nytt saldo: " << balance << " kr.\n";

    waitForEnter(); // Inväntar användarens godkännande att återå till menyn.
}

void bankWithdraw() {
    // En spärr osm ser till att användaren inte låser sig i programmet genom att starta funktionen utan något saldo
    // Hade den som en if-sats i mainMenu(); tidigare men eftersom jag nyttjar funktionen på ett annat ställe förutom menyn så blir det mer stabilt
    // och underhållbart om jag skriver in det i funktionen direkt.
    if (balance < 0.01) {
        std::cout << "Inga pengar är registrerade på ditt konto hos oss!\n";
        waitForEnter();
        return;
    }
    /*
    samma som ovan men använder 'balance' som min 'max' för att se till att man inte drar ut mer pengar än man har.
    Jag gick med i en discord server för att diskutera och få hjälp med kod vi det här laget då jag inte alltid kan vända mig till min kompis forum är svårnavigerade.
    Jag fick hjälp med detta och fick förklarat att jag måste omvandla min double till en string i meddelandet eftersom man inte kan lägga ihop en string och en double
    Vet inte riktigt vad annars jag kan göra här men stör mig milt på att i felkoden visar den en massa onödiga nollor men annars är det inte ett problem.

    Okej så lämnar det jag skrivit tidigare för dokumentation. Tidigare använde jag '"Otillräckligt saldo. Ditt nuvarande saldo är " + std::to_string(balance) + " kr."'
    Jag hittad en fix för min småstörning, 'std::ostringstream' du kan se nedanför hur jag nyttjat den.
    */

    //detta fick jag efter att pratat med ett par folk. Ostringstream låter mig bygga en string för att använda senare.
    std::ostringstream balanceStream;
    balanceStream << std::fixed << std::setprecision(2) << balance;
    //sätter visad decimal till max 2 då det är vad som används av flesta banker när de visar valutor.
    std::string balanceStr = balanceStream.str();

    std::cout << "Du har valt uttag av pengar.\n";
    std::cout << "Ditt saldo hos oss är: " << balance << " kr.\n";

    auto withdrawAmount = getValidInput<double>(
        "Ange belopp att ta ut: ",
        0.01, balance,
        "Otillräckligt saldo / Felaktig inmatning. Ditt nuvarande saldo är " + balanceStr + " kr."
    );

    balance -= withdrawAmount;
    std::cout << "\nDu har tagit ut " << withdrawAmount << " kr. Nytt saldo: " << balance << " kr.\n";

    waitForEnter();
}

void bankCheckBalance() {
    //funktion för att kolla saldo på kontot

    while (true) {
        std::cout << "Ditt saldo är för nuvarande " << balance << " kr.\n";
        std::cout << "\nVill du göra en insättning eller ett utdrag?\n";
        std::cout << "\n1. Insättning.\n";
        std::cout << "2. Utdrag.\n";
        std::cout << "3. Återgå till meny.\n";

        auto bankCheckBalanceChoice = getValidInput<int>(
            "Ange ditt val: ",
            1, 3,
            "Fel! Ange ett korrekt val."
        ); // skapar och kontrollerar bankCheckBalanceChoice

        switch (bankCheckBalanceChoice) {
            case 1:
                cleanConsole();
                bankDeposit();
                return;
            case 2:
                cleanConsole();
                bankWithdraw();
                return;
            case 3:
                cleanConsole();
                return;
            default:
                std::cout << "Felaktig inmatning! Försök igen.\n";
                break;
        }
    }
}

// Min funktion för ränta
void bankInterest() {
    // En spärr osm ser till att användaren inte låser sig i programmet genom att starta funktionen utan något saldo
    if (balance < 0.01) {
        std::cout << "Inga pengar är registrerade på ditt konto hos oss!\n";
        waitForEnter();
        return;
    }
    // Etablerar interestRate typen och ser till att den är acceptabel.
    std::cout << "Ditt nuvarande saldo är " << balance << " kr.\n";
    auto interestRate = getValidInput<double>(
        "\nAnge den årliga räntan (i procent t.ex. 5 för 5%): ",
        0.01, 100.0,
        "Felaktig inmatning ange ett en procentsats mellan 0.01 och 100."
    );

    // Samma sak gäller här, etablerar och kontrollerar interestYears typen.
    auto interestYears = getValidInput<int>(
        "Ange antal år för att beräkna ränta: ",
        1, 100,
        "Fel! Ange ett positivt heltal för antal år (max 100 år)."
    );

    // Här nyttjar jag 'pow' från <cmath> och det känns som den var typ gjord för exakt det här.
    double newBalance = balance * pow(1 + interestRate / 100, interestYears);
    std::cout << "\nEfter " << interestYears << " år med " << interestRate << " % årlig ränta," <<
            " skulle ditt saldo vara: " << newBalance << " kr.\n";

    // Kollar om användaren vill lägga till räntan.
    std::cout << "Vill du att räntan ska läggas till ditt saldo? (j/n): ";

    if (bool isInterestChoice = isValidYesNo(); isInterestChoice) {
        balance = newBalance;
        std::cout << "Räntan har lagt lagts till ditt saldo.\n";
    } else {
        std::cout << "Räntan har inte lagts till ditt saldo.\n";
    }

    waitForEnter();
}

// Ett aningen förbättrad quitProgram funktion från mitt tidigare program.

void quitProgram() {
    while (true) {
        std::cout << "Vill du avsluta ditt ärende hos HäftigBank? (j/n): ";

        if (bool isQuitChoice = isValidYesNo(); isQuitChoice) {
            // Om användaren skrev 'J' eller 'j' så kommer detta vara sant
            cleanConsole();
            std::cout << "Tack för att du använder HäftigBank. Hej då!\n" << std::endl;
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

// Skapar min meny som programmet återvänder till via while-loopen i main();
void mainMenu() {
    // Anger alternativ till användaren
    std::cout << "Välkommen till HäftigBank användare!\n";
    std::cout << "\nVad vill du göra?\n";
    std::cout << "\n1. Insättning\n";
    std::cout << "2. Uttag\n";
    std::cout << "3. Saldo\n";
    std::cout << "4. Räntebetalning\n";
    std::cout << "5. Avsluta\n";

    auto mainMenuChoice = getValidInput<int>(
        "\nAnge ditt val: ",
        1, 5,
        "Felaktig inmatning! Ange ett nummer mellan 1 - 5."
    ); // Initierar mainMenuChoice och ser till att inmatning blir rätt

    // Switch som ansvarar för menyval
    switch (mainMenuChoice) {
        case 1:
            cleanConsole();
            bankDeposit();
            break;
        case 2:
            cleanConsole();
            bankWithdraw();
            break;
        case 3:
            cleanConsole();
            bankCheckBalance();
            break;
        case 4:
            cleanConsole();
            bankInterest();
            break;
        case 5:
            quitProgram();
            return;
        default:
            cleanConsole();
            std::cout << "Ogiltigt val. Försök igen.\n";
    }
}

// Main är endast en deligerare och startar endast 'mainMenu' functionen som styr programflödet.
int main() {
    // Här används koden för den lilla include sektionen jag skrev tidigare i programmer (den som en annan hjälpte mig med)
    // han tipsade om det för att då undviker jag att krångla med lokalen via 'std::locale::global(std::locale(""));'
    // Dock värt att nämna att jag behövde lära mig hur man ändrar till UTF-8 via "https://learn.microsoft.com/en-us/cpp/build/reference/utf-8-set-source-and-executable-character-sets-to-utf-8?view=msvc-170"
    // Jag använde command line lösningen för att rätta detta. Vet inte vilken av de två lösningarna som är bäst men kör på detta för detta projekt.
#ifdef _WIN32
    enableANSI();
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif

    // CLion varnade "Global variable 'isRunning' used in loop condition is not updated in the loop"
    // Jag googlade igen för att lösa.
    while (isRunning) {
        mainMenu();
    }
    isRunning = false;
    return 0;
}
