#pragma once
#include <ntifs.h>

typedef union _CR4{
	UINT64 Value;
	struct 
	{
		UINT64 VME : 1;
		UINT64 PVI : 1;
		UINT64 TSD : 1;
		UINT64 DE : 1;
		UINT64 PSE : 1;
		UINT64 PAE : 1;
		UINT64 MCE : 1;
		UINT64 PGE : 1;
		UINT64 PCE : 1;
		UINT64 OSFXSR : 1;
		UINT64 OSXMMEXCPT : 1;
		UINT64 UMIP : 1;
		UINT64 LA57 : 1;
		UINT64 VMXE : 1;
		UINT64 SMXE : 1;
		UINT64 Reserved1 : 1;
		UINT64 PSGSBASE : 1;
		UINT64 PCIDE : 1;
		UINT64 OSXSAVE : 1;
		UINT64 KL : 1;
		UINT64 SMEP : 1;
		UINT64 SMAP : 1;
		UINT64 PKE : 1;
		UINT64 CET : 1;
		UINT64 PKS : 1;
		UINT64 Reserved2 : 63 - 24;
	} Fields;
}CR4, *PCR4;

typedef union _CR3 {
	UINT64 Value;
	struct  
	{
		UINT64 Ignored1 : 3;
		UINT64 PWT : 1;
		UINT64 PCD : 1;
		UINT64 Ignored2 : 7;
		UINT64 PPN : 40;
		UINT64 Reserved1 : 12;
	} Fields;
}CR3, *PCR3;
static_assert(sizeof(CR3) == 8, "sizeof CR3");

typedef union _PA {
	UINT64 Value;
	LARGE_INTEGER AsLargeInteger;
	struct 
	{
		UINT64 PPO : 12;
		UINT64 PPN : 40;
		UINT64 Reserved1 : 12;
	}Fields4KB;
	struct 
	{
		UINT64 PPO : 21;
		UINT64 PPN : 31;
		UINT64 Reserved1 : 12;
	}Fields2MB;
	struct 
	{
		UINT64 PPO : 30;
		UINT64 PPN : 22;
		UINT64 Reserved1 : 12;
	}Fields1GB;
}PA, *PPA;

typedef union _L1PTE
{
	UINT64 Value;
	struct
	{
		UINT64 P : 1;
		UINT64 R_W : 1;
		UINT64 U_S : 1;
		UINT64 PWT : 1;
		UINT64 PCD : 1;
		UINT64 A : 1;
		UINT64 Ingored1 : 1;
		UINT64 Reserved1 : 1;
		UINT64 Ignored2 : 3;
		UINT64 R : 1;
		UINT64 PPN : 40;
		UINT64 Ignored3 : 11;
		UINT64 XD : 1;
	} Fields;
} L1PTE, * PL1PTE;
static_assert(sizeof(L1PTE) == 8, "sizeof L1PTE");


typedef union _L2PTE
{
    UINT64 Value;
    struct
    {
        UINT64 P : 1;
        UINT64 R_W : 1;
        UINT64 U_S : 1;
        UINT64 PWT : 1;
        UINT64 PCD : 1;
        UINT64 A : 1;
        UINT64 D : 1;
        UINT64 PS : 1;
        UINT64 G : 1;
        UINT64 Ignored1 : 2;
        UINT64 R : 1;
        UINT64 PAT : 1;
        UINT64 Reserved1 : 17;
        UINT64 PPN : 22;
        UINT64 Ignored2 : 7;
        UINT64 ProtKey : 4;
        UINT64 XD : 1;
    } Fields1GB;
    struct
    {
        UINT64 P : 1;
        UINT64 R_W : 1;
        UINT64 U_S : 1;
        UINT64 PWT : 1;
        UINT64 PCD : 1;
        UINT64 A : 1;
        UINT64 Ignored1 : 1;
        UINT64 PS : 1;
        UINT64 Ignored2 : 3;
        UINT64 R : 1;
        UINT64 PPN : 40;
        UINT64 Ignored3 : 11;
        UINT64 XD : 1;
    } Fields;
} L2PTE, * PL2PTE;
static_assert(sizeof(L2PTE) == 8, "sizeof L2PTE");

typedef union _L3PTE
{
    UINT64 Value;
    struct
    {
        UINT64 P : 1;
        UINT64 R_W : 1;
        UINT64 U_S : 1;
        UINT64 PWT : 1;
        UINT64 PCD : 1;
        UINT64 A : 1;
        UINT64 D : 1;
        UINT64 PS : 1;
        UINT64 G : 1;
        UINT64 Ignored1 : 2;
        UINT64 R : 1;
        UINT64 PAT : 1;
        UINT64 Reserved1 : 8;
        UINT64 PPN : 31;
        UINT64 Ignored2 : 7;
        UINT64 ProtKey : 4;
        UINT64 XD : 1;
    } Fields2MB;
    struct
    {
        UINT64 P : 1;
        UINT64 R_W : 1;
        UINT64 U_S : 1;
        UINT64 PWT : 1;
        UINT64 PCD : 1;
        UINT64 A : 1;
        UINT64 Ingored1 : 1;
        UINT64 PS : 1;
        UINT64 Ignored2 : 3;
        UINT64 R : 1;
        UINT64 PPN : 40;
        UINT64 Ignored3 : 11;
        UINT64 XD : 1;
    } Fields;
} L3PTE, * PL3PTE;
static_assert(sizeof(L3PTE) == 8, "sizeof L3PTE");

typedef union _L4PTE
{
    UINT64 Value;
    struct
    {
        UINT64 P : 1;
        UINT64 R_W : 1;
        UINT64 U_S : 1;
        UINT64 PWT : 1;
        UINT64 PCD : 1;
        UINT64 A : 1;
        UINT64 D : 1;
        UINT64 PAT : 1;
        UINT64 G : 1;
        UINT64 Ignored1 : 2;
        UINT64 R : 1;
        UINT64 PPN : 40;
        UINT64 Ignored2 : 7;
        UINT64 ProtKey : 4;
        UINT64 XD : 1;
    } Fields;
} L4PTE, * PL4PTE;
static_assert(sizeof(L4PTE) == 8, "sizeof L4PTE");

VOID DumpUserPageTable(PEPROCESS Process);
