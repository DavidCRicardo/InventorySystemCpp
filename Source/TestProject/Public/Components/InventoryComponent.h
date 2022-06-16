﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory/FSlotStructure.h"
#include "InventoryComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INVENTORYSYSTEMCPP_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventoryComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="NumberOfRows", Category="Inventory UI"))
	uint8 NumberOfRowsInventory = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="RowsPerSlot", Category="Inventory UI"))
	uint8 SlotsPerRowInventory = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="Inventory", Category="Inventory UI"))
	TArray<FSlotStructure> Inventory;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UDataTable* GetItemDB();
	UPROPERTY();
	UDataTable* ItemDB;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(Server, Reliable)
	void Server_InitInventory(const uint8& Size);
	UFUNCTION()
	void InitInventory(const uint8& Size);

	UFUNCTION()
	bool LoadInventoryItems(uint8 Size, TArray<FSlotStructure> Array);

	UFUNCTION()
	void GetInventoryItems(TArray<FSlotStructure>& InventoryItems);

	UFUNCTION()
	void SetInventoryItem(uint8& Index, FSlotStructure& Item);
	UFUNCTION()
	FSlotStructure GetInventorySlot(uint8 Index);

	UFUNCTION()
	void ClearInventorySlot(uint8 Index);
	UFUNCTION()
	void PrintInventory();

	UFUNCTION()
	FSlotStructure GetEmptySlot(EEquipmentSlot FromEquipmentType);
	UFUNCTION()
	FSlotStructure GetItemFromItemDB(FName Name);
};