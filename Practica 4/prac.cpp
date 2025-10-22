#include <iostream>
#include <cmath>
#include <limits>
#include <string>

using namespace std;

class Point {
private:
    double x_, y_;

public:
    Point() : x_(0.0), y_(0.0) {}
    Point(double x, double y) : x_(x), y_(y) {}

    double x() const { return x_; }
    double y() const { return y_; }

    double norm() const { return sqrt(x_*x_ + y_*y_); }

    Point operator+(const Point& r) const { return Point(x_ + r.x_, y_ + r.y_); }
    Point operator-(const Point& r) const { return Point(x_ - r.x_, y_ - r.y_); }
    Point operator*(double s) const { return Point(x_ * s, y_ * s); }

    bool operator==(const Point& r) const {
        return x_ == r.x_ && y_ == r.y_;
    }
    bool operator!=(const Point& r) const { return !(*this == r); }

    friend ostream& operator<<(ostream& os, const Point& p);
    friend double distance(const Point& a, const Point& b);
    friend double pPunto(const Point& a, const Point& b);
    friend Point operator*(double s, const Point& p);
};

ostream& operator<<(ostream& os, const Point& p) {
    os << "(" << p.x_ << ", " << p.y_ << ")";
    return os;
}

double distance(const Point& a, const Point& b) {
    const double dx = a.x_ - b.x_;
    const double dy = a.y_ - b.y_;
    auto sq = [](double u) { return u * u; };
    return sqrt(sq(dx) + sq(dy));
}

double pPunto(const Point& a, const Point& b) {
    return a.x_ * b.x_ + a.y_ * b.y_;
}

Point operator*(double s, const Point& p) {
    return Point(p.x_ * s, p.y_ * s);
}

inline Point midpoint(const Point& a, const Point& b) {
    return (a + b) * 0.5;
}

inline Point sum(const Point& a, const Point& b) {
    return a + b;
}

void leerPunto(Point& p, const string& nombre) {
    double x, y;
    while (true) {
        cout << "Ingrese " << nombre << " como: x y  -> ";
        if (cin >> x >> y) {
            p = Point(x, y);
            return;
        }
        cout << "Entrada invalida. Intente de nuevo.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void mostrarMenu() {
    cout << "\n=== MENU ===\n"
         << "1) Mostrar P y Q\n"
         << "2) Distancia entre P y Q\n"
         << "3) Punto medio de P y Q\n"
         << "4) Suma P + Q\n"
         << "5) Resta P - Q\n"
         << "6) Producto punto P . Q\n"
         << "7) P == Q ?\n"
         << "8) Actualizar valores de P y Q\n"
         << "9) Ejemplo de Covarianza y Contravarianza\n"
         << "0) Salir\n"
         << "Seleccione: ";
}

// Clases para Covarianza y Contravarianza

class Figura {
public:
    virtual Figura* crear() {
        cout << "Creando una Figura base\n";
        return new Figura();
    }
    virtual ~Figura() {}
};

class Circulo : public Figura {
public:
    // Covarianza: el tipo de retorno cambia a una subclase (Circulo*)
    Circulo* crear() override {
        cout << "Creando un Circulo (subtipo de Figura)\n";
        return new Circulo();
    }
};

// Contravarianza conceptual: función que acepta tipos generales
template<typename T>
void mostrarFigura(T* fig) {
    cout << "Mostrando figura genérica.\n";
}

// Main

int main() {
    cout << "Programa: Operaciones con dos puntos en el plano\n\n";

    Point P, Q;
    leerPunto(P, "P");
    leerPunto(Q, "Q");

    for (;;) {
        mostrarMenu();
        char op;
        if (!(cin >> op)) break;

        switch (op) {
            case '1': {
                cout << "P = " << P << "   Q = " << Q << "\n";
            } break;

            case '2': {
                cout << "Distancia(P, Q) = " << distance(P, Q) << "\n";
            } break;

            case '3': {
                Point m = midpoint(P, Q);
                cout << "Punto medio = " << m << "\n";
            } break;

            case '4': {
                cout << "P + Q = " << sum(P, Q) << "\n";
            } break;

            case '5': {
                cout << "P - Q = " << (P - Q) << "\n";
            } break;

            case '6': {
                cout << "P . Q = " << pPunto(P, Q) << "\n";
            } break;

            case '7': {
                cout << (P == Q ? "P y Q son iguales."
                                : "P y Q NO son iguales.") << "\n";
            } break;

            case '8': {
                leerPunto(P, "P");
                leerPunto(Q, "Q");
            } break;

            case '9': {
                cout << "\n=== Ejemplo de Covarianza y Contravarianza ===\n";

                Figura* f = new Figura();
                Circulo* c = new Circulo();

                // Covarianza: el método crear() en Circulo retorna Circulo*
                Figura* f2 = c->crear();

                // Contravarianza: función genérica acepta ambos tipos
                mostrarFigura(f);
                mostrarFigura(c);

                delete f;
                delete f2;
                delete c;
            } break;

            case '0':
                cout << "Adios.\n";
                return 0;

            default:
                cout << "Opcion invalida.\n";
        }
    }
    return 0;
}

