﻿#include "Item/FItemStructure.h"

FItemStructure::FItemStructure()
{
	ID = FGuid::NewGuid();
	Icon = nullptr;
	Name = FText::FromString("None");
	Description = FText::FromString("None");
	ItemType = EItemType::Undefined;
	Quality = EItemQuality::Undefined;
	Amount = 0;
	PriceValue = 0;
	IsStackable = false;
	MaxStackSize = 0;
	Class = nullptr;
	IsDroppable = false;
	WorldMesh = nullptr;
	Health = 0;
	Duration = 0.f;
}