#pragma once

#include "Python.h"

#include "fighting_game.h"

player_input do_nothing(game_state current_state)
{
    return 0;
}

static PyObject* play_game(PyObject* self, PyObject* args)
{
    const int* player_info;
    if (!PyArg_ParseTuple(args, "???", &player_info))
    {
        return NULL;
    }
    game_result result = play_game(do_nothing, do_nothing);
    return Py_BuildValue("???", result);
}

static PyMethodDef SpamMethods[] =
{
    {"system", spam_system, METH_VARARGS, "Execute a shell command."},
    {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC initspam(void)
{
    (void) Py_InitModule("spam", SpamMethods);
}

int main(int argc, char** argv)
{
    Py_SetProgramName(argv[0]);
    Py_Initialize();
    initspam();
}
