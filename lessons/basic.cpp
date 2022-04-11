
#include <Python.h>

// https://api.binance.com/api/v3/ticker/price?symbol=BTCRUB

int main() {
    Py_Initialize();
    PyRun_SimpleString("from requests import get\n"
                       "print(get('https://api.binance.com/api/v3/ticker/price?symbol=BTCRUB').json())\n");
    Py_Finalize();
}