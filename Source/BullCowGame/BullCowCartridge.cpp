// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"


void UBullCowCartridge::BeginPlay()
{
	InitialiseTheGame();
}

void UBullCowCartridge::OnInput(const FString& Input)
{
	OnUserInput(_hiddenWord, Input);
}

void UBullCowCartridge::OnUserInput(const FString& hiddenWord, const FString& userInput)
{
	ClearScreen();

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
	TArray< FStringFormatArg > args; 
	args.Add( FStringFormatArg( hiddenWordLength ) );
	FString desctiprionMessage =FString::Format(TEXT("Guess the {0} letter word!"), args);
	PrintLine(desctiprionMessage);
	PrintLine(TEXT("press enter to continue..."));
}

bool UBullCowCartridge::CheckIfCorrectAnswer(const FString& hiddenWord, const FString& userInput)
{
	return hiddenWord == userInput;
}

void UBullCowCartridge::OnCorrectAnswer()
{
	PrintLine("Bulls eye!");
}

void UBullCowCartridge::OnWrongAnswer()
{
	PrintLine("Wrong answer baby!");
}

void UBullCowCartridge::InitialiseTheGame()
{
	Super::BeginPlay();
	const std::vector<FString> choices{
		TEXT("dick"),TEXT("pubes"),TEXT("arse"),TEXT("pussy"),TEXT("pimp"),TEXT("dildo")
	};

	_hiddenWord = ChooseRandomWord(choices);
	PrintWelcomeMessages(_hiddenWord);
}
