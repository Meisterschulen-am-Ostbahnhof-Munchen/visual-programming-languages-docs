# LREAL2LREAL

<img width="1195" height="182" alt="LREAL2LREAL" src="https://github.com/user-attachments/assets/ae58bb49-bd66-4f30-8a1f-e2f0fcaa8bb1" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `LREAL2LREAL` dient zur direkten Übertragung eines LREAL-Wertes (64-Bit Gleitkommazahl) vom Eingang zum Ausgang. Es handelt sich um einen einfachen Konvertierungsbaustein ohne Wertänderung.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Startet die Ausführung des Funktionsblocks (Normal Execution Request)

### **Ereignis-Ausgänge**
- `CNF`: Signalisiert die erfolgreiche Ausführung (Execution Confirmation)

### **Daten-Eingänge**
- `IN` (LREAL): Eingangswert (64-Bit Gleitkommazahl)

### **Daten-Ausgänge**
- `OUT` (LREAL): Ausgangswert (64-Bit Gleitkommazahl)

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Bei Auslösung des `REQ`-Ereignisses wird der Wert von `IN` unverändert an `OUT` übertragen. Anschließend wird das `CNF`-Ereignis ausgelöst.

Der Algorithmus ist in ST (Structured Text) implementiert:
```ST
ALGORITHM REQ
OUT := IN;
END_ALGORITHM
```

## Technische Besonderheiten
- Keine Wertkonvertierung oder -änderung
- Einfache 1:1-Zuweisung
- Unterstützt den Datentyp LREAL (64-Bit Gleitkommazahl)

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Jeder `REQ`-Ereignis führt zur sofortigen Ausführung und Auslösung von `CNF`.

## Anwendungsszenarien
- Wertweiterleitung in komplexeren Funktionsblocknetzwerken
- Als Platzhalter oder Durchgang in Entwurfsphasen
- Zur expliziten Typdefinition in Verbindungen

## Vergleich mit ähnlichen Bausteinen
- Im Gegensatz zu Konvertierungsbausteinen wie `REAL2LREAL` findet hier keine Typumwandlung statt
- Ähnlich einfache Bausteine wie `BOOL2BOOL`, aber für LREAL-Datentyp

## Fazit
Der `LREAL2LREAL`-Funktionsblock bietet eine minimale Funktionalität zur direkten Wertübertragung von LREAL-Werten. Seine Einfachheit macht ihn besonders als Verbindungsglied in komplexeren Systemen nützlich.
