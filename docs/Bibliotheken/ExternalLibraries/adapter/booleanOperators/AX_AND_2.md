# AX_AND_2

```{index} single: AX_AND_2
```

<img width="1009" height="265" alt="image" src="https://github.com/user-attachments/assets/e9225b9f-ba25-427f-bf49-71f15c562b73" />

* * * * * * * * * *
## Einleitung
Der AX_AND_2 ist ein generischer Funktionsblock zur Berechnung der logischen UND-Verknüpfung. Der Baustein verarbeitet zwei boolesche Eingangssignale und gibt das logische UND-Ergebnis aus.

![AX_AND_2](AX_AND_2.svg)

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
Da es sich um einen kombinatorischen Logikbaustein handelt, besitzt der AX_AND_2 keine internen Zustände. Die Ausgabe wird direkt aus den aktuellen Eingangswerten berechnet.

## Anwendungsszenarien
- Sicherheitskritische Steuerungen, bei denen zwei Bedingungen gleichzeitig erfüllt sein müssen
- Verknüpfung von Sensorsignalen in industriellen Automatisierungsanlagen
- Logische Verknüpfungen in Steuerungssystemen
- Sicherheitsabschaltungen mit Mehrfachbedingungen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu standardmäßigen UND-Bausteinen verwendet AX_AND_2 Adapter-basierte Schnittstellen anstelle von direkten Daten- und Ereignisein-/ausgängen. Dies ermöglicht eine flexiblere Integration in Adapter-basierte Systemarchitekturen.

Vergleich [AND_2](../../../StandardLibraries/iec61131-3/bitwiseOperators/AND_2.md)




## Zugehörige Übungen

* [Uebung_002a_AX](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_002a_AX.md)
* [Uebung_002b3_AX](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_002b3_AX.md)
* [Uebung_006a3_AX](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_006a3_AX.md)

## Fazit
Der AX_AND_2 bietet eine zuverlässige und standardkonforme Implementierung der logischen UND-Funktion mit Adapter-basierten Schnittstellen. Seine generische Natur macht ihn vielseitig einsetzbar in verschiedenen Automatisierungsprojekten, die nach IEC 61499-Standard entwickelt werden.