# AW_TO_AULI


![AW_TO_AULI](./AW_TO_AULI.svg)

* * * * * * * * * *

## Einleitung

Der Composite FB `AW_TO_AULI` dient der Umwandlung eines unidirektionalen Adapters vom Typ `AW` (Datenformat WORD) in einen Adapter vom Typ `AULI` (Datenformat ULINT). Die Konvertierung erfolgt intern mittels des Standardbausteins `F_WORD_TO_ULINT` aus der IEC 61131-Bibliothek.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **AW_IN.E1** – Ereigniseingang über den Socket `AW_IN`. Löst die Konvertierung aus.

### **Ereignis-Ausgänge**

- **AULI_OUT.E1** – Ereignisausgang über den Plug `AULI_OUT`. Signalisiert den Abschluss der Konvertierung.

### **Daten-Eingänge**

- **AW_IN.D1** – Dateneingang vom Typ WORD (über Socket `AW_IN`).

### **Daten-Ausgänge**

- **AULI_OUT.D1** – Datenausgang vom Typ ULINT (über Plug `AULI_OUT`).

### **Adapter**

- **Socket:** `AW_IN` (Typ: `adapter::types::unidirectional::AW`)
- **Plug:** `AULI_OUT` (Typ: `adapter::types::unidirectional::AULI`)

## Funktionsweise

Sobald ein Ereignis am Ereigniseingang `AW_IN.E1` eintrifft, wird der interne Baustein `F_WORD_TO_ULINT` aufgerufen. Dieser liest den aktuellen Wert des Dateneingangs `AW_IN.D1` (WORD) und wandelt ihn in einen ULINT-Wert um. Nach erfolgreicher Konvertierung wird am Ereignisausgang `AULI_OUT.E1` ein Ereignis ausgegeben und der konvertierte Wert am Datenausgang `AULI_OUT.D1` bereitgestellt.

## Technische Besonderheiten

- Der FB ist als Composite realisiert und kapselt die Konvertierungslogik vollständig.
- Die verwendete Konvertierungsfunktion `F_WORD_TO_ULINT` entspricht der IEC 61131-3 Norm.
- Die Schnittstellen basieren auf unidirektionalen Adaptern – Ereignis- und Datenfluss erfolgen nur in eine Richtung.
- Der FB besitzt keine Zustandsmaschine; die Funktionalität ist rein ereignisgesteuert.

## Zustandsübersicht

Der FB enthält keine expliziten Zustände. Die Abarbeitung erfolgt linear: Ereignis → Konvertierung → Ausgabe.

## Anwendungsszenarien

- Einbindung von Sensoren oder Aktoren, die WORD-Daten liefern, in Systeme die ULINT-Werte erwarten.
- Adapterbasierte Protokollkonvertierung in der Automatisierungstechnik (z.B. Landtechnik).
- Wiederverwendbare Kapselung der Standard-Konvertierungsfunktion für modulare Steuerungsprojekte.

## Vergleich mit ähnlichen Bausteinen

- **Direkte Verwendung von `F_WORD_TO_ULINT`:** Erfordert manuelle Verkabelung von Ereignis- und Datenleitungen. Der Composite FB `AW_TO_AULI` vereinfacht die Integration in adapterorientierte Architekturen.
- **Andere Konvertierungsadapter** (z.B. `AW_TO_ADINT` für DINT oder `AW_TO_ABOOL` für BOOL): Bieten analoge Konvertierungen für andere Ziel-Datentypen.

## Fazit

`AW_TO_AULI` stellt eine praktische und leicht einsetzbare Komponente zur Umwandlung von WORD- in ULINT-Daten dar. Die Verwendung von standardisierten Adapterschnittstellen und der IEC-Konvertierungsfunktion gewährleistet Kompatibilität und Zuverlässigkeit. Der FB eignet sich besonders für modulare, adapterbasierte Automatisierungslösungen.