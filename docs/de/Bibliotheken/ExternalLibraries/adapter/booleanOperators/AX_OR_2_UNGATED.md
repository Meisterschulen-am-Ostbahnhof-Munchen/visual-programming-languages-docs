# AX_OR_2_UNGATED

> ℹ️ **UNGATED-Variante:** Dieser Baustein ist die ungegatete Version von [`AX_OR_2`](AX_OR_2.md). Er unterdrückt **keine** unveränderten Wiederholungen – jedes neu berechnete Ergebnis wird bedingungslos weitergegeben, auch ohne Wertänderung. Das ist wichtig für Verbraucher, die eine periodische Kadenz unabhängig von Wertänderung brauchen (z. B. Ableitungs-/Frequenzberechnungen, die sonst nicht gegen Null abklingen). Alle Angaben zu Änderungserkennung/Change-Gating weiter unten auf dieser Seite gelten **nicht** für diesen Baustein.

<img width="963" height="265" alt="image" src="https://github.com/user-attachments/assets/3c1d3b81-2420-46cc-b7cf-fc6828db919c" />

* * * * * * * * * *

## Einleitung

Der AX_OR_2_UNGATED Funktionsblock ist ein generischer Baustein zur Berechnung der booleschen ODER-Verknüpfung. Er verarbeitet zwei Eingangssignale und gibt das logische ODER-Ergebnis aus. Der Baustein ist speziell für die Verwendung in Automatisierungssystemen konzipiert.

![AX_OR_2_UNGATED](AX_OR_2_UNGATED.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine Ereignis-Eingänge vorhanden

### **Ereignis-Ausgänge**

Keine Ereignis-Ausgänge vorhanden

### **Daten-Eingänge**

Keine direkten Daten-Eingänge vorhanden

### **Daten-Ausgänge**

Keine direkten Daten-Ausgänge vorhanden

### **Adapter**

**Eingangsadapter:**

- **IN1** - ODER Eingang 1 (Adapter-Typ: adapter::types::unidirectional::AX)
- **IN2** - ODER Eingang 2 (Adapter-Typ: adapter::types::unidirectional::AX)

**Ausgangsadapter:**

- **OUT** - ODER Ergebnis (Adapter-Typ: adapter::types::unidirectional::AX)

## Funktionsweise

Der AX_OR_2_UNGATED Funktionsblock führt eine logische ODER-Verknüpfung zwischen den beiden Eingangssignalen IN1 und IN2 durch. Das Ergebnis wird über den Ausgangsadapter OUT ausgegeben. Die Verarbeitung erfolgt kontinuierlich, sobald Eingangssignale verfügbar sind.

## Technische Besonderheiten

- Generischer Funktionsblock mit der Klasse 'GEN_AX_OR'
- Verwendet unidirektionale Adapter für die Signalübertragung
- Implementiert als Teil des Packages "adapter::booleanOperators"
- Unterstützt die Eclipse 4diac Standard-Spezifikation 61499-2

## Zustandsübersicht

Da es sich um einen kombinatorischen Logikbaustein handelt, besitzt AX_OR_2_UNGATED keinen internen Zustand. Die Ausgabe wird ausschließlich von den aktuellen Eingangswerten bestimmt.

## Anwendungsszenarien

- Sicherheitskreise mit redundanten Sensoren
- Parallele Steuerungsbefehle
- Überwachungssysteme mit mehreren Eingangssignalen
- Logische Verknüpfungen in Steuerungsalgorithmen

## ⚖️ Vergleich mit ähnlichen Bausteinen

Im Vergleich zu anderen ODER-Bausteinen zeichnet sich AX_OR_2_UNGATED durch seine Adapter-basierte Schnittstelle aus, die eine flexible Integration in verschiedene Systemarchitekturen ermöglicht. Die unidirektionalen Adapter gewährleisten eine klare Signalflussrichtung.

Vergleich mit [OR_2](../../../StandardLibraries/iec61131-3/bitwiseOperators/OR_2.md)

- **[`AX_OR_2`](AX_OR_2.md)**: Die gegatete Variante – aktualisiert den Ausgang nur bei tatsächlicher Wertänderung.

## 🛠️ Zugehörige Übungen

- [Uebung_002a3_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_002a3_AX.md)
- [Uebung_002b3_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_002b3_AX.md)
- [Uebung_035a2_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_035a2_AX.md)
- [Uebung_035a3_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_035a3_AX.md)
- [Uebung_160_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_160_AX.md)
- [Uebung_160b2_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_160b2_AX.md)
- [Uebung_160b_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_160b_AX.md)

## Änderungserkennung

Dieser Baustein führt **keine** Änderungserkennung durch. Jedes neu berechnete Ergebnis wird bedingungslos auf den Ausgang geschrieben und das zugehörige Adapter-Event gesendet, unabhängig davon, ob sich der Wert gegenüber dem vorherigen Durchlauf geändert hat.

## Fazit

Der AX_OR_2_UNGATED Funktionsblock bietet eine zuverlässige und einfach zu integrierende Lösung für boolesche ODER-Verknüpfungen in Automatisierungssystemen. Seine Adapter-basierte Architektur ermöglicht eine flexible Verwendung in verschiedenen Steuerungskontexten.

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
