#ifndef MASKS
#define MASKS
//A 6-bit field to keep track of block states.
struct bf{
	bool low:1;
	bool high:1;
	bool air:1;
};

//A 16-bit field to keep track of cancel states.
struct cf{
	bool neutral:1;
	bool jump:1;
	bool chain1:1;
	bool chain2:1;
	bool chain3:1;
	bool chain4:1;
	bool chain5:1;
	bool special:1;
	bool super:1;
	bool block:1;
	bool tech:1;
	bool misc1:1;
	bool misc2:1;
	bool misc3:1;
	bool misc4:1;
	bool misc5:1;
	bool dash:1;
};

struct sf
{
	/**Scorefield for one entity
	 * in the opera (player, announcer, stage) 
	 * Names not specified because 
	 * states vary among entities,
	 * and should be defined in .ocfg files.
	 * **/
	bool s1:1;
	bool s2:1;
	bool s4:1;
	bool s8:1;
	bool s16:1;
	bool s32:1;
	bool s64:1;
	bool s128:1;
	bool s256:1;
	bool s512:1;
	bool s1024:1;
	bool s2048:1;
	bool s4096:1;
	bool s8192:1;
	bool s16384:1;
	bool s32768:2;

};


typedef union {
	unsigned int i;
	cf b;
} cancelField;

typedef union {
	unsigned int i;
	bf b; 
} blockField;

typedef union 
{
	unsigned int i;
	sf b;
} scoreField;
#endif
