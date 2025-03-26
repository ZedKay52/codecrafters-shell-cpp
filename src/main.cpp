#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // Read-Eval-Print Loop
  while (true) {
	  std::cout << "$ ";

	  std::string command{};
	  std::getline(std::cin, command);

	  // set the recognized built-in commands
	  std::vector<std::string> builtins{ "exit", "echo", "type" };

	  // Get the built-in command
	  std::string token{ command.substr(0, command.find(" ")) };

	  // Handle the token
	  // -- exit built-in command
	  if (token == "exit")
		  return 0;

	  // -- echo built-in command
	  if (token == "echo") {
		  // If there are no arguments, only the <newline> is written.
		  if (command.find(" ") >= command.size()) {
			  std::cout << '\n';
			  continue;
		  }

		  // Write the arguments to standard output, followed by a <newline>
		  std::string argument{ command.substr(command.find(" ") + 1 , command.size()) };
		  std::cout << argument << "\n";
	  }

	  // -- type built-in command
	  if (token == "type") {
		  // If there are no arguments, user is reminded of the command syntax.
		  if (command.find(" ") >= command.size()) {
			  std::cout << "Missing argument: type <command>\n";
			  continue;
		  }

		  // Determine how the command (argument) would be interpreted if used.
		  std::string argument{ command.substr(command.find(" ") + 1 , command.size()) };
		  std::cout << argument;
		  if (!std::count(builtins.begin(), builtins.end(), argument)) // unrecognized command
			  std::cout << ": not found\n";
		  else // built-in command
			  std::cout << " is a shell builtin\n";
	  }

	  // -- Unrecognized command
	  else
		std::cout << command << ": command not found\n";
  }
}
