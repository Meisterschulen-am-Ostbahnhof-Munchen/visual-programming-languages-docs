# F_ULINT_TO_REAL

```{index} single: F_ULINT_TO_REAL
```

<img width="1451" height="214" alt="F_ULINT_TO_REAL" src="https://github.com/user-attachments/assets/d7208c65-91e3-47f3-bfd6-6141f68edc4f" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_ULINT_TO_REAL` dient der Konvertierung eines `ULINT`-Wertes (64-Bit vorzeichenlose Ganzzahl) in einen `REAL`-Wert (32-Bit Gleitkommazahl). Dieser Baustein ist besonders nützlich in Szenarien, wo eine Typumwandlung zwischen diesen beiden Datentypen erforderlich ist.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingangswert vom Typ `ULINT`, der in einen `REAL`-Wert umgewandelt werden soll.

### **Daten-Ausgänge**
- **OUT**: Der Ausgangswert vom Typ `REAL`, der das Ergebnis der Konvertierung darstellt.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, sobald das Ereignis `REQ` ausgelöst wird. Der Algorithmus innerhalb des Bausteins nutzt die Funktion `ULINT_TO_REAL`, um den `ULINT`-Wert in einen `REAL`-Wert umzuwandeln. Das Ergebnis wird über den Daten-Ausgang `OUT` ausgegeben und das Ereignis `CNF` signalisiert die erfolgreiche Ausführung.

## Technische Besonderheiten
- Der Funktionsblock ist Teil des Pakets `iec61131::conversion`.
- Unterstützt die Konvertierung von 64-Bit vorzeichenlosen Ganzzahlen zu 32-Bit Gleitkommazahlen.
- Einfache und direkte Implementierung ohne zusätzliche Parameter oder komplexe Logik.

## Zustandsübersicht
Der Funktionsblock hat einen einfachen Zustandsautomaten:
1. **Idle**: Wartet auf das `REQ`-Ereignis.
2. **Processing**: Führt die Konvertierung durch.
3. **Complete**: Sendet das `CNF`-Ereignis und gibt das Ergebnis aus.

## Anwendungsszenarien
- Datenverarbeitung in Steuerungssystemen, wo eine Typumwandlung erforderlich ist.
- Integration in größere Steuerungsalgorithmen, die Gleitkommaberechnungen mit ursprünglich als Ganzzahlen gespeicherten Werten durchführen.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Funktionsblöcke wie `F_DINT_TO_REAL` oder `F_LINT_TO_REAL` bieten Konvertierungen von anderen Ganzzahltypen zu `REAL`, jedoch mit unterschiedlichen Eingangsgrößen und Präzisionen.
- `F_ULINT_TO_REAL` ist spezifisch für 64-Bit vorzeichenlose Ganzzahlen optimiert.

## Fazit
Der `F_ULINT_TO_REAL`-Funktionsblock ist ein einfacher, aber essentieller Baustein für die Typumwandlung in IEC 61499-basierten Steuerungssystemen. Seine klare Schnittstelle und effiziente Funktionsweise machen ihn zu einer zuverlässigen Lösung für Konvertierungsaufgaben.