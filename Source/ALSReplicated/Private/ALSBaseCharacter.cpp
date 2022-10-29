// Fill out your copyright notice in the Description page of Project Settings.


#include "ALSBaseCharacter.h"

// Sets default values
AALSBaseCharacter::AALSBaseCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UALSCharacterMovementComponent>(CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AALSBaseCharacter::BeginPlay()
{
	if(GetLocalRole() == ROLE_SimulatedProxy)
	{
		GetMesh()->GetAnimInstance()->SetRootMotionMode(ERootMotionMode::IgnoreRootMotion);
	}

	SetReplicateMovement(true);

	if (HasAuthority())
	{
		SetReplicates(true);
	}
	
	Super::BeginPlay();
}

// Called every frame
void AALSBaseCharacter::Tick(float DeltaTime)
{
	if(GetLocalRole() != ROLE_SimulatedProxy)
	{
		ControlRotation = FMath::RInterpTo(ControlRotation,  Controller ? Controller->GetControlRotation() : FRotator::ZeroRotator, DeltaTime, 30.0f);
	}
	
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AALSBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AALSBaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION(AALSBaseCharacter, ControlRotation, COND_SkipOwner);
}

FRotator AALSBaseCharacter::GetControlRotation() const
{
	return ControlRotation;
}

