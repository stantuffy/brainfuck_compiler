#include <iostream>
#include <string.h>
#include <string>
#include <stdint.h>

using namespace std;

#define MEM_SIZE 256

struct Memory {
	int pos;
	uint8_t block[MEM_SIZE];

	Memory() : pos(0) {
		memset(block, 0, MEM_SIZE);
	}
};

int main() {
	string input;
	cin >> input;

	Memory mem;

	for(auto it = input.begin(); it != input.end(); it++) {
		// cout << *it << endl;
		size_t lastOpeningSquareBracket = string::npos;
		switch(*it) {
		case '<':
			mem.pos --;
			break;	
		case '>':
			mem.pos ++;
			break;
		case '+':
			mem.block[mem.pos] ++;
			break;
		case '-':
			mem.block[mem.pos] --;
			break;
		case '.':
			putchar(mem.block[mem.pos]);
			break;
		case ',':
			mem.block[mem.pos] = getchar();
			break;
		case '[':
			lastOpeningSquareBracket = it - input.begin();
			if(mem.block[mem.pos] == 0)
				it = input.begin() + input.find(']') + 1;
			break;
		case ']':
			it = input.begin() + lastOpeningSquareBracket - 1;
			break;
		}
	}

	return 0;
}
