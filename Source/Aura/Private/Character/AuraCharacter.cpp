// Gabkis Games


#include "Character/AuraCharacter.h"
#include "GameFramework\CharacterMovementComponent.h"
#include <Player\AuraPlayerState.h>
#include "AbilitySystemComponent.h"
#include <Player\AuraPlayerController.h>
#include <UI\AuraHUD.h>
#include <AbilitySystem\AuraAbilitySystemComponent.h>

AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 400.0f, 0.0f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void AAuraCharacter::PossessedBy(AController* PossessedController)
{
	Super::PossessedBy(PossessedController);

	InitAbilityActorInfo();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitAbilityActorInfo();
}

void AAuraCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AttributeSet = AuraPlayerState->GetAttributeSet();

	AbilitySystemComponent->InitAbilityActorInfo(AuraPlayerState, this);
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	auto AuraPlayerController = Cast<AAuraPlayerController>(GetController());
	if (!AuraPlayerController)
	{
		return;
	}

	auto AuraHUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD());

	if (!AuraHUD)
	{
		return;
	}

	AuraHUD->InitOverlay(AuraPlayerController, AuraPlayerState, AbilitySystemComponent, AttributeSet);

}
