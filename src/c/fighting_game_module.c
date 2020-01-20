#include "fighting_game.h"

void* p1_ai;
void* p2_ai;

static PyObject* run(PyObject* self, PyObject* args)
{
    char* info;
    if ((p1_ai == NULL | p2_ai == NULL) || !PyArg_ParseTuple(args, "s", &info))
    {
        return NULL;
    }
    if (strcmp(info, "genetic"))
    {
        game_result result = play_game(p1_ai, p2_ai, get_genetic_ai_input, get_genetic_ai_input);
        return Py_BuildValue("s#", result.states, result.states_length);
    }
    return NULL;
}

static PyObject* get_random_genetic_ai(PyObject* self, PyObject* args)
{
    genetic_ai* ai = make_random_genetic_ai();
    PyObject* py_object = Py_BuildValue("s#", ai->dna, NUM_OF_STATES);
    free(ai);
    return py_object;
}

static PyObject* set_genetic_ai(PyObject* self, PyObject* args)
{
    genetic_ai* ai = (genetic_ai*)malloc(sizeof(genetic_ai));
    int dna_length;
    int player_num;
    if (!PyArg_ParseTuple(args, "s#i", &(ai->dna), &dna_length, &player_num))
    {
        return NULL;
    }
    if (player_num == 0)
    {
        p1_ai = ai;
    }
    else
    {
        p2_ai = ai;
    }
    return NULL;
}

static PyMethodDef FightingGameMethods[] = {
    {
        "run",
        run,
        METH_VARARGS,
        "Runs the game with the set AIs."},
    {
        "get_random_genetic_ai",
        get_random_genetic_ai,
        METH_VARARGS,
        "Makes and returns a random genetic AI."},
    {
        "set_genetic_ai",
        set_genetic_ai,
        METH_VARARGS,
        "Sets a genetic AI with given dna and player number."},
    {
        NULL,
        NULL,
        0,
        NULL}};

PyMODINIT_FUNC init_modules()
{
    (void)Py_InitModule("fighting_game", FightingGameMethods);
}

int main(int argc, char** argv)
{
    Py_SetProgramName(argv[0]);
    Py_Initialize();
    init_modules();
}
