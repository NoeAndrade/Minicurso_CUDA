# ¿Qué es programación en paralelo?

> Programar para multiples computadoras o computadoras con multiples procesadores internos, de manera que se puedan resolver problemas más rapido comparado con una sola computadora.

## Propuesta:
Tomar un problema de gran escala y dividirlo en P partes iguales de manera que P computadoras se encarguen de resolver los subproblemas.


### Factor de aceleración (speedup)
Sean p el número de procesadores:

$$S(p)=\frac{\textrm{tiempo de ejecución del mejor programa serial}}{\textrm{tiempo de ejecución utilizando los p procesadores} }=\frac{t_s}{t_p}$$


### Ley de Amdahl
$$S(p)=\frac{1}{1-p}$$

En resumen:
> La mejora del rendimiento del programa, debida a la optimización de una fracción de este, está limitado a al tiempo durante el cual la parte que no es paralelizable es ejecutada.

Ejemplo:

Sin considerar cuantos procesadores tenemos supongamos que podemos paralelizar un 80% del programa, entonces el factor de aceleración es de:

$$S(0.8)=\frac{1}{1-0.8}=1/0.2=5$$

Es decir el programa solo puede ser 5 veces más rapido

Si se puede paralelizar un 97% del programa el factor de aceleración es 1/0.03 que es 33 veces mas rápido

Considerando el ejemplo en wikipedia:
> Si un programa tarda 20 hrs y de un proceso que toma 1 hora no se puede acelerar entonces a lo mucho la aceleración es de 20/1 = 20 veces

Donde la porción del programa que fue optimizado fue de 

$$ \frac{20-1}{20}*100\\% =95\\% $$

### Problema:
Problemas no realistas. Comunicación requerida entre computadoras, los subproblemas no son iguales entre si por lo que hay momentos donde procesadores siguen trabajando mientras otros se mantienen inactivos, lo cual tiene que ser considarado en el calculo del _speedup_, esto se toma en cuenta en la _ley de Gunther_ o _Ley universal de escalamiento_.
