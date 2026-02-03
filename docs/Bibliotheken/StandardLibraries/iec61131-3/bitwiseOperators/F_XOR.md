# F_XOR

```{index} single: F_XOR
```

<img width="1149" height="208" alt="F_XOR" src="https://github.com/user-attachments/assets/5f3451b6-8e0a-479b-9d80-1af4d73f9e69" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_XOR` führt eine bitweise XOR-Operation (exklusives ODER) auf zwei Eingabewerten durch. Er ist Teil der Standard-Bitoperationen gemäß IEC 61131-3 und eignet sich für logische Verarbeitungen in Steuerungsanwendungen.

![F_XOR](F_XOR.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Startet die XOR-Operation. Bei Aktivierung werden die Eingabedaten `IN1` und `IN2` verarbeitet.

### **Ereignis-Ausgänge**
- `CNF`: Bestätigt die erfolgreiche Durchführung der XOR-Operation und liefert das Ergebnis über den Ausgang `OUT`.

### **Daten-Eingänge**
- `IN1`: Erster Eingabewert für die XOR-Operation (Typ: `ANY_BIT`).
- `IN2`: Zweiter Eingabewert für die XOR-Operation (Typ: `ANY_BIT`).

### **Daten-Ausgänge**
- `OUT`: Ergebnis der bitweisen XOR-Operation (Typ: `ANY_BIT`).

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Bei Aktivierung des Ereigniseingangs `REQ` führt der Funktionsblock eine bitweise XOR-Operation zwischen den Werten `IN1` und `IN2` durch. Das Ergebnis wird über den Datenausgang `OUT` ausgegeben und das Ereignis `CNF` wird ausgelöst, um die Fertigstellung der Operation zu signalisieren.

## Technische Besonderheiten
- Unterstützt den Datentyp `ANY_BIT`, was bedeutet, dass verschiedene Bit-Datentypen (z.B. BOOL, BYTE, WORD, DWORD) verarbeitet werden können.
- Die Initialwerte der Eingänge sind leer, was eine explizite Zuweisung der Eingabewerte erfordert.

## Zustandsübersicht
1. **Idle-Zustand**: Wartet auf das Ereignis `REQ`.
2. **Verarbeitungszustand**: Führt die XOR-Operation durch, wenn `REQ` aktiviert wird.
3. **Ausgabe-Zustand**: Sendet das Ergebnis über `OUT` und löst `CNF` aus.

## Anwendungsszenarien
- Logische Verarbeitung in Steuerungssystemen.
- Bitweise Manipulation von Daten in industriellen Automatisierungsprozessen.
- Implementierung von Sicherheitschecks oder Prüfsummenberechnungen.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- **F_AND / F_OR**: Führen bitweise AND- bzw. OR-Operationen durch, während `F_XOR` eine exklusive ODER-Operation bietet.
- **F_NOT**: Invertiert Bits, während `F_XOR` zwei Eingabewerte vergleicht.

## Fazit
Der `F_XOR`-Funktionsblock ist ein effizientes Werkzeug für bitweise XOR-Operationen in IEC 61131-3-konformen Steuerungssystemen. Seine Flexibilität mit dem `ANY_BIT`-Datentyp macht ihn vielseitig einsetzbar in verschiedenen Automatisierungsanwendungen.