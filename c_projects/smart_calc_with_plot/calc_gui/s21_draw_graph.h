#ifndef DRAW_GRAPH_H
#define DRAW_GRAPH_H

#include "s21_main_window.h"
#define LEN_FRM 7
#define LEN_VAL 15

gboolean on_draw(GtkWidget* drawArea, cairo_t* cairo, gpointer data);
int isAreaCorrect(area_t area);
void initCell(area_t* area, cell_t* cell);

void drawAxis(cairo_t* cr, area_t area, cell_t* cell);
void drawArrows(cairo_t* cr, area_t area, cell_t cell);

void drawGrid(cairo_t* cr, area_t area, cell_t cell);
void drawGridX(cairo_t* cr, area_t area, double x);
void drawGridY(cairo_t* cr, area_t area, double y);

void drawMark(cairo_t* cr, area_t area, cell_t cell);
void drawEdges(cairo_t* cr, area_t area, cell_t cell);
void drawNotchX(cairo_t* cr, cell_t cell, double x, int i);
void drawNotchY(cairo_t* cr, cell_t cell, double y, int i);
void drawTextX(cairo_t* cr, area_t area, cell_t cell, double x, double iv,
               int j);
void drawTextY(cairo_t* cr, area_t area, cell_t cell, double y, double iv,
               int j);
void drawText(cairo_t* cr, double iv, double size, int accuracy);
void drawXoY(cairo_t* cr, area_t area, cell_t cell);

void drawFunc(cairo_t* cr, area_t area, cell_t cell, lexems_t* head_l);
double calcY(lexems_t* head_l, double x, errors_e* error);
void drawFuncPart(cairo_t* cr, area_t area, double x, double y,
                  int* flag_after_error, errors_e error);
#endif