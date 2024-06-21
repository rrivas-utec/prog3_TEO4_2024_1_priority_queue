#include <iostream>
#include <queue>
#include <functional>

void ejemplo_1 () {
    std::priority_queue<int, std::vector<int>, std::less<>> pq;
    pq.push(10);
    pq.push(5);
    pq.push(20);
    pq.push(3);
    pq.push(25);
    pq.push(4);
    // O(n log n)
    std::cout << pq.top();
}

void ejemplo_2() {

    std::priority_queue<int> pq;  // O(1)
    std::vector<int> v = {10, 5, 20, 3, 25, 4};
    std::priority_queue<int, std::vector<int>, std::greater<>> pq1(std::greater<>(), v); // O(n)
    std::cout << pq1.top();
}

// Template de Clase Generico
template <typename T = void>
struct mayor_que {
    bool operator() (const T& a, const T& b) const { // Sobrecarga al operador ()
        return a > b;
    }
};

// Especializacion Total del template de Clases
template <>
struct mayor_que<void> {
    template <typename T>
    bool operator () (const T& a, const T& b) const {
        return a > b;
    }
};

// Funciones Objetos

template <typename T = void>
struct menor_que {
    bool operator() (const T& a, const T& b) const { // Sobrecarga al operador ()
        return a < b;
    }
};

// Especializacion Total del template de Clases
template <>
struct menor_que<void> {
    template <typename T>
    bool operator () (const T& a, const T& b) const {
        return a < b;
    }
};

void ejemplo_3() {
    std::priority_queue<int> pq;  // O(1)
    std::vector<int> v = {10, 5, 20, 3, 25, 4};
    std::priority_queue<int, std::vector<int>, menor_que<>> pq1(menor_que<>(), v); // O(n)
    std::cout << pq1.top();
}

void ejemplo_4() {
    std::priority_queue<int> pq;  // O(1)
    std::deque<int> d = {10, 5, 20, 3, 25, 4};
    std::priority_queue<int, std::vector<int>, menor_que<>> pq1(d.begin(), d.end(), menor_que<>()); // O(n)
    std::cout << pq1.top();
}

class Persona {
    std::string nombre;
    int edad = 0;
public:
    Persona() = default;
    Persona(std::string nombre, int edad): nombre(std::move(nombre)), edad(edad) {}
    [[nodiscard]] std::string get_nombre() const {return nombre; }
    [[nodiscard]] int get_edad() const { return edad; }
    bool operator < (const Persona& other) const {
        return edad < other.edad;
    }
    friend std::ostream& operator << (std::ostream& os, const Persona& p) {
        os << p.nombre << " " << p.edad;
        return os;
    }
};

void ejemplo_5() {
    std::vector<Persona> v = { {"Jose", 50}, {"Maria", 19}, {"Alfredo", 30},
                               {"Zaira", 10}};

    std::priority_queue<Persona, std::vector<Persona>, std::less<>> pq(std::less<>(), v);
    std::cout << pq.top();
}

void ejemplo_6() {
    std::vector<Persona> v = { {"Jose", 50}, {"Maria", 19}, {"Alfredo", 30},
                               {"Zaira", 10}};

    auto comparador_nombre_mayor_que = [](auto a, auto b) { return a.get_nombre() > b.get_nombre(); };
    auto comparador_nombre_menor_que = [](auto a, auto b) { return a.get_nombre() < b.get_nombre(); };
    auto comparador_edad_menor_que = [](auto a, auto b) { return a.get_edad() < b.get_edad(); };

    std::priority_queue<Persona,
                        std::vector<Persona>,
                                decltype(comparador_nombre_mayor_que)>
                                pq(comparador_nombre_mayor_que, v);
    std::cout << pq.top();
}

void ejemplo_7() {
    std::vector<Persona> v = { {"Jose", 50}, {"Maria", 19}, {"Alfredo", 30},
                               {"Zaira", 10}};

    auto comparador_nombre_mayor_que = [](auto a, auto b) { return a.get_nombre() > b.get_nombre(); };
    auto comparador_nombre_menor_que = [](auto a, auto b) { return a.get_nombre() < b.get_nombre(); };
    auto comparador_edad_menor_que = [](auto a, auto b) { return a.get_edad() < b.get_edad(); };

    std::priority_queue<Persona,
            std::vector<Persona>,
            std::function<bool(Persona, Persona)>>
            pq(comparador_edad_menor_que, v);
    std::cout << pq.top();
}

int main() {
//    ejemplo_1();
//    ejemplo_2();
//    ejemplo_3();
//    ejemplo_4();
//    ejemplo_5();
//    ejemplo_6();
    ejemplo_7();
    return 0;
}
