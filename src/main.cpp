#include "../inc/Game.hpp"

void clearScreen()
{
	// std::cout << "\033[H\033[2J"; // Use this to keep history of previous window states
	std::cout << "\033c"; // Use this to erase window and not keep history
	std::cout.flush();
}

void printTitle()
{
	std::cout << YELLOW "################################################################################\n" RESET;
	std::cout << YELLOW "#" WHITE "." RED "##" WHITE "....." RED "##" WHITE "." RED "##" WHITE "......." RED "########" WHITE "." RED "####" WHITE "." RED "##" WHITE "....." RED "##" WHITE "...." RED "###" WHITE "...." RED "########" WHITE "." RED "########" WHITE "......." YELLOW "#\n" RESET;
	std::cout << YELLOW "#" WHITE "." RED "##" WHITE "....." RED "##" WHITE "." RED "##" WHITE ".........." RED "##" WHITE "....." RED "##" WHITE ".." RED "###" WHITE "..." RED "###" WHITE "..." RED "##" WHITE "." RED "##" WHITE "......" RED "##" WHITE "...." RED "##" WHITE "............." YELLOW "#\n" RESET;
	std::cout << YELLOW "#" WHITE "." RED "##" WHITE "....." RED "##" WHITE "." RED "##" WHITE ".........." RED "##" WHITE "....." RED "##" WHITE ".." RED "####" WHITE "." RED "####" WHITE ".." RED "##" WHITE "..." RED "##" WHITE "....." RED "##" WHITE "...." RED "##" WHITE "............." YELLOW "#\n" RESET;
	std::cout << YELLOW "#" WHITE "." RED "##" WHITE "....." RED "##" WHITE "." RED "##" WHITE ".........." RED "##" WHITE "....." RED "##" WHITE ".." RED "##" WHITE "." RED "###" WHITE "." RED "##" WHITE "." RED "##" WHITE "....." RED "##" WHITE "...." RED "##" WHITE "...." RED "######" WHITE "........." YELLOW "#\n" RESET;
	std::cout << YELLOW "#" WHITE "." RED "##" WHITE "....." RED "##" WHITE "." RED "##" WHITE ".........." RED "##" WHITE "....." RED "##" WHITE ".." RED "##" WHITE "....." RED "##" WHITE "." RED "#########" WHITE "...." RED "##" WHITE "...." RED "##" WHITE "............." YELLOW "#\n" RESET;
	std::cout << YELLOW "#" WHITE "." RED "##" WHITE "....." RED "##" WHITE "." RED "##" WHITE ".........." RED "##" WHITE "....." RED "##" WHITE ".." RED "##" WHITE "....." RED "##" WHITE "." RED "##" WHITE "....." RED "##" WHITE "...." RED "##" WHITE "...." RED "##" WHITE "............." YELLOW "#\n" RESET;
	std::cout << YELLOW "#" WHITE ".." RED "#######" WHITE ".." RED "########" WHITE "...." RED "##" WHITE "...." RED "####" WHITE "." RED "##" WHITE "....." RED "##" WHITE "." RED "##" WHITE "....." RED "##" WHITE "...." RED "##" WHITE "...." RED "########" WHITE "......." YELLOW "#\n" RESET;
	std::cout << YELLOW "#" WHITE "." RED "##" WHITE "......" RED "##" WHITE "." RED "########" WHITE "." RED "########" WHITE ".." RED "########" WHITE "." RED "##" WHITE "......" RED "##" WHITE ".." RED "#######" WHITE ".." RED "##" WHITE "......." RED "########" YELLOW "#\n" RESET;
	std::cout << YELLOW "#" WHITE "." RED "##" WHITE ".." RED "##" WHITE ".." RED "##" WHITE "." RED "##" WHITE "......." RED "##" WHITE "....." RED "##" WHITE "." RED "##" WHITE "......." RED "##" WHITE ".." RED "##" WHITE ".." RED "##" WHITE "." RED "##" WHITE "....." RED "##" WHITE "." RED "##" WHITE "......." RED "##" WHITE "......" YELLOW "#\n" RESET;
	std::cout << YELLOW "#" WHITE "." RED "##" WHITE ".." RED "##" WHITE ".." RED "##" WHITE "." RED "##" WHITE "......." RED "##" WHITE "....." RED "##" WHITE "." RED "##" WHITE "......." RED "##" WHITE ".." RED "##" WHITE ".." RED "##" WHITE "." RED "##" WHITE "....." RED "##" WHITE "." RED "##" WHITE "......." RED "##" WHITE "......" YELLOW "#\n" RESET;
	std::cout << YELLOW "#" WHITE "." RED "##" WHITE ".." RED "##" WHITE ".." RED "##" WHITE "." RED "######" WHITE "..." RED "########" WHITE ".." RED "######" WHITE "..." RED "##" WHITE ".." RED "##" WHITE ".." RED "##" WHITE "." RED "##" WHITE "....." RED "##" WHITE "." RED "##" WHITE "......." RED "######" WHITE ".." YELLOW "#\n" RESET;
	std::cout << YELLOW "#" WHITE "." RED "##" WHITE ".." RED "##" WHITE ".." RED "##" WHITE "." RED "##" WHITE "......." RED "##" WHITE "..." RED "##" WHITE "..." RED "##" WHITE "......." RED "##" WHITE ".." RED "##" WHITE ".." RED "##" WHITE "." RED "##" WHITE "....." RED "##" WHITE "." RED "##" WHITE "......." RED "##" WHITE "......" YELLOW "#\n" RESET;
	std::cout << YELLOW "#" WHITE "." RED "##" WHITE ".." RED "##" WHITE ".." RED "##" WHITE "." RED "##" WHITE "......." RED "##" WHITE "...." RED "##" WHITE ".." RED "##" WHITE "......." RED "##" WHITE ".." RED "##" WHITE ".." RED "##" WHITE "." RED "##" WHITE "....." RED "##" WHITE "." RED "##" WHITE "......." RED "##" WHITE "......" YELLOW "#\n" RESET;
	std::cout << YELLOW "#" WHITE ".." RED "###" WHITE ".." RED "###" WHITE ".." RED "########" WHITE "." RED "##" WHITE "....." RED "##" WHITE "." RED "########" WHITE ".." RED "###" WHITE ".." RED "###" WHITE "..." RED "#######" WHITE ".." RED "########" WHITE "." RED "##" WHITE "......" YELLOW "#\n" RESET;
	std::cout << YELLOW "################################################################################\n" RESET;
	std::cout << std::endl;
}

/**
 * Check if first input is valid to start game
 * Game states 5-68 players
 */
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
		std::cout << "Commands: " << "add | remove | resize | start | set reveal | set drunk | set ghost | import | export | quit" << std::endl;
		std::cout << "\nCurrent Players: " << game.getPlayerNo() << " | Current Roles: " << game.getPlayers().size() << " | Current Balance: " << game.getBalance();
		if (game.getBalance() > 0)
			std::cout << " (Villager advantage)";
		else if (game.getBalance() < 0)
			std::cout << " (Villager Disadvantage)";
		std::cout << "\n\n" << (game.getGameMode() ? "Roles are revealed on death" : "Roles are not revealed on death");
		std::cout << " | " << (game.getDrunkMode() ? "Drunk is in the game" : "Drunk is not in the game");
		std::cout << " | " << (game.getGhostMode() ? "First player to die is the Ghost" : "First player to die is not the Ghost");
		std::cout << "\n" << std::endl;
		for (int i = 0; i < static_cast<int>(game.getPlayers().size()); i++)
			std::cout << game.getPlayers()[i]->getName() << std::endl;
		std::cout << "\nEnter command: ";
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
					{
						game.nightPhase();
						game.setTimeOfDay();
					}
					if (!game.checkWin())
					{
						game.dayPhase();
						game.setTimeOfDay();
					}
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
		else if (input == "set ghost")
		{
			game.setGhostMode();
			clearScreen();
			printTitle();
		}
		else if (input.substr(0, 7) == "export ")
		{
			str filename = input.substr(7, input.length());
			if (!std::all_of(filename.begin(), filename.end(), ::isalpha))
			{
				clearScreen();
				printTitle();
				std::cout << "Error: Invalid filename" << std::endl;
				continue;
			}
			std::ofstream file;
			try
			{
				std::filesystem::create_directories("presets");
			}
			catch (...)
			{
				clearScreen();
				printTitle();
				std::cout << "Error: preset directory could not be created" << std::endl;
				continue;
			}
			file.open("presets/" + filename + ".ini");
			if (!file.is_open())
			{
				clearScreen();
				printTitle();
				std::cout << "Error Opening File" << std::endl;
				continue;
			}
			game.saveToINI(file);
			clearScreen();
			printTitle();
			std::cout << "Game exported" << std::endl;
		}
		else if (input.substr(0, 7) == "import ")
		{
			str file = "presets/" + input.substr(7, input.length()) + ".ini";
			game.loadFromINI(file);
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
