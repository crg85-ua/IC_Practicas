#ifndef JUGADOR_HXX
#define JUGADOR_HXX

class Jugador
{
private:
    int num;
    int coordX;
    int coordY;

public:
    Jugador(int num, int coordX, int coordY);
    Jugador(int num);
    int getNum() const;
    int getX() const;
    int getY() const;
    void setNum(int num);
    void setX(int coordX);
    void setY(int coordY);
    void moveJugador(int pasos);
    int calcularExp(int exponente);
};

#endif