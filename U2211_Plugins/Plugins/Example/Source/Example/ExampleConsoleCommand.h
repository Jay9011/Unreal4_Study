// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"

class EXAMPLE_API FExampleConsoleCommand
{
public:
	FExampleConsoleCommand();
	~FExampleConsoleCommand();

private:
	struct IConsoleCommand* Command;
	struct IConsoleCommand* Command2;

private:
	void TestDialog();
	void ExecuteCommand(const TArray< FString >& InArgs, UWorld* InWorld);

	void PrintDialog(const FText& Context, const FText* Title = nullptr);
	void PrintDialog(const FString& Context, const FString* Title = nullptr);
	void PrintDialog(const FString& Context, const FString& Title);
};
