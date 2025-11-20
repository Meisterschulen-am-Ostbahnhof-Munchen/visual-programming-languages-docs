# DINT2DINT

<img width="1171" height="182" alt="DINT2DINT" src="https://github.com/user-attachments/assets/d42e917d-876d-4b7e-8ba1-198724d811df" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock DINT2DINT dient zur direkten Übertragung eines DINT-Wertes (32-Bit Ganzzahl) vom Eingang zum Ausgang. Es handelt sich um einen einfachen Konvertierungsbaustein ohne Wertänderung.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Startet die Ausführung des Funktionsblocks (mit Dateninput `IN`)

### **Ereignis-Ausgänge**
- `CNF`: Signalisiert die erfolgreiche Ausführung (mit Datenoutput `OUT`)

### **Daten-Eingänge**
- `IN` (DINT): Eingangswert (32-Bit Ganzzahl)

### **Daten-Ausgänge**
- `OUT` (DINT): Ausgangswert (32-Bit Ganzzahl)

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock kopiert bei Auslösung des `REQ`-Ereignisses den Wert von `IN` unverändert auf `OUT` und bestätigt die Ausführung mit dem `CNF`-Ereignis.

Algorithmus:
```ST
ALGORITHM REQ
OUT := IN;
END_ALGORITHM
```

## Technische Besonderheiten
- Einfache 1:1-Wertübertragung ohne Konvertierung oder Skalierung
- Unterstützt den Datentyp DINT (32-Bit Integer)
- Keine Zustandsbehaftung

## Zustandsübersicht
Der Baustein ist zustandslos und führt bei jedem `REQ` die Wertübertragung durch.

## Anwendungsszenarien
- Wertweitergabe in Funktionsblockketten
- Explizite Typkonvertierung (bei impliziter Kompatibilität)
- Signalverknüpfungen in Steuerungsanwendungen

## Vergleich mit ähnlichen Bausteinen
- Im Gegensatz zu Typkonvertern (z.B. INT2DINT) findet hier keine tatsächliche Typumwandlung statt
- Ähnlich einem "Wire"-Element in grafischen Programmierumgebungen
- Einfacher als Bausteine mit Skalierungs- oder Berechnungsfunktionalität

## Fazit
Der DINT2DINT-Baustein bietet eine minimale Funktionalität zur direkten Wertübertragung zwischen DINT-Variablen. Er eignet sich besonders für klare Signalpfade und explizite Typangaben in Funktionsblocknetzwerken.
