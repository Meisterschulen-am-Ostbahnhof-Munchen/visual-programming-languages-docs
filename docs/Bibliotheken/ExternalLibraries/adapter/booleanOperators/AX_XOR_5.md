# AX_XOR_5

```{index} single: AX_XOR_5
```

<img width="1009" height="366" alt="image" src="https://github.com/user-attachments/assets/cb5ecc68-f421-4466-a82b-f877edbb13f0" />

* * * * * * * * * *

## Einleitung
Der AX_XOR_5 ist ein generischer Funktionsblock zur Berechnung der booleschen XOR-Verknüpfung mit fünf Eingängen. Der Baustein implementiert die exklusive ODER-Operation für bis zu fünf Eingangssignale und gibt das Ergebnis über einen Adapter-Ausgang aus.

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

**Eingangsadapter:**
- **IN1**: XOR-Eingang 1 (unidirektionaler AX-Adapter)
- **IN2**: XOR-Eingang 2 (unidirektionaler AX-Adapter)
- **IN3**: XOR-Eingang 3 (unidirektionaler AX-Adapter)
- **IN4**: XOR-Eingang 4 (unidirektionaler AX-Adapter)
- **IN5**: XOR-Eingang 5 (unidirektionaler AX-Adapter)

**Ausgangsadapter:**
- **OUT**: XOR-Ergebnis (unidirektionaler AX-Adapter)

## Funktionsweise
Der Funktionsblock berechnet die XOR-Verknüpfung über alle fünf Eingänge. Die XOR-Operation (exklusives ODER) liefert genau dann ein "wahr"-Signal, wenn eine ungerade Anzahl der Eingänge aktiv ist. Bei einer geraden Anzahl aktiver Eingänge wird "falsch" ausgegeben.

Die mathematische Formel lautet:
```
OUT = IN1 XOR IN2 XOR IN3 XOR IN4 XOR IN5
```

## Technische Besonderheiten
- Verwendet unidirektionale AX-Adapter für alle Schnittstellen
- Implementiert als generischer Funktionsblock mit der Bezeichnung 'GEN_AX_XOR'
- Unterstützt bis zu fünf unabhängige Eingangssignale
- Keine Ereignissteuerung - arbeitet kontinuierlich basierend auf den Adapter-Eingängen

## Zustandsübersicht
Da es sich um einen kombinatorischen Logikbaustein ohne Speicherfunktion handelt, besitzt der AX_XOR_5 keine internen Zustände. Die Ausgabe wird ausschließlich durch die aktuellen Eingangswerte bestimmt.

## Anwendungsszenarien
- Paritätsprüfung in digitalen Schaltungen
- Fehlererkennung in Sicherheitssystemen
- Steuerungslogik mit Mehrfachbedingungen
- Verteilte Entscheidungsfindung in Automatisierungssystemen
- Sicherheitskritische Anwendungen mit redundanten Sensoren

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu Standard-XOR-Bausteinen mit weniger Eingängen bietet AX_XOR_5 die Möglichkeit, bis zu fünf Signale gleichzeitig zu verarbeiten. Während einfache XOR-Blöcke typischerweise nur zwei Eingänge haben, ermöglicht dieser Baustein komplexere logische Verknüpfungen ohne zusätzliche Verschachtelung.

Vergleich mit [XOR_5](../../../StandardLibraries/iec61131-3/bitwiseOperators/XOR_5.md)

## Fazit
Der AX_XOR_5 Funktionsblock stellt eine flexible Lösung für XOR-Operationen mit mehreren Eingängen dar. Seine Adapter-basierte Schnittstelle ermöglicht eine einfache Integration in bestehende Steuerungssysteme, während die generische Implementierung Wiederverwendbarkeit und Erweiterbarkeit gewährleistet.