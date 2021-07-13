#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "server.hpp"


static PyObject* new_game (PyObject *self, PyObject *args)
{
    unsigned long long seed;
    if (!PyArg_ParseTuple(args, "K", &seed))
        return nullptr;
    Game *g = new Game(seed);
    return Py_BuildValue("K", (unsigned long long)g);
}

static PyObject* play_turn (PyObject *self, PyObject *args)
{
    unsigned char input[16];
    unsigned long long g_address;
    if (!PyArg_ParseTuple(args, "Kz", &g_address, input))
        return nullptr;
    Game *g = (Game*)g_address;
    g->play(input);
    return Py_BuildValue("bb", g->get_turn(), g->get_int_turn());
}

static PyObject* peek(PyObject *self, PyObject *args)
{
    unsigned int id;
    unsigned long long g_address;
    if (!PyArg_ParseTuple(args, "Ku", &g_address, &id))
        return nullptr;
    if (((std::unordered_map<unsigned int, Card>*)g_address)->find(id) != ((std::unordered_map<unsigned int, Card>*)g_address)->end())
    {
        Card &c = ((std::unordered_map<unsigned int, Card> *) g_address)->at(id);
        return
    }
}

static PyObject* fetch (PyObject *self, PyObject *args)
{
    unsigned char player;
    unsigned long long g_address;
    if (!PyArg_ParseTuple(args, "Kb", &g_address, &player))
        return nullptr;
    const Game const* g = (Game*)g_address;
}

static PyObject* debug (PyObject *self, PyObject *args)
{
    unsigned long long g_address;
    if (!PyArg_ParseTuple(args, "K", &g_address))
        return nullptr;
    std::cout << *(Game*)g_address;
}

static PyObject* end_game (PyObject *self, PyObject *args)
{
    unsigned long long g_address;
    if (!PyArg_ParseTuple(args, "K", &g_address))
        return nullptr;
    delete (Game*)g_address;
}

static PyMethodDef myMethods[] = {
    {}
};

static struct PyModuleDef myModule = {
    PyModuleDef_HEAD_INIT,
    "bearsvbabies",
    "bears versus babies game",
    -1,
    myMethods

};

PyMODINIT_FUNC PyInit_bearsvbabies(void)
{
    return PyModule_Create(&myModule);
}