# PMI 2

**fecha de entrega:** Lunes 19 / 10 / 2026 a las 12 hs (semana que viene)

## consideraciones para rebalse
Se utilizará una ranura por balde en cada Rebalse. (**r=1**)

El número estimado de electores en el archivo es de 2000. (**N=2000 electores**)

### funcion de hashing
```
    int hashing(int dni, int M){
        char x[10];
        int longitud, i;
        int contador = 0;
        sprintf(x, "%d", dni);
        longitud = strlen(x);
        for( i=0; i<longitud; i++){
            contador+=((int)x[i]) * (i+1);
        }
        return (contador % M);
    }
```

## objetivos
- [ ] eliminar `ABB.h` `LSOBB.h` `LVO.h`
- [x] crear `RAC.h` con ρ=0.83
    - => ρ = N/Mr
        - -> M = N/ρ = 2000/0.83 = 2409.638...
        - aproximadamente M = 2410
        - ! PERO, se usa 2411 xq es un numero primo
        - x eso dice "calcular bien el M"
    - [ ] checkear los codigos
- [ ] crear `RAL.h` con ρ=0.79
    - => ρ = N/Mr
        - -> M = N/ρ = 2000/0.79 = 2531.645...
        - aproximadamente M = 2532
        - numero primo cercano: 2531
        - ! en RALineal no hace falta buscar un numero primo
        - es necesario usarlo cuando el paso `k` no es `+-1`
- [ ] crear `RS.h` con ρ = 1.61
    - => ρ = N/Mr
        - -> M = N/ρ = 2000/1.61 = 1242.236....
        - numero primo cercano: 1237, 1249
        - aproximadamente M = 1242
- [ ] crear `hashing.h`