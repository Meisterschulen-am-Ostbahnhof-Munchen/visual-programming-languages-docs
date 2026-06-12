# AR_TO_AUDI


![AR_TO_AUDI](./AR_TO_AUDI.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `AR_TO_AUDI` ist ein zusammengesetzter Baustein (Composite FB), der einen REAL‑Wert von einem unidirektionalen **AR**‑Adapter entgegennimmt, in einen **UDINT**‑Wert konvertiert und über einen **AUDI**‑Adapter ausgibt. Er kapselt die Typkonvertierung `REAL_TO_UDINT` und vereinfacht die Einbindung in adapterbasierte Kommunikationsstrukturen.

## Schnittstellenstruktur

Der Baustein besitzt keine eigenen Ereignis- oder Daten-Ein-/Ausgänge. Die gesamte Kommunikation erfolgt über zwei Adapter (Socket und Plug).

### **Adapter (Socket – Eingang)**

| Bezeichnung | Typ | Kommentar |
|---|---|---|
| `AR_IN` | `adapter::types::unidirectional::AR` | Unidirektionaler REAL‑Adapter als Eingang |

Der Adapter `AR_IN` liefert ein Ereignis `E1` und einen Daten-Eingang `D1` vom Typ `REAL`.

### **Adapter (Plug – Ausgang)**

| Bezeichnung | Typ | Kommentar |
|---|---|---|
| `AUDI_OUT` | `adapter::types::unidirectional::AUDI` | Unidirektionaler UDINT‑Adapter als Ausgang |

Der Adapter `AUDI_OUT` erwartet ein Ereignis `E1` und einen Daten-Ausgang `D1` vom Typ `UDINT`.

## Funktionsweise

Der Baustein enthält intern eine Instanz des Konvertierungsbausteins `F_REAL_TO_UDINT` aus der Bibliothek `iec61131::conversion`. Die Signalverbindungen realisieren einen einfachen Datenfluss:

1. **Ereignis vom Eingangsadapter**  
   Das Ereignis `AR_IN.E1` triggert den Konvertierungsbaustein über dessen Ereigniseingang `REQ`.

2. **Datenkonvertierung**  
   Gleichzeitig wird der REAL‑Wert von `AR_IN.D1` an den Dateneingang `IN` von `F_REAL_TO_UDINT` übergeben. Die Konvertierung erfolgt ohne Verzögerung innerhalb des Ereigniszyklus.

3. **Ausgangsereignis und Ergebnis**  
   Nach erfolgreicher Konvertierung sendet `F_REAL_TO_UDINT` ein Bestätigungsereignis (`CNF`) an den Ausgangsadapter (`AUDI_OUT.E1`). Der konvertierte UDINT‑Wert wird über den Datenausgang `OUT` an `AUDI_OUT.D1` weitergeleitet.

Die Umsetzung ist synchron: Jedes eingehende Ereignis löst genau eine Ausgabe aus.

## Technische Besonderheiten

- **Zusammengesetzter Baustein** – Die Logik ist vollständig durch ein inneres Netzwerk realisiert; es existiert kein eigenständiger Algorithmus oder Zustandsautomat.
- **Unidirektionale Adapter** – Sowohl Eingangs- als auch Ausgangsschnittstelle sind unidirektional und übertragen nur einen Ereignis‑/Datenkanal.
- **Verwendete Bibliothek** – Die Konvertierung erfolgt über den IEC‑61131‑Baustein `F_REAL_TO_UDINT`, der hardwareunabhängig und weit verbreitet ist.
- **Keine Fehlerbehandlung** – Der Baustein führt keine Bereichs- oder Typüberprüfung durch; die Konvertierung von REAL nach UDINT folgt den Standardregeln (Rundung, Begrenzung).

## Zustandsübersicht

Da der Baustein keine eigene Zustandsmaschine besitzt, wird die Betriebsweise ausschließlich durch das Ereignisnetzwerk bestimmt:

- **Idle** – Kein Ereignis an `AR_IN.E1` aktiv; Ausgangsadapter bleibt inaktiv.
- **Aktiv** – Eingehendes Ereignis löst sofort die Konvertierung aus und liefert ein Ausgangsereignis. Nach Abschluss kehrt der Baustein in den Ruhezustand zurück (kein interner Speicher).

## Anwendungsszenarien

- **Brückenbildung** zwischen Systemteilen, die REAL‑Werte liefern (z. B. Sensoren für Gleitkommazahlen) und Komponenten, die UDINT‑Werte verarbeiten (z. B. Zähler, Indexverwaltung).
- **Adapter‑basierte Kommunikation** in verteilten Automatisierungssystemen nach IEC 61499, wenn die Schnittstellen als unidirektionale Adapter definiert sind.
- **Typanpassung** in Datenvorverarbeitungspfaden, bevor Werte an speicherprogrammierbare Steuerungen (SPS) oder Visualisierungen übergeben werden.

## Vergleich mit ähnlichen Bausteinen

- **REAL_TO_DINT** – konvertiert REAL in vorzeichenbehaftete 32‑Bit‑Ganzzahl; hier wird stattdessen in vorzeichenlose Ganzzahl (UDINT) gewandelt.
- **AR_TO_xx‑Bausteine** – Andere Varianten könnten z. B. in `AR_TO_BYTE` oder `AR_TO_DWORD` konvertieren, jedoch ohne den Adapter‑Rahmen.
- **Direkter Konverter** – Der interne Baustein `F_REAL_TO_UDINT` lässt sich auch direkt ohne Adapter einbinden; `AR_TO_AUDI` bietet eine gekapselte, leicht austauschbare Schnittstelle.

## Fazit

Der Baustein `AR_TO_AUDI` stellt eine sauber gekapselte, adapterbasierte Typkonvertierung von REAL nach UDINT bereit. Er reduziert den Verdrahtungsaufwand in modularen IEC‑61499‑Projekten und gewährleistet eine zuverlässige, ereignisgesteuerte Umsetzung. Durch die Verwendung standardisierter Konvertierungsbausteine ist die Lösung portabel und leicht verständlich.