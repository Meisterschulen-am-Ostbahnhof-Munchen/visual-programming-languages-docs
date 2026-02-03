# AX_XOR_6

```{index} single: AX_XOR_6
```

<img width="1009" height="398" alt="image" src="https://github.com/user-attachments/assets/73123b00-75a5-4eed-a5ab-368c0216fd0f" />

* * * * * * * * * *

## Einleitung
Der AX_XOR_6 ist ein generischer Funktionsblock zur Berechnung der booleschen XOR-Verknüpfung mit sechs Eingängen. Der Baustein implementiert die exklusive ODER-Operation für bis zu sechs binäre Eingangssignale und gibt das Ergebnis über einen Adapter-Ausgang aus.

![AX_XOR_6](AX_XOR_6.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Keine Ereignis-Eingänge vorhanden.

### **Ereignis-Ausgänge**
Keine Ereignis-Ausgänge vorhanden.

### **Daten-Eingänge**
Keine direkten Daten-Eingänge vorhanden.

### **Daten-Ausgänge**
Keine direkten Daten-Ausgänge vorhanden.

### **Adapter**

**Plug-Adapter:**
- **OUT** (Typ: adapter::types::unidirectional::AX) - XOR-Ergebnis

**Socket-Adapter:**
- **IN1** (Typ: adapter::types::unidirectional::AX) - XOR-Eingang 1
- **IN2** (Typ: adapter::types::unidirectional::AX) - XOR-Eingang 2
- **IN3** (Typ: adapter::types::unidirectional::AX) - XOR-Eingang 3
- **IN4** (Typ: adapter::types::unidirectional::AX) - XOR-Eingang 4
- **IN5** (Typ: adapter::types::unidirectional::AX) - XOR-Eingang 5
- **IN6** (Typ: adapter::types::unidirectional::AX) - XOR-Eingang 6

## Funktionsweise
Der Funktionsblock berechnet die XOR-Verknüpfung aller sechs Eingänge. Die XOR-Operation liefert genau dann ein "wahr"-Signal (TRUE), wenn eine ungerade Anzahl der Eingänge auf "wahr" gesetzt ist. Bei einer geraden Anzahl von "wahr"-Eingängen wird "falsch" (FALSE) ausgegeben.

## Technische Besonderheiten
- Generischer Funktionsblock mit der generischen Klasse 'GEN_AX_XOR'
- Verwendet unidirektionale AX-Adapter für die Kommunikation
- Keine Ereignissteuerung - arbeitet kontinuierlich basierend auf den Eingangswerten
- Unterstützt sechs unabhängige Eingänge für komplexe XOR-Berechnungen

## Zustandsübersicht
Da es sich um einen rein kombinatorischen Baustein ohne Ereignissteuerung handelt, besitzt der AX_XOR_6 keine internen Zustände. Die Ausgabe wird ausschließlich durch die aktuellen Eingangswerte bestimmt.

## Anwendungsszenarien
- Paritätsprüfung in Datenübertragungssystemen
- Sicherheitskritische Steuerungen mit Mehrfachredundanz
- Fehlererkennung in binären Signalketten
- Verschlüsselungsalgorithmen mit XOR-Operationen
- Steuerungssysteme mit Mehrfacheingangs-Logik

## ⚖️ Vergleich mit ähnlichen Bausteinen
Im Vergleich zu Standard-XOR-Bausteinen mit weniger Eingängen bietet der AX_XOR_6 die Möglichkeit, bis zu sechs Signale gleichzeitig zu verarbeiten. Während einfache XOR-Blöcke typischerweise nur zwei Eingänge haben, ermöglicht dieser Baustein komplexere logische Verknüpfungen ohne zusätzliche Verschachtelung mehrerer Blöcke.

Vergleich mit [XOR_6](../../../StandardLibraries/iec61131-3/bitwiseOperators/XOR_6.md)

## Fazit
Der AX_XOR_6 ist ein spezialisierter Funktionsblock für anspruchsvolle XOR-Operationen mit mehreren Eingängen. Durch die Adapter-basierte Schnittstelle lässt er sich gut in bestehende Steuerungssysteme integrieren und bietet eine effiziente Lösung für komplexe boolesche Verknüpfungen ohne zusätzliche Verkabelungskomplexität.