# F_WORD_AS_WSTRING

```{index} single: F_WORD_AS_WSTRING
```

<img width="1477" height="214" alt="F_WORD_AS_WSTRING" src="https://github.com/user-attachments/assets/0501be71-0ef4-45a0-a24e-fc55d97986ca" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_WORD_AS_WSTRING` dient der Konvertierung eines `WORD`-Datentyps in einen `WSTRING`-Datentyp. Dieser Baustein ist besonders nützlich in Szenarien, wo numerische Werte in eine Zeichenkette umgewandelt werden müssen, beispielsweise für die Anzeige oder Protokollierung.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Wird dieser Eingang ausgelöst, wird der Wert am Daten-Eingang `IN` verarbeitet.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der konvertierte Wert steht am Daten-Ausgang `OUT` zur Verfügung.

### **Daten-Eingänge**
- **IN** (`WORD`): Der Eingangswert, der in einen `WSTRING` umgewandelt werden soll.

### **Daten-Ausgänge**
- **OUT** (`WSTRING`): Der Ausgangswert nach der Konvertierung.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter.

## Funktionsweise
Bei Auslösung des Ereigniseingangs `REQ` wird der Algorithmus ausgeführt, der den Wert am Eingang `IN` vom Typ `WORD` in einen `WSTRING` umwandelt. Das Ergebnis wird am Ausgang `OUT` bereitgestellt und das Ereignis `CNF` signalisiert die erfolgreiche Ausführung.

## Technische Besonderheiten
- Die Konvertierung erfolgt direkt und ohne Zwischenschritte.
- Der Baustein ist für einfache Konvertierungen optimiert und benötigt keine zusätzliche Konfiguration.

## Zustandsübersicht
1. **Idle**: Wartet auf das `REQ`-Ereignis.
2. **Processing**: Führt die Konvertierung durch.
3. **Completed**: Signalisiert mit `CNF` den Abschluss.

## Anwendungsszenarien
- Anzeige von numerischen Werten in einer Benutzeroberfläche.
- Protokollierung von `WORD`-Werten als lesbare Zeichenketten.
- Datenkonvertierung für die Kommunikation mit Systemen, die `WSTRING` erwarten.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsbausteinen ist `F_WORD_AS_WSTRING` spezialisiert und daher effizienter für diese spezifische Aufgabe.
- Andere Bausteine könnten zusätzliche Parameter oder komplexere Konvertierungen unterstützen, was hier nicht notwendig ist.

## Fazit
Der `F_WORD_AS_WSTRING`-Funktionsblock ist ein einfacher und effizienter Baustein für die Konvertierung von `WORD` zu `WSTRING`. Seine Stärke liegt in der Einfachheit und direkten Anwendbarkeit für spezifische Konvertierungsaufgaben.
