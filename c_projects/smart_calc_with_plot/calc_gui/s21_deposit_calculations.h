#ifndef DEPOSIT_CALC_H
#define DEPOSIT_CALC_H

#include <cairo.h>
#include <gtk/gtk.h>

#include "../backend/s21_deposit_backend.h"

typedef struct {
  deposit_t* data;
  GtkEntry* rate_gain;
  GtkEntry* tax_sum;
  GtkEntry* total;
  GtkEntry* eIncrease;
  GtkEntry* eDecrease;
} deposit_gui_t;

#include "s21_main_window.h"

void initDeposit(GSList* objs, deposit_gui_t* deposit);
void eDeposit_change(GtkEntry* entry, gpointer gdata);
void periodBox_changed(GtkComboBox* pb, gpointer gdata);
void capitalBox_changed(GtkComboBox* cb, gpointer gdata);
void increaseBox_changed(GtkComboBox* ib, gpointer gdata);
void decreaseBox_changed(GtkComboBox* db, gpointer gdata);
void on_butCapital_toggled(GtkToggleButton* b, gpointer gdata);
void on_butDepositCalc_clicked(GtkWidget* b, gpointer gdata);
int checkDepositEntriesCorrect(deposit_gui_t deposit);

#endif