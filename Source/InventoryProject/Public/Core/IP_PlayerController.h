// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Inventory/IP_InventoryComponent.h"
#include "IP_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYPROJECT_API AIP_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	AIP_PlayerController();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UIP_InventoryComponent* InventoryComponent;

	//Inventory Subsystem
	UFUNCTION(BlueprintCallable, BlueprintPure, meta=(CompactNodeTitle = "Inventory"))
	UIP_InventoryComponent* GetInventoryComponent() const;

	UFUNCTION(BlueprintImplementableEvent)
	void DropItemEvent(FItemData ItemData);
};
