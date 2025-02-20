#include "s21_race_controller.h"

#include <filesystem>
#include <iostream>
#include <string>

namespace s21 {

RaceCController::RaceCController() {
  Py_Initialize();
  std::string file_path = __FILE__;
  std::filesystem::path p(file_path);
  std::filesystem::path dir = p.parent_path();
  pmodule_ = GetModule(dir.c_str(), module_name_);
  pctrl_cls_ = GetClass(ctrl_cls_name_, pmodule_);
  pdir_cls_ = GetClass(dir_cls_name_, pmodule_);
  pctrl_ = GetInstance(pctrl_cls_);
  InitMethodsNames();
}

PyObject *RaceCController::GetModule(std::string path,
                                     const char *module_name) {
  PyRun_SimpleString("import sys");
  std::string add_start = "sys.path.append('";
  std::string add_end = "')";
  std::string total_add = add_start + path + add_end;
  PyRun_SimpleString(total_add.c_str());
  PyObject *pmodule = PyImport_ImportModule(module_name);
  if (pmodule == NULL) {
    throw std::runtime_error(__PRETTY_FUNCTION__);
  }
  return pmodule;
}

PyObject *RaceCController::GetClass(const char *name, PyObject *module) {
  PyObject *class_name = PyObject_GetAttrString(module, name);
  if (class_name == NULL || !PyCallable_Check(class_name)) {
    throw std::runtime_error(__PRETTY_FUNCTION__);
  }
  return class_name;
}

PyObject *RaceCController::GetInstance(PyObject *pcls) {
  PyObject *pinst = PyObject_CallObject(pcls, NULL);
  if (pinst == NULL) {
    if (PyErr_Occurred()) {
      PyErr_Print();
    }
    throw std::runtime_error(__PRETTY_FUNCTION__);
  }
  return pinst;
}

RaceStates RaceCController::SetState(const RaceStates &state, const dirs &dir) {
  PyObject *pstate = SetPyState(state, dir);
  RaceStates state_out{};
  if (pstate != NULL) {
    state_out = static_cast<RaceStates>(PyLong_AsLong(pstate));
    if (PyErr_Occurred()) {
      throw std::runtime_error(__PRETTY_FUNCTION__);
    }
    Py_XDECREF(pstate);
  } else {
    throw std::runtime_error(__PRETTY_FUNCTION__);
  }
  return state_out;
}

PyObject *RaceCController::SetPyState(const RaceStates &state,
                                      const dirs &dir) {
  PyObject *pstate_out = NULL;

  PyObject *pstate = PyLong_FromLong(static_cast<long>(state));
  PyObject *pdir = GetPyDir(dir);

  pstate_out =
      PyObject_CallMethodObjArgs(pctrl_, pname_set_state_, pstate, pdir, NULL);
  Py_XDECREF(pdir);
  Py_XDECREF(pstate);

  return pstate_out;
}

PyObject *RaceCController::GetPyDir(const dirs &dir) {
  PyObject *value = PyLong_FromLong(static_cast<int>(dir));
  PyObject *pdir = PyObject_CallMethod(pdir_cls_, "__call__", "O", value);
  if (!pdir) {
    throw std::runtime_error(__PRETTY_FUNCTION__);
  }
  Py_XDECREF(value);
  return pdir;
}

RaceStates RaceCController::GetState() const {
  RaceStates state{};
  PyObject *pstate = PyObject_CallMethod(pctrl_, pname_get_state_, NULL);
  if (pstate == NULL) {
    throw std::runtime_error(__PRETTY_FUNCTION__);
  } else {
    state = static_cast<RaceStates>(PyLong_AsLong(pstate));
    Py_XDECREF(pstate);
  }
  return state;
}

RaceCController::field RaceCController::GetField() const {
  Controller::field fd{};
  PyObject *pfield = PyObject_CallMethod(pctrl_, pname_field_, NULL);
  if (pfield == NULL) {
    throw std::runtime_error(__PRETTY_FUNCTION__);
  }
  Py_ssize_t height{Controller::field_height}, width{Controller::field_width};
  for (Py_ssize_t row{}; row < height && !error_; ++row) {
    PyObject *line = PyList_GetItem(pfield, row);
    if (PyList_Check(line)) {
      for (Py_ssize_t col{}; col < width && !error_; ++col) {
        fd[row * width + col] = GetSymbol(line, col);
      }
    } else {
      throw std::runtime_error(__PRETTY_FUNCTION__);
    }
  }
  Py_XDECREF(pfield);
  return fd;
}

char RaceCController::GetSymbol(PyObject *line, const size_t col) const {
  char c{};
  PyObject *item = PyList_GetItem(line, col);
  if (PyUnicode_Check(item)) {
    c = PyUnicode_AsUTF8(item)[0];
  } else {
    throw std::runtime_error(__PRETTY_FUNCTION__);
  }
  return c;
}

size_t RaceCController::GetScore() const {
  size_t score{};
  PyObject *pscore = PyObject_CallMethod(pctrl_, pname_score_, NULL);

  if (pscore == NULL) {
    throw std::runtime_error(__PRETTY_FUNCTION__);
  } else {
    score = static_cast<size_t>(PyLong_AsLong(pscore));
    Py_XDECREF(pscore);
  }
  return score;
}

size_t RaceCController::GetHighScore() const {
  size_t highscore{};
  PyObject *phighscore = PyObject_CallMethod(pctrl_, pname_highscore_, NULL);

  if (phighscore == NULL) {
    throw std::runtime_error(__PRETTY_FUNCTION__);
  } else {
    highscore = static_cast<size_t>(PyLong_AsLong(phighscore));
    Py_XDECREF(phighscore);
  }
  return highscore;
}

void RaceCController::SetHighScore(const size_t hscore) {
  PyObject *pvalue = PyLong_FromLong(hscore);
  PyObject_CallMethodObjArgs(pctrl_, pname_set_highscore_, pvalue, NULL);
}

size_t RaceCController::GetLevel() const {
  size_t level{};
  PyObject *plevel = PyObject_CallMethod(pctrl_, pname_level_, NULL);
  if (!plevel) {
    throw std::runtime_error(__PRETTY_FUNCTION__);
  } else {
    level = static_cast<size_t>(PyLong_AsLong(plevel));
    Py_XDECREF(plevel);
  }
  return level;
}

size_t RaceCController::GetSpeed(size_t delay) const {
  size_t speed{};
  PyObject *pdelay = PyLong_FromLong(delay);
  PyObject *pspeed =
      PyObject_CallMethodObjArgs(pctrl_, pname_speed_, pdelay, NULL);
  if (!pspeed) {
    throw std::runtime_error(__PRETTY_FUNCTION__);
  } else {
    speed = static_cast<size_t>(PyLong_AsLong(pspeed));
    Py_XDECREF(pspeed);
  }
  return speed;
}

void RaceCController::InitMethodsNames() {
  pname_set_state_ = PyUnicode_FromString("set_state");
  pname_set_highscore_ = PyUnicode_FromString("set_highscore");
  pname_is_filled_cell_ = PyUnicode_FromString("is_filled_cell");
  pname_speed_ = PyUnicode_FromString("get_speed");

  pname_get_state_ = "get_state";
  pname_field_ = "get_field";
  pname_score_ = "get_score";
  pname_highscore_ = "get_highscore";
  pname_level_ = "get_level";
  pname_write_hscore_ = "write_highscore";
}

void RaceCController::WriteHighScore() {
  PyObject_CallMethod(pctrl_, pname_write_hscore_, NULL);
}

bool RaceCController::IsFilledCell(const char c) const {
  const char cell[2] = {c, '\0'};
  PyObject *pvalue = PyUnicode_FromString(cell);
  PyObject *pfilled =
      PyObject_CallMethodObjArgs(pctrl_, pname_is_filled_cell_, pvalue, NULL);
  if (!pfilled) {
    throw std::runtime_error(__PRETTY_FUNCTION__);
  }
  bool is_filled = PyObject_IsTrue(pfilled);
  return is_filled;
}

void RaceCController::DeleteMethodNames() {
  Py_XDECREF(pname_set_state_);
  Py_XDECREF(pname_set_highscore_);
  Py_XDECREF(pname_is_filled_cell_);
  Py_XDECREF(pname_speed_);
}

RaceCController::~RaceCController() {
  Py_XDECREF(pctrl_);
  Py_XDECREF(pctrl_cls_);
  Py_XDECREF(pdir_cls_);
  Py_XDECREF(pmodule_);
  DeleteMethodNames();
  Py_Finalize();
}

}  // namespace s21