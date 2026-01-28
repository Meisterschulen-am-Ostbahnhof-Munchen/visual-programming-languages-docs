# AX_XOR_2

```{index} single: AX_XOR_2
```

<img width="1009" height="261" alt="image" src="https://github.com/user-attachments/assets/8e5ec6ce-d2bb-4517-ac38-d14a7e43976b" />

* * * * * * * * * *
## Einleitung
Der AX_XOR_2 Funktionsblock ist ein generischer Baustein zur Berechnung der booleschen XOR-Operation (exklusives ODER). Er verarbeitet zwei Eingangssignale und gibt das logische XOR-Ergebnis aus.

![AX_XOR_2](AX_XOR_2.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Keine direkten Ereigniseingänge vorhanden - die Verarbeitung erfolgt über Adapter-Schnittstellen.

### **Ereignis-Ausgänge**
Keine direkten Ereignisausgänge vorhanden - die Ausgabe erfolgt über Adapter-Schnittstellen.

### **Daten-Eingänge**
Keine direkten Dateneingänge vorhanden - die Eingabe erfolgt über Adapter-Schnittstellen.

### **Daten-Ausgänge**
Keine direkten Datenausgänge vorhanden - die Ausgabe erfolgt über Adapter-Schnittstellen.

### **Adapter**
- **IN1** (Socket): XOR-Eingang 1 - Empfängt das erste Eingangssignal
- **IN2** (Socket): XOR-Eingang 2 - Empfängt das zweite Eingangssignal
- **OUT** (Plug): XOR-Ergebnis - Gibt das berechnete XOR-Ergebnis aus

Alle Adapter verwenden den Typ `adapter::types::unidirectional::AX` für unidirektionale Kommunikation.

## Funktionsweise
Der Funktionsblock berechnet kontinuierlich die XOR-Operation zwischen den beiden Eingangssignalen IN1 und IN2. Die XOR-Funktion gibt genau dann ein wahr-Signal (TRUE) aus, wenn genau einer der beiden Eingänge wahr ist (TRUE). Sind beide Eingänge gleich (beide TRUE oder beide FALSE), wird ein falsch-Signal (FALSE) ausgegeben.

## Technische Besonderheiten
- Generischer Funktionsblock mit der Klasse `GEN_AX_XOR`
- Verwendet unidirektionale Adapter für Ein- und Ausgaben
- Implementiert gemäß IEC 61499-2 Standard
- Teil des Pakets `adapter::booleanOperators`

## Zustandsübersicht
Der Baustein besitzt einen kontinuierlichen Betriebszustand und berechnet permanent das XOR-Ergebnis basierend auf den aktuellen Eingangswerten.

## Anwendungsszenarien
- Logische Schaltungen in Steuerungssystemen
- Vergleich von zwei binären Signalen
- Erkennung von Signalunterschieden
- Sicherheitsrelevante Schaltungen
- Digitale Signalverarbeitung

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen logischen Operatoren wie AND oder OR bietet XOR die Besonderheit, dass nur bei unterschiedlichen Eingangswerten ein TRUE-Signal erzeugt wird. Dies macht ihn besonders geeignet für Vergleichs- und Differenzerkennungsaufgaben.

Vergleich mit [XOR_2](../../../StandardLibraries/iec61131-3/bitwiseOperators/XOR_2.md)

## Fazit
Der AX_XOR_2 Funktionsblock stellt eine effiziente und zuverlässige Lösung für XOR-Operationen in 4diac-basierten Steuerungssystemen dar. Durch die Verwendung von Adapter-Schnittstellen ermöglicht er eine flexible Integration in verschiedene Systemarchitekturen und eignet sich besonders für Anwendungen, bei denen Signalunterschiede erkannt werden müssen.