#include "s21_deposit_calculations.h"

void initDeposit(GSList *objs, deposit_gui_t *deposit) {
  GUI_ELEM(GtkEntry, eDepositSum);
  GUI_ELEM(GtkEntry, eDepositRate);
  GUI_ELEM(GtkEntry, eDepositTaxRate);
  GUI_ELEM(GtkEntry, eDepositRateGain);
  GUI_ELEM(GtkEntry, eDepositTaxSum);
  GUI_ELEM(GtkEntry, eDepositTotal);
  GUI_ELEM(GtkEntry, eIncrease);
  GUI_ELEM(GtkEntry, eDecrease);
  GUI_ELEM(GtkComboBox, periodBox);
  GUI_ELEM(GtkComboBox, capitalBox);
  GUI_ELEM(GtkComboBox, increaseBox);
  GUI_ELEM(GtkComboBox, decreaseBox);
  GUI_ELEM(GtkCheckButton, butCapital);
  GUI_ELEM(GtkButton, butDepositCalc);

  deposit->rate_gain = eDepositRateGain;
  deposit->tax_sum = eDepositTaxSum;
  deposit->total = eDepositTotal;
  deposit->eIncrease = eIncrease, deposit->eDecrease = eDecrease;
  g_signal_connect(eDepositSum, "changed", G_CALLBACK(eDeposit_change),
                   deposit);
  g_signal_connect(eDepositRate, "changed", G_CALLBACK(eDeposit_change),
                   deposit);
  g_signal_connect(eDepositTaxRate, "changed", G_CALLBACK(eDeposit_change),
                   deposit);
  g_signal_connect(eIncrease, "changed", G_CALLBACK(eDeposit_change), deposit);
  g_signal_connect(eDecrease, "changed", G_CALLBACK(eDeposit_change), deposit);
  g_signal_connect(periodBox, "changed", G_CALLBACK(periodBox_changed),
                   deposit);
  g_signal_connect(capitalBox, "changed", G_CALLBACK(capitalBox_changed),
                   deposit);
  g_signal_connect(increaseBox, "changed", G_CALLBACK(increaseBox_changed),
                   deposit);
  g_signal_connect(decreaseBox, "changed", G_CALLBACK(decreaseBox_changed),
                   deposit);
  g_signal_connect(butCapital, "toggled", G_CALLBACK(on_butCapital_toggled),
                   deposit);
  g_signal_connect(butDepositCalc, "clicked",
                   G_CALLBACK(on_butDepositCalc_clicked), deposit);
}

void eDeposit_change(GtkEntry *entry, gpointer gdata) {
  const gchar *name = gtk_widget_get_name(GTK_WIDGET(entry));
  const gchar *text = gtk_entry_get_text(entry);
  double val;
  int blank;

  deposit_gui_t *deposit = (deposit_gui_t *)gdata;
  if (textHandler(text, &val, &blank)) {
    if (!strcmp(name, "eDepositSum")) {
      deposit->data->sum = val;
    } else if (!strcmp(name, "eDepositRate")) {
      deposit->data->rate = val;
    } else if (!strcmp(name, "eDepositTaxRate")) {
      deposit->data->tax_rate = val;
    } else if (!strcmp(name, "eIncrease")) {
      deposit->data->increase = val;
    } else if (!strcmp(name, "eDecrease")) {
      deposit->data->decrease = val;
    }
  } else {
    gtk_entry_set_text(deposit->rate_gain, errors[DOMAIN_DEF - 1]);
  }
}

void periodBox_changed(GtkComboBox *pb, gpointer gdata) {
  deposit_gui_t *deposit = (deposit_gui_t *)gdata;
  const gchar *id = gtk_combo_box_get_active_id(pb);
  int periods[] = {1, 3, 6, 9, 12, 18, 24, 36, 60};
  deposit->data->period = periods[id[0] - '0'];
}

void capitalBox_changed(GtkComboBox *cb, gpointer gdata) {
  deposit_gui_t *deposit = (deposit_gui_t *)gdata;
  const gchar *id = gtk_combo_box_get_active_id(cb);
  deposit->data->cap_period = id[0] - '0';
}

void increaseBox_changed(GtkComboBox *ib, gpointer gdata) {
  deposit_gui_t *deposit = (deposit_gui_t *)gdata;
  const gchar *id_s = gtk_combo_box_get_active_id(ib);
  int id = id_s[0] - '0';
  deposit->data->inc_period = id;
  gboolean status = (id) ? TRUE : FALSE;
  double opacity = (id) ? 1 : 0.2;
  gtk_editable_set_editable(GTK_EDITABLE(deposit->eIncrease), status);
  gtk_widget_set_opacity(GTK_WIDGET(deposit->eIncrease), opacity);
  (id) ? 0 : gtk_entry_set_text(deposit->eIncrease, "");
}

void decreaseBox_changed(GtkComboBox *db, gpointer gdata) {
  deposit_gui_t *deposit = (deposit_gui_t *)gdata;
  const gchar *id_s = gtk_combo_box_get_active_id(db);
  int id = id_s[0] - '0';
  deposit->data->inc_period = id;
  gboolean status = (id) ? TRUE : FALSE;
  double opacity = (id) ? 1 : 0.2;
  gtk_editable_set_editable(GTK_EDITABLE(deposit->eDecrease), status);
  gtk_widget_set_opacity(GTK_WIDGET(deposit->eDecrease), opacity);
  (id) ? 0 : gtk_entry_set_text(deposit->eDecrease, "");
}

void on_butCapital_toggled(GtkToggleButton *b, gpointer gdata) {
  deposit_gui_t *deposit = (deposit_gui_t *)gdata;
  if (gtk_toggle_button_get_active(b)) {
    deposit->data->capitalization = 1;
  } else {
    deposit->data->capitalization = 0;
  }
}

void on_butDepositCalc_clicked(GtkWidget *b, gpointer gdata) {
  deposit_gui_t *deposit = (deposit_gui_t *)gdata;
  const gchar *bname = gtk_widget_get_name(b);
  if (checkDepositEntriesCorrect(*deposit) &&
      g_str_equal(bname, "butDepositCalc")) {
    calcDeposit(deposit->data);
    gtk_entry_set_text(deposit->rate_gain, deposit->data->str_rate_gain);
    gtk_entry_set_text(deposit->tax_sum, deposit->data->str_tax_sum);
    gtk_entry_set_text(deposit->total, deposit->data->str_total);
  } else {
    gtk_entry_set_text(deposit->rate_gain, errors[DOMAIN_DEF - 1]);
  }
}

int checkDepositEntriesCorrect(deposit_gui_t deposit) {
  int total = 1;
  if (deposit.data->rate < 0 || deposit.data->tax_rate < 0 ||
      deposit.data->sum < 0) {
    total = 0;
  }
  return total;
}