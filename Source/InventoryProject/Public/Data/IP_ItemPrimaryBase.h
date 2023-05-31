// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "IP_ItemPrimaryBase.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYPROJECT_API UIP_ItemPrimaryBase : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditDefaultsOnly, Category = ItemType, meta=(DisplayPriority="0"))
	FPrimaryAssetType ItemPrimary = FPrimaryAssetType(TEXT("Select Item Type"));
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* Icon;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText ItemName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Description;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 MaxStack;
	
};
