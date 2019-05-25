#include <iostream>
#include <string.h>
#include <string>
#include <stdint.h>
#include <assert.h>
#include <functional>
#include <vector>

using namespace std;

#define MEM_SIZE 256

struct Memory {
	int pos;
	uint8_t block[MEM_SIZE];

	Memory() : pos(0) {
		memset(block, 0, MEM_SIZE);
	}
};

void execute(Memory *mem, std::string cmd) {
  for(auto it = cmd.begin(); it != cmd.end(); it++) {
	  // cout << *it << endl;
	  size_t lastOpeningSquareBracket = string::npos;
	  switch(*it) {
	  case '<':
		  mem->pos --;
		  break;	
	  case '>':
		  mem->pos ++;
		  break;
	  case '+':
		  mem->block[mem->pos] ++;
		  break;
	  case '-':
		  mem->block[mem->pos] --;
		  break;
	  case '.':
		  putchar(mem->block[mem->pos]);
		  break;
	  case ',':
		  mem->block[mem->pos] = getchar();
		  break;
	  case '[':
		  lastOpeningSquareBracket = it - cmd.begin();
		  if(mem->block[mem->pos] == 0)
			  it = cmd.begin() + cmd.find(']') + 1;
		  break;
	  case ']':
		  it = cmd.begin() + lastOpeningSquareBracket - 1;
		  break;
	  }
	}
}

void test_emptyCommand() {
	Memory mem;
	execute(&mem, "");
  
  	for(int i=0; i<MEM_SIZE; i++)
  		assert(mem.block[i] == 0);
    
	assert(mem.pos == 0);
}

void testPlus_alone() {
	Memory mem;
	std::string input = "+";
	execute(&mem, input);
  
	assert(mem.block[0] == 1);
}

// '-' da solo funziona
void testMinus_alone() {
	Memory mem;
	mem.pos ++; // mem.pos = 1
	execute(&mem, "-");
	// ora mem.pos = 0
	assert(mem.block[0] == 0);
}

// '<' sposta correttamente se il data pointer non è 0
void testShl_alone() {
	Memory mem;
	mem.pos = 1;
	execute(&mem, "<");
  
	assert(mem.pos == 0);
}

// Verifica che il loop non venga mai eseguito
void testLoop_alone_skipLoop() {
  Memory mem;
  execute(&mem, "[+]");
  
  assert(mem.block[0] == 0);
}

// '>' sposta correttamente se il data pointer è minore di BLOCK_SIZE - 1

void test() {
	test_emptyCommand();
	testPlus_alone();
	testMinus_alone();
	testShl_alone();
	testLoop_alone_skipLoop();
  
	printf("ALL TESTS PASSED\n");
}

class TestSuite {
 
public: 
	void registerTest(void *testCase) {
		testCases.push_back(testCase);
	}
    
	void run() {
		for(auto it: testCases)
			(*it)();
	}
  
private:
	std::vector<void*> testCases;
};

int main() {
	test();
  
	return 0;
}
