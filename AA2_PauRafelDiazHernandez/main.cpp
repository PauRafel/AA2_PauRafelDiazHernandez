#include <iostream>
#include "ConsoleControl.h"
#include "KeyCodes.h"

int main()
{
    CC::Clear();
    CC::SetColor(CC::YELLOW);
    CC::SetPosition(0, 0);

    std::cout << "==================================" << std::endl;
    std::cout << "    DUNGEON CRAWLER - AA2 THREADS" << std::endl;
    std::cout << "==================================" << std::endl;

    CC::SetColor(CC::GREEN);
    std::cout << "\nConsole utilities test" << std::endl;
    std::cout << "Timer system test" << std::endl;
    std::cout << "Input system test" << std::endl;

    CC::SetColor(CC::WHITE);
    std::cout << "\nPress any key to exit...";
    CC::WaithForReadNextKey();

    return 0;
}