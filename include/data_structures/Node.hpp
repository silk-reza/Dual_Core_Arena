//
// Created by Reza on 7/04/2026.
//

#pragma once

// Nodo generico
// Almacena cualquier tipo de dato
template<typename T>
struct Node {
    T data;
    Node <T>* next;

    Node(const T& value) : data(value), next(nullptr) {}
};