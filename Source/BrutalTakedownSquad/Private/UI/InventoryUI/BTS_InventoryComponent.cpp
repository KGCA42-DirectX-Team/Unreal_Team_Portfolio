// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/InventoryUI/BTS_InventoryComponent.h"
#include "UI/InventoryUI/Tile.h"
#include "Kismet/KismetArrayLibrary.h"
#include"UI\ItemUI\BTS_ItemObject.h"

UBTS_InventoryComponent::UBTS_InventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

TMap<UBTS_ItemObject*, FTile> UBTS_InventoryComponent::GetAllItems()
{
	TMap<UBTS_ItemObject*, FTile> AllItems;

	int32 index = 0;
	for (auto& LocalItem : Items)
	{
		if (LocalItem)
		{
			if (!AllItems.Contains(LocalItem))
				AllItems.Add(LocalItem, IndexToTile(index));
		}
		++index;
	}
	return AllItems;
}

FTile UBTS_InventoryComponent::IndexToTile(int32 Index) const
{
	FTile Tile;

	Tile.X = Index % Colums;
	Tile.Y = Index / Colums;

	return Tile;
}

int32 UBTS_InventoryComponent::TileToIndex(FTile Tile) const
{
	int32 Index = Tile.Y * Colums + Tile.X;
	return Index;
}

void UBTS_InventoryComponent::RemoveItem(UBTS_ItemObject* ItemObject)
{
	int32 index = 0;

	if (ItemObject)
	{
		for (auto& item : Items)
		{
			if (item == ItemObject)
			{
				if (index >= Items.Num())
				{
					Items.SetNum(index + 1);
				}
				Items[index] = nullptr;

				IsDirty = true;
			}
			++index;
		}
	}

	FName ItemID = ItemObject->GetItemID();
	if (StoredItemCounts.Contains(ItemID))
	{
		if (StoredItemCounts[ItemID] > 0)
		{
			StoredItemCounts[ItemID] = StoredItemCounts[ItemID] - 1;
		}
		else {
			StoredItemCounts.Remove(ItemID);
		}
	}

}

/*
bool UBTS_InventoryComponent::IsRoomAvailable(UBTS_ItemObject* ItemObject, int32 TopLeftIndex)
{

	FTile Tile = IndexToTile(TopLeftIndex);
	FIntPoint Demensions = ItemObject->GetDimensions();
	int32 LastIndexX = Demensions.X - 1 + Tile.X;
	int32 LastIndexY = Demensions.Y - 1 + Tile.Y;

	for (int32 i = Tile.X; i <= LastIndexX; ++i)
	{
		for (int32 j = Tile.Y; j <= LastIndexY; ++j)
		{
			if (i >= 0 && j >= 0 && i < Colums && j < Rows)
			{

				FTile TileIndex;
				TileIndex.X = i;
				TileIndex.Y = j;
				FItemIndex Data = GetItemIndex(TileToIndex(TileIndex));
				if (Data.isValid)
				{
					if (IsValid(Data.ItemObject))
					{
						return false;
					}
				}
				else
				{
					return false;
				}

			}
			else
			{
				return false;
			}

		}

	}

	return true;
}
*/

bool UBTS_InventoryComponent::IsRoomAvailable(UBTS_ItemObject* itemObject, int32 desiredStartIndex)
{
	FTile position = IndexToTile(desiredStartIndex);
	FIntPoint dimensions = itemObject->GetDimensions();
	int32 endPositionX = position.X + dimensions.X - 1;
	int32 endPositionY = position.Y + dimensions.Y - 1;

	int32 maxColumns = Colums - 1; 
	int32 maxRows = Rows - 1;   

	for (int32 x = position.X; x <= endPositionX; ++x)
	{
		for (int32 y = position.Y; y <= endPositionY; ++y)
		{
			if (x >= 0 && x <= maxColumns && y >= 0 && y <= maxRows)
			{
				FTile tileIndex = { x, y };
				FItemIndex tileData = GetItemIndex(TileToIndex(tileIndex));

				if (tileData.isValid && IsValid(tileData.ItemObject)) {
					return false; // No space available
				}
			}
			else {
				return false; // Out of bounds
			}
		}
	}

	return true; // Space is available
}


void UBTS_InventoryComponent::AddItemAt(UBTS_ItemObject* ItemObject, int32 TopLeftIndex)
{
	FTile TopLeftTile = IndexToTile(TopLeftIndex);

	FIntPoint temp = ItemObject->GetDimensions();

	int32 LastIndexX = temp.X - 1 + TopLeftTile.X;
	int32 LastIndexY = temp.Y - 1 + TopLeftTile.Y;

	for (int32 i = TopLeftTile.X; i <= LastIndexX; ++i)
	{
		for (int32 j = TopLeftTile.Y; j <= LastIndexY; ++j)
		{
			FTile TileIndex{};
			TileIndex.X = i;
			TileIndex.Y = j;

			if (TileToIndex(TopLeftTile) >= Items.Num())
			{
				Items.SetNum(TileToIndex(TopLeftTile) + 1);
			}

			Items[TileToIndex(TileIndex)] = ItemObject;

		}
	}
	IsDirty = true;

	FName ItemID = ItemObject->GetItemID();
	if (StoredItemCounts.Contains(ItemID))
	{
		StoredItemCounts[ItemID] = StoredItemCounts[ItemID] + 1;
	}
	else
	{
		StoredItemCounts.Emplace(ItemID, 1);
	}
}

bool UBTS_InventoryComponent::TryAddItem(UBTS_ItemObject* ItemObject)
{
	bool isAdded = false;

	int32 itemLength = ItemObject->GetDimensions().X -1;

	for (int32 TopLeftIndex = 0; TopLeftIndex < Colums * Rows; ++TopLeftIndex)
	{
		if((TopLeftIndex + itemLength) % 16 == 0)
		{
			TopLeftIndex += Colums - 16;
		}


		if (IsRoomAvailable(ItemObject, TopLeftIndex))
		{
			AddItemAt(ItemObject, TopLeftIndex);
			isAdded = true;
			break;
		}
	}

	if (!isAdded)
	{
		ItemObject->Rotate();

		for (int32 TopLeftIndex = 0; TopLeftIndex < Colums * Rows; ++TopLeftIndex)
		{

			if ((TopLeftIndex + itemLength) % 16 == 0)
			{
				TopLeftIndex += Colums - 16;
			}

			if (IsRoomAvailable(ItemObject, TopLeftIndex))
			{
				AddItemAt(ItemObject, TopLeftIndex);
				isAdded = true;
				break;
			}
		}
	}

	return isAdded;
}

FItemIndex UBTS_InventoryComponent::GetItemIndex(int32 TopLeftIndex)
{
	FItemIndex index;

	if (Items.IsValidIndex(TopLeftIndex))
	{
		index.isValid = true;
		index.ItemObject = Items[TopLeftIndex];
	}
	else {
		index.isValid = false;
		index.ItemObject = nullptr;
	}

	return index;
}

void UBTS_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	Items.SetNum(Colums * Rows);
}

void UBTS_InventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

