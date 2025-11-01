#include <bits/stdc++.h>
using namespace std;

// --- Token Types ---
// These are all the possible types of tokens our mini language supports.
// Its like using a Union to save memory by sharing spaces;
enum TokenType { INT, PRINT, IDENT, NUMBER, PLUS, MINUS, MUL, DIV, ASSIGN, LPAREN, RPAREN, SEMICOLON, END };

// --- Token ---
// Represents a single token with its type and value.
struct Token {
    TokenType type;
    string value;
};

// --- Lexer ---
// Responsible for converting raw source code into a list of tokens.
class Lexer {
    string text;      // The input code as a string.
    int pos;          // Current position in the input.
    char current_char;// The character at the current position.
public:
    Lexer(string t) : text(t), pos(0) {
        current_char = text[pos];
    }

    // Move to the next character in the input.
    void advance() {
        pos++;
        if (pos < text.size()) current_char = text[pos];
        else current_char = '\0'; // End of input.
    }

    // Skip any whitespace characters.
    void skip_whitespace() {
        while (current_char != '\0' && isspace(current_char)) advance();
    }

    // Parse a sequence of digits as an integer.
    string integer() {
        string result = "";
        while (current_char != '\0' && isdigit(current_char)) {
            result += current_char;
            advance();
        }
        return result;
    }

    // Parse an identifier (variable name or keyword).
    string identifier() {
        string result = "";
        while (current_char != '\0' && (isalnum(current_char) || current_char == '_')) {
            result += current_char;
            advance();
        }
        return result;
    }

    // Main function to tokenize the input string.
    vector<Token> tokenize() {
        vector<Token> tokens;
        while (current_char != '\0') {
            if (isspace(current_char)) { skip_whitespace(); continue; }

            // Numbers
            if (isdigit(current_char)) {
                tokens.push_back({NUMBER, integer()});
                continue;
            }

            // Identifiers and keywords
            if (isalpha(current_char)) {
                string id = identifier();
                if (id == "int") tokens.push_back({INT, id});
                else if (id == "print") tokens.push_back({PRINT, id});
                else tokens.push_back({IDENT, id});
                continue;
            }

            // Operators and punctuation
            switch (current_char) {
                case '+': tokens.push_back({PLUS, "+"}); break;
                case '-': tokens.push_back({MINUS, "-"}); break;
                case '*': tokens.push_back({MUL, "*"}); break;
                case '/': tokens.push_back({DIV, "/"}); break;
                case '=': tokens.push_back({ASSIGN, "="}); break;
                case '(': tokens.push_back({LPAREN, "("}); break;
                case ')': tokens.push_back({RPAREN, ")"}); break;
                case ';': tokens.push_back({SEMICOLON, ";"}); break;
                default: cerr << "Unknown char: " << current_char << endl; exit(1);
            }
            advance();
        }
        tokens.push_back({END, ""}); // End of input token.
        return tokens;
    }
};

// --- AST Nodes ---
// Abstract Syntax Tree base class.
struct AST {
    virtual ~AST() {}
};

// Represents a binary operation (e.g., addition, multiplication).
struct BinOp : AST {
    AST* left;
    Token op;
    AST* right;
    BinOp(AST* l, Token o, AST* r) : left(l), op(o), right(r) {}
};

// Represents a number literal or variable (for simplicity).
struct Num : AST {
    Token token;
    Num(Token t) : token(t) {}
};

// Represents a variable declaration (e.g., int x = 5;)
struct VarDecl : AST {
    string name;
    AST* value;
    VarDecl(string n, AST* v) : name(n), value(v) {}
};

// Represents a print statement (e.g., print(x);)
struct PrintStmt : AST {
    AST* expr;
    PrintStmt(AST* e) : expr(e) {}
};

// --- Parser ---
// Converts tokens into an AST.
class Parser {
    vector<Token> tokens;
    int pos;
public:
    Parser(vector<Token> t) : tokens(t), pos(0) {}

    // Get the current token.
    Token current_token() { return tokens[pos]; }

    // Consume a token of the expected type.
    void eat(TokenType type) {
        if (current_token().type == type) pos++;
        else { cerr << "Unexpected token: " << current_token().value << endl; exit(1); }
    }

    // Parse a factor (number, variable, or parenthesized expression).
    AST* factor() {
        Token tok = current_token();
        if (tok.type == NUMBER) { eat(NUMBER); return new Num(tok); }
        if (tok.type == LPAREN) {
            eat(LPAREN);
            AST* node = expr();
            eat(RPAREN);
            return node;
        }
        // For simplicity, treat identifiers as numbers (could be improved).
        if (tok.type == IDENT) { eat(IDENT); return new Num(tok); }
        cerr << "Invalid factor"; exit(1);
    }

    // Parse multiplication and division.
    AST* term() {
        AST* node = factor();
        while (current_token().type == MUL || current_token().type == DIV) {
            Token tok = current_token();
            if (tok.type == MUL) { eat(MUL); node = new BinOp(node, tok, factor()); }
            else if (tok.type == DIV) { eat(DIV); node = new BinOp(node, tok, factor()); }
        }
        return node;
    }

    // Parse addition and subtraction.
    AST* expr() {
        AST* node = term();
        while (current_token().type == PLUS || current_token().type == MINUS) {
            Token tok = current_token();
            if (tok.type == PLUS) { eat(PLUS); node = new BinOp(node, tok, term()); }
            else if (tok.type == MINUS) { eat(MINUS); node = new BinOp(node, tok, term()); }
        }
        return node;
    }

    // Parse a statement (variable declaration or print).
    AST* statement() {
        Token tok = current_token();
        if (tok.type == INT) {
            eat(INT);
            string name = current_token().value;
            eat(IDENT);
            AST* val = nullptr;
            if (current_token().type == ASSIGN) {
                eat(ASSIGN);
                val = expr();
            }
            eat(SEMICOLON);
            return new VarDecl(name, val);
        }
        if (tok.type == PRINT) {
            eat(PRINT);
            eat(LPAREN);
            AST* val = expr();
            eat(RPAREN);
            eat(SEMICOLON);
            return new PrintStmt(val);
        }
        cerr << "Unknown statement: " << tok.value << endl; exit(1);
    }

    // Parse the whole input into a list of statements.
    vector<AST*> parse() {
        vector<AST*> res;
        while (current_token().type != END) res.push_back(statement());
        return res;
    }
};

// --- Code Generator ---
// Converts the AST into C++ code and prints it out.
class CodeGen {
public:
    // Generate C++ code from the AST.
    void generate(vector<AST*> ast) {
        cout << "#include <iostream>\nusing namespace std;\nint main() {\n";
        for (AST* node : ast) {
            // Handle variable declarations.
            if (VarDecl* v = dynamic_cast<VarDecl*>(node)) {
                cout << "int " << v->name;
                if (v->value) cout << " = " << eval_expr(v->value);
                cout << ";\n";
            }
            // Handle print statements.
            else if (PrintStmt* p = dynamic_cast<PrintStmt*>(node)) {
                cout << "cout << " << eval_expr(p->expr) << " << endl;\n";
            }
        }
        cout << "return 0;\n}\n";
    }

    // Recursively evaluate expressions to generate code.
    string eval_expr(AST* node) {
        if (Num* n = dynamic_cast<Num*>(node)) return n->token.value;
        if (BinOp* b = dynamic_cast<BinOp*>(node))
            return "(" + eval_expr(b->left) + b->op.value + eval_expr(b->right) + ")";
        return "";
    }
};

// --- Main ---
// Entry point of the compiler.
int main(int argc, char* argv[]) {
    // Check for input file argument.
    if (argc < 2) { cerr << "Usage: ./compiler file.cppm\n"; return 1; }

    // Read the source code from the file.
    ifstream fin(argv[1]);
    string code((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());

    // Lexical analysis: convert code to tokens.
    Lexer lexer(code);
    vector<Token> tokens = lexer.tokenize();

    // Parsing: convert tokens to AST.
    Parser parser(tokens);
    vector<AST*> ast = parser.parse();

    // Code generation: print out C++ code.
    CodeGen gen;
    gen.generate(ast);

    return 0;
}
