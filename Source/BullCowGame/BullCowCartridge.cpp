// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay()
{
	Super::BeginPlay();
	PrintLine("Welcome to Bull Cows!");
	PrintLine("Type something and press enter please.");
}

void UBullCowCartridge::OnInput(const FString& Input)
{
	ClearScreen();
}
