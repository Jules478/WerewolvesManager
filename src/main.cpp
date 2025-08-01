#include "../inc/Game.hpp"

void clearScreen()
{
    // std::cout << "\033[H\033[2J"; // Use this to keep history of previous window states
	std::cout << "\033c"; // Use this to erase window and not keep history
    std::cout.flush();
}

void printTitle()
{
	std::cout << YELLOW << "################################################################################" << RESET << std::endl;
	std::cout << YELLOW << "#" << WHITE << "." << RED << "##" << WHITE << "....." << RED << "##" << WHITE << "." << RED << "##" << WHITE << "......." << RED << "########" << WHITE << "." << RED << "####" << WHITE << "." << RED << "##" << WHITE << "....." << RED << "##" << WHITE << "...." << RED << "###" << WHITE << "...." << RED << "########" << WHITE << "." << RED << "########" << WHITE << "......." << YELLOW << "#" << RESET << std::endl;
	std::cout << YELLOW << "#" << WHITE << "." << RED << "##" << WHITE << "....." << RED << "##" << WHITE << "." << RED << "##" << WHITE << ".........." << RED << "##" << WHITE << "....." << RED << "##" << WHITE << ".." << RED << "###" << WHITE << "..." << RED << "###" << WHITE << "..." << RED << "##" << WHITE << "." << RED << "##" << WHITE << "......" << RED << "##" << WHITE << "...." << RED << "##" << WHITE << "............." << YELLOW << "#" << RESET << std::endl;
	std::cout << YELLOW << "#" << WHITE << "." << RED << "##" << WHITE << "....." << RED << "##" << WHITE << "." << RED << "##" << WHITE << ".........." << RED << "##" << WHITE << "....." << RED << "##" << WHITE << ".." << RED << "####" << WHITE << "." << RED << "####" << WHITE << ".." << RED << "##" << WHITE << "..." << RED << "##" << WHITE << "....." << RED << "##" << WHITE << "...." << RED << "##" << WHITE << "............." << YELLOW << "#" << RESET << std::endl;
	std::cout << YELLOW << "#" << WHITE << "." << RED << "##" << WHITE << "....." << RED << "##" << WHITE << "." << RED << "##" << WHITE << ".........." << RED << "##" << WHITE << "....." << RED << "##" << WHITE << ".." << RED << "##" << WHITE << "." << RED << "###" << WHITE << "." << RED << "##" << WHITE << "." << RED << "##" << WHITE << "....." << RED << "##" << WHITE << "...." << RED << "##" << WHITE << "...." << RED << "######" << WHITE << "........." << YELLOW << "#" << RESET << std::endl;
	std::cout << YELLOW << "#" << WHITE << "." << RED << "##" << WHITE << "....." << RED << "##" << WHITE << "." << RED << "##" << WHITE << ".........." << RED << "##" << WHITE << "....." << RED << "##" << WHITE << ".." << RED << "##" << WHITE << "....." << RED << "##" << WHITE << "." << RED << "#########" << WHITE << "...." << RED << "##" << WHITE << "...." << RED << "##" << WHITE << "............." << YELLOW << "#" << RESET << std::endl;
	std::cout << YELLOW << "#" << WHITE << "." << RED << "##" << WHITE << "....." << RED << "##" << WHITE << "." << RED << "##" << WHITE << ".........." << RED << "##" << WHITE << "....." << RED << "##" << WHITE << ".." << RED << "##" << WHITE << "....." << RED << "##" << WHITE << "." << RED << "##" << WHITE << "....." << RED << "##" << WHITE << "...." << RED << "##" << WHITE << "...." << RED << "##" << WHITE << "............." << YELLOW << "#" << RESET << std::endl;
	std::cout << YELLOW << "#" << WHITE << ".." << RED << "#######" << WHITE << ".." << RED << "########" << WHITE << "...." << RED << "##" << WHITE << "...." << RED << "####" << WHITE << "." << RED << "##" << WHITE << "....." << RED << "##" << WHITE << "." << RED << "##" << WHITE << "....." << RED << "##" << WHITE << "...." << RED << "##" << WHITE << "...." << RED << "########" << WHITE << "......." << YELLOW << "#" << RESET << std::endl;
	std::cout << YELLOW << "#" << WHITE << "." << RED << "##" << WHITE << "......" << RED << "##" << WHITE << "." << RED << "########" << WHITE << "." << RED << "########" << WHITE << ".." << RED << "########" << WHITE << "." << RED << "##" << WHITE << "......" << RED << "##" << WHITE << ".." << RED << "#######" << WHITE << ".." << RED << "##" << WHITE << "......." << RED << "########" << YELLOW << "#" << RESET << std::endl;
	std::cout << YELLOW << "#" << WHITE << "." << RED << "##" << WHITE << ".." << RED << "##" << WHITE << ".." << RED << "##" << WHITE << "." << RED << "##" << WHITE << "......." << RED << "##" << WHITE << "....." << RED << "##" << WHITE << "." << RED << "##" << WHITE << "......." << RED << "##" << WHITE << ".." << RED << "##" << WHITE << ".." << RED << "##" << WHITE << "." << RED << "##" << WHITE << "....." << RED << "##" << WHITE << "." << RED << "##" << WHITE << "......." << RED << "##" << WHITE << "......" << YELLOW << "#" << RESET << std::endl;
	std::cout << YELLOW << "#" << WHITE << "." << RED << "##" << WHITE << ".." << RED << "##" << WHITE << ".." << RED << "##" << WHITE << "." << RED << "##" << WHITE << "......." << RED << "##" << WHITE << "....." << RED << "##" << WHITE << "." << RED << "##" << WHITE << "......." << RED << "##" << WHITE << ".." << RED << "##" << WHITE << ".." << RED << "##" << WHITE << "." << RED << "##" << WHITE << "....." << RED << "##" << WHITE << "." << RED << "##" << WHITE << "......." << RED << "##" << WHITE << "......" << YELLOW << "#" << RESET << std::endl;
	std::cout << YELLOW << "#" << WHITE << "." << RED << "##" << WHITE << ".." << RED << "##" << WHITE << ".." << RED << "##" << WHITE << "." << RED << "######" << WHITE << "..." << RED << "########" << WHITE << ".." << RED << "######" << WHITE << "..." << RED << "##" << WHITE << ".." << RED << "##" << WHITE << ".." << RED << "##" << WHITE << "." << RED << "##" << WHITE << "....." << RED << "##" << WHITE << "." << RED << "##" << WHITE << "......." << RED << "######" << WHITE << ".." << YELLOW << "#" << RESET << std::endl;
	std::cout << YELLOW << "#" << WHITE << "." << RED << "##" << WHITE << ".." << RED << "##" << WHITE << ".." << RED << "##" << WHITE << "." << RED << "##" << WHITE << "......." << RED << "##" << WHITE << "..." << RED << "##" << WHITE << "..." << RED << "##" << WHITE << "......." << RED << "##" << WHITE << ".." << RED << "##" << WHITE << ".." << RED << "##" << WHITE << "." << RED << "##" << WHITE << "....." << RED << "##" << WHITE << "." << RED << "##" << WHITE << "......." << RED << "##" << WHITE << "......" << YELLOW << "#" << RESET << std::endl;
	std::cout << YELLOW << "#" << WHITE << "." << RED << "##" << WHITE << ".." << RED << "##" << WHITE << ".." << RED << "##" << WHITE << "." << RED << "##" << WHITE << "......." << RED << "##" << WHITE << "...." << RED << "##" << WHITE << ".." << RED << "##" << WHITE << "......." << RED << "##" << WHITE << ".." << RED << "##" << WHITE << ".." << RED << "##" << WHITE << "." << RED << "##" << WHITE << "....." << RED << "##" << WHITE << "." << RED << "##" << WHITE << "......." << RED << "##" << WHITE << "......" << YELLOW << "#" << RESET << std::endl;
	std::cout << YELLOW << "#" << WHITE << ".." << RED << "###" << WHITE << ".." << RED << "###" << WHITE << ".." << RED << "########" << WHITE << "." << RED << "##" << WHITE << "....." << RED << "##" << WHITE << "." << RED << "########" << WHITE << ".." << RED << "###" << WHITE << ".." << RED << "###" << WHITE << "..." << RED << "#######" << WHITE << ".." << RED << "########" << WHITE << "." << RED << "##" << WHITE << "......" << YELLOW << "#" << RESET << std::endl;
	std::cout << YELLOW << "################################################################################" << RESET << std::endl;
	std::cout << std::endl;
}

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
	clearScreen();
	printTitle();
	str input = "";
	std::cout << "Enter number of players: ";
	input = get_input();
	while (!isValidStartNumber(input))
	{
		std::cout << "Enter between 5 and 68 players: ";
		input = get_input();
	}
	Game game(std::stoi(input));
	clearScreen();
	printTitle();
	while (1)
	{
		std::cout << "Commands: " << "add | remove | resize | start | set reveal | set drunk | quit" << std::endl;
		std::cout << "Current Players: " << game.getPlayerNo() << " | Current Roles: " << game.getPlayers().size() << " | Current Balance: " << game.getBalance();
		if (game.getBalance() > 0)
			std::cout << " (Villager advantage)";
		else if (game.getBalance() < 0)
			std::cout << " (Villager Disadvantage)";
		std::cout << " | " << (game.getGameMode() ? "Roles are revealed on death" : "Roles are not revealed on death");
		std::cout << " | " << (game.getDrunkMode() ? "Drunk is in the game" : "Drunk is not in the game");
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
				game.firstNight();
				while (game.stopGame() == false)
				{
					if (!game.checkWin())
						game.nightPhase();
					if (!game.checkWin())
						game.dayPhase();
					if (game.checkWin())
						break;
				}
				game.checkSideWins();
				return 0;
			}
		}
		else if (input == "set reveal")
		{
			game.setGameMode();
			clearScreen();
			printTitle();
		}
		else if (input == "set drunk")
		{
			game.setDrunkMode();
			clearScreen();
			printTitle();
		}
		else if (input == "quit")
		{
			clearScreen();
			return 0;
		}
		else
		{
			clearScreen();
			printTitle();
			std::cout << "Command '" << input << "' not recognised" << std::endl;
		}
	}
	return 0;
}
