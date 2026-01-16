# E_RS

<img width="1139" height="202" alt="E_RS" src="https://user-images.githubusercontent.com/113907528/204902213-fedab003-82e3-4adf-ab40-fbb82a526c02.png">

* * * * * * * * * *

## Einleitung
Der `E_RS` (Event-driven RS Flip-Flop) ist ein ereignisgesteuerter, bistabiler Funktionsbaustein nach IEC 61499. Er dient als grundlegendes Speicherelement, das durch separate "Set"- und "Reset"-Ereignisse gesteuert wird. Sein Ausgang `Q` behält seinen Zustand bei, bis ein entgegengesetztes Ereignis eintrifft.

## Schnittstellenstruktur

### **Ereignis-Eingänge:**
- **S (Set)**: Setzt den Ausgang `Q` auf `TRUE`.
- **R (Reset)**: Setzt den Ausgang `Q` auf `FALSE`.

### **Ereignis-Ausgänge:**
- **EO (Event Output)**: Wird ausgelöst, wenn sich der Zustand von `Q` ändert.
    - **Verbundene Daten**: `Q`

### **Daten-Ausgänge:**
- **Q**: Der aktuelle Zustand des Flip-Flops (Datentyp: `BOOL`).

## Funktionsweise
Der `E_RS`-Baustein funktioniert als einfacher Speicher (Latch):
1.  **Setzen**: Wenn ein Ereignis am Eingang `S` eintrifft, wird der Ausgang `Q` auf `TRUE` gesetzt. Wenn `Q` vorher `FALSE` war, wird das `EO`-Ereignis ausgelöst.
2.  **Zurücksetzen**: Wenn ein Ereignis am Eingang `R` eintrifft, wird der Ausgang `Q` auf `FALSE` gesetzt. Wenn `Q` vorher `TRUE` war, wird das `EO`-Ereignis ausgelöst.
3.  **Speichern**: Zwischen den Ereignissen behält `Q` seinen zuletzt gesetzten Zustand bei.

## Technische Besonderheiten
- **Keine Priorisierung (Dominanz)**: Im Gegensatz zur IEC 61131-3 wird in der IEC 61499 nicht zwischen setz-dominant (SR) und rücksetz-dominant (RS) unterschieden. Treffen `S`- and `R`-Ereignisse quasi gleichzeitig ein, bestimmt die Verarbeitungsreihenfolge der Laufzeitumgebung, welches Ereignis "gewinnt". Der letzte verarbeitete Befehl bestimmt den Endzustand.
- **Änderungserkennung**: Der `EO`-Ausgang wird nur bei einer tatsächlichen Zustandsänderung ausgelöst, nicht, wenn der Baustein in seinen bereits aktiven Zustand gesetzt wird (z.B. ein `S`-Ereignis bei `Q=TRUE`).

## Anwendungsszenarien
- **Start/Stopp-Logik**: Ein "Start"-Taster ist mit `S` verbunden, ein "Stopp"-Taster mit `R`, um den Zustand einer Maschine zu steuern.
- **Fehlerspeicherung**: Ein Fehlerereignis setzt den Baustein (`S`), der den Fehlerzustand speichert, bis er von einem Bediener oder einem anderen Prozess explizit quittiert (`R`) wird.
- **Modus-Speicher**: Speichern des aktuellen Betriebsmodus einer Anlage (z.B. "Hand" vs. "Automatik").

## Vergleich mit ähnlichen Bausteinen
- **`E_SR`**: Funktional identisch zum `E_RS`, nur die Position der `S`- und `R`-Eingänge am grafischen Symbol ist vertauscht.
- **`E_D_FF`**: Speichert ebenfalls einen Zustand, aber taktbasiert. `E_D_FF` übernimmt den Wert am `D`-Eingang bei einem `CLK`-Ereignis, während `E_RS` durch separate Set/Reset-Ereignisse gesteuert wird.

## Fazit
Der `E_RS`-Baustein ist ein fundamentaler Speicherbaustein in der IEC 61499. Er ist ideal für einfache Zustandspeicherungen, bei denen ein Zustand durch ein Ereignis gesetzt und durch ein anderes explizit zurückgesetzt wird. Das Fehlen einer garantierten Set- oder Reset-Dominanz bei gleichzeitigen Ereignissen muss in kritischen Anwendungen beachtet werden.