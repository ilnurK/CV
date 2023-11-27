#ifndef CREDIT_CALC_H
#define CREDIT_CALC_H

#include <cairo.h>
#include <gtk/gtk.h>

#include "../backend/s21_credit_backend.h"

typedef struct {
  credit_t* data;
  GtkEntry* monthly_pay;
  GtkEntry* overpay;
  GtkEntry* total_pay;
} credit_gui_t;

#include "s21_main_window.h"

void initCredit(GSList* objs, credit_gui_t* credit);
void eCredit_change(GtkEntry* entry, gpointer gdata);
void on_toggled(GtkToggleButton* b, gpointer gdata);
void on_butCreditCalc_clicked(GtkWidget* b, gpointer gdata);
int checkCreditEntriesCorrect(credit_gui_t credit);

#endif