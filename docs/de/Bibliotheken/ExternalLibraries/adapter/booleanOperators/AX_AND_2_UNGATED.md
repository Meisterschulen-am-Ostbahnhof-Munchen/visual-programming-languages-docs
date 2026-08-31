# AX_AND_2_UNGATED

> ℹ️ **UNGATED-Variante:** Dieser Baustein ist die ungegatete Version von [`AX_AND_2`](AX_AND_2.md). Er unterdrückt **keine** unveränderten Wiederholungen – jedes neu berechnete Ergebnis wird bedingungslos weitergegeben, auch ohne Wertänderung. Das ist wichtig für Verbraucher, die eine periodische Kadenz unabhängig von Wertänderung brauchen (z. B. Ableitungs-/Frequenzberechnungen, die sonst nicht gegen Null abklingen). Alle Angaben zu Änderungserkennung/Change-Gating weiter unten auf dieser Seite gelten **nicht** für diesen Baustein.

<img width="1009" height="265" alt="image" src="https://github.com/user-attachments/assets/e9225b9f-ba25-427f-bf49-71f15c562b73" />

* * * * * * * * * *

## Einleitung

Der AX_AND_2_UNGATED ist ein generischer Funktionsblock zur Berechnung der logischen UND-Verknüpfung. Der Baustein verarbeitet zwei boolesche Eingangssignale und gibt das logische UND-Ergebnis aus.

![AX_AND_2_UNGATED](AX_AND_2_UNGATED.svg)

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

- **IN1** - UND-Eingang 1 (Adapter-Typ: adapter::types::unidirectional::AX)
- **IN2** - UND-Eingang 2 (Adapter-Typ: adapter::types::unidirectional::AX)

**Ausgangsadapter:**

- **OUT** - UND-Ergebnis (Adapter-Typ: adapter::types::unidirectional::AX)

## Funktionsweise

Der Funktionsblock führt eine logische UND-Verknüpfung der beiden Eingangssignale IN1 und IN2 durch. Das Ergebnis wird über den Ausgangsadapter OUT ausgegeben. Die Verarbeitung erfolgt unidirektional über die Adapterschnittstellen.

## Technische Besonderheiten

- Generischer Funktionsblock mit spezifischem Klassennamen 'GEN_AX_AND'
- Verwendet unidirektionale Adapter für die Signalübertragung
- Implementiert gemäß IEC 61499-2 Standard

## Zustandsübersicht

Da es sich um einen kombinatorischen Logikbaustein handelt, besitzt der AX_AND_2_UNGATED keine internen Zustände. Die Ausgabe wird direkt aus den aktuellen Eingangswerten berechnet.

## Anwendungsszenarien

- Sicherheitskritische Steuerungen, bei denen zwei Bedingungen gleichzeitig erfüllt sein müssen
- Verknüpfung von Sensorsignalen in industriellen Automatisierungsanlagen
- Logische Verknüpfungen in Steuerungssystemen
- Sicherheitsabschaltungen mit Mehrfachbedingungen

## ⚖️ Vergleich mit ähnlichen Bausteinen

Im Vergleich zu standardmäßigen UND-Bausteinen verwendet AX_AND_2_UNGATED Adapter-basierte Schnittstellen anstelle von direkten Daten- und Ereignisein-/ausgängen. Dies ermöglicht eine flexiblere Integration in Adapter-basierte Systemarchitekturen.

Vergleich [AND_2](../../../StandardLibraries/iec61131-3/bitwiseOperators/AND_2.md)

- **[`AX_AND_2`](AX_AND_2.md)**: Die gegatete Variante – aktualisiert den Ausgang nur bei tatsächlicher Wertänderung.

## 🛠️ Zugehörige Übungen

- [Uebung_002a_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_002a_AX.md)
- [Uebung_002b3_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_002b3_AX.md)
- [Uebung_006a3_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_006a3_AX.md)

## Änderungserkennung

Dieser Baustein führt **keine** Änderungserkennung durch. Jedes neu berechnete Ergebnis wird bedingungslos auf den Ausgang geschrieben und das zugehörige Adapter-Event gesendet, unabhängig davon, ob sich der Wert gegenüber dem vorherigen Durchlauf geändert hat.

## Fazit

Der AX_AND_2_UNGATED bietet eine zuverlässige und standardkonforme Implementierung der logischen UND-Funktion mit Adapter-basierten Schnittstellen. Seine generische Natur macht ihn vielseitig einsetzbar in verschiedenen Automatisierungsprojekten, die nach IEC 61499-Standard entwickelt werden.
