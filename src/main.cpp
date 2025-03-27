#include <cstdlib>
#include <iostream>
#include <filesystem>
#include <Windows.h>
#include <string>
#include <vector>
#include <algorithm>

enum CommandType {
	quit,
	echo,
	type,
	notBuiltin,
};

CommandType commandToType(std::string& command) {
	if (command == "exit") return quit;
	if (command == "echo") return echo;
	if (command == "type") return type;
	return notBuiltin;
}

void handleEcho(std::string& args) {
	// If there are no arguments, only the <newline> is written.
	if (args.empty()) {
		std::cout << '\n';
		return;
	}

	// Write the arguments to standard output, followed by a <newline>
	std::cout << args << "\n";
}

std::string checkExecutable(std::string& command) {
	std::string envPath{ std::getenv("PATH") };
	envPath += ";;";
	while (!envPath.empty()) {
		std::string directory{ envPath.substr(0, envPath.find_first_of(";")) };
		try
		{
			for (const auto& entry : std::filesystem::directory_iterator(directory)) {
				if (entry.path().stem().string() == command)
					return entry.path().string();
			}
		}
		catch (const std::exception&) { ; }

		envPath = envPath.substr(envPath.find_first_of(";") + 1);
	}

	return "";
}

void handleType(std::string& command) {
	// If there are no arguments, user is reminded of the command syntax.
	if (command.empty()) {
		std::cout << "Missing argument: type <command>\n";
		return;
	}

	// Otherwise determine how the command (argument) would be interpreted if used.
	std::cout << command;

	// -- search for the command in the built-in commands list
	std::vector<std::string> builtins{ "exit", "echo", "type" };
	if (std::count(builtins.begin(), builtins.end(), command)) {
		std::cout << " is a shell builtin\n";
		return;
	}

	// -- loop through each PATH directory and search for the command
	std::string commandPath{ checkExecutable(command) };
	if (!commandPath.empty())
		std::cout << " is " << commandPath;

	// Otherwise, the command is unrecognized
	std::cout << ": not found\n";

}

void handleExecutable(std::string& cmdPath, std::string& args) {
	ShellExecute(nullptr, "open", cmdPath.c_str(), args.c_str(), nullptr, SW_SHOWNA);
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
	  input.erase(0, input.find_first_not_of(" \t")); // ignore leading whitespace
	  input.erase(input.find_last_not_of(" \t") + 1); // ignore tailing whitespace
	  if (input == "")								  // ignore empty input
		  continue;

	  // Get Command
	  std::string command{ input.substr(0, input.find(" ")) };

	  // Get Arguments
	  std::string arguments{};
	  if (input.find(" ") < input.size())
		  arguments = input.substr(input.find(" ") + 1, input.size());

	  // Handle the command
	  switch (commandToType(command))
	  {
	  case quit: // -- exit built-in command
		  return 0;

	  case echo: // -- echo built-in command
		  handleEcho(arguments);
		  break;

	  case type: // -- type built-in command
		  handleType(arguments);
		  break;

	  case notBuiltin: // -- Not a buit-in command
		  std::string commandPath{ checkExecutable(command) };
		  if (!commandPath.empty())
			  handleExecutable(commandPath, arguments);     // Executable file
		  else
			  std::cout << command << ": not found\n";  // unrecognized command
	  }

  }
}
