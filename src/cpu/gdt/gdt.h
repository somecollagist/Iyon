// Stolen from PonchoOs, check Resources.md

#pragma once
#include <types.h>

typedef struct {
	uint16_t 	LimitLow;
	uint16_t 	BaseLow;
	uint8_t		BaseMid;
	uint8_t		Access;
	uint8_t		LimitFlags;
	uint8_t		BaseHigh;
	uint32_t	BaseTop;
	uint32_t	Reserved;
} __attribute__((packed)) TSSEntry;

typedef struct {
	uint32_t Reserved0;
	uint64_t RSP[3];
	uint64_t Reserved1;
	uint64_t IST[7];
	uint32_t Reserved2;
	uint32_t Reserved3;
	uint16_t Reserved4;
	uint16_t IOMapBase;
} __attribute__((packed)) TSS;

typedef struct {
	uint16_t 	Size;
	uint64_t 	Offset;
} __attribute__((packed)) GDTDescriptor;

typedef struct {
	uint16_t 	LimitLow;
	uint16_t 	BaseLow;
	uint8_t		BaseMid;
	uint8_t		Access;
	uint8_t		LimitFlags;
	uint8_t		BaseHigh;
} __attribute__((packed)) GDTEntry;

typedef struct {
	GDTEntry Null;
	GDTEntry KernelCode;
	GDTEntry KernelData;
	GDTEntry UserCode;
	GDTEntry UserData;
	TSSEntry TSS;
} __attribute__((packed, aligned(0x1000))) GDT;

//Initialises the GDT
void InitGDT();