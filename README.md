# RSA-KEY-GENERATOR
```
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
```

Lo que hacemos con el algoritmo MILLER RABIN es comprobar con una cantidad de bases si el numero es con mayor probabilidad primo, siendo de esta manera no necesario que se calcule con todas las bases.

La lista de los numeros primos de 3 cifras son:
101	103	107	109	113	127	131	137	139	149	151	157	163
167	173	179	181	191	193	197	199	211	223	227	229	233	239	241	251	257	263	269
271	277	281	283	293	307	311	313	317	331	337	347	349	353	359	367	373	379	383
389	397	401	409	419	421	431	433	439	443	449	457	461	463	467	479	487	491	499
503	509	521	523	541	547	557	563	569	571	577	587	593	599	601	607	613	617	619
631	641	643	647	653	659	661	673	677	683	691	701	709	719	727	733	739	743	751
757	761	769	773	787	797	809	811	821	823	827	829	839	853	857	859	863	877	881
883	887	907	911	919	929	937	941	947	953	967	971	977	983	991	997

El valor apropiado para S es 128.


```
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
```

En este algoritmo lo que se busca es que a travez del la prueba de Miller Rabin, nosotros podamos enviar numeros no especificos, sino por una cantidad de bits, lo cual nos ayuda en la criptografia primero convirtiendo el numero enviado a bits y luego filtrandolo para que sea impar consiguiendo de esa forma tanto una permutacion como una prueba para el diseño de un campo mas grande de posibles candidatos a ser la clave para nuestro RSA

el valor apropiado para el parametro s= 128
