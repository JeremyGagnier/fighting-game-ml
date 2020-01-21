#include "fighting_game_module.h"

#include "stdio.h"

void* p1_ai;
void* p2_ai;

static PyObject* run(PyObject* self, PyObject* args)
{
    char* p1_type;
    char* p2_type;
    if (((p1_ai == NULL) | (p2_ai == NULL)) || !PyArg_ParseTuple(args, "ss", &p1_type, &p2_type))
    {
        return NULL;
    }
    input_fn* get_p1_input;
    input_fn* get_p2_input;
    if (strcmp(p1_type, "genetic") == 0)
    {
        get_p1_input = &get_genetic_ai_input;
    }
    else
    {
        return NULL;
    }
    if (strcmp(p2_type, "genetic") == 0)
    {
        get_p2_input = &get_genetic_ai_input;
    }
    else
    {
        return NULL;
    }
    game_result result = play_game(p1_ai, p2_ai, *get_p1_input, *get_p2_input);
    PyObject* py_object = Py_BuildValue("s#", (char*)result.states, result.states_length * sizeof(game_state));
    free(result.states);
    return py_object;
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
    Py_ssize_t dna_size;
    const char* str;
    int player_num;
    if (!PyArg_ParseTuple(args, "is#", &player_num, &str, &dna_size))
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
    return Py_BuildValue("");
}

static PyMethodDef fighting_gameModule_methods[] = {
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

PyMODINIT_FUNC initfighting_game(void)
{
    (void)Py_InitModule("fighting_game", fighting_gameModule_methods);
}

int main(int argc, char** argv)
{
    Py_SetProgramName(argv[0]);
    Py_Initialize();
    initfighting_game();
}
