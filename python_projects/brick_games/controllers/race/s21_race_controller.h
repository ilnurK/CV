#ifndef S21_RACE_CONTROLLER_C
#define S21_RACE_CONTROLLER_C

#ifdef __cplusplus
extern "C" {
#endif

#include <Python.h>

#ifdef __cplusplus
}
#endif

#include <fstream>
#include <map>
#include <utility>
#include <vector>

#include "../../brick_game/s21_brick_games_directions.h"
#include "../s21_controller.h"

namespace s21 {

enum class RaceStates {
  NULL_STATE = 0,
  START = 1,
  DRIVE = 2,
  CHANGE_LANES = 3,
  OVERTAKE = 4,
  COLLISION = 5,
  GAME_OVER = 6,
  WIN = -1
};

class RaceCController : public Controller<RaceStates> {
 private:
  const char *module_name_ = "s21_race_controller";
  const char *ctrl_cls_name_ = "RaceController";
  const char *dir_cls_name_ = "Directions";

 private:
  int error_{};

 private:
  PyObject *pmodule_;
  PyObject *pctrl_cls_;
  PyObject *pdir_cls_;
  PyObject *pctrl_;

 private:
  PyObject *pname_set_state_;
  PyObject *pname_set_highscore_;
  PyObject *pname_is_filled_cell_;
  PyObject *pname_speed_;

  const char *pname_get_state_;
  const char *pname_field_;
  const char *pname_score_;
  const char *pname_highscore_;
  const char *pname_level_;
  const char *pname_write_hscore_;

 public:
  RaceCController();
  ~RaceCController();

 public:
  RaceStates SetState(const RaceStates &state, const dirs &dir) override;

 public:
  RaceStates GetState() const override;
  Controller::field GetField() const override;
  size_t GetScore() const override;
  size_t GetHighScore() const override;
  size_t GetLevel() const override;
  size_t GetSpeed(size_t delay) const;
  bool IsFilledCell(const char c) const override;

  void SetHighScore(const size_t hscore) override;
  void WriteHighScore() override;

 private:
  PyObject *SetPyState(const RaceStates &state, const dirs &dir);
  PyObject *GetPyDir(const dirs &dir);

  char GetSymbol(PyObject *line, const size_t col) const;
  void InitMethodsNames();
  void DeleteMethodNames();

  PyObject *GetModule(std::string path, const char *module_name);
  PyObject *GetClass(const char *name, PyObject *module);
  PyObject *GetInstance(PyObject *pcls);
};

}  // namespace s21
#endif