/*
 * zTLV_Buffer.c
 *
 *  Created on: Jan 4, 2015
 *      Author: sherpa
 */

#include "zTTLV_Buffer.h"
#include <string.h>

int zTTLV_Initialize( zTTLV_Buffer_t * pzTTLV_Buffer, size_t AzTTLV_Buffer_Size )
{
	pzTTLV_Buffer->current_Position = 0 ;
	pzTTLV_Buffer->total_Length = AzTTLV_Buffer_Size ;

	memset(pzTTLV_Buffer->pzTTLV_Buffer, 0, pzTTLV_Buffer->total_Length ) ;

	return 0 ;
}

int zTTLV_Put( zTTLV_Buffer_t * pzTTLV_Buffer, zTTLV_Item_t AzTTLV_Item )
{
	uint8_t ui8 = 0 ;
	zTTLV_Value_t pValue = {NULL} ;

	// Set the Tag value
	pzTTLV_Buffer->pzTTLV_Buffer[pzTTLV_Buffer->current_Position] = AzTTLV_Item.zTag ;
	pzTTLV_Buffer->current_Position += sizeof(AzTTLV_Item.zTag) ;

	// Set the Type value
	pzTTLV_Buffer->pzTTLV_Buffer[pzTTLV_Buffer->current_Position] = AzTTLV_Item.zType ;
	pzTTLV_Buffer->current_Position ++ ; // Type should fits in a byte

	// Set the Length
	pzTTLV_Buffer->pzTTLV_Buffer[pzTTLV_Buffer->current_Position] = AzTTLV_Item.zLength ;
	pzTTLV_Buffer->current_Position += sizeof(AzTTLV_Item.zLength) ;

	pValue.pChar = (char *) & pzTTLV_Buffer->pzTTLV_Buffer[pzTTLV_Buffer->current_Position] ;

	switch( AzTTLV_Item.zType )
	{
		case CHAR :
			(*pValue.pChar) = (char) *AzTTLV_Item.zValue.pChar ;
			pzTTLV_Buffer->current_Position += sizeof(char) ;
			break ;
		case UINT8 :
			(*pValue.pUInt8) = (uint8_t) *AzTTLV_Item.zValue.pUInt8 ;
			pzTTLV_Buffer->current_Position += sizeof(uint8_t) ;
			break ;
		case INT8 :
			(*pValue.pInt8) = (int8_t) *AzTTLV_Item.zValue.pInt8 ;
			pzTTLV_Buffer->current_Position += sizeof(int8_t) ;
			break ;
		case UINT16 :
			(*pValue.pUInt16) = (uint16_t) *AzTTLV_Item.zValue.pUInt16 ;
			pzTTLV_Buffer->current_Position += sizeof(uint16_t) ;
			break ;
		case INT16 :
			(*pValue.pInt16) = (int16_t) *AzTTLV_Item.zValue.pInt16 ;
			pzTTLV_Buffer->current_Position += sizeof(int16_t) ;
			break ;
		case ZTTLV_BUFFER :
			// (*pValue.pzTTLV_Buffer) = (zTTLV_Buffer_t) *AzTTLV_Item.zValue.pzTTLV_Buffer ;
			memcpy( pValue.pzTTLV_Buffer, AzTTLV_Item.zValue.pzTTLV_Buffer->pzTTLV_Buffer, AzTTLV_Item.zLength ) ;
//			for( ui8 = 0 ; ui8 < AzTTLV_Item.zLength ; ui8 ++ )
//			{
//				pValue.pzTTLV_Buffer[ui8] = AzTTLV_Item.zValue.pzTTLV_Buffer->pzTTLV_Buffer[ui8] ;
//			}

			pzTTLV_Buffer->current_Position += AzTTLV_Item.zLength ;
			break ;
		default :
			break ;
	}


	return 0 ;
}

zTTLV_Item_t zTTLV_Get( zTTLV_Buffer_t AzTTLV_Buffer, zTTLV_Tag_t zTTLV_Tag )
{
	zTTLV_Item_t AzTTLV_Item ;

	AzTTLV_Item.zType = 0 ;

	return AzTTLV_Item ;
}

