#include <iostream>
#include <string>
#include <map>
#include <locale>
#include <windows.h>

using namespace std;

class KeyboardTranslator
{
private:

    // Àíãë -> Óêð
    static map<char, wchar_t> engToUkr;

    // Óêð -> Àíãë
    static map<wchar_t, char> ukrToEng;

public:

    // Àíãë³éñüêà -> Óêðà¿íñüêà
    static wstring toUkr(const string& text)
    {
        wstring result;

        for (char ch : text)
        {
            char lower = tolower(ch);

            if (engToUkr.find(lower) != engToUkr.end())
            {
                wchar_t ukr = engToUkr[lower];

                // âåëèê³ áóêâè
                if (isupper(ch))
                {
                    ukr = towupper(ukr);
                }

                result += ukr;
            }
            else
            {
                result += ch;
            }
        }

        return result;
    }

    // Óêðà¿íñüêà -> Àíãë³éñüêà
    static string toEng(const wstring& text)
    {
        string result;

        for (wchar_t ch : text)
        {
            wchar_t lower = towlower(ch);

            if (ukrToEng.find(lower) != ukrToEng.end())
            {
                char eng = ukrToEng[lower];

                // âåëèê³ áóêâè
                if (iswupper(ch))
                {
                    eng = toupper(eng);
                }

                result += eng;
            }
            else
            {
                result += '?';
            }
        }

        return result;
    }
};

// Àíãë -> Óêð
map<char, wchar_t> KeyboardTranslator::engToUkr =
{
    {'q', L'é'}, {'w', L'ö'}, {'e', L'ó'}, {'r', L'ê'}, {'t', L'å'},
    {'y', L'í'}, {'u', L'ã'}, {'i', L'ø'}, {'o', L'ù'}, {'p', L'ç'},
    {'[', L'õ'}, {']', L'¿'}, {'\\', L'´'},

    {'a', L'ô'}, {'s', L'³'}, {'d', L'â'}, {'f', L'à'}, {'g', L'ï'},
    {'h', L'ð'}, {'j', L'î'}, {'k', L'ë'}, {'l', L'ä'}, {';', L'æ'},
    {'\'', L'º'},

    {'z', L'ÿ'}, {'x', L'÷'}, {'c', L'ñ'}, {'v', L'ì'}, {'b', L'è'},
    {'n', L'ò'}, {'m', L'ü'}, {',', L'á'}, {'.', L'þ'}, {'/', L'.'}
};

// Óêð -> Àíãë
map<wchar_t, char> KeyboardTranslator::ukrToEng =
{
    {L'é', 'q'}, {L'ö', 'w'}, {L'ó', 'e'}, {L'ê', 'r'}, {L'å', 't'},
    {L'í', 'y'}, {L'ã', 'u'}, {L'ø', 'i'}, {L'ù', 'o'}, {L'ç', 'p'},
    {L'õ', '['}, {L'¿', ']'}, {L'´', '\\'},

    {L'ô', 'a'}, {L'³', 's'}, {L'â', 'd'}, {L'à', 'f'}, {L'ï', 'g'},
    {L'ð', 'h'}, {L'î', 'j'}, {L'ë', 'k'}, {L'ä', 'l'}, {L'æ', ';'},
    {L'º', '\''},

    {L'ÿ', 'z'}, {L'÷', 'x'}, {L'ñ', 'c'}, {L'ì', 'v'}, {L'è', 'b'},
    {L'ò', 'n'}, {L'ü', 'm'}, {L'á', ','}, {L'þ', '.'}
};

int main()
{
    // UTF-8 äëÿ Windows
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    setlocale(LC_ALL, "");

    wcout << L"=== Êîíâåðòåð ðîçêëàäêè ===" << endl;

    int choice;

    wcout << L"1: Àíãë³éñüêà -> Óêðà¿íñüêà" << endl;
    wcout << L"2: Óêðà¿íñüêà -> Àíãë³éñüêà" << endl;
    wcout << L"Âàø âèá³ð: ";

    cin >> choice;
    cin.ignore();

    if (choice == 1)
    {
        string text;

        cout << "Ââåä³òü òåêñò: ";
        getline(cin, text);

        wstring result = KeyboardTranslator::toUkr(text);

        wcout << L"Ðåçóëüòàò: " << result << endl;
    }
    else if (choice == 2)
    {
        wstring text;

        wcout << L"Ââåä³òü òåêñò: ";
        getline(wcin, text);

        string result = KeyboardTranslator::toEng(text);

        cout << "Result: " << result << endl;
    }
    else
    {
        wcout << L"Íåïðàâèëüíèé âèá³ð!" << endl;
    }

    return 0;
}
