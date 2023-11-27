#include "s21_credit_calculations.h"

void initCredit(GSList* objs, credit_gui_t* credit) {
  GUI_ELEM(GtkEntry, eCreditSum);
  GUI_ELEM(GtkEntry, eCreditTime);
  GUI_ELEM(GtkEntry, eCreditRate);
  GUI_ELEM(GtkEntry, eMonthlyPay);
  GUI_ELEM(GtkEntry, eCreditOverpay);
  GUI_ELEM(GtkEntry, eTotalPayment);
  GUI_ELEM(GtkRadioButton, butMonths);
  GUI_ELEM(GtkRadioButton, butYears);
  GUI_ELEM(GtkRadioButton, butAnnuit);
  GUI_ELEM(GtkRadioButton, butDif);
  GUI_ELEM(GtkButton, butCreditCalc);

  credit->monthly_pay = eMonthlyPay;
  credit->overpay = eCreditOverpay;
  credit->total_pay = eTotalPayment;
  g_signal_connect(eCreditSum, "changed", G_CALLBACK(eCredit_change), credit);
  g_signal_connect(eCreditTime, "changed", G_CALLBACK(eCredit_change), credit);
  g_signal_connect(eCreditRate, "changed", G_CALLBACK(eCredit_change), credit);
  g_signal_connect(butMonths, "toggled", G_CALLBACK(on_toggled), credit);
  g_signal_connect(butYears, "toggled", G_CALLBACK(on_toggled), credit);
  g_signal_connect(butAnnuit, "toggled", G_CALLBACK(on_toggled), credit);
  g_signal_connect(butDif, "toggled", G_CALLBACK(on_toggled), credit);
  g_signal_connect(butCreditCalc, "clicked",
                   G_CALLBACK(on_butCreditCalc_clicked), credit);
}

void eCredit_change(GtkEntry* entry, gpointer gdata) {
  const gchar* name = gtk_widget_get_name(GTK_WIDGET(entry));
  const gchar* text = gtk_entry_get_text(entry);
  double val;
  int blank;

  credit_gui_t* credit = (credit_gui_t*)gdata;
  if (textHandler(text, &val, &blank)) {
    if (!strcmp(name, "eCreditSum")) {
      credit->data->sum = val;
    } else if (!strcmp(name, "eCreditRate")) {
      credit->data->rate = val;
    } else if (!strcmp(name, "eCreditTime")) {
      credit->data->time = val;
    }
  } else {
    gtk_entry_set_text(credit->monthly_pay, errors[DOMAIN_DEF - 1]);
  }
}

void on_toggled(GtkToggleButton* b, gpointer gdata) {
  credit_gui_t* credit = (credit_gui_t*)gdata;
  const char* bname = gtk_widget_get_name(GTK_WIDGET(b));
  if (g_str_equal(bname, "butMonths")) {
    credit->data->time_type = MONTHS;
  } else if (g_str_equal(bname, "butYears")) {
    credit->data->time_type = YEARS;
  } else if (g_str_equal(bname, "butAnnuit")) {
    credit->data->pay_type = ANNUIT;
  } else if (g_str_equal(bname, "butDif")) {
    credit->data->pay_type = DIFFER;
  }
}

void on_butCreditCalc_clicked(GtkWidget* b, gpointer gdata) {
  credit_gui_t* credit = (credit_gui_t*)gdata;
  const gchar* bname = gtk_widget_get_name(b);
  if (checkCreditEntriesCorrect(*credit) &&
      g_str_equal(bname, "butCreditCalc")) {
    calcCredit(credit->data);
    gtk_entry_set_text(credit->monthly_pay, credit->data->str_monthly);
    gtk_entry_set_text(credit->overpay, credit->data->str_overpay);
    gtk_entry_set_text(credit->total_pay, credit->data->str_total);
  } else {
    gtk_entry_set_text(credit->monthly_pay, errors[DOMAIN_DEF - 1]);
  }
}

int checkCreditEntriesCorrect(credit_gui_t credit) {
  int total = 1;
  if (credit.data->rate < 0 || credit.data->time < 0 || credit.data->sum < 0) {
    total = 0;
  }
  return total;
}
