#ifndef UI_SLIDER_H
#define UI_SLIDER_H

#include "ui/ui_core.h"
#include "ui/control.h"


#define SLIDER_CHILD_NUM     (SLIDER_CHILD_END - SLIDER_CHILD_BEGIN)


struct slider_text_info {
	u8 move;
	int min_value;
	int max_value;
	int text_color;
};


struct ui_slider {
	struct element elm;
	struct element child_elm[SLIDER_CHILD_NUM];
	u8 step;
	char persent;
	s16 left;
	s16 width;
	s16 min_value;
	s16 max_value;
	u16 text_color;
	const struct ui_slider_info *info;
	const struct slider_text_info *text_info;
	const struct element_event_handler *handler;
};

void ui_slider_enable();
int ui_slider_set_persent_by_id(int id, int persent);

#endif

