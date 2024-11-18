// Gabkis Games


#include "AuraEffectActor.h"
#include "Components/SphereComponent.h"
#include "Components/PrimitiveComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include <AbilitySystem\AuraAttributeSet.h>

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");

	Sphere->SetupAttachment(Mesh);
}

void AAuraEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	TScriptInterface<IAbilitySystemInterface> Asi = OtherActor;
	if (Asi)
	{
		const auto AuraAttributeSet = Cast<UAuraAttributeSet>(Asi->GetAbilitySystemComponent()->GetAttributeSet(UAuraAttributeSet::StaticClass()));
		auto NonConst = const_cast<UAuraAttributeSet*>(AuraAttributeSet);
		NonConst->SetHealth(AuraAttributeSet->GetHealth() + 25.0f);
		Destroy();
	}
}

void AAuraEffectActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AAuraEffectActor::OnEndOverlap);
}