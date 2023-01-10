### E\_D\_FF

Data latch (d) flip flop

Ein Datenlatch ist eine Schaltung in der Elektronik, die es ermöglicht, ein Datensignal zu speichern. Es besteht aus zwei Hauptkomponenten: einem Flip-Flop und zwei Eingängen, die als "D" und "CLK" bezeichnet werden. Der Eingang "D" steht für das Datensignal, das gespeichert werden soll, während der Eingang "CLK" ein Taktsignal darstellt, das angibt, wann das Datensignal gespeichert werden soll.

Wenn das Flip-Flop aktiviert wird, speichert es den Wert des Eingangs "D" und hält ihn fest, bis es erneut aktiviert wird. Dies geschieht, indem das Flip-Flop auf das Taktsignal "CLK" reagiert und den Wert des Eingangs "D" speichert, wenn das Taktsignal einen vorbestimmten Zustand erreicht.

Das Datenlatch wird häufig in Schaltungen verwendet, die Daten zwischen verschiedenen Komponenten übertragen, um sicherzustellen, dass die Daten zum richtigen Zeitpunkt verfügbar sind. Es kann auch verwendet werden, um den Zustand eines Systems zu speichern, z.B. um die Eingabe eines Benutzers zu speichern, während andere Operationen ausgeführt werden.

![](https://user-images.githubusercontent.com/113907528/204898130-f9f31fd9-da42-4b29-a664-add0d91e8890.png)

*   Input
    *   CLK Clock 
    *   D Value to latch
*   Output
    *   EO Triggered if clock results in a change of Q
    *   Q Latched value
