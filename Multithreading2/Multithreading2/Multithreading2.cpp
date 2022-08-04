// Multithreading2.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Manages Player and health of Player with multithreading
//

#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
std::mutex Mutex;

bool DidQuit = false;
bool ShouldDecrementLife = false;

struct Character 
{
    float Position = 0.0f;
    std::atomic<int> Score = 0;
    //int Score = 0;
    int Lives = 1;

    void DisplayStats() 
    {
        std::cout << "Lives: " << Lives << '\n';
    }
};

Character Player;

void UpdateCharacter1() 
{
    while (!DidQuit) 
    {
        if (ShouldDecrementLife) 
        {
            std::lock_guard<std::mutex> Guard(Mutex);
            if (Player.Lives > 0) 
            {
                //std::this_thread::sleep_for(std::chrono::milliseconds(500));
                std::this_thread::yield();
                --Player.Lives;
            }
        }
    }
}

void UpdateCharacter2()
{
    while (!DidQuit)
    {
        if (ShouldDecrementLife)
        {
            std::lock_guard<std::mutex> Guard(Mutex);
            if (Player.Lives > 0)
            {
                //std::this_thread::sleep_for(std::chrono::milliseconds(500));
                std::this_thread::yield();
                --Player.Lives;
            }
        }
    }
}

void ProcessInput() 
{
    while (!DidQuit) 
    {
        std::cout << "'a' to decrement player life\n";
        std::cout << "'d' to display player stats\n";
        std::cout << "'q' to quit\n";
        char userInput;
        std::cin >> userInput;
        switch (userInput)
        {
        case 'a':
            ShouldDecrementLife = true;
            break;
        case 'd':
            Player.DisplayStats();
            break;
        case 'q':
            DidQuit = true;
            break;
        default:
            break;
        }
        DidQuit = (userInput == 'q');
    }
}

int main()
{
    std::thread InputHandler(ProcessInput);
    std::thread CharacterUpdate1(UpdateCharacter1);
    std::thread CharacterUpdate2(UpdateCharacter2);

    InputHandler.join();
    CharacterUpdate1.join();
    CharacterUpdate2.join();

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
