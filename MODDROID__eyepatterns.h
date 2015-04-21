// (c) daniel ford, daniel.jb.ford@gmail.com

/*
/		bit values for color codes
/		bit		7 6 5	4 3 2 	1 0
/		color	red		green	blue
/				
*/						

#include<stdio.h>
#include"colors.h"

const rom far char all_off[8][8] = {
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	______,	______,	______,	______,	______,	______,	______	}
};

const rom far char calm_L[8][8] = {
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	______	},
{	______,	______,	______,	LT_YEL,	LT_YEL,	______,	______,	_PINK_	},
{	______,	______,	LT_YEL,	_BLUE_,	_BLUE_,	LT_YEL,	______,	______	},
{	______,	LT_YEL,	_BLUE_,	_BLUE_,	_BLUE_,	_BLUE_,	LT_YEL,	______	},
{	______,	LT_YEL,	_BLUE_,	_BLUE_,	_BLUE_,	_BLUE_,	LT_YEL,	______	},
{	______,	______,	LT_YEL,	_BLUE_,	_BLUE_,	LT_YEL,	______,	______	},
{	______,	______,	______,	LT_YEL,	LT_YEL,	______,	______,	______	}
};

const rom far char calm_R[8][8] = {
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	______	},
{	_PINK_,	______,	______,	LT_YEL,	LT_YEL,	______,	______,	______	},
{	______,	______,	LT_YEL,	_BLUE_,	_BLUE_,	LT_YEL,	______,	______	},
{	______,	LT_YEL,	_BLUE_,	_BLUE_,	_BLUE_,	_BLUE_,	LT_YEL,	______	},
{	______,	LT_YEL,	_BLUE_,	_BLUE_,	_BLUE_,	_BLUE_,	LT_YEL,	______	},
{	______,	______,	LT_YEL,	_BLUE_,	_BLUE_,	LT_YEL,	______,	______	},
{	______,	______,	______,	LT_YEL,	LT_YEL,	______,	______,	______	}
};

const rom char calm_blink_L[8][8] = {
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	______	},
{	______,	______,	______,	______,	______,	______,	______,	_PINK_	},
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	______	},
{	______,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	______	},
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	______,	______,	______,	______,	______,	______,	______	}
};

const rom char calm_blink_R[8][8] = {
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	______	},
{	_PINK_,	______,	______,	______,	______,	______,	______,	______	},
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	______	},
{	______,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	______	},
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	______,	______,	______,	______,	______,	______,	______	}
};

const rom far char look_left_L[8][8] = {
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	______	},
{	______,	______,	LT_YEL,	LT_YEL,	______,	______,	______,	_PINK_	},
{	______,	LT_YEL,	_BLUE_,	_BLUE_,	LT_YEL,	______,	______,	______	},
{	LT_YEL,	_BLUE_,	_BLUE_,	_BLUE_,	_BLUE_,	LT_YEL,	______,	______	},
{	LT_YEL,	_BLUE_,	_BLUE_,	_BLUE_,	_BLUE_,	LT_YEL,	______,	______	},
{	______,	LT_YEL,	_BLUE_,	_BLUE_,	LT_YEL,	______,	______,	______	},
{	______,	______,	LT_YEL,	LT_YEL,	______,	______,	______,	______	}
};

const rom far char look_left_R[8][8] = {
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	______	},
{	_PINK_,	______,	LT_YEL,	LT_YEL,	______,	______,	______,	______	},
{	______,	LT_YEL,	_BLUE_,	_BLUE_,	LT_YEL,	______,	______,	______	},
{	LT_YEL,	_BLUE_,	_BLUE_,	_BLUE_,	_BLUE_,	LT_YEL,	______,	______	},
{	LT_YEL,	_BLUE_,	_BLUE_,	_BLUE_,	_BLUE_,	LT_YEL,	______,	______	},
{	______,	LT_YEL,	_BLUE_,	_BLUE_,	LT_YEL,	______,	______,	______	},
{	______,	______,	LT_YEL,	LT_YEL,	______,	______,	______,	______	}
};

const rom far char look_left_blink_L[8][8] = {
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	______	},
{	______,	______,	______,	______,	______,	______,	______,	_PINK_	},
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	______,	______	},
{	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	______,	______	},
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	______,	______,	______,	______,	______,	______,	______	}
};

const rom far char look_left_blink_R[8][8] = {
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	______	},
{	_PINK_,	______,	______,	______,	______,	______,	______,	______	},
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	______,	______	},
{	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	______,	______	},
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	______,	______,	______,	______,	______,	______,	______	}
};

const rom far char look_right_L[8][8] = {
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	______	},
{	______,	______,	______,	______,	LT_YEL,	LT_YEL,	______,	_PINK_	},
{	______,	______,	______,	LT_YEL,	_BLUE_,	_BLUE_,	LT_YEL,	______	},
{	______,	______,	LT_YEL,	_BLUE_,	_BLUE_,	_BLUE_,	_BLUE_,	LT_YEL	},
{	______,	______,	LT_YEL,	_BLUE_,	_BLUE_,	_BLUE_,	_BLUE_,	LT_YEL	},
{	______,	______,	______,	LT_YEL,	_BLUE_,	_BLUE_,	LT_YEL,	______	},
{	______,	______,	______,	______,	LT_YEL,	LT_YEL,	______,	______	}
};

const rom far char look_right_R[8][8] = {
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	______	},
{	_PINK_,	______,	______,	______,	LT_YEL,	LT_YEL,	______,	______	},
{	______,	______,	______,	LT_YEL,	_BLUE_,	_BLUE_,	LT_YEL,	______	},
{	______,	______,	LT_YEL,	_BLUE_,	_BLUE_,	_BLUE_,	_BLUE_,	LT_YEL	},
{	______,	______,	LT_YEL,	_BLUE_,	_BLUE_,	_BLUE_,	_BLUE_,	LT_YEL	},
{	______,	______,	______,	LT_YEL,	_BLUE_,	_BLUE_,	LT_YEL,	______	},
{	______,	______,	______,	______,	LT_YEL,	LT_YEL,	______,	______	}
};

const rom far char look_right_blink_L[8][8] = {
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	______	},
{	______,	______,	______,	______,	______,	______,	______,	_PINK_	},
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	______,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL	},
{	______,	______,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL	},
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	______,	______,	______,	______,	______,	______,	______	}
};

const rom far char look_right_blink_R[8][8] = {
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	______	},
{	_PINK_,	______,	______,	______,	______,	______,	______,	______	},
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	______,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL	},
{	______,	______,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL	},
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	______,	______,	______,	______,	______,	______,	______	}
};

const rom char angry_L[8][8] = {
{	______,	______,	______,	_RED__,	_RED__,	______,	______,	______	},
{	______,	______,	______,	______,	_RED__,	_RED__,	______,	______	},
{	______,	______,	______,	LT_YEL,	LT_YEL,	_RED__,	_RED__,	______	},
{	______,	______,	LT_YEL,	_BLUE_,	_BLUE_,	LT_YEL,	_RED__,	_RED__	},
{	______,	LT_YEL,	_BLUE_,	_BLUE_,	_BLUE_,	_BLUE_,	LT_YEL,	______	},
{	______,	LT_YEL,	_BLUE_,	_BLUE_,	_BLUE_,	_BLUE_,	LT_YEL,	______	},
{	______,	______,	LT_YEL,	_BLUE_,	_BLUE_,	LT_YEL,	______,	______	},
{	______,	______,	______,	LT_YEL,	LT_YEL,	______,	______,	______	}
};

const rom char angry_R[8][8] = {
{	______,	______,	______,	_RED__,	_RED__,	______,	______,	______	},
{	______,	______,	_RED__,	_RED__,	______,	______,	______,	______	},
{	______,	_RED__,	_RED__,	LT_YEL,	LT_YEL,	______,	______,	______	},
{	_RED__,	_RED__,	LT_YEL,	_BLUE_,	_BLUE_,	LT_YEL,	______,	______	},
{	______,	LT_YEL,	_BLUE_,	_BLUE_,	_BLUE_,	_BLUE_,	LT_YEL,	______	},
{	______,	LT_YEL,	_BLUE_,	_BLUE_,	_BLUE_,	_BLUE_,	LT_YEL,	______	},
{	______,	______,	LT_YEL,	_BLUE_,	_BLUE_,	LT_YEL,	______,	______	},
{	______,	______,	______,	LT_YEL,	LT_YEL,	______,	______,	______	}
};

const rom char angry_blink_L[8][8] = {
{	______,	______,	______,	_RED__,	_RED__,	______,	______,	______	},
{	______,	______,	______,	______,	_RED__,	_RED__,	______,	______	},
{	______,	______,	______,	______,	______,	_RED__,	_RED__,	______	},
{	______,	______,	______,	______,	______,	______,	_RED__,	_RED__	},
{	______,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	______	},
{	______,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	______	},
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	______,	______,	______,	______,	______,	______,	______	}
};

const rom char angry_blink_R[8][8] = {
{	______,	______,	______,	_RED__,	_RED__,	______,	______,	______	},
{	______,	______,	_RED__,	_RED__,	______,	______,	______,	______	},
{	______,	_RED__,	_RED__,	______,	______,	______,	______,	______	},
{	_RED__,	_RED__,	______,	______,	______,	______,	______,	______	},
{	______,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	______	},
{	______,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	______	},
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	______,	______,	______,	______,	______,	______,	______	}
};

const rom char sleeping[8][8] = {
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	LT_BLU,	LT_BLU,	LT_BLU,	LT_BLU,	LT_BLU,	LT_BLU,	LT_BLU,	LT_BLU	},
{	LT_BLU,	LT_BLU,	LT_BLU,	LT_BLU,	LT_BLU,	LT_BLU,	LT_BLU,	LT_BLU	},
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	______,	______,	______,	______,	______,	______,	______	}
};

const rom far char excited_L[8][8] = {
{	______,	______,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	______,	______	},
{	______,	_PINK_,	______,	______,	______,	______,	_PINK_,	______	},
{	_PINK_,	______,	______,	LT_YEL,	LT_YEL,	______,	______,	_PINK_	},
{	______,	______,	LT_YEL,	_BLUE_,	_BLUE_,	LT_YEL,	______,	______	},
{	______,	LT_YEL,	_BLUE_,	_BLUE_,	_BLUE_,	_BLUE_,	LT_YEL,	______	},
{	______,	LT_YEL,	_BLUE_,	_BLUE_,	_BLUE_,	_BLUE_,	LT_YEL,	______	},
{	______,	______,	LT_YEL,	_BLUE_,	_BLUE_,	LT_YEL,	______,	______	},
{	______,	______,	______,	LT_YEL,	LT_YEL,	______,	______,	______	}
};

const rom far char excited_R[8][8] = {
{	______,	______,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	______,	______	},
{	______,	_PINK_,	______,	______,	______,	______,	_PINK_,	______	},
{	_PINK_,	______,	______,	LT_YEL,	LT_YEL,	______,	______,	_PINK_	},
{	______,	______,	LT_YEL,	_BLUE_,	_BLUE_,	LT_YEL,	______,	______	},
{	______,	LT_YEL,	_BLUE_,	_BLUE_,	_BLUE_,	_BLUE_,	LT_YEL,	______	},
{	______,	LT_YEL,	_BLUE_,	_BLUE_,	_BLUE_,	_BLUE_,	LT_YEL,	______	},
{	______,	______,	LT_YEL,	_BLUE_,	_BLUE_,	LT_YEL,	______,	______	},
{	______,	______,	______,	LT_YEL,	LT_YEL,	______,	______,	______	}
};

const rom far char excited_blink_L[8][8] = {
{	______,	______,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	______,	______	},
{	______,	_PINK_,	______,	______,	______,	______,	_PINK_,	______	},
{	_PINK_,	______,	______,	______,	______,	______,	______,	_PINK_	},
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	______	},
{	______,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	______	},
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	______,	______,	______,	______,	______,	______,	______	}
};

const rom far char excited_blink_R[8][8] = {
{	______,	______,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	______,	______	},
{	______,	_PINK_,	______,	______,	______,	______,	_PINK_,	______	},
{	_PINK_,	______,	______,	______,	______,	______,	______,	_PINK_	},
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	______	},
{	______,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	______	},
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	______,	______,	______,	______,	______,	______,	______	}
};

const rom far char very_excited_1_L[8][8] = {
{	______,	______,	LTORNG,	LTORNG,	LTORNG,	LTORNG,	______,	______	},
{	______,	LTORNG,	______,	______,	______,	______,	LTORNG,	______	},
{	LTORNG,	______,	______,	LT_YEL,	LT_YEL,	______,	______,	LTORNG	},
{	______,	______,	LT_YEL,	GREEN_,	GREEN_,	LT_YEL,	______,	______	},
{	______,	LT_YEL,	GREEN_,	GREEN_,	GREEN_,	GREEN_,	LT_YEL,	______	},
{	______,	LT_YEL,	GREEN_,	GREEN_,	GREEN_,	GREEN_,	LT_YEL,	______	},
{	______,	______,	LT_YEL,	GREEN_,	GREEN_,	LT_YEL,	______,	______	},
{	______,	______,	______,	LT_YEL,	LT_YEL,	______,	______,	______	}
};

const rom far char very_excited_1_R[8][8] = {
{	______,	______,	LTORNG,	LTORNG,	LTORNG,	LTORNG,	______,	______	},
{	______,	LTORNG,	______,	______,	______,	______,	LTORNG,	______	},
{	LTORNG,	______,	______,	LT_YEL,	LT_YEL,	______,	______,	LTORNG	},
{	______,	______,	LT_YEL,	GREEN_,	GREEN_,	LT_YEL,	______,	______	},
{	______,	LT_YEL,	GREEN_,	GREEN_,	GREEN_,	GREEN_,	LT_YEL,	______	},
{	______,	LT_YEL,	GREEN_,	GREEN_,	GREEN_,	GREEN_,	LT_YEL,	______	},
{	______,	______,	LT_YEL,	GREEN_,	GREEN_,	LT_YEL,	______,	______	},
{	______,	______,	______,	LT_YEL,	LT_YEL,	______,	______,	______	}
};

const rom far char very_excited_2_L[8][8] = {
{	______,	______,	ORANGE,	ORANGE,	ORANGE,	ORANGE,	______,	______	},
{	______,	ORANGE,	______,	LTPRPL,	LTPRPL,	______,	ORANGE,	______	},
{	ORANGE,	______,	LTPRPL,	PURPLE,	PURPLE,	LTPRPL,	______,	ORANGE	},
{	______,	LTPRPL,	PURPLE,	PURPLE,	PURPLE,	PURPLE,	LTPRPL,	______	},
{	LTPRPL,	PURPLE,	PURPLE,	PURPLE,	PURPLE,	PURPLE,	PURPLE,	LTPRPL	},
{	LTPRPL,	PURPLE,	PURPLE,	PURPLE,	PURPLE,	PURPLE,	PURPLE,	LTPRPL	},
{	______,	LTPRPL,	PURPLE,	PURPLE,	PURPLE,	PURPLE,	LTPRPL,	______	},
{	______,	______,	LTPRPL,	PURPLE,	PURPLE,	LTPRPL,	______,	______	}
};

const rom far char very_excited_2_R[8][8] = {
{	______,	______,	ORANGE,	ORANGE,	ORANGE,	ORANGE,	______,	______	},
{	______,	ORANGE,	______,	LTPRPL,	LTPRPL,	______,	ORANGE,	______	},
{	ORANGE,	______,	LTPRPL,	PURPLE,	PURPLE,	LTPRPL,	______,	ORANGE	},
{	______,	LTPRPL,	PURPLE,	PURPLE,	PURPLE,	PURPLE,	LTPRPL,	______	},
{	LTPRPL,	PURPLE,	PURPLE,	PURPLE,	PURPLE,	PURPLE,	PURPLE,	LTPRPL	},
{	LTPRPL,	PURPLE,	PURPLE,	PURPLE,	PURPLE,	PURPLE,	PURPLE,	LTPRPL	},
{	______,	LTPRPL,	PURPLE,	PURPLE,	PURPLE,	PURPLE,	LTPRPL,	______	},
{	______,	______,	LTPRPL,	PURPLE,	PURPLE,	LTPRPL,	______,	______	}
};

const rom far char sad_L[8][8] = {
{	______,	______,	LT_RED,	LT_RED,	LT_RED,	LT_RED,	______,	______	},
{	______,	LT_RED,	______,	______,	______,	______,	LT_RED,	______	},
{	LT_RED,	______,	______,	LT_YEL,	LT_YEL,	______,	______,	LT_RED	},
{	______,	______,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	______,	______	},
{	______,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	______	},
{	______,	LT_YEL,	_BLUE_,	_BLUE_,	_BLUE_,	_BLUE_,	LT_YEL,	______	},
{	______,	______,	LT_YEL,	_BLUE_,	_BLUE_,	LT_YEL,	______,	______	},
{	______,	______,	______,	LT_YEL,	LT_YEL,	______,	______,	______	}
};

const rom far char sad_R[8][8] = {
{	______,	______,	LT_RED,	LT_RED,	LT_RED,	LT_RED,	______,	______	},
{	______,	LT_RED,	______,	______,	______,	______,	LT_RED,	______	},
{	LT_RED,	______,	______,	LT_YEL,	LT_YEL,	______,	______,	LT_RED	},
{	______,	______,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	______,	______	},
{	______,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	______	},
{	______,	LT_YEL,	_BLUE_,	_BLUE_,	_BLUE_,	_BLUE_,	LT_YEL,	______	},
{	______,	______,	LT_YEL,	_BLUE_,	_BLUE_,	LT_YEL,	______,	______	},
{	______,	______,	______,	LT_YEL,	LT_YEL,	______,	______,	______	}
};

const rom far char sad_blink_L[8][8] = {
{	______,	______,	LT_RED,	LT_RED,	LT_RED,	LT_RED,	______,	______	},
{	______,	LT_RED,	______,	______,	______,	______,	LT_RED,	______	},
{	LT_RED,	______,	______,	______,	______,	______,	______,	LT_RED	},
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	______	},
{	______,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	______	},
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	______,	______,	______,	______,	______,	______,	______	}
};

const rom far char sad_blink_R[8][8] = {
{	______,	______,	LT_RED,	LT_RED,	LT_RED,	LT_RED,	______,	______	},
{	______,	LT_RED,	______,	______,	______,	______,	LT_RED,	______	},
{	LT_RED,	______,	______,	______,	______,	______,	______,	LT_RED	},
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	______	},
{	______,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	______	},
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	______,	______,	______,	______,	______,	______,	______	}
};

const rom far char scared_L[8][8] = {
{	______,	______,	LTPRPL,	LTPRPL,	LTPRPL,	LTPRPL,	______,	______	},
{	______,	LTPRPL,	______,	LT_YEL,	LT_YEL,	______,	LTPRPL,	______	},
{	LTPRPL,	______,	LT_YEL,	_BLUE_,	_BLUE_,	LT_YEL,	______,	LTPRPL	},
{	______,	LT_YEL,	_BLUE_,	_BLUE_,	_BLUE_,	_BLUE_,	LT_YEL,	______	},
{	LT_YEL,	_BLUE_,	_BLUE_,	_BLUE_,	_BLUE_,	_BLUE_,	_BLUE_,	LT_YEL	},
{	LT_YEL,	_BLUE_,	_BLUE_,	_BLUE_,	_BLUE_,	_BLUE_,	_BLUE_,	LT_YEL	},
{	______,	LT_YEL,	_BLUE_,	_BLUE_,	_BLUE_,	_BLUE_,	LT_YEL,	______	},
{	______,	______,	LT_YEL,	_BLUE_,	_BLUE_,	LT_YEL,	______,	______	}
};

const rom far char scared_R[8][8] = {
{	______,	______,	LTPRPL,	LTPRPL,	LTPRPL,	LTPRPL,	______,	______	},
{	______,	LTPRPL,	______,	LT_YEL,	LT_YEL,	______,	LTPRPL,	______	},
{	LTPRPL,	______,	LT_YEL,	_BLUE_,	_BLUE_,	LT_YEL,	______,	LTPRPL	},
{	______,	LT_YEL,	_BLUE_,	_BLUE_,	_BLUE_,	_BLUE_,	LT_YEL,	______	},
{	LT_YEL,	_BLUE_,	_BLUE_,	_BLUE_,	_BLUE_,	_BLUE_,	_BLUE_,	LT_YEL	},
{	LT_YEL,	_BLUE_,	_BLUE_,	_BLUE_,	_BLUE_,	_BLUE_,	_BLUE_,	LT_YEL	},
{	______,	LT_YEL,	_BLUE_,	_BLUE_,	_BLUE_,	_BLUE_,	LT_YEL,	______	},
{	______,	______,	LT_YEL,	_BLUE_,	_BLUE_,	LT_YEL,	______,	______	}
};

const rom far char scared_blink_L[8][8] = {
{	______,	______,	LTPRPL,	LTPRPL,	LTPRPL,	LTPRPL,	______,	______	},
{	______,	LTPRPL,	______,	______,	______,	______,	LTPRPL,	______	},
{	LTPRPL,	______,	______,	______,	______,	______,	______,	LTPRPL	},
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	______	},
{	______,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	______	},
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	______,	______,	______,	______,	______,	______,	______	}
};

const rom far char scared_blink_R[8][8] = {
{	______,	______,	LTPRPL,	LTPRPL,	LTPRPL,	LTPRPL,	______,	______	},
{	______,	LTPRPL,	______,	______,	______,	______,	LTPRPL,	______	},
{	LTPRPL,	______,	______,	______,	______,	______,	______,	LTPRPL	},
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	______	},
{	______,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	LT_YEL,	______	},
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	______,	______,	______,	______,	______,	______,	______	}
};

const rom far char heartbeat_L[8][8] = {
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	_RED__,	_RED__,	______,	______,	_RED__,	_RED__,	______	},
{	_RED__,	_RED__,	_RED__,	_RED__,	_RED__,	_RED__,	_RED__,	_RED__	},
{	_RED__,	_RED__,	_RED__,	_RED__,	_RED__,	_RED__,	_RED__,	_RED__	},
{	_RED__,	_RED__,	_RED__,	_RED__,	_RED__,	_RED__,	_RED__,	_RED__	},
{	______,	_RED__,	_RED__,	_RED__,	_RED__,	_RED__,	_RED__,	______	},
{	______,	______,	_RED__,	_RED__,	_RED__,	_RED__,	______,	______	},
{	______,	______,	______,	_RED__,	_RED__,	______,	______,	______	}
};

const rom far char heartbeat_R[8][8] = {
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	_RED__,	_RED__,	______,	______,	_RED__,	_RED__,	______	},
{	_RED__,	_RED__,	_RED__,	_RED__,	_RED__,	_RED__,	_RED__,	_RED__	},
{	_RED__,	_RED__,	_RED__,	_RED__,	_RED__,	_RED__,	_RED__,	_RED__	},
{	_RED__,	_RED__,	_RED__,	_RED__,	_RED__,	_RED__,	_RED__,	_RED__	},
{	______,	_RED__,	_RED__,	_RED__,	_RED__,	_RED__,	_RED__,	______	},
{	______,	______,	_RED__,	_RED__,	_RED__,	_RED__,	______,	______	},
{	______,	______,	______,	_RED__,	_RED__,	______,	______,	______	}
};

const rom far char heart_off_L[8][8] = {
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	_PINK_,	_PINK_,	______,	______,	_PINK_,	_PINK_,	______	},
{	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_	},
{	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_	},
{	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_	},
{	______,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	______	},
{	______,	______,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	______,	______	},
{	______,	______,	______,	_PINK_,	_PINK_,	______,	______,	______	}
};

const rom far char heart_off_R[8][8] = {
{	______,	______,	______,	______,	______,	______,	______,	______	},
{	______,	_PINK_,	_PINK_,	______,	______,	_PINK_,	_PINK_,	______	},
{	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_	},
{	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_	},
{	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_	},
{	______,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	______	},
{	______,	______,	_PINK_,	_PINK_,	_PINK_,	_PINK_,	______,	______	},
{	______,	______,	______,	_PINK_,	_PINK_,	______,	______,	______	}
};
	