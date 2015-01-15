/*
 * zTTLV_lib.h
 *
 *  Created on: Jan 3, 2015
 *      Author: Sébastien PELLÉ
 * Description: A Really simple static TTLV (Tag-Type-Length-Value)
 *              cross-portable implementation in C
 */

#ifndef ZTTLV_H_
#define ZTTLV_H_

#include <stdint.h>

#ifndef pzTTLV_NULL
	#define pzTTLV_NULL 0
#endif

// zTTLV_Tag is 8-bit long : up to 255
typedef uint8_t zTTLV_Tag_t ;

/*
 * This enum describes the type
 * It should fit in an 8-bit word for an AVR
 */
typedef enum
{
	CHAR = 0x01 ,
	UINT8 ,
	INT8 ,

	UINT16,
	INT16 ,

	ZTTLV_BUFFER
} zTTLV_Type_t ;

typedef uint8_t zTTLV_Length_t ;

struct zTTLV_Item ;

/*
 * This union links to the value of desired zTLV_Item
 */
typedef union
{
	char          * pChar   ;
	uint8_t       * pUInt8  ;
	int8_t        * pInt8   ;

	uint16_t      * pUInt16 ;
	int16_t       * pInt16 ;

	struct zTTLV_Buffer   * pzTTLV_Buffer   ;
} zTTLV_Value_t ;

/*
 * This structure describes a zTTLV Item
 */
typedef struct zTTLV_Item
{
	zTTLV_Tag_t    zTag ;    // Tags up to 255
	zTTLV_Type_t   zType ;
	zTTLV_Length_t zLength ; // up to 255 in length
	zTTLV_Value_t  zValue ;
} zTTLV_Item_t ;

#endif /* ZTTLV_H_ */
