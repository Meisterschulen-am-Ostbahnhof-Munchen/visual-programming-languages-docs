### E\_CTUD

Event-Driven Up-Down Counter

Der Funktionsblock E\_CTUD (Counter Up/Down) ist ein wichtiger Bestandteil der IEC 61499 Norm und wird häufig in Steuerungssystemen verwendet. Er dient dazu, Zählerwerte zu erhöhen oder zu verringern und kann in vielen verschiedenen Anwendungen eingesetzt werden.

Der E\_CTUD Funktionsblock besteht aus mehreren Eingängen und Ausgängen, die für die Steuerung und Überwachung des Zählerwerts verwendet werden. Der wichtigste Eingang ist der "CU" Eingang, der verwendet wird, um den Zählerwert zu erhöhen oder zu verringern. Der "RESET" Eingang dient zum Zurücksetzen des Zählerwerts auf null, während der "LOAD" Eingang verwendet wird, um den Zählerwert auf einen festgelegten Wert zu laden.

Der E\_CTUD Funktionsblock hat auch mehrere Ausgänge, die für die Überwachung des Zählerwerts und die Steuerung von Prozessen verwendet werden.

![](https://user-images.githubusercontent.com/113907528/204895474-3f88876a-7ce5-406e-8f44-765c1b97226c.png)

*   Input
    *   CU Count Up 
    *   CD Count Down
    *   R Reset
    *   LD Load
    *   PV Preset Value
*   Output
    *   CO Count Output Event
    *   RO Reset Output Event
    *   QU CV   >= PV
    *   QD CV  \<= 0
