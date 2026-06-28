#include <iostream>
#include <string>
#include <map>
#include <locale>
#include <windows.h>

using namespace std;

class KeyboardTranslator
{
private:

    // јнгл -> ”кр
    static map<char, wchar_t> engToUkr;

    // ”кр -> јнгл
    static map<wchar_t, char> ukrToEng;

public:

    // јнгл≥йська -> ”крањнська
    static wstring toUkr(const string& text)
    {
        wstring result;

        for (char ch : text)
        {
            char lower = tolower(ch);

            if (engToUkr.find(lower) != engToUkr.end())
            {
                wchar_t ukr = engToUkr[lower];

                // велик≥ букви
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

    // ”крањнська -> јнгл≥йська
    static string toEng(const wstring& text)
    {
        string result;

        for (wchar_t ch : text)
        {
            wchar_t lower = towlower(ch);

            if (ukrToEng.find(lower) != ukrToEng.end())
            {
                char eng = ukrToEng[lower];

                // велик≥ букви
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

// јнгл -> ”кр
map<char, wchar_t> KeyboardTranslator::engToUkr =
{
    {'q', L'й'}, {'w', L'ц'}, {'e', L'у'}, {'r', L'к'}, {'t', L'е'},
    {'y', L'н'}, {'u', L'г'}, {'i', L'ш'}, {'o', L'щ'}, {'p', L'з'},
    {'[', L'х'}, {']', L'њ'}, {'\\', L'і'},

    {'a', L'ф'}, {'s', L'≥'}, {'d', L'в'}, {'f', L'а'}, {'g', L'п'},
    {'h', L'р'}, {'j', L'о'}, {'k', L'л'}, {'l', L'д'}, {';', L'ж'},
    {'\'', L'Ї'},

    {'z', L'€'}, {'x', L'ч'}, {'c', L'с'}, {'v', L'м'}, {'b', L'и'},
    {'n', L'т'}, {'m', L'ь'}, {',', L'б'}, {'.', L'ю'}, {'/', L'.'}
};

// ”кр -> јнгл
map<wchar_t, char> KeyboardTranslator::ukrToEng =
{
    {L'й', 'q'}, {L'ц', 'w'}, {L'у', 'e'}, {L'к', 'r'}, {L'е', 't'},
    {L'н', 'y'}, {L'г', 'u'}, {L'ш', 'i'}, {L'щ', 'o'}, {L'з', 'p'},
    {L'х', '['}, {L'њ', ']'}, {L'і', '\\'},

    {L'ф', 'a'}, {L'≥', 's'}, {L'в', 'd'}, {L'а', 'f'}, {L'п', 'g'},
    {L'р', 'h'}, {L'о', 'j'}, {L'л', 'k'}, {L'д', 'l'}, {L'ж', ';'},
    {L'Ї', '\''},

    {L'€', 'z'}, {L'ч', 'x'}, {L'с', 'c'}, {L'м', 'v'}, {L'и', 'b'},
    {L'т', 'n'}, {L'ь', 'm'}, {L'б', ','}, {L'ю', '.'}
};

int main()
{
    // UTF-8 дл€ Windows
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    setlocale(LC_ALL, "");

    wcout << L"===  онвертер розкладки ===" << endl;

    int choice;

    wcout << L"1: јнгл≥йська -> ”крањнська" << endl;
    wcout << L"2: ”крањнська -> јнгл≥йська" << endl;
    wcout << L"¬аш виб≥р: ";

    cin >> choice;
    cin.ignore();

    if (choice == 1)
    {
        string text;

        cout << "¬вед≥ть текст: ";
        getline(cin, text);

        wstring result = KeyboardTranslator::toUkr(text);

        wcout << L"–езультат: " << result << endl;
    }
    else if (choice == 2)
    {
        wstring text;

        wcout << L"¬вед≥ть текст: ";
        getline(wcin, text);

        string result = KeyboardTranslator::toEng(text);

        cout << "Result: " << result << endl;
    }
    else
    {
        wcout << L"Ќеправильний виб≥р!" << endl;
    }

    return 0;
}