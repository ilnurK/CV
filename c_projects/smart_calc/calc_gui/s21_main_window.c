#include "s21_main_window.h"

void calc_gui(int argc, char *argv[]) {
  GtkBuilder *builder = gtk_builder_new();
  GError *error = NULL;
  gtk_init(&argc, &argv);
  const char path[] = "calc_gui/mainWindow.glade";
  if (!gtk_builder_add_from_file(builder, path, &error)) {
    g_warning("%s\n", error->message);
  } else {
    text_t text = {0};
    credit_t cdata = {0};
    deposit_t ddata = {0};
    credit_gui_t credit = {.data = &cdata};
    deposit_gui_t deposit = {.data = &ddata};
    GtkWidget *mainWindow = initMainWindow(builder, &text, &credit, &deposit);
    gtk_widget_show_all(mainWindow);
    gtk_main();
  }
  g_free(error);
}

GtkWidget *initMainWindow(GtkBuilder *builder, text_t *text,
                          credit_gui_t *credit, deposit_gui_t *deposit) {
  GSList *objs = gtk_builder_get_objects(builder);
  GUI_ELEM(GtkWidget, mainWindow);
  GUI_ELEM(GtkTextView, textCalc);
  GUI_ELEM(GtkTextView, textRes);

  text->calc = textCalc, text->res = textRes;
  initLeftBlockButtons(objs, text);
  initRightBlockButtons(objs, text);

  g_signal_connect(mainWindow, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  initCredit(objs, credit);
  initDeposit(objs, deposit);
  g_slist_free(objs);
  g_object_unref(builder);
  return mainWindow;
}

void initLeftBlockButtons(GSList *objs, text_t *text) {
  GUI_ELEM(GtkButton, butNull);
  GUI_ELEM(GtkButton, butOne);
  GUI_ELEM(GtkButton, butTwo);
  GUI_ELEM(GtkButton, butThree);
  GUI_ELEM(GtkButton, butFour);
  GUI_ELEM(GtkButton, butFive);
  GUI_ELEM(GtkButton, butSix);
  GUI_ELEM(GtkButton, butSeven);
  GUI_ELEM(GtkButton, butEight);
  GUI_ELEM(GtkButton, butNine);

  GUI_ELEM(GtkButton, butEqual);
  GUI_ELEM(GtkButton, butEqual1);
  GUI_ELEM(GtkButton, butDot);
  GUI_ELEM(GtkButton, butMul);
  GUI_ELEM(GtkButton, butDiv);
  GUI_ELEM(GtkButton, butMin);
  GUI_ELEM(GtkButton, butPlus);

  g_signal_connect(butNull, "clicked", G_CALLBACK(on_but_clicked), text);
  g_signal_connect(butOne, "clicked", G_CALLBACK(on_but_clicked), text);
  g_signal_connect(butTwo, "clicked", G_CALLBACK(on_but_clicked), text);
  g_signal_connect(butThree, "clicked", G_CALLBACK(on_but_clicked), text);
  g_signal_connect(butFour, "clicked", G_CALLBACK(on_but_clicked), text);
  g_signal_connect(butFive, "clicked", G_CALLBACK(on_but_clicked), text);
  g_signal_connect(butSix, "clicked", G_CALLBACK(on_but_clicked), text);
  g_signal_connect(butSeven, "clicked", G_CALLBACK(on_but_clicked), text);
  g_signal_connect(butEight, "clicked", G_CALLBACK(on_but_clicked), text);
  g_signal_connect(butNine, "clicked", G_CALLBACK(on_but_clicked), text);

  g_signal_connect(butEqual, "clicked", G_CALLBACK(on_equal_clicked), text);
  g_signal_connect(butEqual1, "clicked", G_CALLBACK(on_equal_clicked), text);
  g_signal_connect(butDot, "clicked", G_CALLBACK(on_but_clicked), text);
  g_signal_connect(butPlus, "clicked", G_CALLBACK(on_but_clicked), text);
  g_signal_connect(butMin, "clicked", G_CALLBACK(on_but_clicked), text);
  g_signal_connect(butDiv, "clicked", G_CALLBACK(on_but_clicked), text);
  g_signal_connect(butMul, "clicked", G_CALLBACK(on_but_clicked), text);
}

void initRightBlockButtons(GSList *objs, text_t *text) {
  GUI_ELEM(GtkButton, butMod);
  GUI_ELEM(GtkButton, butX);
  GUI_ELEM(GtkButton, butPow);
  GUI_ELEM(GtkButton, butDel);
  GUI_ELEM(GtkButton, butLn);
  GUI_ELEM(GtkButton, butLog);
  GUI_ELEM(GtkButton, butSqrt);
  GUI_ELEM(GtkButton, butReset);

  GUI_ELEM(GtkButton, butSin);
  GUI_ELEM(GtkButton, butCos);
  GUI_ELEM(GtkButton, butAsin);
  GUI_ELEM(GtkButton, butAcos);
  GUI_ELEM(GtkButton, butTan);
  GUI_ELEM(GtkButton, butAtan);
  GUI_ELEM(GtkButton, butParL);
  GUI_ELEM(GtkButton, butParR);

  g_signal_connect(butMod, "clicked", G_CALLBACK(on_butOper_clicked), text);
  g_signal_connect(butX, "clicked", G_CALLBACK(on_butOper_clicked), text);
  g_signal_connect(butPow, "clicked", G_CALLBACK(on_butOper_clicked), text);
  g_signal_connect(butDel, "clicked", G_CALLBACK(on_butOper_clicked), text);
  g_signal_connect(butLn, "clicked", G_CALLBACK(on_butOper_clicked), text);
  g_signal_connect(butLog, "clicked", G_CALLBACK(on_butOper_clicked), text);
  g_signal_connect(butSqrt, "clicked", G_CALLBACK(on_butOper_clicked), text);
  g_signal_connect(butReset, "clicked", G_CALLBACK(on_butOper_clicked), text);
  g_signal_connect(butSin, "clicked", G_CALLBACK(on_butOper_clicked), text);
  g_signal_connect(butCos, "clicked", G_CALLBACK(on_butOper_clicked), text);
  g_signal_connect(butAsin, "clicked", G_CALLBACK(on_butOper_clicked), text);
  g_signal_connect(butAcos, "clicked", G_CALLBACK(on_butOper_clicked), text);
  g_signal_connect(butTan, "clicked", G_CALLBACK(on_butOper_clicked), text);
  g_signal_connect(butAtan, "clicked", G_CALLBACK(on_butOper_clicked), text);
  g_signal_connect(butParL, "clicked", G_CALLBACK(on_butOper_clicked), text);
  g_signal_connect(butParR, "clicked", G_CALLBACK(on_butOper_clicked), text);
}

void showResult(text_t *text) {
  errors_e error = 0;
  int is_x = 0;
  GtkTextBuffer *buffer = gtk_text_view_get_buffer(text->calc);
  GtkTextBuffer *bufferRes = gtk_text_view_get_buffer(text->res);
  gchar *inp = getTextFromWidget(buffer);
  lexems_t *head_l = getLexemResult(inp, &error, &is_x);
  if (!error) {
    if (is_x) {
      openDrawWindow(head_l);
    } else if (head_l) {
      double res = getResult(head_l);
      char out[255] = {0};
      sprintf(out, "%lf", res);
      gtk_text_buffer_set_text(bufferRes, out, -1);
    }
  }
  if (error) {
    gtk_text_buffer_set_text(bufferRes, errors[error - 1], -1);
  }
  lexemsDelete(head_l);
  (inp) ? g_free(inp) : 0;
}

void on_equal_clicked(GtkWidget *widget, gpointer gdata) {
  text_t *text = (text_t *)gdata;
  const gchar *ename = gtk_widget_get_name(widget);
  if (g_str_equal(ename, "butEqual")) {
    showResult(text);
  }
}

void on_but_clicked(GtkWidget *b, gpointer gdata) {
  text_t *text = (text_t *)gdata;
  char temp[2] = {0};
  const gchar *bname = gtk_widget_get_name(b);
  if (g_str_equal(bname, "butNull")) {
    temp[0] = '0';
  } else if (g_str_equal(bname, "butOne")) {
    temp[0] = '1';
  } else if (g_str_equal(bname, "butTwo")) {
    temp[0] = '2';
  } else if (g_str_equal(bname, "butThree")) {
    temp[0] = '3';
  } else if (g_str_equal(bname, "butFour")) {
    temp[0] = '4';
  } else if (g_str_equal(bname, "butFive")) {
    temp[0] = '5';
  } else if (g_str_equal(bname, "butSix")) {
    temp[0] = '6';
  } else if (g_str_equal(bname, "butSeven")) {
    temp[0] = '7';
  } else if (g_str_equal(bname, "butEight")) {
    temp[0] = '8';
  } else if (g_str_equal(bname, "butNine")) {
    temp[0] = '9';
  } else if (g_str_equal(bname, "butDot")) {
    temp[0] = '.';
  } else if (g_str_equal(bname, "butPlus")) {
    temp[0] = '+';
  } else if (g_str_equal(bname, "butMin")) {
    temp[0] = '-';
  } else if (g_str_equal(bname, "butDiv")) {
    temp[0] = '/';
  } else {
    temp[0] = '*';
  }
  GtkTextBuffer *buffer = gtk_text_view_get_buffer(text->calc);
  gtk_text_buffer_insert_at_cursor(buffer, temp, -1);
  putTextInWidget(buffer);
}

void on_butOper_clicked(GtkWidget *b, gpointer gdata) {
  text_t *text = (text_t *)gdata;
  const gchar *bname = gtk_widget_get_name(b);
  gchar temp[5] = {0};
  if (g_str_equal(bname, "butPow")) {
    temp[0] = '^';
  } else if (g_str_equal(bname, "butX")) {
    temp[0] = 'x';
  } else if (g_str_equal(bname, "butParL")) {
    temp[0] = '(';
  } else if (g_str_equal(bname, "butParR")) {
    temp[0] = ')';
  } else if (g_str_equal(bname, "butMod")) {
    strOperCpy(temp, "mod");
  } else if (g_str_equal(bname, "butLn")) {
    strOperCpy(temp, "ln");
  } else if (g_str_equal(bname, "butLog")) {
    strOperCpy(temp, "log");
  } else if (g_str_equal(bname, "butSqrt")) {
    strOperCpy(temp, "sqrt");
  } else if (g_str_equal(bname, "butSin")) {
    strOperCpy(temp, "sin");
  } else if (g_str_equal(bname, "butCos")) {
    strOperCpy(temp, "cos");
  } else if (g_str_equal(bname, "butAsin")) {
    strOperCpy(temp, "asin");
  } else if (g_str_equal(bname, "butAcos")) {
    strOperCpy(temp, "acos");
  } else if (g_str_equal(bname, "butTan")) {
    strOperCpy(temp, "tan");
  } else if (g_str_equal(bname, "butAtan")) {
    strOperCpy(temp, "atan");
  }
  GtkTextBuffer *buffer = gtk_text_view_get_buffer(text->calc);
  gtk_text_buffer_insert_at_cursor(buffer, temp, -1);
  if (g_str_equal(bname, "butDel")) {
    backspaceText(buffer);
  } else if (g_str_equal(bname, "butReset")) {
    deleteText(buffer);
  }
  putTextInWidget(buffer);
}

gchar *getTextFromWidget(GtkTextBuffer *buffer) {
  GtkTextIter start, end;
  gtk_text_buffer_get_start_iter(buffer, &start);
  gtk_text_buffer_get_end_iter(buffer, &end);
  gchar *text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
  return text;
}

void putTextInWidget(GtkTextBuffer *buffer) {
  gchar *inp = getTextFromWidget(buffer);
  gtk_text_buffer_set_text(buffer, inp, -1);
  (inp) ? g_free(inp) : 0;
}

void backspaceText(GtkTextBuffer *buffer) {
  GtkTextIter end;
  gtk_text_buffer_get_end_iter(buffer, &end);
  gtk_text_buffer_backspace(buffer, &end, 0, 1);
}

void deleteText(GtkTextBuffer *buffer) {
  GtkTextIter start, end;
  gtk_text_buffer_get_start_iter(buffer, &start);
  gtk_text_buffer_get_end_iter(buffer, &end);
  gtk_text_buffer_delete(buffer, &start, &end);
}

void strOperCpy(gchar *temp, const char *oper) {
  int j = -1;
  while (++j < (int)strlen(oper)) {
    temp[j] = oper[j];
  }
}

GObject *getGuiElem(GSList *objs, const gchar *name) {
  const gchar *str;
  GObject *obj = NULL;
  GSList *list = objs;
  do {
    str = gtk_buildable_get_name(list->data);
    if (!strcmp(str, name)) {
      obj = list->data;
    }
  } while ((list = g_slist_next(list)));
  return obj;
}