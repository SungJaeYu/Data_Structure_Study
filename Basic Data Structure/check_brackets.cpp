#include <iostream>
#include <stack>
#include <string>
#include <filesystem>

#define SUCCESS 0

struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int check_brackets(std::string text){
	std::stack <Bracket> opening_brackets_stack;
	for (int position = 0; position < text.length(); ++position) {
		char next = text[position];

		if (next == '(' || next == '[' || next == '{') {
			Bracket foo(next, position+1);
			opening_brackets_stack.push(foo);
			continue;
		}

		if (next == ')' || next == ']' || next == '}') {
			if(opening_brackets_stack.empty()) return 0;
			Bracket top = opening_brackets_stack.top();
			if(top.Matchc(next)){
				opening_brackets_stack.pop();
				continue;
			}
			else
				return position+1;
		}
	}
	if(opening_brackets_stack.empty())
		return SUCCESS;
	else
		return opening_brackets_stack.top().position;
}


int main() {
    std::string text;
    getline(std::cin, text);
    int check = check_brackets(text);

	if(check == SUCCESS)
		std::cout << "Success" << std::endl;
	else
		std::cout << check << std::endl;
}
