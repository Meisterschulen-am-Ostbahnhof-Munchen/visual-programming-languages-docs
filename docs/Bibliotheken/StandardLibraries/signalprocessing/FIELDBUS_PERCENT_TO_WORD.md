# FIELDBUS_PERCENT_TO_WORD

```{index} single: FIELDBUS_PERCENT_TO_WORD
```

<img width="919" height="181" alt="FIELDBUS_PERCENT_TO_WORD" src="https://github.com/user-attachments/assets/559a5a2e-44fd-433f-b22a-d685fe90c062" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `FIELDBUS_PERCENT_TO_WORD` konvertiert einen REAL-Wert im Bereich von 0.0 bis 100.0 in einen WORD-Wert im Bereich von 0 bis FAFF (hexadezimal). Dieser Baustein ist besonders für die Signalverarbeitung in Feldbussystemen nach den Standards SAE J1939 und ISO 11783 geeignet.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Auslöseereignis für die Konvertierung. Wird mit dem Eingangswert `RI` verknüpft.

### **Ereignis-Ausgänge**
- `CNF`: Bestätigungsereignis, das nach erfolgreicher Konvertierung ausgelöst wird.

### **Daten-Eingänge**
- `RI` (REAL): Eingangswert im Bereich 0.0 bis 100.0, der konvertiert werden soll.

### **Daten-Ausgänge**
- (WORD): Der konvertierte Ausgangswert im Bereich 0 bis FAFF (hexadezimal).

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt folgende Schritte durch:
1. Multiplikation des Eingangs-REAL-Werts (`RI`) mit dem konvertierten maximalen gültigen Signalwert (`FIELDBUS_SIGNAL::VALID_SIGNAL_W`).
2. Konvertierung des Ergebnisses in einen UDINT-Wert.
3. Umwandlung des UDINT-Werts in den finalen WORD-Ausgangswert.

Die Konvertierung erfolgt nach der Formel:
```
FIELDBUS_PERCENT_TO_WORD = UDINT_TO_WORD(REAL_TO_UDINT(RI * UDINT_TO_REAL(WORD_TO_UDINT(FIELDBUS_SIGNAL::VALID_SIGNAL_W))))
```

## Technische Besonderheiten
- Verwendet spezielle Typkonvertierungsfunktionen (REAL_TO_UDINT, UDINT_TO_WORD etc.)
- Arbeitet mit dem konstanten Wert `FIELDBUS_SIGNAL::VALID_SIGNAL_W` als maximale Obergrenze
- Eingebettet im Package `eclipse4diac::signalprocessing`

## Zustandsübersicht
1. Wartezustand: Auf `REQ`-Ereignis warten
2. Verarbeitungszustand: Bei `REQ`-Eingang wird die Konvertierung durchgeführt
3. Ausgabezustand: Nach erfolgreicher Konvertierung wird `CNF` ausgelöst

## Anwendungsszenarien
- Signalverarbeitung in landwirtschaftlichen Maschinen
- Fahrzeugsteuerungssysteme
- Industrielle Automatisierung mit Feldbuskommunikation
- Prozessdatenkonvertierung zwischen verschiedenen Systemen

## Vergleich mit ähnlichen Bausteinen
- Spezialisiert auf die spezifischen Anforderungen von SAE J1939 und ISO 11783
- Bietet genauere Kontrolle über den Wertebereich als generische Konvertierungsbausteine
- Optimiert für die Verwendung in der Signalverarbeitung

## Fazit
Der `FIELDBUS_PERCENT_TO_WORD`-Funktionsblock ist ein spezialisiertes Werkzeug für die präzise Konvertierung von Prozentwerten in feldbusspezifische WORD-Werte. Seine klare Schnittstelle und effiziente Implementierung machen ihn besonders geeignet für Anwendungen in der mobilen Arbeitsmaschinensteuerung und industriellen Automatisierung.