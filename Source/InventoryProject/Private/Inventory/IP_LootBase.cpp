// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/IP_LootBase.h"

void AIP_LootBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AIP_LootBase, ItemData)
}

// Sets default values
AIP_LootBase::AIP_LootBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AIP_LootBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIP_LootBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

