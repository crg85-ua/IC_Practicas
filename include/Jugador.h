#ifndef JUGADOR_HXX
#define JUGADOR_HXX

class Jugador
{
private:
    int num;
    int coordX;
    int coordY;
    int estado;

public:
    Jugador();
    Jugador(int num, int coordX, int coordY,int estado);
    Jugador(int num,int estado);
    int getNum() const;
    int getX() const;
    int getY() const;
    void setNum(int num);
    void setX(int coordX);
    void setY(int coordY);
    void moveJugador(int pasos);
    int calcularExp(int exponente);
    int getEstado() const;
    void setEstado(int estado);
};

#endif