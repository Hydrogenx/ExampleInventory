// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/IP_ItemPrimaryBase.h"
#include "Net/UnrealNetwork.h"
#include "IP_InventoryComponent.generated.h"

class AIP_LootBase;
class AIP_PlayerController;

//Single Item Data Structure
USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UIP_ItemPrimaryBase* Item = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Stack = 0;

	UPROPERTY(BlueprintReadOnly)
	FGuid UniqueID;
};

//Item Array Data Structure
USTRUCT(BlueprintType)
struct FInventoryData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FItemData> Items;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInventoryUpdated);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVENTORYPROJECT_API UIP_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UIP_InventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	//Inventory Data. All items are here.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, ReplicatedUsing = OnRep_InventoryData)
	FInventoryData InventoryData;
	
	//Slot Count
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TotalSlotCount = 24;
	
	//Inventory Updated Dispatcher.
	UPROPERTY(BlueprintAssignable)
	FInventoryUpdated OnInventoryUpdated;

	//Inventory Data Repnotify
	UFUNCTION()
	void OnRep_InventoryData() const;

	//Example Set New Size of Inventory if needed. Works always on Server
	UFUNCTION(BlueprintCallable, Server, Reliable)
	void SetInventorySize(int32 NewSize);

	//SwapRequest
	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "Inventory")
	void MoveItem(const int32 From, const int32 To, const bool IsShiftDown);

	//Drop From Inventory
	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "Inventory")
	void DropItem(const int32 SlotIndex = -1, const bool DropHalfStack = false);

	//Loot Item 
	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "Inventory")
	void LootItem(AIP_LootBase* LootRef);
	
	void SwapSlotsCheck(int32 From, int32 To);
	void SwapSlots (int32 From, int32 To);
	bool CanSlotTakeMoreStack(int32 SlotIndex);
	void ClearSlot (int32 IndexToRemove);
	int32 FindEmptySlot();
	AIP_PlayerController* GetOwningPlayerController();
	

	
};
