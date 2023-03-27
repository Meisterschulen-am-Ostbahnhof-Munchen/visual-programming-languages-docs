### E\_SR = (Holzspalter Schalter)

:::{tip}
In der IEC 61131-3 wird noch noch zwischen SR(vorrangiges Setzen) und RS(vorrangiges Rücksetzen) unterschieden, in der IEC 61499-1 nicht mehr. Das bedeutet RS und SR haben die gleiche Funktion nur die Anschlüsse Imput S und R sind vertauscht
:::

Event-driven bistable

Der Funktionsblock E\_SR (Set-Reset) ist ein wichtiger Bestandteil der IEC 61499 Norm und wird häufig in Steuerungssystemen verwendet. Er dient dazu, eine bestimmte Aktion auszulösen, wenn eine bestimmte Bedingung erfüllt ist.

Der Funktionsblock E\_SR besteht aus zwei Eingängen und einem Ausgang. Der erste Eingang (S) dient dazu, die Aktion auszulösen, während der zweite Eingang (R) dazu dient, die Aktion zurückzusetzen. Der Ausgang des Funktionsblocks gibt an, ob die Aktion ausgelöst wurde oder nicht.

![](https://user-images.githubusercontent.com/113907528/204904299-a6a3580a-42b4-4ea9-80c9-52b38b2d002b.png)

*   Input
    *   S Set output Q
    *   R Reset output Q
*   Output
    *   EO Output Q has changed

![](https://agro-center.de/out/pictures/master/product/1/ETZXXX961020_1.jpg)

https://agro-center.de/schalter-fuer-holzspaltermotor-etzxxx961020.html

*   Ein Schalter = Einschalten
*   Aus Schalter = Ausschalten

Siehe auch: \[https://www.holobloc.com/doc/fb/rt/events/E_SR.htm](https://www.holobloc.com/doc/fb/rt/events/E_SR.htm)
