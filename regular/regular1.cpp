
/*
letter(letter|digit)*
*/

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

enum TokenType
{
    ERROR,
    LPAREN,
    RPAREN,
    EQUAL,
    NOTEQUAL,
    NOT,
    TEOF,
    AND,
    OR,
    ID
};

class Token
{
public:


public:
    Token()
    {
        kind = ERROR;
    }

    Token(TokenType type)
    {
        kind = type;
    }

    Token(TokenType type, string tmp)
    {
        kind = type;
        str = tmp;
    }

public:
    TokenType kind;
    string str;
};

class ScriptScanner
{
public:
    ScriptScanner(string str) : 
        current_pos(0), start_read_pos(0), script(str)
    {}

    Token getNextToken()
    {
        Token currentToken;
        LexerStatus state = STATE_START;

        start_read_pos = current_pos;
        while (state != STATE_IN_DONE)
        {
            char ch = readChar();
            switch (state)
            {
            case STATE_START:
            {
                if (isalpha(ch))
                    state = STATE_IN_VAR;
                else if (ch == '=')
                    state = STATE_IN_EQUAL;
                else if (ch == '<')
                    state = STATE_IN_NOTEQUAL;
                else {
                    state = STATE_IN_DONE;

                    switch (ch)
                    {
                    case EOF:
                        currentToken = Token(TEOF);
                        break;
                    case '&':
                        currentToken = Token(AND);
                        break;
                    case '|':
                        currentToken = Token(OR);
                        break;
                    case '~':
                        currentToken = Token(NOT);
                        break;
                    case '(':
                        currentToken = Token(LPAREN);
                        break;
                    case ')':
                        currentToken = Token(RPAREN);
                        break;
                    default:
                        currentToken = Token(ERROR);
                        break;
                    }
                }
                current_pos++;
                break;
            }

            case STATE_IN_EQUAL:
            {
                state = STATE_IN_DONE;

                if (ch == '=')
                    currentToken = Token(EQUAL);
                else
                    currentToken = Token(ERROR);

                current_pos++;
                break;
            }

            case STATE_IN_NOTEQUAL:
            {
                state = STATE_IN_DONE;

                if (ch == '>')
                    currentToken = Token(NOTEQUAL);
                else
                    currentToken = Token(ERROR);

                current_pos++;
                break;
            }

            case STATE_IN_VAR:
            {
                // state = STATE_IN_DONE;

                if (!(isalpha(ch) || isdigit(ch)))
                {
                    state = STATE_IN_DONE;
                    string tmp = script.substr(start_read_pos, current_pos);
                    currentToken = Token(ID, tmp);
                }
                else {
                    current_pos++;
                }
                break;
            }

            default:
            {
                state = STATE_IN_DONE;
                currentToken = Token(ERROR);
            }
            }
        }

        return currentToken;
    }

private:
    int current_pos;
    int start_read_pos;
    string script;

    enum LexerStatus
    {
        STATE_START,
        STATE_IN_VAR,
        STATE_IN_EQUAL,
        STATE_IN_NOTEQUAL,
        STATE_IN_DONE
    };

    char readChar()
    {
        if (script.length() == 0 || current_pos >= script.length())
            return TEOF;

        return script[current_pos];
    }
};

int main()
{
    string readin;
    while (cin >> readin)
    {
        ScriptScanner testscan(readin);
        Token testtoken = testscan.getNextToken();
        cout << testtoken.kind << "     " << testtoken.str << endl;
    }


    return 0;
}