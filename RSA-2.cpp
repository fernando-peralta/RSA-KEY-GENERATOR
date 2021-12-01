#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <vector>

using namespace std;


long long int resto(long long int a, long long int n) { //funcion resto recibe a (dividendo) y n )(divisor)
    long long int r; // Las dos salidas a entregar en la division: q (cociente) y r (resto)
    if (a < 0) {//en caso a sea negativo
        r = a - (((a / n) - 1) * n); //realizamos la operacion original del resto pero se le aumenta 1 al cociente para exceder y obtener el resto positivo.
        return r; //basicamente es siguiendo la logica de Galo
    }
    else {// En caso a sea positivo
        r = a - ((a / n) * n);// simplemente la diferencia entre a y la multiplicacion
        return r;
    }
}



long long int exponenciacion(long long int b, long long int e) {
    long long int result = 1;
    while (e > 0) {
        if (e % 2) {
            result = result * b;
        }
        b = (b * b);
        e /= 2;
    }

    return result;
}

        
bool witness(long long int  a, long long int n, long long int t, long long int u) {
    vector<long long int> g1;
    if (g1[0] == 1 || g1[0] == n - 1) {
        return false;
    }
    else {
        for (long long int i = 1; i < t; i++) {
            g1[i] = resto(exponenciacion(g1[i - 1], 2), n);
            if (g1[i] == (n - 1)) {
                return false;
            };
        }
    }return true;
}


bool MILLER_RABIN(long long int n, long long s) {
    long long int u = n - 1; long long int t = 0;
    // n-1 = u*2^t
    while (!(u & 1)) u >>= 1, t++;
    for (long long int j = 1; j < s; j++) {
        //e = 2 + rand() % (n - 2);
        long long int a = 1 + resto(rand(), ((n - 1) - 1));
        if (witness(a, n,t,u)) {
            return true;
        }
    }

    return false;
}

long long int RAMDOM_INT_BITS(long long int b) {
    return (exponenciacion(2, (b - 1)) + 1) + resto(rand(), (exponenciacion(2, (b - 1)) - (exponenciacion(2, (b - 1)) + 1)));
}


long long int GENERATE_PRIME_CANDIDATE(long long int b){
    long long int n = RAMDOM_INT_BITS(b);
    long long int m = exponenciacion(2, b - 1)+1;
    n = n | m;
    return n;
}

long long int GENERATE_PRIME(long long int b) {
    long long int s = 128;
    long long int n = GENERATE_PRIME_CANDIDATE(b);
    cout << "SEÑAL 4" << endl;
    cout << n << endl;
    while (MILLER_RABIN(n, s)) {
        cout << n << endl;
        n = n + 2;
    }
    cout << n << endl;
    return n;
}



long long int Euclides_extendido(long long int a, long long int b, long long int* d, long long int* x, long long int* y) {
    long long int x1, y1;//variables auxiliares para el desarrollo del algoritmo

    if (a % b == 0) {//Caso base o final de Euclides normal
        *d = b;//Sabemos cual es el gcd(a,b)
        *x = 0;//Valores para el caso base
        *y = 1;
    }
    else {//En caso aun no se encuentre un b que cumpla la condicion (un gcd)
        Euclides_extendido(b, a % b, d, x, y);//Aplicamos recursividad con la teoria vista en clase
        x1 = *x; y1 = *y; *x = y1;//Los valores x1 y y1 los guardamos para el calculo de y mientras el valor de x pasa a ser el almacenado en y1
        *y = x1 - (a / b) * y1;//Calculamos y con la formula vista en clase donde (a/b) es q y y1
    }

    return *d;
}

long long int inversa(long long int e, long long int N) {
    long long int d, x, y;

    long long int inversa = Euclides_extendido(e, N, &d, &x, &y);
    if (inversa == 1) {
        return resto(x, N);
    }
    else {
        return 0;
    }
}

long long int euc(long long int x, long long int y) {
    return (!y) ? x : euc(y, x % y);
}

void RSA_KEY_GENERATOR(long long int b, long long int *n_result, long long int *e_result, long long int *d_result) {
    int expo[5] = { 3, 5, 17, 257, 65537 };
    cout << "SEÑAL 1" << endl;
    long long int e = expo[resto(rand(), 4)];
    cout << "SEÑAL 2" << endl;
    long long int p = GENERATE_PRIME(b / 2);
    cout << "SEÑAL 3" << endl;
    long long int q = GENERATE_PRIME(b / 2);
    long long int n = p * q;
    long long int phi_n = (p - 1) * (q - 1);
    long long int d = inversa(e, phi_n);
    //return { n,e,d };
    *n_result = n;
    *e_result = e;
    *d_result = d;
}




int main() {
    srand(time(NULL));
    long long int n;
    long long int e;
    long long int d;

    RSA_KEY_GENERATOR(10,&n,&e,&d);

    cout << "n: " << n<<endl;
    cout << "e:" << e << endl;
    cout << "d" << d << endl;
   
}