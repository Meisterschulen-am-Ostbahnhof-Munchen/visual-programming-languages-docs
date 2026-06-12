# AUI_UDINT_NE


![AUI_UDINT_NE](./AUI_UDINT_NE.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AUI_UDINT_NE** führt einen Ungleich-Vergleich (not equal) zwischen zwei Werten des Typs **UDINT** durch. Er ist als zusammengesetzter Baustein (Composite) realisiert und verwendet standardisierte Adapter-Schnittstellen für die Anbindung an andere Bausteine. Der Baustein entspricht der IEC 61131-3 und ist als Standardvergleichsfunktion klassifiziert.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| REQ  | Event | Service Request (Auslöser für den Vergleich) |

### **Ereignis-Ausgänge**

Der Baustein selbst besitzt keine direkten Ereignisausgänge. Das Ergebnis wird über den Adapter-Ausgang `OUT` bereitgestellt, der nach erfolgtem Vergleich ein Ereignis auf seinem `E1`-Port ausgibt.

### **Daten-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| IN2  | UDINT | Input value 2 (zweiter Vergleichswert) |

### **Daten-Ausgänge**

Der Baustein besitzt keine direkten Datenausgänge. Der Vergleichswert wird über den Adapter-Ausgang `OUT` auf dessen `D1`-Port als **BOOL** (true bei Ungleichheit) ausgegeben.

### **Adapter**

| Typ | Richtung | Name | Kommentar |
|-----|----------|------|-----------|
| `adapter::types::unidirectional::AUI` | Socket | IN1 | Input value 1 (erster Vergleichswert) |
| `adapter::types::unidirectional::AX`  | Plug   | OUT | value 1 != value2 = true |

## Funktionsweise

Der Baustein vergleicht zwei Werte des Typs **UDINT** auf Ungleichheit. Der erste Wert wird über den Socket `IN1` (Port `D1`) bereitgestellt, der zweite Wert über den Dateneingang `IN2`. Der Vergleich wird durch ein Ereignis an `REQ` oder durch das Ereignis des Sockets `IN1.E1` ausgelöst. Im Inneren befindet sich der FB `F_NE` (Typ `iec61131::comparison::F_NE`), der den eigentlichen Ungleich-Vergleich durchführt. Das Ergebnis (BOOL) wird über den Plug `OUT` auf `D1` ausgegeben, zusammen mit einem Ereignis auf `E1`, sobald der Vergleich abgeschlossen ist.

Die Verwendung von Adaptern ermöglicht eine lose Kopplung und standardisierte Kommunikation zwischen Bausteinen in der 4diac-IDE.

## Technische Besonderheiten

- **Adapterbasierte Schnittstelle:** Der Baustein verwendet unidirektionale Adapter (`AUI` und `AX`), die für den Austausch von Werten und Ereignissen zwischen Funktionsblöcken optimiert sind.
- **Interne Realisierung:** Der Vergleich wird durch einen eingebetteten Standardbaustein `F_NE` aus der Bibliothek `iec61131::comparison` durchgeführt.
- **Typumgebung:** Die Eingangswerte sind als `UDINT` (unsigned double integer) definiert, das Ergebnis wird als `BOOL` ausgegeben.
- **Kompatibilität:** Geeignet für Anwendungen nach IEC 61131-3, insbesondere Steuerungs- und Regelungsaufgaben.

## Zustandsübersicht

Der Baustein besitzt keinen expliziten Zustandsautomaten im XML. Die interne Logik des FB `F_NE` arbeitet ereignisgesteuert:
1. **Warten:** Der Baustein wartet auf ein Ereignis an `REQ` oder `IN1.E1`.
2. **Verarbeitung:** Bei Auslösung werden die Werte `IN1.D1` und `IN2` gelesen und verglichen.
3. **Ausgabe:** Das Ergebnis wird auf `OUT.D1` gesetzt und ein Ereignis auf `OUT.E1` ausgelöst.

## Anwendungsszenarien

- **Zustandsüberwachung:** Vergleichen von Zählerständen oder Sensormesswerten, um Abweichungen zu erkennen.
- **Sicherheitslogik:** Prüfen, ob zwei unabhängige Signalquellen unterschiedliche Werte liefern (z.B. Redundanzvergleich).
- **Datenvalidierung:** Feststellen, ob ein aktueller Wert von einem Referenzwert abweicht.

## Vergleich mit ähnlichen Bausteinen

Es existieren weitere Vergleichsbausteine für `UDINT` wie **AUI_UDINT_EQ** (gleich), **AUI_UDINT_LT** (kleiner) oder **AUI_UDINT_GT** (größer). Der hier beschriebene Baustein **AUI_UDINT_NE** fokussiert speziell auf den Ungleich-Fall. Im Unterschied zu einfachen Funktionsblöcken mit direkten Ein-/Ausgängen bietet die Adapter-Schnittstelle eine standardisierte und wiederverwendbare Kopplungsmöglichkeit in der 4diac-Umgebung.

## Fazit

Der Funktionsblock **AUI_UDINT_NE** ist ein spezialisierter, adapterbasierter Vergleichsbaustein für den Ungleich-Test zweier UDINT-Werte. Dank der modularen Bauweise und der internen Nutzung eines Standardvergleichsblocks lässt er sich flexibel in IEC-61131-3-Projekte integrieren. Er eignet sich besonders für Anwendungen, die eine lose, ereignisgesteuerte Datenkopplung erfordern.