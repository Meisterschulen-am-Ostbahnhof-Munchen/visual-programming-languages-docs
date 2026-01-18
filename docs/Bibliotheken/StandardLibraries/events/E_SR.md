# E_SR

```{index} single: E_SR
```

<img width="1139" height="202" alt="E_SR" src="https://user-images.githubusercontent.com/113907528/204904299-a6a3580a-42b4-4ea9-80c9-52b38b2d002b.png">

* * * * * * * * * *

## Einleitung
Der `E_SR` (Event-driven SR Flip-Flop) ist ein ereignisgesteuerter, bistabiler Funktionsbaustein nach IEC 61499. Er dient als grundlegendes Speicherelement, das durch separate "Set"- und "Reset"-Ereignisse gesteuert wird. Sein Ausgang `Q` behält seinen Zustand bei, bis ein entgegengesetztes Ereignis eintrifft.

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
Der `E_SR`-Baustein funktioniert als einfacher Speicher (Latch):
1.  **Setzen**: Wenn ein Ereignis am Eingang `S` eintrifft, wird der Ausgang `Q` auf `TRUE` gesetzt. Wenn `Q` vorher `FALSE` war, wird das `EO`-Ereignis ausgelöst.
2.  **Zurücksetzen**: Wenn ein Ereignis am Eingang `R` eintrifft, wird der Ausgang `Q` auf `FALSE` gesetzt. Wenn `Q` vorher `TRUE` war, wird das `EO`-Ereignis ausgelöst.
3.  **Speichern**: Zwischen den Ereignissen behält `Q` seinen zuletzt gesetzten Zustand bei.

## Technische Besonderheiten
- **Keine Priorisierung (Dominanz)**: Im Gegensatz zur IEC 61131-3 wird in der IEC 61499 nicht zwischen setz-dominant (SR) und rücksetz-dominant (RS) unterschieden. Treffen `S`- and `R`-Ereignisse quasi gleichzeitig ein, bestimmt die Verarbeitungsreihenfolge der Laufzeitumgebung, welches Ereignis "gewinnt". Der letzte verarbeitete Befehl bestimmt den Endzustand.
- **Änderungserkennung**: Der `EO`-Ausgang wird nur bei einer tatsächlichen Zustandsänderung ausgelöst.

## Anwendungsszenarien
- **Start/Stopp-Logik**: Ein "Start"-Taster ist mit `S` verbunden, ein "Stopp"-Taster mit `R`, um den Zustand einer Maschine zu steuern.
- **Fehlerspeicherung**: Ein Fehlerereignis setzt den Baustein (`S`), der den Fehlerzustand speichert, bis er von einem Bediener oder einem anderen Prozess explizit quittiert (`R`) wird.
- **Modus-Speicher**: Speichern des aktuellen Betriebsmodus einer Anlage (z.B. "Hand" vs. "Automatik").

## Vergleich mit ähnlichen Bausteinen
- **`E_RS`**: Funktional identisch zum `E_SR`. Der einzige Unterschied liegt in der grafischen Anordnung der `S`- und `R`-Anschlüsse am Symbol, um unterschiedlichen Konventionen gerecht zu werden.
- **`E_D_FF`**: Speichert ebenfalls einen Zustand, aber taktbasiert. `E_D_FF` übernimmt den Wert am `D`-Eingang bei einem `CLK`-Ereignis, während `E_SR` durch separate Set/Reset-Ereignisse gesteuert wird.

## Fazit
Der `E_SR`-Baustein ist ein fundamentaler Speicherbaustein in der IEC 61499. Er ist ideal für einfache Zustandspeicherungen, bei denen ein Zustand durch ein Ereignis gesetzt und durch ein anderes explizit zurückgesetzt wird. Das Fehlen einer garantierten Set- oder Reset-Dominanz bei gleichzeitigen Ereignissen muss in kritischen Anwendungen beachtet werden.