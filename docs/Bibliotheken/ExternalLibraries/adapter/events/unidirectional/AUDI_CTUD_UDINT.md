# AUDI_CTUD_UDINT (Adapter-basierter Auf-/Abwärtszähler)

```{index} single: AUDI_CTUD_UDINT (Adapter-basierter Auf-/Abwärtszähler)
```

## 🎧 Podcast

* [E_CTD: Ereignisgesteuerter Abwärtszähler nach IEC 61499](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/E_CTD-Ereignisgesteuerter-Abwrtszhler-nach-IEC-61499-e368lli)
* [Code-Renovierung mit AX-Adaptern: Wie Eclipse 4diac™ durch Signal-Bündelung Komplexität besiegt](https://podcasters.spotify.com/pod/show/logibus/episodes/Code-Renovierung-mit-AX-Adaptern-Wie-Eclipse-4diac-durch-Signal-Bndelung-Komplexitt-besiegt-e3ahcd1)
* [Von 1400 Fehlern zum sauberen Code: Die Migration der „Getreidehacke“ auf Eclipse 4diac™ 3.0 und die Macht der AX-Adapter](https://podcasters.spotify.com/pod/show/logibus/episodes/Von-1400-Fehlern-zum-sauberen-Code-Die-Migration-der-Getreidehacke-auf-Eclipse-4diac-3-0-und-die-Macht-der-AX-Adapter-e3ahcko)

## 📺 Video

* [2025-11-04 20-15-06 LogiBUS® auf dem Weg zu Eclipse 4diac™ 3.0 - noch mehr Adapter (AX)](https://www.youtube.com/watch?v=RsY65VqTAMc)
* [Zusätzlich: Uebung_083: Aufwärts/Abwärts zählen: E_CTUD_UDINT Datentyp UDINT; mit Anzeige am VT.](https://www.youtube.com/watch?v=oTPDtsw5eAw)

## Einleitung
Der `AUDI_CTUD_UDINT` ist ein ereignisgesteuerter Auf-/Abwärtszähler (Counter Up/Down) für vorzeichenlose 32-Bit-Ganzzahlen (UDINT), der speziell für die Integration in adapterbasierte Systeme entwickelt wurde. Er nutzt `AUDI`-Adapter für die Übergabe des Zählwerts und des Vorgabewerts, was eine saubere Trennung von Ereignis- und Datenfluss ermöglicht.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **CU**: `Event` - Zählt den Wert um eins hoch (`Count Up`).
- **CD**: `Event` - Zählt den Wert um eins herunter (`Count Down`).
- **R**: `Event` - Setzt den Zähler auf Null zurück (`Reset`).

### **Ereignis-Ausgänge**
- **CO**: `Event` - Wird ausgelöst, wenn der Zählerstand den Vorgabewert `PV` erreicht (`Count Output`).
  - Mit Variablen `QU` und `QD` verknüpft.
- **RO**: `Event` - Wird ausgelöst, wenn der Zähler auf Null zurückgesetzt wurde (`Reset Output`).
  - Mit Variablen `QU` und `QD` verknüpft.

### **Output-Variablen**
- **QU**: `BOOL` - `TRUE`, wenn der Zählwert (`CV.D1`) größer oder gleich dem Vorgabewert (`PV.D1`) ist.
- **QD**: `BOOL` - `TRUE`, wenn der Zählwert (`CV.D1`) kleiner oder gleich Null ist.

### **Adapter**
- **CV** (Plug): `AUDI` - Der aktuelle Zählwert (`Counter Value`).
- **PV** (Socket): `AUDI` - Der Vorgabewert (`Preset Value`), gegen den der Zähler geprüft wird (für `QU`).

## Funktionsweise
Der Zähler reagiert auf die Ereignis-Eingänge `CU`, `CD` und `R`. Ein `CU`-Ereignis erhöht `CV.D1` um 1, ein `CD`-Ereignis verringert `CV.D1` um 1. Ein `R`-Ereignis setzt `CV.D1` auf 0.

Das Laden eines Vorgabewertes (`PV.D1`) in den Zähler (`CV.D1`) erfolgt automatisch, wenn am `PV`-Adapter ein Ereignis (`PV.E1`) eintrifft. Dies ersetzt den expliziten `LD`-Eingang des originalen `E_CTUD_UDINT`.

Der Zählwert wird über den `CV`-Adapter als `AUDI`-Signal ausgegeben. Die Ausgänge `CO` und `RO` signalisieren Zustandsänderungen und liefern `QU`/`QD`.

## Technische Besonderheiten
✔ **Adapter-basiert**: Nahtlose Integration in AX-Systeme.
✔ **Ereignisgesteuert**: Keine zyklischen Aufrufe notwendig.
✔ **UDINT-Basis**: Unterstützt den vollen Wertebereich von vorzeichenlosen 32-Bit-Ganzzahlen.
✔ **Vereinfachte Lade-Logik**: Der explizite `LD`-Eingang wurde entfernt und durch die Ereignis-Erkennung am `PV`-Adapter (`PV.E1`) ersetzt. Der `LDO`-Ausgang entfällt. Stattdessen signalisiert `CV.E1` die Wertänderung.

## Anwendungsszenarien
- **Stückzählung**: Zählen von Objekten in Fertigungslinien.
- **Betriebsstundenzähler**: Erfassen von Betriebszeiten (in Kombination mit Timern).
- **Positionsüberwachung**: Einfache Positionszähler in Handling-Systemen.