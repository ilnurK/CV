#include "s21_draw_graph.h"

gboolean on_draw(GtkWidget *drawArea, cairo_t *cr, gpointer gdata) {
  gint w = gtk_widget_get_allocated_width(drawArea);
  gint h = gtk_widget_get_allocated_height(drawArea);

  cairo_set_source_rgb(cr, 0.7, 0.7, 0.7);
  cairo_paint(cr);

  data_t *data = (data_t *)gdata;
  area_t area = data->area;
  lexems_t *head_l = data->lexs;
  cell_t cell = data->cell;
  GtkWidget *error = data->error;
  cairo_scale(cr, 1, -1);
  area.w = w, area.h = h;
  area.wmax = (double)w / 2, area.hmax = (double)h / 2;
  area.wmin = -area.wmax, area.hmin = -area.hmax;
  cairo_translate(cr, area.wmax, area.hmin);
  int error_condition = strcmp(gtk_entry_get_text(GTK_ENTRY(error)), "OK");
  if (isAreaCorrect(area) && !error_condition) {
    initCell(&area, &cell);
    drawAxis(cr, area, &cell);
    drawEdges(cr, area, cell);
    drawGrid(cr, area, cell);
    drawMark(cr, area, cell);
    drawFunc(cr, area, cell, head_l);
    showScale(data->xscale, data->yscale, area, cell);
  } else {
    gtk_entry_set_text(GTK_ENTRY(data->error), errors[DOMAIN_DEF - 1]);
  }
  return FALSE;
}

int isAreaCorrect(area_t area) {
  int res = 0;
  if (area.x1 < area.x2 && area.y1 < area.y2) {
    res = 1;
  }
  return res;
}

void initCell(area_t *area, cell_t *cell) {
  cell->on_x = (area->x2 - area->x1) / area->xstep + 2;
  cell->on_y = (area->y2 - area->y1) / area->ystep + 2;

  cell->xsize = (double)area->w / cell->on_x;
  cell->ysize = (double)area->h / cell->on_y;
  cell->xsize = (cell->xsize < 10) ? 10 : cell->xsize;
  cell->ysize = (cell->ysize < 10) ? 10 : cell->ysize;
}

void drawAxis(cairo_t *cr, area_t area, cell_t *cell) {
  cairo_set_source_rgba(cr, 0.1, 0.1, 0.1, 0.8);
  double min = area.wmin + cell->xsize;
  double indent_min = cell->xsize;
  double max = area.wmax - cell->xsize;
  double indent_max = area.w - cell->xsize;
  double oY_x = min;
  if (area.x2 > 0 && area.x1 <= 0) {
    double indent = (0 - area.x1) / (area.x2 - area.x1) * area.w;
    if (indent > indent_min && indent < indent_max) {
      oY_x = area.wmin + indent;
    } else if (indent > indent_max) {
      oY_x = max;
    }
  } else if (area.x2 <= 0) {
    oY_x = max;
    cell->x0 = area.x2;
  }
  cairo_move_to(cr, oY_x, area.hmin);
  cairo_line_to(cr, oY_x, area.hmax);

  min = area.hmin + cell->xsize;
  max = area.hmax - cell->xsize;
  indent_max = area.h - cell->ysize;
  indent_min = cell->ysize;
  double oX_y = min;
  if (area.y2 > 0 && area.y1 <= 0) {
    double indent = (-area.y1) / (area.y2 - area.y1) * area.h;
    if (indent > indent_min && indent < indent_max) {
      oX_y = area.hmin + indent;
    } else if (indent > indent_max) {
      oX_y = max;
    }
  } else if (area.y2 <= 0) {
    oX_y = max;
    cell->y0 = area.y2;
  }

  cairo_move_to(cr, area.wmin, oX_y);
  cairo_line_to(cr, area.wmax, oX_y);

  cairo_stroke(cr);

  cairo_arc(cr, oY_x, oX_y, 2, 0, 2 * G_PI);
  cairo_fill(cr);

  cell->oY_x = oY_x;
  cell->oX_y = oX_y;
  drawArrows(cr, area, *cell);
}

void drawArrows(cairo_t *cr, area_t area, cell_t cell) {
  int arrow_angle = 8;
  double oY_x = cell.oY_x, oX_y = cell.oX_y;
  double arrow_h = cell.ysize / arrow_angle;
  double arrow_w = cell.ysize / 2;
  if (cell.xsize > cell.ysize) {
    arrow_h = cell.xsize / arrow_angle;
    arrow_w = cell.xsize / 2;
  }
  cairo_move_to(cr, oY_x, area.hmax);
  cairo_line_to(cr, oY_x - arrow_h, area.hmax - arrow_w);
  cairo_move_to(cr, oY_x, area.hmax);
  cairo_line_to(cr, oY_x + arrow_h, area.hmax - arrow_w);

  cairo_move_to(cr, area.wmax, oX_y);
  cairo_line_to(cr, area.wmax - arrow_w, oX_y + arrow_h);
  cairo_move_to(cr, area.wmax, oX_y);
  cairo_line_to(cr, area.wmax - arrow_w, oX_y - arrow_h);
  cairo_stroke(cr);
}

void drawGrid(cairo_t *cr, area_t area, cell_t cell) {
  cairo_set_source_rgba(cr, 0, 0.1, 0, 0.2);
  for (double x = cell.oY_x; x < area.wmax; x += cell.xsize) {
    drawGridX(cr, area, x);
  }
  for (double x = cell.oY_x; x > area.wmin; x -= cell.xsize) {
    drawGridX(cr, area, x);
  }
  for (double y = cell.oX_y; y < area.hmax; y += cell.ysize) {
    drawGridY(cr, area, y);
  }
  for (double y = cell.oX_y; y > area.hmin; y -= cell.ysize) {
    drawGridY(cr, area, y);
  }
  cairo_stroke(cr);
}

void drawGridX(cairo_t *cr, area_t area, double x) {
  cairo_move_to(cr, x, area.hmin);
  cairo_line_to(cr, x, area.hmax);
}

void drawGridY(cairo_t *cr, area_t area, double y) {
  cairo_move_to(cr, area.wmin, y);
  cairo_line_to(cr, area.wmax, y);
}

void drawMark(cairo_t *cr, area_t area, cell_t cell) {
  cairo_save(cr);
  cairo_scale(cr, 1, -1);
  cairo_set_source_rgba(cr, 0, 0, 0, 0.5);

  double coef = 2;
  double pos = cell.oY_x + cell.xsize * coef;
  double val = cell.x0 + area.xstep * coef;
  int i = 0;
  while (pos < area.wmax && cell.x0 >= 0) {
    drawNotchX(cr, cell, pos, i);
    drawTextX(cr, area, cell, pos - cell.xsize * 0.75, val, i++);
    pos += cell.xsize * coef, val += area.xstep * coef;
  }
  pos = cell.oY_x - cell.xsize * coef;
  val = cell.x0 - area.xstep * coef, i = 0;
  while (pos > area.wmin && cell.x0 <= 0) {
    drawNotchX(cr, cell, pos, i);
    drawTextX(cr, area, cell, pos, val, i++);
    pos -= cell.xsize * coef, val -= area.xstep * coef;
  }
  pos = -cell.oX_y + cell.ysize * coef;
  val = cell.y0 - area.ystep * coef, i = 0;
  while (pos < area.hmax && cell.y0 <= 0) {
    drawNotchY(cr, cell, pos, i);
    drawTextY(cr, area, cell, pos, val, i++);
    pos += cell.ysize * coef, val -= area.ystep * coef;
  }
  pos = -cell.oX_y - cell.ysize * coef;
  val = cell.y0 + area.ystep * coef, i = 0;
  while (pos > area.hmin && cell.y0 >= 0) {
    drawNotchY(cr, cell, pos, i);
    drawTextY(cr, area, cell, pos + cell.ysize / 2, val, i++);
    pos -= cell.ysize * coef, val += area.ystep * coef;
  }
  drawXoY(cr, area, cell);
  cairo_restore(cr);
}

void drawNotchX(cairo_t *cr, cell_t cell, double x, int i) {
  double len = (i % 2 == 1) ? cell.ysize / 6 : cell.ysize / 3;
  cairo_rectangle(cr, x, -cell.oX_y - len / 2, 0, len);
}

void drawNotchY(cairo_t *cr, cell_t cell, double y, int i) {
  double len = (i % 2 == 1) ? cell.xsize / 6 : cell.xsize / 3;
  cairo_rectangle(cr, cell.oY_x - len / 2, y, len, 0);
}

void drawTextX(cairo_t *cr, area_t area, cell_t cell, double x, double val,
               int i) {
  double down_side = -cell.oX_y + cell.ysize / 2;
  double up_side = -cell.oX_y - cell.ysize / 4;
  double y = (i % 2 == 1) ? up_side : down_side;
  cairo_move_to(cr, x, y);
  drawText(cr, val, cell.xsize, area.xaccuracy);
}

void drawTextY(cairo_t *cr, area_t area, cell_t cell, double y, double val,
               int i) {
  double left_side = cell.oY_x - cell.xsize / 1.2;
  double right_side = cell.oY_x + cell.xsize / 4;
  double x = (i % 2 == 1) ? left_side : right_side;
  cairo_move_to(cr, x, y);
  drawText(cr, val, cell.ysize, area.yaccuracy);
}

void drawText(cairo_t *cr, double val, double size, int accuracy) {
  char num[LEN_VAL] = {0}, format[LEN_FRM] = {0};
  changeFormatStr(format, accuracy);
  sprintf(num, format, val);
  double len_num = strlen(num);
  len_num = (len_num) ? len_num : 4;
  double font_len = 14 * len_num;
  font_len = (font_len < size * 2) ? font_len : size * 2;

  cairo_set_font_size(cr, font_len / len_num);
  cairo_show_text(cr, num);
}

void drawXoY(cairo_t *cr, area_t area, cell_t cell) {
  cairo_set_source_rgba(cr, 0.1, 0.1, 0.1, 0.8);
  cairo_move_to(cr, area.wmax - cell.xsize / 2, -cell.oX_y - cell.ysize / 2);
  cairo_show_text(cr, "x");
  cairo_move_to(cr, cell.oY_x - cell.xsize / 2, area.hmin + cell.ysize / 2);
  cairo_show_text(cr, "y");

  char xformat[LEN_FRM] = {0}, yformat[LEN_FRM] = {0};
  char xtext[LEN_VAL] = {0}, ytext[LEN_VAL] = {0};
  double left_side = cell.oY_x - cell.xsize / 1.2;
  double right_side = cell.oY_x + cell.xsize / 4;
  double down_side = -cell.oX_y + cell.ysize / 2;
  double up_side = -cell.oX_y - cell.ysize / 4;
  if (cell.x0 == 0 && cell.y0 == 0) {
    cairo_move_to(cr, left_side, down_side);
    cairo_show_text(cr, "0");
  }
  if (cell.x0) {
    if (cell.x0 > 0) {
      cairo_move_to(cr, left_side, down_side);
    } else {
      cairo_move_to(cr, right_side, down_side);
    }
    changeFormatStr(xformat, area.xaccuracy);
    sprintf(xtext, xformat, cell.x0);
    cairo_show_text(cr, xtext);
  }
  if (cell.y0) {
    if (cell.y0 > 0) {
      cairo_move_to(cr, left_side, up_side);
    } else {
      cairo_move_to(cr, left_side, up_side);
    }
    changeFormatStr(yformat, area.yaccuracy);
    sprintf(ytext, yformat, cell.y0);
    cairo_show_text(cr, ytext);
  }
}

void drawEdges(cairo_t *cr, area_t area, cell_t cell) {
  double cells_to_x1 = 0, cells_to_x2 = 0, cells_to_y1 = 0, cells_to_y2 = 0;
  double pos_x1 = cell.oY_x, pos_x2 = cell.oY_x;
  double pos_y1 = cell.oX_y, pos_y2 = cell.oX_y;
  if (cell.x0 == 0) {
    cells_to_x1 = -area.x1 / area.xstep, cells_to_x2 = area.x2 / area.xstep;
    pos_x1 -= cells_to_x1 * cell.xsize, pos_x2 += cells_to_x2 * cell.xsize;
  } else if (cell.x0 > 0) {
    cells_to_x2 = (area.x2 - cell.x0) / area.xstep;
    pos_x2 += cells_to_x2 * cell.xsize;
  } else {
    cells_to_x1 = -(area.x1 - cell.x0) / area.xstep;
    pos_x1 -= cells_to_x1 * cell.xsize;
  }
  if (cell.y0 == 0) {
    cells_to_y1 = -area.y1 / area.ystep, cells_to_y2 = area.y2 / area.ystep;
    pos_y1 -= cells_to_y1 * cell.ysize, pos_y2 += cells_to_y2 * cell.ysize;
  } else if (cell.y0 > 0) {
    cells_to_y2 = (area.y2 - cell.y0) / area.ystep;
    pos_y2 += cells_to_y2 * cell.ysize;
  } else {
    cells_to_y1 = -(area.y1 - cell.y0) / area.ystep;
    pos_y1 -= cells_to_y1 * cell.ysize;
  }

  int size = 3;
  cairo_arc(cr, pos_x1, cell.oX_y, size, 0, 2 * G_PI);
  cairo_fill(cr);
  cairo_arc(cr, pos_x2, cell.oX_y, size, 0, 2 * G_PI);
  cairo_fill(cr);
  cairo_arc(cr, cell.oY_x, pos_y1, size, 0, 2 * G_PI);
  cairo_fill(cr);
  cairo_arc(cr, cell.oY_x, pos_y2, size, 0, 2 * G_PI);
  cairo_fill(cr);
}

void drawFunc(cairo_t *cr, area_t area, cell_t cell, lexems_t *head_l) {
  cairo_set_source_rgba(cr, 0.1, 0.2, 0.1, 1);
  double xv = cell.x0, factor = cell.xsize;
  int flag_after_error = 1;
  errors_e error = 0;
  double coef = cell.ysize / area.ystep;
  for (double x = cell.oY_x; x < area.wmax;
       x += cell.xsize / factor, xv += area.xstep / factor) {
    double y = cell.oX_y + (calcY(head_l, xv, &error) - cell.y0) * coef;
    drawFuncPart(cr, area, x, y, &flag_after_error, error);
  }
  xv = cell.x0, flag_after_error = 1, error = 0;
  for (double x = cell.oY_x; x > area.wmin;
       x -= cell.xsize / factor, xv -= area.xstep / factor) {
    double y = cell.oX_y + (calcY(head_l, xv, &error) - cell.y0) * coef;
    drawFuncPart(cr, area, x, y, &flag_after_error, error);
  }
  cairo_stroke(cr);
}

double calcY(lexems_t *head_l, double x, errors_e *error) {
  double res = 0;
  *error = 0;
  lexems_t *copy = lexemsCopy(head_l, error);
  copy = changeX(copy, x);
  copy = parse(copy, error);
  if (*error == 0) {
    res = getResult(copy);
  }
  if (copy) {
    lexemsDelete(copy);
  }
  return res;
}

void drawFuncPart(cairo_t *cr, area_t area, double x, double y,
                  int *flag_after_error, errors_e error) {
  if (error == 0 && y >= area.hmin && y <= area.hmax) {
    if (*flag_after_error) {
      cairo_move_to(cr, x, y);
      *flag_after_error = 0;
    }
    cairo_line_to(cr, x, y);
  } else {
    *flag_after_error = 1;
  }
}
