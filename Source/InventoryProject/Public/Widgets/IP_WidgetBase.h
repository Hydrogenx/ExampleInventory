// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Core/IP_PlayerController.h"
#include "Inventory/IP_InventoryComponent.h"
#include "IP_WidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYPROJECT_API UIP_WidgetBase : public UUserWidget
{
	GENERATED_BODY()

protected:
	
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
public:
	
	//Returns Owner Player Controller
	UFUNCTION(BlueprintCallable, BlueprintPure, meta=(CompactNodeTitle="OwningController"))
	AIP_PlayerController* GetOwningPlayerController() const;

	//Returns Inventory Component only on clients. 
	UFUNCTION(BlueprintCallable, BlueprintPure, meta=(CompactNodeTitle="Inventory"))
	UIP_InventoryComponent* GetInventory() const;

	UFUNCTION(BlueprintImplementableEvent)
	void InventoryUpdated();
	
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn))
	FItemData ItemData;*/
	
	
	
};
