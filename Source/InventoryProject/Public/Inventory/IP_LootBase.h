// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IP_InventoryComponent.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"
#include "IP_LootBase.generated.h"

UCLASS()
class INVENTORYPROJECT_API AIP_LootBase : public AActor
{
	GENERATED_BODY()

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
public:	
	// Sets default values for this actor's properties
	AIP_LootBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, meta=(ExposeOnSpawn))
	FItemData ItemData;
	
};
