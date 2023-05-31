// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/IP_PlayerController.h"

AIP_PlayerController::AIP_PlayerController()
{
	InventoryComponent = CreateDefaultSubobject<UIP_InventoryComponent>(TEXT("Inventory"));
	bEnableClickEvents = 1;
}

UIP_InventoryComponent* AIP_PlayerController::GetInventoryComponent() const
{
	return InventoryComponent;
}
