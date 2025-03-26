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

	  // Handle the token
	  // -- exit built-in command
	  if (token == "exit")
		  return 0;

	  // -- echo built-in command
	  else if (token == "echo") {
		  // If there are no arguments, only the <newline> is written.
		  if (command.find(" ") >= command.size()) {
			  std::cout << '\n';
			  continue;
		  }

		  // Write the arguments to standard output, followed by a <newline>
		  std::string argument{ command.substr(command.find(" ") + 1 , command.size()) };
		  std::cout << argument << "\n";
	  }
	  else
		std::cout << command << ": command not found\n";
  }
}
