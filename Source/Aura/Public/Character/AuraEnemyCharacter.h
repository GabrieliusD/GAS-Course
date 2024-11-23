// Gabkis Games

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "EnemyInterface.h"
#include "AuraEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemyCharacter : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
	
public:
	AAuraEnemyCharacter();
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	
	
	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted;
protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
};
