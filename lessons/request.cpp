#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <iostream>

int main()
{
    std::string currencies_pair;
    std::cout << "Input the pair of currencies: " << std::endl;
    std::cin >> currencies_pair;

    PyObject *pName, *pModule, *pFunc;
    PyObject *pArgs, *pValue;

    Py_Initialize();
    // Каст С-строки в Python-строку
    pName = PyUnicode_DecodeFSDefault("request");

    // Импортируем файлик request.py
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        // Получение функции из модуля, который мы импортировали
        pFunc = PyObject_GetAttrString(pModule, "price");

        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(1);
            for (int i = 0; i < 1; ++i) {
                pValue = PyUnicode_DecodeFSDefault(currencies_pair.c_str());
                if (!pValue) {
                    Py_DECREF(pArgs);
                    Py_DECREF(pModule);
                    fprintf(stderr, "Cannot convert argument\n");
                    return 1;
                }
                PyTuple_SetItem(pArgs, i, pValue);
            }
            pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);
            if (pValue != NULL) {
                printf("Price: %f\n", PyFloat_AsDouble(pValue));
                Py_DECREF(pValue);
            }
            else {
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                PyErr_Print();
                std::cerr << "Call failed" << std::endl;
                return 1;
            }
        }
        else {
            if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find function");
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    }
    else {
        PyErr_Print();
        std::cerr << "Failed to load module :(";
        return 1;
    }
    Py_Finalize();
    return 0;
}