// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include <random>
#include <string>
#include "BullCowCartridge.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
	void OnUserInput(const FString& hiddenWord, const FString& userInput);

	// Your declarations go below!
private:
#pragma region Fields
FString _hiddenWord;
#pragma  endregion
#pragma  region Methods
	FString ChooseRandomWord(const std::vector<FString>& choices);
	void PrintWelcomeMessages(const FString& hiddenWord);
	bool CheckIfCorrectAnswer(const FString& hiddenWord,const  FString& userInput);
	void OnCorrectAnswer();
	void OnWrongAnswer();
void InitialiseTheGame();
#pragma  endregion
};
