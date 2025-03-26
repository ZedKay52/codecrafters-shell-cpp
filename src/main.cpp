#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

enum CommandType {
	quit,
	echo,
	type,
	invalid,
};

CommandType commandToType(std::string& command) {
	if (command == "exit") return quit;
	if (command == "echo") return echo;
	if (command == "type") return type;
	return invalid;
}

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // Read-Eval-Print Loop
  while (true) {
	  std::cout << "$ ";

	  std::string input{};
	  std::getline(std::cin, input);

	  // set the recognized built-in commands
	  std::vector<std::string> builtins{ "exit", "echo", "type" };

	  // Get the built-in command and the provided arguments
	  std::string command{ input.substr(0, input.find(" ")) };
	  std::string argument{ input.substr(input.find(" ") + 1 , input.size()) };

	  // Handle the command
	  switch (commandToType(command))
	  {
	  case quit: // -- exit built-in command
		  return 0;

	  case echo: // -- echo built-in command
		  // If there are no arguments, only the <newline> is written.
		  if (input.find(" ") >= input.size()) {
			  std::cout << '\n';
			  continue;
		  }

		  // Write the arguments to standard output, followed by a <newline>
		  std::cout << argument << "\n";
		  break;

	  case type: // -- type built-in command
		  // If there are no arguments, user is reminded of the command syntax.
		  if (input.find(" ") >= input.size()) {
			  std::cout << "Missing argument: type <command>\n";
			  continue;
		  }

		  // Determine how the command (argument) would be interpreted if used.
		  std::cout << argument;
		  if (!std::count(builtins.begin(), builtins.end(), argument)) // unrecognized command
			  std::cout << ": not found\n";
		  else // built-in command
			  std::cout << " is a shell builtin\n";

		  break;

	  case invalid: // -- Unrecognized command
		  std::cout << command << ": command not found\n";
	  }

  }
}
