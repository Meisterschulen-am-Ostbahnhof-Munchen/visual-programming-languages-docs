# XOR_9

<img width="1122" height="386" alt="XOR_9" src="https://github.com/user-attachments/assets/c115089f-b2d9-4440-8c6f-6db5cba185f8" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `XOR_9` dient zur bitweisen Berechnung der XOR-Verknüpfung mit bis zu neun Eingängen. Er ist Teil der Standard-Bitoperationen gemäß IEC 61131-3 und ermöglicht die Verarbeitung beliebiger Bit-Datentypen (`ANY_BIT`).

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ` (Normal Execution Request): Startet die Berechnung der XOR-Verknüpfung. Löst die Auswertung aller verknüpften Daten-Eingänge aus.

### **Ereignis-Ausgänge**
- `CNF` (Execution Confirmation): Signalisiert den Abschluss der Berechnung und liefert das Ergebnis über den Daten-Ausgang `OUT`.

### **Daten-Eingänge**
- `IN1` bis `IN9` (XOR input 1-9): Bis zu neun Eingänge für die bitweise XOR-Verknüpfung. Jeder Eingang unterstützt den Datentyp `ANY_BIT` (z.B. BOOL, BYTE, WORD, DWORD, LWORD).

### **Daten-Ausgänge**
- `OUT` (XOR result): Ergebnis der bitweisen XOR-Verknüpfung aller aktiven Eingänge. Der Datentyp entspricht dem der Eingänge (`ANY_BIT`).

### **Adapter**
Der Funktionsblock verfügt über keine Adapter.

## Funktionsweise
Bei Auslösung des `REQ`-Ereignisses berechnet der FB die XOR-Verknüpfung aller übergebenen Eingangswerte (`IN1` bis `IN9`). Das Ergebnis wird an `OUT` ausgegeben und das `CNF`-Ereignis signalisiert die Bereitschaft des Ergebnisses. 

**Beispiel (für BOOL-Eingänge):**  
`OUT = IN1 XOR IN2 XOR ... XOR IN9`

## Technische Besonderheiten
- **Generische Implementierung:** Unterstützt alle `ANY_BIT`-Datentypen durch Verwendung der generischen Klasse `GEN_XOR`.
- **Flexible Eingangsanzahl:** Nicht genutzte Eingänge werden ignoriert (wirken als neutrale Elemente).
- **Bitweise Operation:** Die Verknüpfung erfolgt für jedes Bit separat (bei mehrbitigen Datentypen).

## Zustandsübersicht
1. **Idle:** Wartet auf `REQ`-Ereignis.
2. **Processing:** Berechnet XOR und setzt `OUT`.
3. **Ready:** Sendet `CNF` und kehrt nach Idle zurück.

## Anwendungsszenarien
- Paritätsprüfung in Kommunikationsprotokollen
- Toggeln von Steuersignalen (z.B. Wechsel zwischen Zuständen)
- Kryptografische Grundoperationen
- Fehlererkennung in Binärdaten

## Vergleich mit ähnlichen Bausteinen
| Feature        | XOR_9       | Standard-XOR (2 Eingänge) |
|---------------|-------------|---------------------------|
| Eingangsanzahl | 9           | 2                         |
| Datentyp       | ANY_BIT     | Typabhängig (z.B. BOOL)   |
| Flexibilität   | Hoch        | Gering                    |

## Fazit
Der `XOR_9`-FB erweitert die klassische XOR-Funktionalität durch Unterstützung mehrerer Eingänge und generischer Datentypen. Ideal für Anwendungen, die komplexere bitweise Verknüpfungen erfordern, ohne individuelle FB-Ketten aufbauen zu müssen. Die IEC 61131-3-Konformität gewährleistet breite Kompatibilität.
