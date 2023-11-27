#include "s21_draw_window.h"

void openDrawWindow(lexems_t *head_l) {
  GtkBuilder *builderDraw = gtk_builder_new();
  GError *gerror = NULL;
  if (!gtk_builder_add_from_file(builderDraw, "calc_gui/drawWindow.glade",
                                 &gerror)) {
    g_warning("%s\n", gerror->message);
    g_free(gerror);
  } else {
    area_t area;
    cell_t cell;
    data_t data;
    initStructs(&area, &cell, &data, head_l);
    GtkWidget *drawWindow = initDrawWindow(builderDraw, &area, &data);
    gtk_widget_show_all(drawWindow);
    gtk_main();
    g_object_unref(builderDraw);
  }
}

void initStructs(area_t *area, cell_t *cell, data_t *data, lexems_t *head_l) {
  area->x1 = -10, area->x2 = 10, area->y1 = -10, area->y2 = 10;
  area->xstep = 1, area->ystep = 1;

  cell->x0 = 0, cell->y0 = 0;
  cell->on_x = (area->x2 - area->x1) / area->xstep + 2;
  cell->on_y = (area->x2 - area->x1) / area->xstep + 2;
  data->lexs = head_l, data->area = *area, data->cell = *cell;
}

GtkWidget *initDrawWindow(GtkBuilder *b, area_t *area, data_t *data) {
  GtkWidget *drawWindow = GTK_WIDGET(gtk_builder_get_object(b, "drawWindow"));
  GtkWidget *drawArea = GTK_WIDGET(gtk_builder_get_object(b, "drawArea"));
  GtkWidget *entryX1 = GTK_WIDGET(gtk_builder_get_object(b, "entryX1"));
  GtkWidget *entryX2 = GTK_WIDGET(gtk_builder_get_object(b, "entryX2"));
  GtkWidget *entryY1 = GTK_WIDGET(gtk_builder_get_object(b, "entryY1"));
  GtkWidget *entryY2 = GTK_WIDGET(gtk_builder_get_object(b, "entryY2"));
  GtkWidget *eScaleX = GTK_WIDGET(gtk_builder_get_object(b, "entryScaleX"));
  GtkWidget *eScaleY = GTK_WIDGET(gtk_builder_get_object(b, "entryScaleY"));
  GtkWidget *eChangeX = GTK_WIDGET(gtk_builder_get_object(b, "eChangeX"));
  GtkWidget *eShowY = GTK_WIDGET(gtk_builder_get_object(b, "eShowY"));
  GtkWidget *entryStepX = GTK_WIDGET(gtk_builder_get_object(b, "entryStepX"));
  GtkWidget *entryStepY = GTK_WIDGET(gtk_builder_get_object(b, "entryStepY"));
  GtkWidget *butDraw = GTK_WIDGET(gtk_builder_get_object(b, "butDraw"));
  GtkWidget *entryError = GTK_WIDGET(gtk_builder_get_object(b, "entryError"));

  gtk_widget_set_size_request(GTK_WIDGET(drawArea), 1000, 660);

  data->window = drawWindow, data->button = butDraw, data->error = entryError;
  data->entryX1 = entryX1, data->entryX2 = entryX2, data->xstep = entryStepX;
  data->entryY1 = entryY1, data->entryY2 = entryY2, data->ystep = entryStepY;
  data->xscale = eScaleX, data->yscale = eScaleY, data->showY = eShowY;

  g_signal_connect(drawWindow, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect(drawWindow, "show", G_CALLBACK(on_show), data);
  g_signal_connect(drawArea, "draw", G_CALLBACK(on_draw), data);
  g_signal_connect(butDraw, "clicked", G_CALLBACK(on_draw_clicked), data);
  g_signal_connect(entryX1, "activate", G_CALLBACK(entries_act), data);
  g_signal_connect(entryX2, "activate", G_CALLBACK(entries_act), data);
  g_signal_connect(entryY1, "activate", G_CALLBACK(entries_act), data);
  g_signal_connect(entryY2, "activate", G_CALLBACK(entries_act), data);
  g_signal_connect(entryX1, "activate", G_CALLBACK(entries_act), data);
  g_signal_connect(eChangeX, "activate", G_CALLBACK(entries_act), data);
  g_signal_connect(entryStepY, "activate", G_CALLBACK(entries_act), data);

  showDomainParams(entryX1, entryX2, entryY1, entryY2, *area);
  gtk_widget_grab_focus(entryX1);
  return drawWindow;
}

void showDomainParams(GtkWidget *X1, GtkWidget *X2, GtkWidget *Y1,
                      GtkWidget *Y2, area_t area) {
  char text[LEN_VAL] = {0}, format[LEN_FRM] = "%.0lf";
  sprintf(text, format, area.x1);
  gtk_entry_set_text(GTK_ENTRY(X1), text);
  sprintf(text, format, area.x2);
  gtk_entry_set_text(GTK_ENTRY(X2), text);
  sprintf(text, format, area.y1);
  gtk_entry_set_text(GTK_ENTRY(Y1), text);
  sprintf(text, format, area.y2);
  gtk_entry_set_text(GTK_ENTRY(Y2), text);
}

void showScale(GtkWidget *xscale, GtkWidget *yscale, area_t area, cell_t cell) {
  char text[255] = {0};
  if (cell.on_x != 0) {
    sprintf(text, "%d", area.w / cell.on_x);
    gtk_entry_set_text(GTK_ENTRY(xscale), text);
  }
  if (cell.on_y != 0) {
    sprintf(text, "%d", area.h / cell.on_y);
    gtk_entry_set_text(GTK_ENTRY(yscale), text);
  }
}

void on_draw_clicked(GtkButton *button, gpointer gdata) {
  if (!strcmp(gtk_widget_get_name(GTK_WIDGET(button)), "butDraw")) {
    data_t *data = (data_t *)gdata;
    entries_act(GTK_ENTRY(data->entryX1), gdata);
    entries_act(GTK_ENTRY(data->entryX2), gdata);
    entries_act(GTK_ENTRY(data->entryY1), gdata);
    entries_act(GTK_ENTRY(data->entryY2), gdata);
  }
}

void on_show(GtkWindow *window, gpointer gdata) {
  if (!strcmp(gtk_widget_get_name(GTK_WIDGET(window)), "drawWindow")) {
    data_t *data = (data_t *)gdata;
    on_draw_clicked(GTK_BUTTON(data->button), gdata);
  }
}

void entries_act(GtkEntry *entry, gpointer gdata) {
  const gchar *name = gtk_widget_get_name(GTK_WIDGET(entry));
  const gchar *text = gtk_entry_get_text(GTK_ENTRY(entry));
  double val;
  int accuracy = 0;
  errors_e error = 0;
  data_t *data = (data_t *)gdata;
  if (textHandler(text, &val, &accuracy)) {
    if (!strcmp(name, "entryX1") || !strcmp(name, "entryX2")) {
      entriesXChanged(data, val, name, accuracy);
    } else if (!strcmp(name, "entryY1") || !strcmp(name, "entryY2")) {
      entriesYChanged(data, val, name, accuracy);
    } else if (!strcmp(name, "entryStepX") && val > 0) {
      data->area.xstep = (val <= data->area.x2) ? val : data->area.x2 / 2;
    } else if (!strcmp(name, "entryStepY") && val > 0) {
      data->area.ystep = (val <= data->area.y2) ? val : data->area.y2 / 2;
    } else if (!strcmp(name, "eChangeX")) {
      double res = calcY(data->lexs, val, &error);
      char out[LEN_VAL] = {0};
      sprintf(out, "%lf", res);
      gtk_entry_set_text(GTK_ENTRY(data->showY), out);
    }
    gtk_entry_set_text(GTK_ENTRY(data->error), "OK");
  } else {
    error = DOMAIN_DEF;
  }
  (error) ? gtk_entry_set_text(GTK_ENTRY(data->error), errors[DOMAIN_DEF - 1])
          : 0;
  gtk_widget_queue_draw(GTK_WIDGET(data->window));
}

int textHandler(const gchar *text, double *val, int *accuracy) {
  int res = 1, i = 0, len = (int)strlen(text);
  int flag_dot_uniq = 0, flag_min_uniq = 0;
  *accuracy = 0;
  while (i < len && res) {
    if (text[i] == DOT || text[i] == COMMA) {
      if (!flag_dot_uniq) {
        flag_dot_uniq++;
      } else {
        res = 0;
      }
    } else if (i == 0 && text[i] == '-') {
      if (!flag_min_uniq) {
        flag_min_uniq++;
      } else {
        res = 0;
      }
    } else if (!isdigit(text[i])) {
      res = 0;
    }
    i++;
    *accuracy += (flag_dot_uniq) ? 1 : 0;
  }
  if (res) {
    *val = atof(text);
    *accuracy -= 1;
  }
  return res;
}

void entriesXChanged(data_t *data, double val, const gchar *name,
                     int accuracy) {
  double step;
  if (!strcmp(name, "entryX1")) {
    val = (val < MIN_X1) ? MIN_X1 : val;
    step = (val) ? getNewStep(data->area.x2, val, data->cell.on_x) : 1;
    data->area.x1 = val;
    data->cell.x0 = (val > 0) ? val : 0;
  } else {
    val = (val > MAX_X2) ? MAX_X2 : val;
    step = (val) ? getNewStep(val, data->area.x1, data->cell.on_x) : 1;
    data->area.x2 = val;
    data->cell.x0 = (val < 0) ? val : (data->area.x1 > 0) ? data->area.x1 : 0;
  }
  data->area.xstep = step;
  int step_accuracy = stepAccuracy(step);
  data->area.xaccuracy = (accuracy > step_accuracy) ? accuracy : step_accuracy;
  correctStep(GTK_ENTRY(data->xstep), step, data->area.xaccuracy);
}

void entriesYChanged(data_t *data, double val, const gchar *name,
                     int accuracy) {
  double step;
  if (!strcmp(name, "entryY1")) {
    val = (val < MIN_Y1) ? MIN_Y1 : val;
    step = (val) ? getNewStep(data->area.y2, val, data->cell.on_y) : 1;
    data->area.y1 = val;
    data->cell.y0 = (val > 0) ? val : 0;
  } else {
    val = (val > MAX_Y2) ? MAX_Y2 : val;
    step = (val) ? getNewStep(val, data->area.y1, data->cell.on_y) : 1;
    data->area.y2 = val;
    data->cell.y0 = (val < 0) ? val : (data->area.y1 > 0) ? data->area.y1 : 0;
  }
  data->area.ystep = step;
  int step_accuracy = stepAccuracy(step);
  data->area.yaccuracy = (accuracy > step_accuracy) ? accuracy : step_accuracy;
  correctStep(GTK_ENTRY(data->ystep), step, data->area.yaccuracy);
}

double getNewStep(double a, double b, double cells) {
  cells = (cells > 2) ? cells : 3;
  double res = fabs(a - b) / (cells - 2);
  return res;
}

int stepAccuracy(double step) {
  int accuracy = 0;
  double fract_part = step - (int)step;
  if (fract_part) {
    int max_accuracy = 7, flag_null_nine = 0, flag_stop = 0;
    for (int i = 0; i < max_accuracy && !flag_stop; i++) {
      fract_part *= 10;
      int last_dig = (int)fract_part % 10;
      int condition = last_dig == 9 || last_dig == 0;
      (condition && flag_null_nine) ? flag_stop++ : 0;
      flag_null_nine = (condition) ? 1 : 0;
      accuracy++;
    }
    accuracy -= 2;
  }
  return accuracy;
}

void correctStep(GtkEntry *entry, double step, int accuracy) {
  char step_text[LEN_VAL] = {0}, format[LEN_FRM] = {0};
  changeFormatStr(format, accuracy);
  sprintf(step_text, format, step);
  gtk_entry_set_text(entry, step_text);
}

void changeFormatStr(char *format, int accuracy) {
  char accuracy_str[7] = {0}, type[3] = "lf";
  accuracy = (accuracy > 7) ? 7 : (accuracy < 0) ? 0 : accuracy;
  sprintf(accuracy_str, "%d", accuracy);
  strcat(accuracy_str, type);
  strcat(format, "%.");
  strncat(format, accuracy_str, 7);
}