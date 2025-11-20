# F_OR

<img width="1324" height="244" alt="F_OR" src="https://github.com/user-attachments/assets/aef4acae-7a18-40f2-85a5-69e0c6e0ef3b" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_OR` implementiert eine bitweise ODER-Verknüpfung gemäß dem IEC 61131-3 Standard. Er führt eine logische ODER-Operation auf zwei Eingangsvariablen vom Typ `ANY_BIT` durch und gibt das Ergebnis auf dem Ausgang aus.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung der ODER-Operation. Bei diesem Ereignis werden die Eingänge `IN1` und `IN2` ausgewertet.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert die erfolgreiche Beendigung der Operation. Dieses Ereignis wird zusammen mit dem Ergebnis `OUT` ausgegeben.

### **Daten-Eingänge**
- **IN1**: Erster Eingang für die bitweise ODER-Verknüpfung (Typ: `ANY_BIT`).
- **IN2**: Zweiter Eingang für die bitweise ODER-Verknüpfung (Typ: `ANY_BIT`).

### **Daten-Ausgänge**
- **OUT**: Ergebnis der bitweisen ODER-Verknüpfung (Typ: `ANY_BIT`).

### **Adapter**
Der Funktionsblock verwendet keine Adapter.

## Funktionsweise
Bei Auslösung des `REQ`-Ereignisses führt der `F_OR`-Block eine bitweise ODER-Verknüpfung der Werte an `IN1` und `IN2` durch. Das Ergebnis wird an `OUT` ausgegeben und das `CNF`-Ereignis signalisiert die erfolgreiche Berechnung.

## Technische Besonderheiten
- **Typflexibilität**: Unterstützt alle `ANY_BIT`-Datentypen (z.B. BOOL, BYTE, WORD, DWORD, LWORD).
- **Einfache Implementierung**: Keine Zustandsmaschine erforderlich, da es sich um eine statische Operation handelt.

## Zustandsübersicht
Der Funktionsblock besitzt keine interne Zustandsmaschine, da die Operation direkt bei Auftreten des `REQ`-Ereignisses durchgeführt wird.

## Anwendungsszenarien
- Bitweise Verknüpfung in Steuerungsalgorithmen
- Maskenoperationen in der Signalverarbeitung
- Logische Kombination von digitalen Signalen

## Vergleich mit ähnlichen Bausteinen
- **F_AND**: Führt eine bitweise UND-Verknüpfung durch
- **F_XOR**: Führt eine bitweise exklusive ODER-Verknüpfung durch
- **F_NOT**: Führt eine bitweise Negation durch

## Fazit
Der `F_OR`-Funktionsblock bietet eine einfache und effiziente Möglichkeit, bitweise ODER-Operationen in IEC 61131-3-konformen Steuerungssystemen durchzuführen. Seine Typflexibilität und direkte Funktionsweise machen ihn zu einem universell einsetzbaren Baustein für logische Verknüpfungen.
