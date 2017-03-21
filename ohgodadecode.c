// Copyright (c) 2017 OhGodACompany - OhGodAGirl & OhGodAPet

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "ohgodadecode.h"

// Parameter len is the size in bytes of asciistr, meaning rawstr
// must have (len >> 1) bytes allocated
// Maybe asciistr just NULL terminated?
// Returns length of rawstr in bytes
int ASCIIHexToBinary(void *restrict rawstr, const char *restrict asciistr, size_t len)
{
	for(int i = 0, j = 0; i < len; ++i)
	{
		char tmp = asciistr[i];
		if(tmp < 'A') tmp -= '0';
		else if(tmp < 'a') tmp = (tmp - 'A') + 10;
		else tmp = (tmp - 'a') + 10;
		
		if(i & 1) ((uint8_t *)rawstr)[j++] |= tmp & 0x0F;
		else ((uint8_t *)rawstr)[j] = tmp << 4;
	}
	
	return(len >> 1);
}

int main(int argc, char **argv)
{
	uint32_t buf[12];
	VBIOS_TIMING_FORMAT *Timings = (VBIOS_TIMING_FORMAT *)buf;
		
	// Short circuited logic should prevent a segfault.
	if(argc != 2 || strlen(argv[1]) != 96)
	{
		printf("Usage: %s <96-char hex string>\n");
		return(1);
	}
	
	ASCIIHexToBinary(buf, argv[1], 96);
		
	printf("TRCDW = %d\n", Timings->SEQ_RAS_TIMING.TRCDW);
	printf("TRCDWA = %d\n", Timings->SEQ_RAS_TIMING.TRCDWA);
	printf("TRCDR = %d\n", Timings->SEQ_RAS_TIMING.TRCDR);
	printf("TRCDRA = %d\n", Timings->SEQ_RAS_TIMING.TRCDRA);
	printf("TRRD = %d\n", Timings->SEQ_RAS_TIMING.TRRD);
	printf("TRC = %d\n", Timings->SEQ_RAS_TIMING.TRC);
	printf("Pad0 = %d\n\n", Timings->SEQ_RAS_TIMING.Pad0);
	
	printf("TRP_WRA = %d\n", Timings->SEQ_MISC_TIMING.TRP_WRA);
	printf("Pad0 = %d\n", Timings->SEQ_MISC_TIMING.Pad0);
	printf("TRP_RDA = %d\n", Timings->SEQ_MISC_TIMING.TRP_RDA);
	printf("TRP = %d\n", Timings->SEQ_MISC_TIMING.TRP);
	printf("TRFC = %d\n\n", Timings->SEQ_MISC_TIMING.TRFC);
	
	printf("PA2RDATA = %d\n", Timings->SEQ_MISC_TIMING2.PA2RDATA);
	printf("Pad0 = %d\n", Timings->SEQ_MISC_TIMING2.Pad0);
	printf("PA2WDATA = %d\n", Timings->SEQ_MISC_TIMING2.PA2WDATA);
	printf("Pad1 = %d\n", Timings->SEQ_MISC_TIMING2.Pad1);
	printf("TFAW = %d\n", Timings->SEQ_MISC_TIMING2.TFAW);
	printf("TCRCRL = %d\n", Timings->SEQ_MISC_TIMING2.TCRCRL);
	printf("TCRCWL = %d\n", Timings->SEQ_MISC_TIMING2.TCRCWL);
	printf("TFAW32 = %d\n\n", Timings->SEQ_MISC_TIMING2.TFAW32);
	
	printf("MC_SEQ_MISC1: 0x%08X\n\n", Timings->SEQ_MISC1);
	printf("MC_SEQ_MISC3: 0x%08X\n\n", Timings->SEQ_MISC3);
	printf("MC_SEQ_MISC8: 0x%08X\n\n", Timings->SEQ_MISC8);
	
	printf("ACTRD = %d\n", Timings->ARB_DRAM_TIMING.ACTRD);
	printf("ACTWR = %d\n", Timings->ARB_DRAM_TIMING.ACTWR);
	printf("RASMACTRD = %d\n", Timings->ARB_DRAM_TIMING.RASMACTRD);
	printf("RASMACTWR = %d\n\n", Timings->ARB_DRAM_TIMING.RASMACTWR);
	
	printf("RAS2RAS = %d\n", Timings->ARB_DRAM_TIMING2.RAS2RAS);
	printf("RP = %d\n", Timings->ARB_DRAM_TIMING2.RP);
	printf("WRPLUSRP = %d\n", Timings->ARB_DRAM_TIMING2.WRPLUSRP);
	printf("BUS_TURN = %d\n\n", Timings->ARB_DRAM_TIMING2.BUS_TURN);
	
	return(0);
}
