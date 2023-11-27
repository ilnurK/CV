#ifndef DRAW_WINDOW_H
#define DRAW_WINDOW_H

#include "s21_main_window.h"
#define MIN_X1 -1e7
#define MAX_X2 1e7
#define MIN_Y1 -1e7
#define MAX_Y2 1e7

typedef struct {
  lexems_t* lexs;
  area_t area;
  cell_t cell;
  GtkWidget* window;
  GtkWidget* button;
  GtkWidget* entryX1;
  GtkWidget* entryX2;
  GtkWidget* entryY1;
  GtkWidget* entryY2;
  GtkWidget* showY;
  GtkWidget* xstep;
  GtkWidget* ystep;
  GtkWidget* xscale;
  GtkWidget* yscale;
  GtkWidget* error;
} data_t;

void openDrawWindow(lexems_t* head_l);
GtkWidget* initDrawWindow(GtkBuilder* b, area_t* area, data_t* data);
void initStructs(area_t* area, cell_t* cell, data_t* data, lexems_t* head_l);
void showDomainParams(GtkWidget* X1, GtkWidget* X2, GtkWidget* Y1,
                      GtkWidget* Y2, area_t area);
void showScale(GtkWidget* xscale, GtkWidget* yscale, area_t area, cell_t cell);
void on_show(GtkWindow* window, gpointer gdata);
void on_draw_clicked(GtkButton* button, gpointer data);

void entries_act(GtkEntry* entry, gpointer gdata);
int textHandler(const gchar* text, double* val, int* accuracy);
void entriesXChanged(data_t* data, double val, const gchar* name, int accuracy);
void entriesYChanged(data_t* data, double val, const gchar* name, int accuracy);
double getNewStep(double a, double b, double cells);
int stepAccuracy(double step);
void correctStep(GtkEntry* entry, double step, int accuracy);
void changeFormatStr(char* format, int accuracy);

#endif