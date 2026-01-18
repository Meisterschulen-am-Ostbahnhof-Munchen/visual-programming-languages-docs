# E_SR

```{index} single: E_SR
```
## 🎧 Podcast

* [IEC 61499: Der E_SR-Baustein entschlüsselt – Einfachheit trifft Ereignissteuerung](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/IEC-61499-Der-E_SR-Baustein-entschlsselt--Einfachheit-trifft-Ereignissteuerung-e3682bo)
* [Decoding the E_SR Function Block: The Unsung Hero of Industrial Automation](https://podcasters.spotify.com/pod/show/iec-61499-prime-course-en/episodes/Decoding-the-E_SR-Function-Block-The-Unsung-Hero-of-Industrial-Automation-e3681qo)

## 📺 Video

* [SR-Flip-Flop Baustein E_SR aus der IEC 61499 (Übung 006)](https://www.youtube.com/watch?v=6nGmGX7gwAE)

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