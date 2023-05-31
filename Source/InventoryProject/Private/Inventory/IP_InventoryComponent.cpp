// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/IP_InventoryComponent.h"
#include "Core/IP_PlayerController.h"
#include "Inventory/IP_LootBase.h"

// Sets default values for this component's properties
UIP_InventoryComponent::UIP_InventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	//Sets this component replicated true
	SetIsReplicatedByDefault(true);
}

void UIP_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	//Only Server can edit the inventory
	if (GetOwnerRole() == ROLE_Authority)
	{
		//Set Inventory Size here.
		InventoryData.Items.SetNum(TotalSlotCount);
	}
}

void UIP_InventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	//Tick Disabled
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

//Replicated Props
void UIP_InventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION(UIP_InventoryComponent, InventoryData, COND_OwnerOnly);
}

//Inventory Updated Dispatcher Broadcast
void UIP_InventoryComponent::OnRep_InventoryData() const
{
	OnInventoryUpdated.Broadcast();	
}


void UIP_InventoryComponent::DropItem_Implementation(const int32 SlotIndex, const bool DropHalfStack)
{
	//Function works only item is valid
	if (!InventoryData.Items[SlotIndex].Item)
	{
		return;
	}
	
	const int32 DropToStack = DropHalfStack ? InventoryData.Items[SlotIndex].Stack / 2 : InventoryData.Items[SlotIndex].Stack;
	FItemData ItemToDrop = InventoryData.Items[SlotIndex];
	ItemToDrop.Stack = DropToStack;
	InventoryData.Items[SlotIndex].Stack -= DropToStack;
	GetOwningPlayerController()->DropItemEvent(ItemToDrop);

	UE_LOG(LogTemp, Warning, TEXT("Drop Half %i"), DropToStack);
	if (InventoryData.Items[SlotIndex].Stack < 1)
	{
		ClearSlot(SlotIndex);
	}
}

void UIP_InventoryComponent::SwapSlotsCheck(const int32 From, const int32 To)
{
	//Target slot and source slot is not equal
	if (InventoryData.Items[From].Item != InventoryData.Items[To].Item)
	{
		//Sawp directly
		SwapSlots(From,To);
	}

	else
	{
		//Check Here Can Slots Take more stack
		if (CanSlotTakeMoreStack(From) && CanSlotTakeMoreStack(To))
			{
				if (InventoryData.Items[From].Stack <= (InventoryData.Items[To].Item->MaxStack - InventoryData.Items[To].Stack))
				{
					//Target slot can take all source stack. Take them all and remove source slot 
					InventoryData.Items[To].Stack += InventoryData.Items[From].Stack;
					ClearSlot(From);
				}
				else
				{
					//Target slot can't take all stacks. Slots will be shared.
					InventoryData.Items[From].Stack -= (InventoryData.Items[To].Item->MaxStack - InventoryData.Items[To].Stack); // ToTakeStackCount;
					InventoryData.Items[To].Stack = InventoryData.Items[From].Item->MaxStack;			
				}
			}

		else
		{
			//Both two slots can't take more slot and it will be swapped.
			SwapSlots(From,To);
		}
	}
	
}

void UIP_InventoryComponent::SwapSlots(const int32 From, const int32 To)
{
	InventoryData.Items.Swap(From, To);
}

bool UIP_InventoryComponent::CanSlotTakeMoreStack(const int32 SlotIndex)
{
	return IsValid(InventoryData.Items[SlotIndex].Item) && InventoryData.Items[SlotIndex].Stack < InventoryData.Items[SlotIndex].Item->MaxStack;
}

void UIP_InventoryComponent::ClearSlot(const int32 IndexToRemove)
{
	InventoryData.Items[IndexToRemove] = FItemData();
}

int32 UIP_InventoryComponent::FindEmptySlot()
{
	int32 LoopIndex = -1;
	for (const FItemData LoopBody: InventoryData.Items)
	{
		LoopIndex++;
		if (!LoopBody.Item)
		{
			return LoopIndex;
		}
		
	}
	GEngine->AddOnScreenDebugMessage(-1 ,2.f, FColor::Yellow, FString::Printf(TEXT("Inventory is Full")));
	//UE_LOG(LogTemp, Warning, TEXT("There Is No Empty Slot %i"), LoopIndex);
	
	return -1;
}

AIP_PlayerController* UIP_InventoryComponent::GetOwningPlayerController()
{
	return Cast<AIP_PlayerController>(GetOwner());
}

//Example Set New Size of Inventory if needed
void UIP_InventoryComponent::SetInventorySize_Implementation(const int32 NewSize)
{
	InventoryData.Items.SetNum(NewSize);
}

void UIP_InventoryComponent::MoveItem_Implementation(const int32 From, const int32 To, const bool IsShiftDown)
{
	//Pass only requested slot data is valid
	if (!InventoryData.Items[From].Item)
	{
		//GEngine->AddOnScreenDebugMessage(-1 ,2.f, FColor::Yellow, FString::Printf(TEXT("Swap")));
		return;
	}
	//If Target slot is not valid(empty) and shift pressed, split half to new slot.
	if (!IsValid(InventoryData.Items[To].Item) && IsShiftDown)
	{
		if(IsValid(InventoryData.Items[From].Item) && InventoryData.Items[From].Stack > 1)
		{
			const int32 Half = InventoryData.Items[From].Stack / 2;
			InventoryData.Items[To] = InventoryData.Items[From];
			InventoryData.Items[To].Stack = Half;
			InventoryData.Items[From].Stack -= Half;
			
		}
		else
		{
			SwapSlotsCheck(From, To);
		}
		//Done
	}
	else
	{
		//Swap Check
		SwapSlotsCheck(From, To);
		//Done
	}
}

void UIP_InventoryComponent::LootItem_Implementation(AIP_LootBase* LootRef)
{
	if (!LootRef)
	{
		return;
	}

	if (const int32 EmptySlot = FindEmptySlot(); EmptySlot > -1)
	{
		InventoryData.Items[EmptySlot] = LootRef->ItemData;
		LootRef->Destroy();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1 ,2.f, FColor::Yellow, FString::Printf(TEXT("There Is No Empty Slot")));
	}
}