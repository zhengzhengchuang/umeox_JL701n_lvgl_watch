#ifndef UI_GRID_H
#define UI_GRID_H


#include "ui/ui_core.h"
#include "ui/control.h"

enum {
	GRID_SCROLL_MODE,
	GRID_PAGE_MODE,
};

struct ui_grid_item_info {
	u8 row;
	u8 col;
	u8 page_mode;
	u8 highlight_index;
	u16 interval;
	struct layout_info *info;
};

struct ui_grid {
	struct element elm;
	char hi_num;
	char hi_index;
	char touch_index;
	char onfocus;
	u8   page_mode;
	u8   col_num;
	u8   row_num;
	u8   show_row;
	u8   show_col;
	u8   avail_item_num;
	u8   pix_scroll;
	u8   rotate;
	int  x_interval;
	int  y_interval;
	int  max_show_left;
	int  max_show_top;
	int  min_show_left;
	int  min_show_top;
	int  max_left;
	int  max_top;
	int  min_left;
	int  min_top;
	int  scroll_step;
	u8   ctrl_num;
	struct layout *item;
	struct layout_info *item_info;
	struct element elm2;
	struct position pos;
	struct draw_context dc;
	const struct ui_grid_info *info;
	const struct element_event_handler *handler;
};

extern const struct element_event_handler grid_elm_handler;

static inline int ui_grid_cur_item(struct ui_grid *grid)
{
	if (grid->touch_index >= 0) {
		return grid->touch_index;
	}
	return grid->hi_index;
}

#define ui_grid_set_item(grid, index)   (grid)->hi_index = index


void ui_grid_enable();
void ui_grid_on_focus(struct ui_grid *grid);
void ui_grid_lose_focus(struct ui_grid *grid);
void ui_grid_state_reset(struct ui_grid *grid, int highlight_item);
int ui_grid_highlight_item(struct ui_grid *grid, int item, bool yes);
int ui_grid_highlight_item_by_id(int id, int item, bool yes);
struct ui_grid *__ui_grid_new(struct element_css1 *css, int id,
                              struct ui_grid_item_info *info, struct element *parent);

#endif


