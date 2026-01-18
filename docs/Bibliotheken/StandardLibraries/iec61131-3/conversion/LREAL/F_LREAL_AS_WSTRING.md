# F_LREAL_AS_WSTRING

```{index} single: F_LREAL_AS_WSTRING
```

<img width="1280" height="182" alt="F_LREAL_AS_WSTRING" src="https://github.com/user-attachments/assets/440d684c-51cd-48e7-a918-9a5a0d6dcc22" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_LREAL_AS_WSTRING` dient der Konvertierung eines LREAL-Wertes (64-Bit Fließkommazahl) in einen WSTRING (Wide-String). Dies ist besonders nützlich, wenn numerische Werte für die Anzeige oder Weiterverarbeitung als Text benötigt werden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung des Eingabewertes. Der Eingabewert `IN` wird mit diesem Ereignis verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgabewert `OUT` wird mit diesem Ereignis ausgegeben.

### **Daten-Eingänge**
- **IN** (LREAL): Der Eingabewert, der in einen WSTRING konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (WSTRING): Der Ergebnisstring nach der Konvertierung.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Bei Auslösung des `REQ`-Ereignisses wird der Eingabewert `IN` vom Typ LREAL mit der Funktion `LREAL_AS_WSTRING` in einen WSTRING konvertiert und am Ausgang `OUT` bereitgestellt. Das `CNF`-Ereignis signalisiert die erfolgreiche Konvertierung.

## Technische Besonderheiten
- Die Konvertierung erfolgt direkt und ohne zusätzliche Parameter.
- Der Funktionsblock ist für die Verwendung in Echtzeitsystemen geeignet.

## Zustandsübersicht
1. **Idle**: Wartet auf das `REQ`-Ereignis.
2. **Processing**: Konvertiert den Eingabewert.
3. **Done**: Sendet das `CNF`-Ereignis mit dem konvertierten Wert.

## Anwendungsszenarien
- Anzeige von Fließkommawerten auf Benutzeroberflächen.
- Protokollierung von Messwerten in Textdateien.
- Vorbereitung von Daten für die Kommunikation mit Systemen, die String-Daten erwarten.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu `F_REAL_AS_WSTRING` verarbeitet dieser Baustein 64-Bit Fließkommazahlen statt 32-Bit.
- Ähnlich zu `F_DINT_AS_WSTRING`, aber für Fließkommazahlen statt Ganzzahlen.

## Fazit
Der `F_LREAL_AS_WSTRING` Funktionsblock bietet eine einfache und effiziente Möglichkeit, LREAL-Werte in WSTRINGs zu konvertieren. Seine klare Schnittstelle und direkte Funktionsweise machen ihn zu einem nützlichen Werkzeug in verschiedenen Anwendungsfällen.