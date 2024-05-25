#include "s21_3DViewer.h"

char *ErrorHandle(errors_e err_e) {
  char *error = "";
  if (err_e == VERTEX_INCORRECT) {
    error = "Неверная вершина модели";
  } else if (err_e == SURFACE_INCORRECT) {
    error = "Неверная поверхность модели";
  } else if (err_e == EMPTY_FILE) {
    error = "Файл не содержит вершин и/или поверхностей";
  } else if (err_e == MAX_IDX) {
    error = "Поверхность ссылается на несуществующую вершину";
  } else if (err_e == MEMORY_NA) {
    error = "Ошибка выделения памяти";
  } else if (err_e == CONFIGFILE_ERR) {
    error = "Ошибка файла настроек";
  }
  return error;
}
