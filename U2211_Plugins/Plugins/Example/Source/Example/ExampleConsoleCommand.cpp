#include "ExampleConsoleCommand.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "HAL/IConsoleManager.h"
#include "Misc/MessageDialog.h"

FExampleConsoleCommand::FExampleConsoleCommand()
{
	FConsoleCommandDelegate command;
	command.BindRaw(this, &FExampleConsoleCommand::TestDialog);

	Command = IConsoleManager::Get().RegisterConsoleCommand(L"TestPrintDialog", L"Move Actor To Position(FVector)", command);

	FConsoleCommandWithWorldAndArgsDelegate command2;
	command2.BindRaw(this, &FExampleConsoleCommand::ExecuteCommand);

	Command2 = IConsoleManager::Get().RegisterConsoleCommand(L"MovePlayer", L"Move Actor To Position(FVector)", command2);
}

FExampleConsoleCommand::~FExampleConsoleCommand()
{
	if(!!Command)
		IConsoleManager::Get().UnregisterConsoleObject(Command);

	if(!!Command2)
		IConsoleManager::Get().UnregisterConsoleObject(Command2);
}

void FExampleConsoleCommand::TestDialog()
{
	FText title = FText::FromString("Warning");
	FText context = FText::FromString("Don't Moving. Need to position input");
	FMessageDialog::Debugf(context, &title);

}

void FExampleConsoleCommand::ExecuteCommand(const TArray<FString>& InArgs, UWorld* InWorld)
{
	// FString str;
	// for(FString args : InArgs)
	// 	str += args + ", ";
	//
	// GLog->Log(str);

	if(InArgs.Num() != 3)
	{
		PrintDialog("Don't move from your position. Provide input for the X, Y, Z coordinates.", "Warning");
		return;
	}

	FVector position;
	position.X = FCString::Atof(*InArgs[0]);
	position.Y = FCString::Atof(*InArgs[1]);
	position.Z = FCString::Atof(*InArgs[2]);

	if(FApp::IsGame())
	{
		APlayerController* controller = InWorld->GetFirstPlayerController<APlayerController>();
		ACharacter* character = controller->GetPawn<ACharacter>();

		character->SetActorLocation(position);

		return;
	}

	for(AActor* actor :  InWorld->GetCurrentLevel()->Actors)
	{
		if(!!actor && actor->GetName().Contains("PlayerStart"))
			actor->SetActorLocation(position);
	}
}

void FExampleConsoleCommand::PrintDialog(const FText& Context, const FText* Title)
{
	FMessageDialog::Debugf(Context, Title);
}

void FExampleConsoleCommand::PrintDialog(const FString& Context, const FString* Title)
{
	if(Title)
    {
        const FText TitleText = FText::FromString(*Title);
        PrintDialog(FText::FromString(Context), &TitleText);
    }
    else
    {
        PrintDialog(FText::FromString(Context));
    }
}

void FExampleConsoleCommand::PrintDialog(const FString& Context, const FString& Title)
{
    const FText TitleText = FText::FromString(Title);
    PrintDialog(FText::FromString(Context), &TitleText);
}