    Jugador::Jugador(int num, int coordX, int coordY)
    {
        this->num = num;
        this->coordX = coordX this->coordY = coordY
    }

    Jugador::Jugador(int num)
    {
        this.num = num;
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
        this->coordY += pasos;
    }

    int Jugador::calcularExp(int exponente)
    {
        int resultado = 0;
        if (exponente > 0)
        {
            resultado = (int)pow(3, exponent);
        }
        return resultado;
    }