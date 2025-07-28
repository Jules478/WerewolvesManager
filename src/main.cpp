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
#ifdef NICE
	system("clear");
#endif
	str input = "";
	std::cout << "Enter number of players: " << std::endl;
	input = get_input();
	while (!isValidStartNumber(input))
	{
		std::cout << "Enter between 5 and 68 players" << std::endl;
		input = get_input();
	}
	Game game(std::stoi(input));
#ifdef NICE
	system("clear");
#endif
	while (1)
	{
		std::cout << "Commands: " << "add | remove | resize | start | quit" << std::endl;
		std::cout << "Current Players: " << game.getPlayerNo() << " | Current Roles: " << game.getPlayers().size() << " | Current Balance: " << game.getBalance();
		if (game.getBalance() > 0)
			std::cout << " (Villager advantage)";
		else if (game.getBalance() < 0)
			std::cout << " (Villager Disadvantage)";
		std::cout << std::endl << std::endl;
		for (int i = 0; i < static_cast<int>(game.getPlayers().size()); i++)
			std::cout << game.getPlayers()[i]->getName() << std::endl;
		std::cout << std::endl << "Enter command: ";
		input = get_input();
		if (input.substr(0, 4) == "add ")
		{
			str arg = input.substr(4);
			game.addPlayer(arg);
		}
		else if (input.substr(0, 7) == "remove ")
		{
			str arg = input.substr(7);
			game.removePlayer(arg);
		}
		else if (input.substr(0, 7) == "resize ")
		{
			str arg = input.substr(7);
			while (!isValidStartNumber(arg))
			{
				std::cout << "Enter between 5 and 68 players" << std::endl;
				arg = get_input();
			}
			game.setPlayerNo(std::stoi(arg));
		}
		else if (input == "start")
		{
			if (game.tryStart() == true)
			{
				std::cout << "Game is Good we can start..." << std::endl;
				exit (0);
			}
		}
		else if (input == "quit")
		{
#ifdef NICE
			system("clear");
#endif
			exit(0);
		}
		else
		{
#ifdef NICE
			system("clear");
#endif
			std::cout << "Command '" << input << "' not recognised" << std::endl;
		}

	}
	return 0;
}