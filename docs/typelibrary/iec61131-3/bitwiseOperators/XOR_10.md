# XOR_10

<img width="400" alt="XOR_10 Funktionsblock" src="https://github.com/user-attachments/assets/7fb9f08e-7e56-4861-be45-c8e99338ca01" />


* * * * * * * * * *

## Einleitung
Der XOR_10 Funktionsblock ist ein generischer Baustein zur Berechnung einer bitweisen XOR-Verknüpfung mit bis zu 10 Eingängen. Er ist Teil der IEC 61131-3 Standardbibliothek für bitweise boolesche Operationen und kann mit verschiedenen Bit-Datentypen (ANY_BIT) verwendet werden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Berechnung der XOR-Verknüpfung. Verknüpft mit allen Daten-Eingängen (IN1 bis IN10).

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert die Beendigung der Berechnung und liefert das Ergebnis über den OUT-Ausgang.

### **Daten-Eingänge**
- **IN1** bis **IN10** (ANY_BIT): Bis zu 10 Eingangswerte für die XOR-Berechnung. Jeder Eingang kann einen beliebigen Bit-Datentyp (BOOL, BYTE, WORD, DWORD, LWORD) enthalten.

### **Daten-Ausgänge**
- **OUT** (ANY_BIT): Ergebnis der bitweisen XOR-Verknüpfung aller aktiven Eingänge.

### **Adapter**
Dieser FB verwendet keine Adapter.

## Funktionsweise
Bei Empfang des REQ-Ereignisses berechnet der FB eine bitweise XOR-Verknüpfung aller aktiven Eingänge (IN1 bis IN10). Das Ergebnis wird am OUT-Ausgang ausgegeben und das CNF-Ereignis ausgelöst.

Die XOR-Operation wird für jedes Bitposition separat durchgeführt:
- Ergebnisbit = 1, wenn eine ungerade Anzahl von Eingangsbits an dieser Position 1 ist
- Ergebnisbit = 0, wenn eine gerade Anzahl von Eingangsbits an dieser Position 1 ist

## Technische Besonderheiten
- Unterstützt generische Bit-Datentypen (ANY_BIT)
- Verarbeitet bis zu 10 Eingangswerte
- Alle Eingänge müssen denselben Datentyp haben
- Nicht verwendete Eingänge werden als 0 behandelt
- Teil des `iec61131::bitwiseOperators` Pakets

## Zustandsübersicht
1. **Wartezustand**: Wartet auf REQ-Ereignis
2. **Berechnungszustand**: Führt XOR-Operation durch
3. **Ausgabezustand**: Sendet Ergebnis und CNF-Ereignis
4. Rückkehr in Wartezustand

## Anwendungsszenarien
- Bitweise Verschlüsselungsoperationen
- Paritätsprüfungen
- Fehlererkennung in digitalen Systemen
- Steuerungslogik mit mehreren Eingangssignalen
- Generische Logikoperationen in Automatisierungssystemen

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu einfachen XOR-Blöcken mit 2 Eingängen bietet XOR_10 mehr Flexibilität
- Ähnlich zu OR_10/AND_10 Blöcken, aber mit XOR-Logik
- Generische Implementierung im Gegensatz zu typ-spezifischen Blöcken (z.B. XOR_BOOL, XOR_WORD)

## Fazit
Der XOR_10 Funktionsblock bietet eine flexible Lösung für komplexe bitweise XOR-Operationen in IEC 61131-3 basierten Steuerungssystemen. Seine generische Natur und Unterstützung für bis zu 10 Eingänge machen ihn besonders geeignet für Anwendungen, die mehr als die traditionellen zwei Eingänge erfordern.
