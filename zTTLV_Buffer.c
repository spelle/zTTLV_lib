/*
 * zTLV_Buffer.c
 *
 *  Created on: Jan 4, 2015
 *      Author: sherpa
 */

#include "zTTLV_Buffer.h"
#include <string.h>


int zTTLV_Initialize( zTTLV_Buffer_t AzTLV_Buffer, size_t AzTLV_Buffer_Size )
{
	memset(AzTLV_Buffer, 0, AzTLV_Buffer_Size ) ;

	return 0 ;
}

int zTTLV_Put( zTTLV_Buffer_t AzTLV_Buffer, zTTLV_Item_t AzTLV_Item )
{

	return 0 ;
}

zTTLV_Item_t zTTLV_Get( zTTLV_Buffer_t AzTTLV_Buffer, zTTLV_Tag_t zTTLV_Tag )
{
	zTTLV_Item_t AzTTLV_Item ;

	AzTTLV_Item.zType = 0 ;

	return AzTTLV_Item ;
}

