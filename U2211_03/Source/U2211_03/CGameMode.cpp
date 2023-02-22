#include "CGameMode.h"
#include "Global.h"

ACGameMode::ACGameMode()
{
	// ConstructorHelpers::FClassFinder<APawn> pawn(L"Blueprint'/Game/BP_CPlayer.BP_CPlayer_C'");
	// if (pawn.Succeeded())
	//	DefaultPawnClass = pawn.Class;

	CHelpers::GetClass<APawn>(&DefaultPawnClass, "Blueprint'/Game/BP_CPlayer.BP_CPlayer_C'");
}
