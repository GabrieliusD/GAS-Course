// Gabkis Games


#include "Character/AuraEnemyCharacter.h"
#include "Aura\Aura.h"
#include <AbilitySystem\AuraAbilitySystemComponent.h>
#include <AbilitySystem\AuraAttributeSet.h>

AAuraEnemyCharacter::AAuraEnemyCharacter()
{
	bHighlighted = false;
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
	
}

void AAuraEnemyCharacter::HighlightActor()
{
	UE_LOG(LogTemp, Display, TEXT("Enemy Actor Highlighted: %s"), *GetActorNameOrLabel());
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);

	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	bHighlighted = true;
}

void AAuraEnemyCharacter::UnHighlightActor()
{
	UE_LOG(LogTemp, Display, TEXT("Enemy Actor UnHighlighted: %s"), *GetActorNameOrLabel());
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);

	bHighlighted = false;
}

void AAuraEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}
