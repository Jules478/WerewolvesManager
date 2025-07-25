#include "../inc/Game.hpp"

bool isValidStartNumber(const str& input)
{
	if (input.empty())
		return false;
	for (char c : input)
	{
		if (!std::isdigit(c))
			return false;
	}
	try
	{
		int number = std::stoi(input);
		return (number >= 5 && number <= 68);
	}
	catch (const std::exception&)
	{
		return false;
	}
}

int main()
{
	str input = "";
	std::cout << "Enter number of players: " << std::endl;
	input = get_input();
	while (!isValidStartNumber(input))
	{
		std::cout << "Enter between 5 and 68 players" << std::endl;
		input = get_input();
	}
	Game game(std::stoi(input));
	while (1)
	{
		std::cout << "Enter command: ";
		input = get_input();
		if (input == "add")
		{
			std::cout << "Enter role to add: ";
			input = get_input();
			game.addPlayer(input);
		}
		else if (input == "remove")
		{
			std::cout << "Enter role to remove: ";
			input = get_input();
			game.removePlayer(input);
		}
		else if (input == "resize")
		{
			std::cout << "Enter new number of players: ";
			input = get_input();
			while (!isValidStartNumber(input))
			{
				std::cout << "Enter between 5 and 68 players" << std::endl;
				input = get_input();
			}
			game.setPlayerNo(std::stoi(input));
		}
		else
			std::cout << "Commands:" << std::endl << "add" << std::endl << "remove" << std::endl << "resize" << std::endl << "start" << std::endl;
	}
	return 0;
}