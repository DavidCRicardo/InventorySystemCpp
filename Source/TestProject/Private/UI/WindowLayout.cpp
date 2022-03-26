﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WindowLayout.h"

#include "DragItem.h"
#include "DragWidget.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UWindowLayout::NativeConstruct()
{
	Super::NativeConstruct();

	QuitButton->OnClicked.AddUniqueDynamic(this, &UWindowLayout::OnButtonQuitClicked);

	SetTitleToWindow();

	TopBorder->OnMouseButtonDownEvent.BindUFunction(this,"MyFunction");
}

void UWindowLayout::MyFunction(FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	//UE_LOG (LogTemp, Warning, TEXT ("Border1 - Mouse Button Down Event!"))
}

void UWindowLayout::SetTitleToWindow(FString Title)
{
	WindowTitle->SetText(FText::FromString(Title));
}

FEventReply UWindowLayout::RedirectMouseDownToWidget(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply reply;
	reply.NativeReply = NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	return reply;
}

FReply UWindowLayout::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	return Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);
	return RedirectMouseDownToWidget(InGeometry, InMouseEvent).NativeReply;
}

void UWindowLayout::ToggleWindow()
{
	if (GetVisibility() == ESlateVisibility::Hidden)
	{
		SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
}
/*Testing Description 2*/
void UWindowLayout::RefreshWindow()
{
}

void UWindowLayout::InitializeSlots()
{
}

void UWindowLayout::CreateChildWidgets()
{
}

void UWindowLayout::SetIndexToChilds(uint8& IndexStart)
{
}

void UWindowLayout::OnButtonQuitClicked()
{
}

FReply UWindowLayout::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	
	/*FEventReply ReplyResult =
		UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
	return ReplyResult.NativeReply;*/

	return CustomDetectDrag(InMouseEvent, this, EKeys::LeftMouseButton);
}

void UWindowLayout::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	UDragWidget* DragDropOperation = NewObject<UDragWidget>();
	SetVisibility(ESlateVisibility::HitTestInvisible);
	
	DragDropOperation->WidgetReference = this;
	DragDropOperation->DragOffset = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());

	DragDropOperation->DefaultDragVisual = this;
	DragDropOperation->Pivot = EDragPivot::MouseDown;
	
	OutOperation = DragDropOperation;
}

void UWindowLayout::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	if (UDragWidget* DragWidgetResult = Cast<UDragWidget>(InOperation) )
	{
		if (DragWidgetResult->WidgetReference->GetName() == GetName())
		{
			RemoveFromParent();
		}
	}
}

bool UWindowLayout::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	bool Success = false;

	/*
	UDragItem* DragItemResult = Cast<UDragItem>(InOperation);
	if (IsValid(DragItemResult))
	{
		if (GetVisibility() == ESlateVisibility::Visible)
		{
			Success = true;
		}
	}
	*/
	return Success;
}

void UWindowLayout::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	Super::NativeOnDragEnter(InGeometry, InDragDropEvent, InOperation);

	if (UDragWidget* DragWidgetResult = Cast<UDragWidget>(InOperation))
	{
		if (DragWidgetResult->WidgetReference->GetName() != GetName())
		{
			SetVisibility(ESlateVisibility::HitTestInvisible);
		}
	}
}

FReply UWindowLayout::CustomDetectDrag(const FPointerEvent& InMouseEvent, UWidget* WidgetDetectingDrag, FKey DragKey)
{
	if ( InMouseEvent.GetEffectingButton() == DragKey /*|| PointerEvent.IsTouchEvent()*/ && TopBorder->IsHovered())
	{
		FEventReply Reply;
		Reply.NativeReply = FReply::Handled();
		
		if ( WidgetDetectingDrag )
		{
			TSharedPtr<SWidget> SlateWidgetDetectingDrag = WidgetDetectingDrag->GetCachedWidget();
			if ( SlateWidgetDetectingDrag.IsValid() )
			{
				Reply.NativeReply = Reply.NativeReply.DetectDrag(SlateWidgetDetectingDrag.ToSharedRef(), DragKey);
				return Reply.NativeReply;
			}
		}
	}

	return FReply::Unhandled();
}
