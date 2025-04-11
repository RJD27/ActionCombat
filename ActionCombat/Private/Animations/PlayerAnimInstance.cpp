// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/PlayerAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"

void UPlayerAnimInstance::UpdateSpeed()
{
	APawn* PawnRef{ TryGetPawnOwner() };

	if (!IsValid(PawnRef)) { return; }
	 
	FVector Velocity{ PawnRef->GetVelocity() };

	CurrentSpeed = static_cast<float>(Velocity.Length());
}

void UPlayerAnimInstance::HandleUpdatedTarget(AActor* NewTargetActorRef)
{
	bIsInCombat = IsValid(NewTargetActorRef);
}

void UPlayerAnimInstance::UpdateDirection()
{
	APawn* PawnRef{ TryGetPawnOwner() };

	if (!IsValid(PawnRef)) { return; }

	if (!bIsInCombat) { return; }

	const FVector Velocity = PawnRef->GetVelocity();
	const FRotator ActorRotation = PawnRef->GetActorRotation();

	if (!Velocity.IsNearlyZero())
	{
		const FVector ForwardVector = ActorRotation.Vector();
		const FVector RightVector = FRotationMatrix(ActorRotation).GetScaledAxis(EAxis::Y);

		// Calculate movement direction in degrees
		CurrentDirection = FMath::RadiansToDegrees(FMath::Atan2(
			FVector::DotProduct(Velocity, RightVector),
			FVector::DotProduct(Velocity, ForwardVector)
		));
	}
	else
	{
		CurrentDirection = 0.0f;
	}
}
