#include <iostream>
#include <string>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // Read-Eval-Print Loop
  while (true) {
	  std::cout << "$ ";

	  std::string command{};
	  std::getline(std::cin, command);

	  // Get the built-in command
	  std::string token{ command.substr(0, command.find(" ")) };

	  // Handle exit command
	  if (token == "exit")
		  return 0;

	  std::cout << command << ": command not found\n";
  }
}
