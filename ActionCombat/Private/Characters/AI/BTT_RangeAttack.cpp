// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AI/BTT_RangeAttack.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/EEnemyState.h"
#include "Interfaces/Fighter.h"

EBTNodeResult::Type UBTT_RangeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACharacter* CharacterRef{
		OwnerComp.GetAIOwner()->GetPawn<ACharacter>()
	};
	
	if (!IsValid(CharacterRef)){ return EBTNodeResult::Failed; } 

	float Distance { // Gets player distance
		OwnerComp.GetBlackboardComponent()
			->GetValueAsFloat(TEXT("Distance"))
	};

	IFighter* FighterRef{
		Cast<IFighter>( CharacterRef )
	};
	
	if (FighterRef->GetMeleeRange() > Distance)
	{
		OwnerComp.GetBlackboardComponent()
			->SetValueAsEnum(TEXT("CurrentState"), EEnemyState::Melee);

		AbortTask(OwnerComp, NodeMemory); // Cleans memory allocated to task
		return EBTNodeResult::Aborted;
	}
	
	CharacterRef->PlayAnimMontage(AnimMontage);

	double RandomValue{ UKismetMathLibrary::RandomFloat() }; // Float is actually a double

	if (RandomValue > Threshold)
	{
		Threshold = 0.9;

		OwnerComp.GetBlackboardComponent()
			->SetValueAsEnum(
				TEXT("CurrentState"),
				EEnemyState::Charge
			);
	}
	else
	{
		Threshold -= 0.1;
	}
	
	return EBTNodeResult::Succeeded;
};
