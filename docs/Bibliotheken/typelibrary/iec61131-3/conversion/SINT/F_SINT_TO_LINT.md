# F_SINT_TO_LINT

<img width="1434" height="213" alt="F_SINT_TO_LINT" src="https://github.com/user-attachments/assets/87eb573f-d686-40fb-aa1e-1a3c3c21f187" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_SINT_TO_LINT` dient der Konvertierung eines `SINT`-Wertes (8-Bit Ganzzahl) in einen `LINT`-Wert (64-Bit Ganzahl). Diese Konvertierung ist nützlich, wenn Daten mit unterschiedlicher Bitbreite verarbeitet werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verbunden.

### **Ereignis-Ausgänge**
- `CNF`: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verbunden.

### **Daten-Eingänge**
- `IN` (`SINT`): Der zu konvertierende 8-Bit Ganzzahlwert.

### **Daten-Ausgänge**
- `OUT` (`LINT`): Der konvertierte 64-Bit Ganzzahlwert.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt eine direkte Zuweisung des Eingabewertes `IN` zum Ausgabewert `OUT` durch. Da `LINT` eine größere Bitbreite als `SINT` hat, erfolgt die Konvertierung ohne Datenverlust.

## Technische Besonderheiten
- Die Konvertierung ist verlustfrei, da der `LINT`-Datentyp alle möglichen Werte des `SINT`-Datentyps darstellen kann.
- Der Funktionsblock ist deterministisch und hat keine internen Zustände.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Ausführung erfolgt sofort bei Empfang des `REQ`-Ereignisses.

## Anwendungsszenarien
- Verarbeitung von 8-Bit Sensordaten in 64-Bit Systemen
- Kompatibilität zwischen Systemen mit unterschiedlicher Bitbreite
- Datenkonvertierung in Automatisierungssystemen

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsblöcken (z.B. `F_INT_TO_LINT`) arbeitet dieser Block speziell mit 8-Bit Eingabedaten.
- Ähnlich wie `F_BYTE_TO_LWORD`, aber für vorzeichenbehaftete Ganzzahlen.

## Fazit
Der `F_SINT_TO_LINT` Funktionsblock bietet eine einfache und effiziente Möglichkeit, 8-Bit Ganzzahlen in 64-Bit Ganzzahlen zu konvertieren. Seine einfache Struktur und deterministische Arbeitsweise machen ihn zu einem zuverlässigen Baustein in Automatisierungslösungen.
