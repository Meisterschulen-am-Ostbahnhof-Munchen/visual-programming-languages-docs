# FB_CTD_UDINT

```{index} single: FB_CTD_UDINT
```

<img width="1411" height="282" alt="FB_CTD_UDINT" src="https://github.com/user-attachments/assets/a8aab825-6766-4328-b0cb-4b841157bc33" />

* * * * * * * * * *
## 📺 Video

* [Zusätzlich: Uebung_083: Aufwärts/Abwärts zählen: E_CTUD_UDINT Datentyp UDINT; mit Anzeige am VT.](https://www.youtube.com/watch?v=oTPDtsw5eAw)

## Einleitung
Der Funktionsblock `FB_CTD_UDINT` ist ein Abwärtszähler (Down Counter) für vorzeichenlose 32-Bit-Ganzzahlen (UDINT). Er wird verwendet, um einen Zählerwert bei jedem Ereignis herunterzuzählen, bis er Null erreicht.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung. Wird verwendet, um den Zählvorgang oder das Laden eines neuen Wertes auszulösen.

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung. Wird nach der Bearbeitung der Anforderung ausgelöst und gibt den aktuellen Zählerstand und den Ausgangszustand zurück.

### **Daten-Eingänge**
- **CD** (BOOL): Zählt herunter, wenn `TRUE` und der Zählerwert größer als Null ist.
- **LD** (BOOL): Lädt den vorgegebenen Wert (`PV`) in den Zähler, wenn `TRUE`.
- **PV** (UDINT): Vorgegebener Wert, der in den Zähler geladen wird, wenn `LD` aktiviert ist.

### **Daten-Ausgänge**
- **Q** (BOOL): Wird `TRUE`, wenn der Zählerwert kleiner oder gleich Null ist.
- **CV** (UDINT): Aktueller Zählerwert.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock verarbeitet die Eingabeereignisse und -daten wie folgt:
1. Wenn `LD` aktiviert ist (`TRUE`), wird der vorgegebene Wert (`PV`) in den Zähler (`CV`) geladen.
2. Wenn `CD` aktiviert ist (`TRUE`) und der Zählerwert (`CV`) größer als Null ist, wird der Zählerwert um eins verringert.
3. Der Ausgang `Q` wird auf `TRUE` gesetzt, wenn der Zählerwert (`CV`) kleiner oder gleich Null ist.
4. Nach der Bearbeitung wird das Ausgabeereignis `CNF` ausgelöst, um den neuen Zustand zu bestätigen.

## Technische Besonderheiten
- Der Zähler arbeitet mit vorzeichenlosen 32-Bit-Ganzzahlen (UDINT).
- Der Zählerwert wird nur verringert, wenn `CD` aktiviert ist und der aktuelle Wert größer als Null ist.
- Der Ausgang `Q` signalisiert, wenn der Zählerwert Null oder darunter erreicht hat.

## Zustandsübersicht
- **Initialisierung**: Der Zählerwert (`CV`) ist undefiniert, bis ein `LD`-Signal empfangen wird.
- **Laden**: Bei aktiviertem `LD` wird `PV` in `CV` geladen.
- **Herunterzählen**: Bei aktiviertem `CD` und `CV > 0` wird `CV` um eins verringert.
- **Ausgangszustand**: `Q` wird `TRUE`, wenn `CV <= 0`.

## Anwendungsszenarien
- Steuerung von Prozessen, die eine bestimmte Anzahl von Schritten oder Ereignissen erfordern.
- Zeitgesteuerte Abläufe, bei denen ein Countdown benötigt wird.
- Überwachung von Zyklen oder Wiederholungen in automatisierten Systemen.

## Vergleich mit ähnlichen Bausteinen
- Im Gegensatz zu einem Aufwärtszähler (CTU) verringert dieser Baustein den Zählerwert.
- Ähnlich wie andere Zählerbausteine, aber spezialisiert auf vorzeichenlose 32-Bit-Ganzzahlen.

## Fazit
Der `FB_CTD_UDINT` ist ein effizienter und einfacher Abwärtszähler für Anwendungen, die eine Zählfunktion mit vorzeichenlosen 32-Bit-Ganzzahlen erfordern. Seine klare Schnittstelle und einfache Funktionsweise machen ihn zu einem nützlichen Baustein in der Automatisierungstechnik.