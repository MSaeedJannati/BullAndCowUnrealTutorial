// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

#include "Engine/RendererSettings.h"


void UBullCowCartridge::BeginPlay()
{
	Super::BeginPlay();
	InitialiseTheGame();
}

void UBullCowCartridge::OnInput(const FString& Input)
{
	OnUserInput(_hiddenWord, Input);
}

void UBullCowCartridge::OnUserInput(const FString& hiddenWord, const FString& userInput)
{
	ClearScreen();
	if (CheckIfGameOver(userInput))
		return;

	PrintCurrentStat();
	if (!HasCorrectLength(userInput))
	{
		PrintLine(TEXT("Please input a word with correct length!"));
		return;
	}
	if(!IsIsogram(userInput))
	{
		PrintLine(TEXT("Please enter an isogram word!"));
		return;
	}
	if (CheckIfCorrectAnswer(hiddenWord, userInput))
	{
		OnCorrectAnswer();
		return;
	}
	OnWrongAnswer();
}

FString UBullCowCartridge::ChooseRandomWord(const std::vector<FString>& choices)
{
	std::random_device randomDevice;
	std::default_random_engine randomGenerator{randomDevice()};
	const int32 max{static_cast<int32>(choices.size()) - 1};
	std::uniform_int_distribution<int> dist{0, max};
	const int32 randomIndex{dist(randomGenerator)};
	return choices[randomIndex];
}

void UBullCowCartridge::PrintWelcomeMessages(const FString& hiddenWord)
{
	PrintLine(TEXT("Welcome to Bull Cows!"));
	int32 hiddenWordLength = _hiddenWord.Len();
	FString desctiprionMessage = FString::Printf(TEXT("Guess the %i letter word!"), hiddenWordLength);
	PrintLine(desctiprionMessage);
	desctiprionMessage = FString::Printf(TEXT("Lives remaining: %i,%s"), hiddenWordLength,*hiddenWord);
	PrintLine(desctiprionMessage);
	PrintLine(TEXT("Press Enter to continue"));
}

bool UBullCowCartridge::CheckIfCorrectAnswer(const FString& hiddenWord, const FString& userInput)
{
	return hiddenWord == userInput;
}

void UBullCowCartridge::OnCorrectAnswer()
{
	PrintLine("Bulls eye!\nPress Enter to continue");
	_isGameOver = true;
}

void UBullCowCartridge::OnWrongAnswer()
{
	PrintLine(TEXT("Wrong answer baby!"));
	if (!CheckForLose())
		return;
	PrintLine(TEXT("You lost!\nPress Enter to continue"));
	
}

void UBullCowCartridge::InitialiseTheGame()
{
	const std::vector<FString> choices{
		TEXT("dick"),TEXT("pubes"),TEXT("arse")
	};

	_hiddenWord = ChooseRandomWord(choices);
	_lives = _hiddenWord.Len();
	_isGameOver = false;
	PrintWelcomeMessages(_hiddenWord);
}

void UBullCowCartridge::PrintCurrentStat()
{
	int32 hiddenWordLength = _hiddenWord.Len();
	FString desctiprionMessage = FString::Printf(TEXT("Guess the %i letter word!"), hiddenWordLength);
	PrintLine(desctiprionMessage);
	desctiprionMessage = FString::Printf(TEXT("Lives remaining: %i"), _lives);
	PrintLine(desctiprionMessage);
}

bool UBullCowCartridge::CheckForLose()
{
	_lives--;
	if (_lives >= 0)
	{
		return false;;
	}
	_isGameOver = true;
	return true;
}

bool UBullCowCartridge::CheckIfGameOver(const FString& userInput)
{
	if (!_isGameOver)
		return false;
	PrintLine("The game is over! Do you like to play again? [Y/N]");
	if (userInput == TEXT("y") || userInput == TEXT("Y"))
	{
		ClearScreen();
		InitialiseTheGame();
	}
	return true;
}

bool UBullCowCartridge::HasCorrectLength(const FString& userInput)
{
	return userInput.Len() == _hiddenWord.Len();
}
bool UBullCowCartridge::IsIsogram(const FString userInput)
{
	auto length=userInput.Len();
	for (int i=0;i<length;i++)
	{
		for(int j=i+1;j<length;j++)
		{
			if(userInput[i]==userInput[j])
				return false;
		}
	}
	return true;
}