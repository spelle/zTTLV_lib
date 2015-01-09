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

typedef uint8_t * zTTLV_Buffer_t ;

int zTTLV_Initialize( zTTLV_Buffer_t AzTTLV_Buffer, size_t AzTLV_Buffer_Size ) ;

int zTTLV_Put( zTTLV_Buffer_t AzTTLV_Buffer, zTTLV_Item_t AzTTLV_Item ) ;

zTTLV_Item_t zTTLV_Get( zTTLV_Buffer_t AzTTLV_Buffer, zTTLV_Tag_t zTTLV_Tag ) ;

#endif /* ZTTLV_BUFFER_H_ */
