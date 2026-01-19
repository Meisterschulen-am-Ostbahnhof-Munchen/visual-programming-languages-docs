# AX_INTERLOCK_2

```{index} single: AX_INTERLOCK_2
```

<img width="1586" height="363" alt="image" src="https://github.com/user-attachments/assets/4dffb3ad-aa02-4748-b05b-3aa330a04b7c" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `AX_INTERLOCK_2` ist ein ereignisgesteuerter, bistabiler Baustein mit Toggle-Funktionalität und einem dualen Verriegelungsmechanismus (Interlock). Er dient zur Steuerung zweier unabhängiger, aber gegenseitig ausschließender Ausgänge. Der Baustein kombiniert Set-, Reset- und Toggle-Funktionen für zwei Kanäle und stellt sicher, dass immer nur einer der beiden Ausgänge aktiv sein kann.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
*   **SET1**: Setzt den Ausgang OUT1.
*   **CLK1**: Dient als Takt (Clock) und löst bei einem Ereignis ein Toggle (Umschalten) des Ausgangs OUT1 aus.
*   **SET2**: Setzt den Ausgang OUT2.
*   **CLK2**: Dient als Takt (Clock) und löst bei einem Ereignis ein Toggle (Umschalten) des Ausgangs OUT2 aus.
*   **R**: Setzt alle Ausgänge zurück (Reset).

### **Ereignis-Ausgänge**
*   Keine direkten Ereignisausgänge vorhanden. Die Ausgabe erfolgt über Adapter.

### **Daten-Eingänge**
*   Keine Dateneingänge vorhanden.

### **Daten-Ausgänge**
*   Keine direkten Datenausgänge vorhanden. Die Datenausgabe erfolgt über Adapter.

### **Adapter**
*   **OUT1**: Unidirektionaler Adapter vom Typ `adapter::types::unidirectional::AX`. Überträgt den Zustand des ersten Flip-Flops (TRUE/FALSE).
*   **OUT2**: Unidirektionaler Adapter vom Typ `adapter::types::unidirectional::AX`. Überträgt den Zustand des zweiten Flip-Flops (TRUE/FALSE).

## Funktionsweise
Der `AX_INTERLOCK_2` ist als Basic Function Block (BFB) implementiert und besitzt einen Execution Control Chart (ECC) mit vier Zuständen: `START`, `SET1`, `SET2` und `RESET`.

*   **Ausgangszustand (`START`)**: Beide Ausgänge sind inaktiv (FALSE).
*   **Setzen/Togglen eines Ausgangs**: Bei einem `SET1`- oder `CLK1`-Ereignis wechselt der ECC in den Zustand `SET1`. Hier wird der Algorithmus `SET1` ausgeführt, der `OUT1.D1` auf TRUE setzt. Gleichzeitig wird der Algorithmus `RESET2` ausgeführt, der `OUT2.D1` auf FALSE setzt. Dies stellt die gegenseitige Verriegelung sicher. Analog funktioniert dies für `SET2`/`CLK2` mit dem Zustand `SET2`.
*   **Reset**: Ein `R`-Ereignis führt unabhängig vom aktuellen Zustand in den `RESET`-Zustand. Hier werden beide Ausgänge (`OUT1.D1` und `OUT2.D1`) über die Algorithmen `RESET1` und `RESET2` auf FALSE gesetzt.
*   **Rückkehr in den Startzustand**: Nach der Ausführung der Aktionen in den Zuständen `SET1`, `SET2` oder `RESET` erfolgt ein automatischer Übergang (Condition=`1`, also immer wahr) zurück in den `START`-Zustand. Der Baustein ist dann bereit für das nächste Eingangsereignis.

Die Toggle-Funktion wird durch die `CLK1`- und `CLK2`-Eingänge realisiert. Ein `CLK1`-Ereignis im `START`-Zustand führt zum Zustand `SET1` und aktiviert somit `OUT1` (falls es vorher aus war). Befand sich der Baustein bereits im Zustand `SET1`, würde ein weiteres `CLK1`-Ereignis (nach Rückkehr in `START`) erneut in `SET1` führen, was jedoch keine Zustandsänderung bewirkt, da `OUT1` bereits TRUE ist. Die eigentliche Toggle-Logik (Umschalten zwischen TRUE/FALSE) muss durch die externe Logik, die die `CLKx`-Ereignisse generiert, in Abhängigkeit vom aktuellen Ausgangszustand realisiert werden.

## Technische Besonderheiten
*   **Dualer Interlock**: Die gegenseitige Ausschließlichkeit der Ausgänge ist hart im Zustandsübergang verankert. Im Zustand `SET1` wird immer auch `RESET2` aufgerufen und umgekehrt.
*   **Priorität**: Ein globales Reset-Ereignis (`R`) hat Vorrang und setzt beide Ausgänge zurück, unabhängig von anderen anstehenden Ereignissen oder dem aktuellen Zustand.
*   **Adapter-basierte Ausgabe**: Die Ausgabewerte werden nicht über klassische Datenausgangspins, sondern über unidirektionale Adapter bereitgestellt. Dies ermöglicht eine saubere, typisierte Schnittstelle zur Anbindung anderer Bausteine.

## Zustandsübergang
1.  **START** (beide Ausgänge FALSE)
    *   Bei `SET1` oder `CLK1` -> **SET1** (OUT1=TRUE, OUT2=FALSE)
    *   Bei `SET2` oder `CLK2` -> **SET2** (OUT1=FALSE, OUT2=TRUE)
    *   Bei `R` -> **RESET** (OUT1=FALSE, OUT2=FALSE)
2.  **SET1** (OUT1=TRUE, OUT2=FALSE)
    *   Automatischer Übergang -> **START**
3.  **SET2** (OUT1=FALSE, OUT2=TRUE)
    *   Automatischer Übergang -> **START**
4.  **RESET** (beide Ausgänge FALSE)
    *   Automatischer Übergang -> **START**

## Anwendungsszenarien
*   **Steuerung gegensätzlicher Aktoren**: Ideal für die Ansteuerung von zwei Aktoren, die nie gleichzeitig aktiv sein dürfen, wie z.B. "Ventil Öffnen" / "Ventil Schließen" oder "Vorwärts" / "Rückwärts" bei einem Antrieb.
*   **Betriebsartenschaltung**: Umschaltung zwischen zwei verschiedenen Betriebsarten einer Maschine (z.B. "Automatik" / "Manuell"), wobei sichergestellt wird, dass nur eine aktiv ist.
*   **Toggle-Funktion mit Sicherheit**: Bereitstellung einer Toggle-Funktion (z.B. für ein Hand-/Ausschaltgerät), die mit einer gegenseitigen Verriegelung kombiniert ist.

## Vergleich mit ähnlichen Bausteinen
*   **E_RS / E_SR (Bistabile Flip-Flops)**: Diese klassischen Bausteine bieten Set/Reset für einen einzigen Ausgang. Der `AX_INTERLOCK_2` erweitert dieses Konzept um einen zweiten Kanal mit integrierter gegenseitiger Verriegelung und separaten Toggle-Eingängen.
*   **E_TOGGLE**: Bietet eine reine Toggle-Funktion für einen Ausgang. Der `AX_INTERLOCK_2` bietet Toggle-Funktionalität für zwei Kanäle, jedoch mit dem wesentlichen Zusatz der zwingenden gegenseitigen Ausschließlichkeit (Interlock).
*   **E_D_FF (D-Flip-Flop)**: Übernimmt einen Datenwert taktgesteuert. Der `AX_INTERLOCK_2` hat keine Dateneingänge; sein Zustand wird ausschließlich durch die Ereigniseingänge bestimmt.

## Fazit
Der `AX_INTERLOCK_2` ist ein spezialisierter Steuerbaustein für Anwendungen, bei denen zwei sich gegenseitig ausschließende Zustände sicher verwaltet werden müssen. Durch die Kombination von bistabilen Set/Reset-Funktionen, Toggle-Möglichkeiten und einer hart verdrahteten gegenseitigen Verriegelung reduziert er den Programmieraufwand und erhöht die Zuverlässigkeit der Steuerungslogik. Die Verwendung von Adaptern für die Ausgabe fördert eine modulare und gut strukturierte Anwendungsarchitektur.