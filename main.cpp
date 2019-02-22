/* This is the console executable, that makes use of the BullCow Class
This acts as the view in a MVC pattern and is responsible for all
user interaction. For game logic, see the FBullCowGame class.
*/

#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool PlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; 

// the entry point for our application
int main()
{
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = PlayAgain();
	} 
	while (bPlayAgain);

	return 0;	
}


void PrintIntro()
{	
	std::cout << "\nWelcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {          ___ " << std::endl;
	std::cout << "          (o o)         (o o) " << std::endl;
	std::cout << "   /-------\\ /           \\ /-------\\ " << std::endl;
	std::cout << "  / | Bull  |o            o| Cow  | \\ " << std::endl;
	std::cout << " *  |-------|              |------|  *" << std::endl;
	std::cout << "    ^       ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

// plays a single game to completion
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop askng for guesses while the game is NOT won
	// and there are still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess(); 

		// submit valid guess to the game and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
	return;
}

// loop continually until the user gives a valid guess
FText GetValidGuess() 
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do
	{
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		// check status and give feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an isogram.\n\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter your guess in all lowercase letters.\n\n";
			break;
		default:
			// assume guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
}

bool PlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word? (y/n) ";
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
	
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Well Done! You win!\n";
	}
	else
	{
		std::cout << "Better luck next time!\n";
	}
}
