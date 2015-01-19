/*
 * zTTLV_Buffer.h
 *
 *  Created on: Jan 4, 2015
 *      Author: sherpa
 */

#ifndef ZTTLV_BUFFER_H_
#define ZTTLV_BUFFER_H_

#include <stddef.h>
#include "zTTLV.h"

typedef struct zTTLV_Buffer
{
	uint8_t  last_Position ;
	size_t   total_Length ;
	uint8_t * pzTTLV_Buffer ;
} zTTLV_Buffer_t ;

int zTTLV_Initialize( zTTLV_Buffer_t * pzTTLV_Buffer, size_t AzTLV_Buffer_Size ) ;

int zTTLV_Put( zTTLV_Buffer_t * pzTTLV_Buffer, zTTLV_Item_t AzTTLV_Item ) ;

zTTLV_Item_t zTTLV_Get( zTTLV_Buffer_t AzTTLV_Buffer, zTTLV_Tag_t zTTLV_Tag ) ;

void zTTLV_Item_Print( zTTLV_Item_t * AzTTLV_Item ) ;

#endif /* ZTTLV_BUFFER_H_ */
