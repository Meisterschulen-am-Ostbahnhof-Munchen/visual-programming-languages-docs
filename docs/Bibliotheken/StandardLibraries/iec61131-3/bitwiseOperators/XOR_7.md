# XOR_7

```{index} single: XOR_7
```

<img width="1308" height="390" alt="XOR_7" src="https://github.com/user-attachments/assets/8d4bc1de-83b7-41c4-bcdf-e5f584e271dd" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `XOR_7` führt eine bitweise XOR-Operation auf sieben Eingabewerten durch. Es handelt sich um einen generischen Funktionsblock, der mit verschiedenen Bit-Datentypen (z.B. BOOL, BYTE, WORD, DWORD, LWORD) verwendet werden kann. Der Block ist gemäß dem IEC 61131-3 Standard klassifiziert und dient zur Verarbeitung boolescher Operationen.

![XOR_7](XOR_7.svg)

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ** (Normal Execution Request): Löst die Berechnung der XOR-Operation aus. Wird mit allen Daten-Eingängen (`IN1` bis `IN7`) verknüpft.

### **Ereignis-Ausgänge**
- **CNF** (Execution Confirmation): Signalisiert die erfolgreiche Berechnung und liefert das Ergebnis über den Daten-Ausgang `OUT`.

### **Daten-Eingänge**
- **IN1** (XOR input 1): Erster Eingabewert (Typ: `ANY_BIT`).
- **IN2** (XOR input 2): Zweiter Eingabewert (Typ: `ANY_BIT`).
- **IN3** (XOR input 3): Dritter Eingabewert (Typ: `ANY_BIT`).
- **IN4** (XOR input 4): Vierter Eingabewert (Typ: `ANY_BIT`).
- **IN5** (XOR input 5): Fünfter Eingabewert (Typ: `ANY_BIT`).
- **IN6** (XOR input 6): Sechster Eingabewert (Typ: `ANY_BIT`).
- **IN7** (XOR input 7): Siebter Eingabewert (Typ: `ANY_BIT`).

### **Daten-Ausgänge**
- **OUT** (XOR result): Ergebnis der bitweisen XOR-Operation (Typ: `ANY_BIT`).

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt eine bitweise XOR-Operation auf den sieben Eingabewerten (`IN1` bis `IN7`) aus. Die Operation wird durch das Ereignis `REQ` ausgelöst. Das Ergebnis wird über den Ausgang `OUT` ausgegeben und durch das Ereignis `CNF` bestätigt.

## Technische Besonderheiten
- **Generische Implementierung**: Unterstützt verschiedene Bit-Datentypen (`ANY_BIT`).
- **Flexibilität**: Kann mit bis zu sieben Eingabewerten arbeiten.
- **Standardkonform**: Entspricht dem IEC 61131-3 Standard.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Operation wird bei jedem `REQ`-Ereignis neu ausgeführt.

## Anwendungsszenarien
- Bitweise Verschlüsselung.
- Fehlererkennung in Datenübertragungen.
- Logische Steuerungen in Automatisierungssystemen.

## Vergleich mit ähnlichen Bausteinen
- **XOR (Standard)**: Bietet typischerweise nur zwei Eingänge, während `XOR_7` sieben Eingänge unterstützt.
- **AND/OR-Blöcke**: Führen andere logische Operationen durch, während `XOR_7` spezifisch für die XOR-Operation optimiert ist.

## Fazit
Der `XOR_7`-Funktionsblock ist ein leistungsfähiges Werkzeug für bitweise XOR-Operationen mit bis zu sieben Eingabewerten. Seine generische Natur und Standardkonformität machen ihn vielseitig einsetzbar in verschiedenen Automatisierungs- und Steuerungsszenarien.