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
    return Py_BuildValue("i", g->play(input)); // the return tells which player and which turn is next
}

static PyObject* peek(PyObject *self, PyObject *args)
{
    unsigned int id;
    unsigned long long g_address;
    if (!PyArg_ParseTuple(args, "KI", &g_address, &id))
        return nullptr;
    Card& card = ((Game*)g_address)->query(id);
    return Py_BuildValue("Bb", card.type, card.owner);
}

//static PyObject* fetch (PyObject *self, PyObject *args)
//{
//    unsigned char player;
//    unsigned long long g_address;
//    if (!PyArg_ParseTuple(args, "KB", &g_address, &player))
//        return nullptr;
//    const Game const* g = (Game*)g_address;
//}

static PyObject* debug (PyObject *self, PyObject *args)
{
    unsigned long long g_address;
    if (!PyArg_ParseTuple(args, "K", &g_address))
        return nullptr;
    std::cout << *(Game*)g_address;
    return Py_BuildValue("");
}

static PyObject* end_game (PyObject *self, PyObject *args)
{
    unsigned long long g_address;
    if (!PyArg_ParseTuple(args, "K", &g_address))
        return nullptr;
    delete (Game*)g_address;
    return Py_BuildValue("");
}

static PyMethodDef myMethods[] = {
    {"new_game", new_game, METH_VARARGS, "start a new game. input the seed and output the address."},
    {"play_turn", play_turn, METH_VARARGS, "plays a turn given a address and player input, outputs info about the next player to play."},
    {"peek", peek, METH_VARARGS, "query what the cards are. input the address and id and output the type and owner."},
    {"debug", debug, METH_VARARGS, "print elaborate debug info about the current game state."},
    {"end_game", end_game, METH_VARARGS, "at the end of the game, free up the space. irreversible."},
    {NULL, NULL, 0, NULL}
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
