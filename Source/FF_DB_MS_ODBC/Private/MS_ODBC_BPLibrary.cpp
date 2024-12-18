// Copyright Epic Games, Inc. All Rights Reserved.

#include "MS_ODBC_BPLibrary.h"
#include "FF_DB_MS_ODBC.h"

UMS_ODBC_BPLibrary::UMS_ODBC_BPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

FString UMS_ODBC_BPLibrary::MS_Insert_Into(FString TargetDb, TMap<FString, FString> KeyValue)
{
	TArray<FString> Array_Keys;
	KeyValue.GenerateKeyArray(Array_Keys);

	TArray<FString> Array_Values;
	KeyValue.GenerateValueArray(Array_Values);

	const FString PlaceHoldersString = " (" + UKismetStringLibrary::JoinStringArray(Array_Keys, ", ") + ") ";
	const FString ValuesString = " (" + UKismetStringLibrary::JoinStringArray(Array_Values, ", ") + ") ";
	const FString MainQuery = "INSERT INTO " + TargetDb + PlaceHoldersString + "VALUES" + ValuesString;

	return MainQuery;
}

FString UMS_ODBC_BPLibrary::MS_Select_From(FString TargetDb, FString Condition, TSet<FString> PlaceHolders)
{
	TArray<FString> Array_PlaceHolders = PlaceHolders.Array();
	const FString PlaceHolderString = UKismetStringLibrary::JoinStringArray(Array_PlaceHolders, ", ");

	FString MainQuery = "SELECT " + PlaceHolderString + " FROM " + TargetDb;
	if (!Condition.IsEmpty())
	{
		MainQuery += " WHERE " + Condition;
	}

	return MainQuery;
}