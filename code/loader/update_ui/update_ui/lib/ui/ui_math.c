#include "ui/ui_math.h"
#include "ui/ui_type.h"
#include "asm/math_fast_function.h"


static const int sin0_90_table[] AT_UI_SIM_RAM = {
	0,     572,   1144,  1715,  2286,  2856,  3425,  3993,  4560,  5126,  5690,  6252,  6813,  7371,  7927,  8481,
	9032,  9580,  10126, 10668, 11207, 11743, 12275, 12803, 13328, 13848, 14364, 14876, 15383, 15886, 16383, 16876,
	17364, 17846, 18323, 18794, 19260, 19720, 20173, 20621, 21062, 21497, 21925, 22347, 22762, 23170, 23571, 23964,
	24351, 24730, 25101, 25465, 25821, 26169, 26509, 26841, 27165, 27481, 27788, 28087, 28377, 28659, 28932, 29196,
	29451, 29697, 29934, 30162, 30381, 30591, 30791, 30982, 31163, 31335, 31498, 31650, 31794, 31927, 32051, 32165,
	32269, 32364, 32448, 32523, 32587, 32642, 32687, 32722, 32747, 32762, 32767
};

AT_UI_SIM_RAM
int _trigo_sin(int angle)
{
#if 0
	int ret;
	ret = (int)(sin_float(angle / 180.f) * 32767);
	return ret;
#else
	int ret = 0;
	angle       = angle % 360;

	if (angle < 0) {
		angle = 360 + angle;
	}

	if (angle < 90) {
		ret = sin0_90_table[angle];
	} else if (angle >= 90 && angle < 180) {
		angle = 180 - angle;
		ret   = sin0_90_table[angle];
	} else if (angle >= 180 && angle < 270) {
		angle = angle - 180;
		ret   = -sin0_90_table[angle];
	} else { /*angle >=270*/
		angle = 360 - angle;
		ret   = -sin0_90_table[angle];
	}

	return ret;
#endif

}
AT_UI_SIM_RAM
void _sqrt(u32 x, sqrt_res_t *q, u32 mask)
{
#if 0

	float _x = (float)x;
	float r;

	r = root_float(_x);
	q->i = (u32) r;
	q->f = (u32)((r - (float)q->i) * 256.0f);

	/* printf("_sq1: %d, %d\n", q->i, q->f); */
#else
	x = x << 8;

	u32 root = 0;
	u32 trial;
	do {
		trial = root + mask;
		if ((u32)trial * trial <= x) {
			root = trial;
		}
		mask = mask >> 1;
	} while (mask);

	q->i = (u32) root >> 4;
	q->f = (u32)(root & 0xf) << 4;
#endif // 1
}


