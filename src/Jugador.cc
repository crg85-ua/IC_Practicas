#include "Jugador.h"

#include <cmath>

Jugador::Jugador()
{
    this->num = 0;
    this->coordX = 0;
    this->coordY = 0;
    this->estado = 0;
}

Jugador::Jugador(int num, int coordX, int coordY, int estado)
{
    this->num = num;
    this->coordX = coordX;
    this->coordY = coordY;
    this->estado = estado;
}

Jugador::Jugador(int num, int estado)
{
    this->num = num;
    this->estado = estado;
}

int Jugador::getNum() const
{
    return this->num;
}

int Jugador::getX() const
{
    return this->coordX;
}

int Jugador::getY() const
{
    return this->coordY;
}

void Jugador::setNum(int num)
{
    this->num = num;
}

void Jugador::setX(int coordX)
{
    this->coordX = coordX;
}

void Jugador::setY(int coordY)
{
    this->coordY = coordY;
}

void Jugador::moveJugador(int pasos)
{
    this->coordX += pasos;
}

int Jugador::calcularExp(int exponent)
{
    int resultado = 0;
    if (exponent > 0)
    {
        resultado = (int)pow(3, exponent);
    }
    return resultado;
}

int Jugador::getEstado() const
{
    return this->estado;
}

void Jugador::setEstado(int estado)
{
    this->estado = estado;
}