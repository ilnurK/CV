#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <cairo.h>
#include <gtk/gtk.h>
#include <string.h>

#include "../backend/s21_calculations.h"
#include "../backend/s21_lexems.h"
#include "../backend/s21_structs.h"
#include "s21_credit_calculations.h"
#include "s21_deposit_calculations.h"
#include "s21_draw_graph.h"
#include "s21_draw_window.h"

#define GUI_ELEM(TYPE, ELEM) TYPE* ELEM = (TYPE*)getGuiElem(objs, #ELEM);

typedef struct {
  GtkTextView* calc;
  GtkTextView* res;
} text_t;

void calc_gui(int argc, char* argv[]);
GtkWidget* initMainWindow(GtkBuilder* builder, text_t* text,
                          credit_gui_t* credit, deposit_gui_t* deposit);
void initLeftBlockButtons(GSList* objs, text_t* text);
void initRightBlockButtons(GSList* objs, text_t* text);
void initCredit(GSList* objs, credit_gui_t* credit);

void showResult(text_t* text);
void on_equal_clicked(GtkWidget* textCalc, gpointer data);

void on_but_clicked(GtkWidget* b, gpointer data);
void on_butOper_clicked(GtkWidget* b, gpointer data);
gchar* getTextFromWidget(GtkTextBuffer* buffer);
void putTextInWidget(GtkTextBuffer* buffer);
void backspaceText(GtkTextBuffer* buffer);
void deleteText(GtkTextBuffer* buffer);
void strOperCpy(gchar* temp, const char* oper);
GObject* getGuiElem(GSList* objs, const gchar* name);

#endif