# AND_8

<img width="1123" height="360" alt="AND_8" src="https://github.com/user-attachments/assets/355c40e0-f2ad-48ea-be24-7a6449093f41" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `AND_8` führt eine bitweise logische UND-Operation auf bis zu acht Eingängen durch. Es handelt sich um einen generischen Funktionsblock, der mit verschiedenen Bit-Datentypen arbeiten kann. Der Block ist gemäß der Norm IEC 61131-3 klassifiziert und dient zur Verarbeitung von booleschen Operationen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung des Funktionsblocks. Die Operation wird ausgeführt, wenn dieses Ereignis eintritt. Es ist mit allen Daten-Eingängen verknüpft (`IN1` bis `IN8`).

### **Ereignis-Ausgänge**
- **CNF**: Bestätigt die Ausführung des Funktionsblocks. Dieses Ereignis wird nach der Berechnung ausgegeben und ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN1** bis **IN8** (`ANY_BIT`): Acht Eingänge für die bitweise UND-Operation. Jeder Eingang kann einen beliebigen Bit-Datentyp (z.B. BOOL, BYTE, WORD, DWORD, LWORD) annehmen.

### **Daten-Ausgänge**
- **OUT** (`ANY_BIT`): Das Ergebnis der bitweisen UND-Operation aller Eingänge. Der Datentyp entspricht dem der Eingänge.

### **Adapter**
Der Funktionsblock verfügt über keine Adapter.

## Funktionsweise
Der `AND_8`-Block führt eine bitweise UND-Operation auf den Werten aller aktiven Eingänge (`IN1` bis `IN8`) aus. Das Ergebnis wird am Ausgang `OUT` ausgegeben. Die Operation wird durch das Ereignis `REQ` gestartet und durch `CNF` bestätigt.

## Technische Besonderheiten
- **Generische Implementierung**: Der Block kann mit verschiedenen Bit-Datentypen arbeiten, da die Eingänge und Ausgänge vom Typ `ANY_BIT` sind.
- **Flexible Eingangsanzahl**: Bis zu acht Eingänge können verwendet werden, wobei nicht alle zwingend belegt sein müssen.

## Zustandsübersicht
1. **Idle-Zustand**: Der Block wartet auf das Ereignis `REQ`.
2. **Ausführungszustand**: Bei `REQ` werden die Eingänge verarbeitet und das Ergebnis berechnet.
3. **Bestätigungszustand**: Nach der Berechnung wird `CNF` ausgelöst und das Ergebnis an `OUT` ausgegeben.

## Anwendungsszenarien
- Logische Verknüpfung mehrerer Bit-Signale in Steuerungsanwendungen.
- Filterung von Signalen durch bitweise Maskierung.
- Generische Verarbeitung von Bit-Daten in komplexen Automatisierungssystemen.

## Vergleich mit ähnlichen Bausteinen
- **AND (Standard)**: Standard-UND-Block mit typischerweise zwei Eingängen. `AND_8` bietet mehr Flexibilität durch acht Eingänge und generische Typen.
- **GEN_AND**: Generische UND-Implementierung, die als Basis für `AND_8` dient. `AND_8` ist eine spezialisierte Version mit fester Eingangsanzahl.

## Fazit
Der `AND_8`-Funktionsblock ist ein leistungsfähiges Werkzeug für bitweise logische Operationen in IEC 61131-3-konformen Steuerungssystemen. Seine generische Natur und flexible Eingangsanzahl machen ihn besonders vielseitig einsetzbar.
