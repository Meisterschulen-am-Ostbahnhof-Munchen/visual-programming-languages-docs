# FIELDBUS_WORD_TO_SIGNAL_COMPOUND_SCALE


![FIELDBUS_WORD_TO_SIGNAL_COMPOUND_SCALE](./FIELDBUS_WORD_TO_SIGNAL_COMPOUND_SCALE.svg)

* * * * * * * * * *
## Einleitung
Dieser Funktionsbaustein bildet einen 16‑Bit‑Wort‑Eingang auf einen skalierten Realwert ab. Dabei wird das eingehende Wort zunächst auf Gültigkeit geprüft. Ist das Signal gültig, werden das obere und das untere Byte mit jeweils eigenen Skalierungsfaktoren multipliziert und mit einem Offset addiert. Das Ergebnis wird als Skalierung des ursprünglichen Feldbussignals ausgegeben.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **INIT** (EInit) – Initialisierungsaufforderung; mit den Parametern `SCALE_HIGH`, `SCALE_LOW` und `OFFSET`.
- **REQ** (Event) – Normale Ausführungsanforderung; mit dem Parameter `IN`.

### **Ereignis-Ausgänge**
- **INITO** (EInit) – Bestätigung der Initialisierung.
- **CNF** (Event) – Bestätigung der Ausführung; mit den Parametern `OUT` und `VALID`.

### **Daten-Eingänge**
| Name | Typ | Initialwert | Beschreibung |
|------|-----|-------------|--------------|
| `IN` | WORD | `NOT_AVAILABLE_WM` | Das zu verarbeitende 16‑Bit‑Feldbussignal. |
| `SCALE_HIGH` | REAL | 0.256 | Skalierungsfaktor für das obere Byte (High‑Byte). |
| `SCALE_LOW` | REAL | 0.001 | Skalierungsfaktor für das untere Byte (Low‑Byte). |
| `OFFSET` | DINT | 0 | Ganzzahliger Offset, der nach der Skalierung addiert wird. |

### **Daten-Ausgänge**
| Name | Typ | Initialwert | Beschreibung |
|------|-----|-------------|--------------|
| `OUT` | REAL | 0.0 | Berechneter skalarer Ausgangswert. |
| `VALID` | BOOL | FALSE | Zeigt an, ob das Eingangssignal gültig ist (`TRUE`) oder nicht (`FALSE`). |

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Baustein arbeitet in zwei Schritten, gesteuert durch die Ereignisse:

1. **Initialisierung (INIT)**  
   - Der interne Algorithmus ist leer; es wird lediglich der Ereignisausgang `INITO` gesetzt.  
   - Die Skalierungsparameter (`SCALE_HIGH`, `SCALE_LOW`, `OFFSET`) werden beim Initialisierungsereignis übergeben, jedoch erst im **REQ**‑Zyklus verwendet.

2. **Verarbeitung (REQ)**  
   - Der eingehende Wert `IN` wird mit der externen Konstanten `VALID_SIGNAL_W` verglichen.  
   - **Gültiges Signal** (`IN` ≤ `VALID_SIGNAL_W`):
     1. Das obere Byte wird durch Rechtsverschiebung um 8 Bit und Maskierung mit `0x00FF` extrahiert.  
     2. Das untere Byte wird durch Maskierung mit `0x00FF` gewonnen.  
     3. Beide Bytes werden in `REAL` konvertiert, mit den zugehörigen Skalierungsfaktoren multipliziert und zum Offset addiert:  
        `OUT = (highByte * SCALE_HIGH) + (lowByte * SCALE_LOW) + OFFSET`  
     4. `VALID` wird auf `TRUE` gesetzt.  
   - **Ungültiges Signal** (sonst):  
     - `OUT` wird auf `0.0` gesetzt.  
     - `VALID` wird auf `FALSE` gesetzt.  

Der folgende ST‑Code verdeutlicht die interne Logik:
```pascal
IF (WORD_TO_UINT(IN) <= WORD_TO_UINT(VALID_SIGNAL_W)) THEN
    temp := SHR(IN, SINT#8);
    highByte := temp AND WORD#16#00FF;
    lowByte := IN AND WORD#16#00FF;
    OUT := UINT_TO_REAL(WORD_TO_UINT(highByte)) * SCALE_HIGH
         + UINT_TO_REAL(WORD_TO_UINT(lowByte)) * SCALE_LOW
         + DINT_TO_REAL(OFFSET);
    VALID := BOOL#TRUE;
ELSE
    OUT := REAL#0.0;
    VALID := BOOL#FALSE;
END_IF;
```

## Technische Besonderheiten
- **Compound‑Skalierung:** Die beiden Bytes eines Words werden getrennt skaliert. Dies ermöglicht die Abbildung von Messwerten, deren Information auf zwei Bytes verteilt ist (z. B. unterschiedliche Auflösungen oder Einheiten).  
- **Feldbus‑Konstanten:** Die beiden externen Konstanten `VALID_SIGNAL_W` und `NOT_AVAILABLE_WM` definieren den gültigen Wertebereich bzw. den „nicht verfügbar“‑Zustand. Sie stammen aus dem Paket `eclipse4diac::signalprocessing::FIELDBUS_SIGNAL`.  
- **Initialwerte:** Die Voreinstellungen `SCALE_HIGH = 0.256`, `SCALE_LOW = 0.001` und `OFFSET = 0` sind praxiserprobte Werte für typische Feldbussignale (z. B. Temperaturmessung).  
- **Keine Zustandsabhängigkeit:** Der Baustein besitzt keine internen Zustandsautomaten, die über INIT/REQ hinausgehen – die Reaktion ist rein kombinatorisch beim REQ‑Ereignis.

## Zustandsübersicht
Der Baustein verfügt über zwei einfache Zustände, die direkt den Ereignissen entsprechen:

| Zustand | Ausgelöst durch | Ausgeführte Aktion | Ausgangsereignis |
|---------|----------------|--------------------|------------------|
| `INIT`  | Ereignis `INIT` | Algorithmus `INIT` (leer) | `INITO` |
| `REQ`   | Ereignis `REQ`  | Algorithmus `REQ` (Skalierung) | `CNF` |

Weitere Zustände oder Verzweigungen sind nicht vorhanden.

## Anwendungsszenarien
- **Temperaturmessung über zwei Kanäle** – High‑Byte repräsentiert den ganzzahligen Anteil, Low‑Byte den Nachkommateil einer Temperatur (z. B. 0.256 °C/LSB für High, 0.001 °C/LSB für Low).  
- **Druck‑ oder Füllstandssensoren** – Liefern einen 16‑Bit‑Rohwert, der in zwei unterschiedlich skalierte Anteile zerlegt wird, um den physikalischen Wert zu ermitteln.  
- **Feldbus‑Datenvorverarbeitung** – In einer logiBUS‑Signalverarbeitungskette kann dieser Baustein als erste Stufe zur Konvertierung von Wortwerten in reale physikalische Größen eingesetzt werden.

## Vergleich mit ähnlichen Bausteinen
- **FIELDBUS_WORD_TO_SIGNAL** (ohne Compound) – Wendet nur einen einzigen Skalierungsfaktor auf das gesamte Word an. Geeignet, wenn High‑ und Low‑Byte die gleiche Gewichtung haben.  
- **FIELDBUS_BYTE_TO_SIGNAL** – Verarbeitet nur ein einzelnes Byte. Benötigt zwei Instanzen, um beide Bytes eines Words zu behandeln.  
- **FIELDBUS_WORD_TO_SIGNAL_COMPOUND_SCALE** zeichnet sich durch die getrennte Skalierung der beiden Bytes aus, was eine flexiblere und genauere Abbildung vieler Sensorprotokolle ermöglicht.

## Fazit
Der Baustein **FIELDBUS_WORD_TO_SIGNAL_COMPOUND_SCALE** ist ein spezialisiertes Werkzeug zur Aufbereitung von 16‑Bit‑Feldbussignalen, bei denen die beiden Bytes unterschiedliche physikalische Bedeutung oder Auflösung haben. Die klare Trennung von Gültigkeitsprüfung, Byte‑Extraktion und Compound‑Skalierung macht ihn zu einem verlässlichen und konfigurierbaren Element in der Signalverarbeitungskette. Durch die extern definierten Feldbus‑Konstanten ist er leicht an verschiedene Protokolle anpassbar.