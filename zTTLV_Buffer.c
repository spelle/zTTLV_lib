/*
 * zTLV_Buffer.c
 *
 *  Created on: Jan 4, 2015
 *      Author: sherpa
 */

#include <stdio.h>
#include <string.h>

#include "zTTLV_Buffer.h"

int zTTLV_Initialize( zTTLV_Buffer_t * pzTTLV_Buffer, size_t AzTTLV_Buffer_Size )
{
	pzTTLV_Buffer->last_Position = 0 ;
	pzTTLV_Buffer->total_Length = AzTTLV_Buffer_Size ;

	memset(pzTTLV_Buffer->pzTTLV_Buffer, 0, pzTTLV_Buffer->total_Length ) ;

	return 0 ;
}

// Put and serialize in a zTTLV_Buffer
int zTTLV_Put( zTTLV_Buffer_t * pzTTLV_Buffer, zTTLV_Item_t AzTTLV_Item )
{
	zTTLV_Value_t pValue = {NULL} ;

	// Set the Tag value
	pzTTLV_Buffer->pzTTLV_Buffer[pzTTLV_Buffer->last_Position] = AzTTLV_Item.zTag ;
	pzTTLV_Buffer->last_Position += sizeof(AzTTLV_Item.zTag) ;

	// Set the Type value
	pzTTLV_Buffer->pzTTLV_Buffer[pzTTLV_Buffer->last_Position] = AzTTLV_Item.zType ;
	pzTTLV_Buffer->last_Position ++ ; // Type should fits in a byte

	// Set the Length
	pzTTLV_Buffer->pzTTLV_Buffer[pzTTLV_Buffer->last_Position] = AzTTLV_Item.zLength ;
	pzTTLV_Buffer->last_Position += sizeof(AzTTLV_Item.zLength) ;

	// Initialize the pValue pointer to destination
	pValue.pVoid = (void *) & pzTTLV_Buffer->pzTTLV_Buffer[pzTTLV_Buffer->last_Position] ;

	// Depending on type, sets the destination value
	switch( AzTTLV_Item.zType )
	{
		case CHAR :
			(*pValue.pChar) = (char) *AzTTLV_Item.zValue.pChar ;
			pzTTLV_Buffer->last_Position += sizeof(char) ;
			break ;
		case UINT8 :
			(*pValue.pUInt8) = (uint8_t) *AzTTLV_Item.zValue.pUInt8 ;
			pzTTLV_Buffer->last_Position += sizeof(uint8_t) ;
			break ;
		case INT8 :
			(*pValue.pInt8) = (int8_t) *AzTTLV_Item.zValue.pInt8 ;
			pzTTLV_Buffer->last_Position += sizeof(int8_t) ;
			break ;
		case UINT16 :
			(*pValue.pUInt16) = (uint16_t) *AzTTLV_Item.zValue.pUInt16 ;
			pzTTLV_Buffer->last_Position += sizeof(uint16_t) ;
			break ;
		case INT16 :
			(*pValue.pInt16) = (int16_t) *AzTTLV_Item.zValue.pInt16 ;
			pzTTLV_Buffer->last_Position += sizeof(int16_t) ;
			break ;
		case ZTTLV_BUFFER :
			// For a zTTLV_Buffer, the totality of the buffer is copied.
			memcpy( pValue.pzTTLV_Buffer, AzTTLV_Item.zValue.pzTTLV_Buffer->pzTTLV_Buffer, AzTTLV_Item.zLength ) ;
			pzTTLV_Buffer->last_Position += AzTTLV_Item.zValue.pzTTLV_Buffer->last_Position ;
			break ;
		default :
			break ;
	}

	return 0 ;
}

// Get from a zTTLV_Buffer
zTTLV_Item_t zTTLV_Get( zTTLV_Buffer_t AzTTLV_Buffer, zTTLV_Tag_t zTTLV_Tag )
{

	zTTLV_Item_t AzTTLV_Item ;

	uint8_t ui8Index = 0 ;

	do
	{
		// Get the Tag
		AzTTLV_Item.zTag  = AzTTLV_Buffer.pzTTLV_Buffer[ui8Index] ;
		ui8Index++ ;

		// Get the Type
		AzTTLV_Item.zType = AzTTLV_Buffer.pzTTLV_Buffer[ui8Index] ;
		ui8Index++ ;

		// Get the Length
		AzTTLV_Item.zLength = AzTTLV_Buffer.pzTTLV_Buffer[ui8Index] ;
		ui8Index++ ;

		// Get the Value
		if( AzTTLV_Item.zTag == zTTLV_Tag )
		{
			AzTTLV_Item.zValue.pVoid = (void *) & AzTTLV_Buffer.pzTTLV_Buffer[ui8Index] ;
			break ;
		}

		ui8Index += AzTTLV_Item.zLength ;
	}
	while( END != AzTTLV_Item.zType ) ;

	// Try to update the last_Position.
	if( END == AzTTLV_Item.zType )
	{
		AzTTLV_Buffer.last_Position = ui8Index ;
	}

	return AzTTLV_Item ;
}

// Print a zTTLV_Item
void zTTLV_Item_Print( zTTLV_Item_t * pzTTLV_Item )
{
	fprintf( stdout, "zTTLV_Item.zTag=%d\n", pzTTLV_Item->zTag ) ;
	fprintf( stdout, "zTTLV_Item.zType=%d\n", pzTTLV_Item->zType ) ;
	fprintf( stdout, "zTTLV_Item.zLength=%d\n", pzTTLV_Item->zLength ) ;

	// Depending on type, sets the destination value
	switch( pzTTLV_Item->zType )
	{
		case CHAR :
			fprintf( stdout, "zTTLV_Item.zValue=%c\n", *pzTTLV_Item->zValue.pChar ) ;
			break ;
		case UINT8 :
			fprintf( stdout, "zTTLV_Item.zValue=%hhu\n", *pzTTLV_Item->zValue.pUInt8 ) ;
			break ;
		case INT8 :
			fprintf( stdout, "zTTLV_Item.zValue=%hhi\n", *pzTTLV_Item->zValue.pInt8 ) ;
			break ;
		case UINT16 :
			fprintf( stdout, "zTTLV_Item.zValue=%hu\n", *pzTTLV_Item->zValue.pUInt16 ) ;
			break ;
		case INT16 :
			fprintf( stdout, "zTTLV_Item.zValue=%hi\n", *pzTTLV_Item->zValue.pInt16 ) ;
			break ;
		case ZTTLV_BUFFER :
			fprintf( stdout, "zTTLV_Item.zValue=%p\n", pzTTLV_Item->zValue.pVoid ) ;
			break ;
		default :
			break ;
	}
}
