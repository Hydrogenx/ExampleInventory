// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/IP_WidgetBase.h"


void UIP_WidgetBase::NativeConstruct()
{
	Super::NativeConstruct();
	//Assign Inventory Updated when this widget created
	GetInventory()->OnInventoryUpdated.AddDynamic(this, &UIP_WidgetBase::UIP_WidgetBase::InventoryUpdated);
	InventoryUpdated();
}

void UIP_WidgetBase::NativeDestruct()
{
	Super::NativeDestruct();
	//Clear Assign when this widget removed
	GetInventory()->OnInventoryUpdated.RemoveDynamic(this, &UIP_WidgetBase::UIP_WidgetBase::InventoryUpdated);
}

AIP_PlayerController* UIP_WidgetBase::GetOwningPlayerController() const
{
	const auto PlayerController = Cast<AIP_PlayerController>(GetOwningPlayer());
	return PlayerController;
}

UIP_InventoryComponent* UIP_WidgetBase::GetInventory() const
{	
	const auto PlayerController = GetOwningPlayerController();
	if (!PlayerController)
	{
		return nullptr;
	}
	return PlayerController->GetInventoryComponent();
}

