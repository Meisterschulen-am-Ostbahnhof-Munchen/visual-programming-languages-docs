# AS_AX_SEL_AS


![AS_AX_SEL_AS](./AS_AX_SEL_AS.svg)

*(Kein Bild vorhanden)*

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `AS_AX_SEL_AS` dient der binären Auswahl (Selektion) zwischen zwei über Adapter bereitgestellten Eingangssignalen. Basierend auf dem Zustand eines Selektions-Adapters (`G`) wird entweder der Wert des Eingangs `IN0` oder des Eingangs `IN1` an den Ausgang `OUT` weitergeleitet.

Dieser Baustein kapselt die klassische Multiplexer-Funktion (entsprechend `SEL` aus der IEC 61131-3) in einer eventgesteuerten IEC 61499-Architektur unter Verwendung von unidirektionalen Adaptern. Dies vereinfacht die Signalverdrahtung in komplexen Steuerungsanwendungen erheblich.

## Schnittstellenstruktur

Der Funktionsbaustein besitzt keine klassischen ereignis- oder datenbasierten Ein- und Ausgänge auf der Hauptebene. Die gesamte Kommunikation wird über Adapter-Schnittstellen abgewickelt.

### **Ereignis-Eingänge**

*Keine direkten Ereignis-Eingänge vorhanden. Die Ereignisverarbeitung erfolgt gekapselt über die Sockets der Adapter.*

### **Ereignis-Ausgänge**

*Keine direkten Ereignis-Ausgänge vorhanden. Die Ereignisweiterleitung erfolgt gekapselt über den Plug des Ausgangs-Adapters.*

### **Daten-Eingänge**

*Keine direkten Daten-Eingänge vorhanden.*

### **Daten-Ausgänge**

*Keine direkten Daten-Ausgänge vorhanden.*

### **Adapter**

#### **Sockets (Eingangs-Schnittstellen)**

- **G** (Typ: `adapter::types::unidirectional::AX`):
  - **Beschreibung:** Selektor-Schnittstelle. Bestimmt, welcher Eingang auf den Ausgang geschaltet wird.
  - **Ereignis:** `E1` (Trigger für die Aktualisierung des Selektionssignals).
  - **Daten:** `D1` (Boolean-Wert; bestimmt den aktiven Pfad).
- **IN0** (Typ: `adapter::types::unidirectional::AS`):
  - **Beschreibung:** Erster auswählbarer Datenkanal (wird gewählt, wenn `G` den Wert `FALSE` hat).
  - **Ereignis:** `E1` (Signalisiert neue Daten an `IN0`).
  - **Daten:** `D1` (Datenwert des ersten Kanals).
- **IN1** (Typ: `adapter::types::unidirectional::AS`):
  - **Beschreibung:** Zweiter auswählbarer Datenkanal (wird gewählt, wenn `G` den Wert `TRUE` hat).
  - **Ereignis:** `E1` (Signalisiert neue Daten an `IN1`).
  - **Daten:** `D1` (Datenwert des zweiten Kanals).

#### **Plugs (Ausgangs-Schnittstellen)**

- **OUT** (Typ: `adapter::types::unidirectional::AS`):
  - **Beschreibung:** Der ausgewählte Ausgangskanal, welcher die Daten des aktiven Eingangs spiegelt.
  - **Ereignis:** `E1` (Wird ausgelöst, wenn ein neuer selektierter Wert ausgegeben wird).
  - **Daten:** `D1` (Der weitergeleitete Datenwert von `IN0` oder `IN1`).

## Funktionsweise

Im Inneren des Funktionsbausteins befindet sich ein Netzwerk aus Standard-Funktionsbausteinen, welches die Adapter-Signale verarbeitet:

1. **Signalspeicherung (Latch):** Die über die Adapter eingehenden Daten (`G.D1`, `IN0.D1`, `IN1.D1`) werden bei Eintreffen des jeweiligen Ereignisses (`E1`) in ereignisgesteuerten D-Flip-Flops (`E_D_FF` bzw. `E_D_FF_ANY`) zwischengespeichert.
2. **Daten-Konvertierung & Weiterleitung:** Über `F_MOVE`-Bausteine werden die zwischengespeicherten Daten der Typen `IN0` und `IN1` an den zentralen Auswahlbaustein übergeben. Intern sind diese Bewegungsoperationen für den Datentyp `SINT` (Short Integer) konfiguriert.
3. **Auswahl-Logik (`F_SEL`):** Der Baustein `F_SEL` (IEC 61131-3 Selection) führt die eigentliche Auswahl durch:
   - Ist der Zustand am Selektor `G` gleich `FALSE`, wird der Wert von `IN0` durchgeschaltet.
   - Ist der Zustand am Selektor `G` gleich `TRUE`, wird der Wert von `IN1` durchgeschaltet.
4. **Ausgabe-Triggerung:** Nach erfolgreicher Selektion wird das Ergebnis über einen weiteren `F_MOVE`-Baustein an das Ausgangs-Flip-Flop `E_D_FF_ANY_OUT` geleitet. Dieses erzeugt das Ausgangsereignis `OUT.E1` und legt den selektierten Wert an `OUT.D1` an.

```
       +-------+
IN0 -->|       |
       | F_SEL |--> OUT (wenn G = FALSE, dann IN0; wenn G = TRUE, dann IN1)
IN1 -->|       |
       +-------+
           ^
           |
G ---------+
```

## Technische Besonderheiten

- **Datentyp-Spezifität:** Obwohl die Adapter flexibel ausgelegt sein können, sind die internen Konvertierungsglieder (`F_MOVE`) fest auf den Datentyp **`SINT`** parametriert. Der Baustein ist somit speziell für die Auswahl von vorzeichenbehafteten 8-Bit-Ganzzahlen (Short Integers) konzipiert.
- **Ereignisgesteuert:** Jede Änderung oder jedes Ereignis an den Eingängen `IN0`, `IN1` oder `G` stößt die Kette neu an und aktualisiert den Ausgang `OUT`.

## Zustandsübersicht

Die folgende Tabelle zeigt das logische Verhalten des Bausteins basierend auf dem Selektionssignal `G.D1`:

| Zustand G.D1 | Ausgewählter Pfad | Ausgangswert (OUT.D1) | Ausgangsereignis (OUT.E1) |
| :--- | :--- | :--- | :--- |
| `FALSE` | Kanal 0 (`IN0`) | Wert von `IN0.D1` | Wird bei Wertänderung/Ereignis getriggert |
| `TRUE` | Kanal 1 (`IN1`) | Wert von `IN1.D1` | Wird bei Wertänderung/Ereignis getriggert |

## Anwendungsszenarien

- **Umschaltung von Betriebsmodi:** Routing von Sollwerten (z. B. Umschalten zwischen einem manuell vorgegebenen SINT-Wert und einem Automatik-Sollwert).
- **Signal-Quellen-Selektion:** Dynamisches Auswählen zwischen zwei Sensorwerten oder Parameterkonfigurationen, die über standardisierte unidirektionale Adapterstrukturen im System verteilt werden.
- **Kanalbündelung:** Reduzierung des Verdrahtungsaufwands in 4diac-Applikationen durch die Kapselung von Daten und Events in Adaptern.

## Vergleich mit ähnlichen Bausteinen

- **`F_SEL` (Standard-Auswahlbaustein):** Arbeitet direkt mit Standard-Datentypen und benötigt explizite Event-Verbindungen auf Applikationsebene. `AS_AX_SEL_AS` hingegen kapselt diese Logik vollständig und nutzt Adapter, was das Anwendungsdiagramm übersichtlicher macht.
- **Andere adapterbasierte Selektoren:** Unterscheiden sich im Wesentlichen durch die unterstützten Datentypen in den Adaptern (z. B. `INT`, `REAL` statt `SINT`).

## Fazit

Der Baustein `AS_AX_SEL_AS` stellt eine elegante, saubere und wiederverwendbare Lösung dar, um eine binäre Signal-Umschaltung auf Basis von unidirektionalen Adaptern in 4diac-IDE zu realisieren. Durch die interne Verwendung standardisierter Komponenten ist ein deterministisches Verhalten im ereignisgesteuerten System gewährleistet.
