# FIELDBUS_ULINT_TO_SIGNAL_SCALED


![FIELDBUS_ULINT_TO_SIGNAL_SCALED](./FIELDBUS_ULINT_TO_SIGNAL_SCALED.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **FIELDBUS_ULINT_TO_SIGNAL_SCALED** dient zur Konvertierung eines ULINT-Rohwerts (z. B. von einem Feldbus) in einen skalierten LREAL-Wert. Dabei wird die Gültigkeit des Eingangssignals anhand eines konstanten Schwellwerts (`VALID_SIGNAL_LW`) überprüft. Ist der Eingang gültig, erfolgt eine lineare Skalierung (Multiplikation mit einem Faktor und Addition eines Offsets); andernfalls wird der Ausgang auf 0,0 gesetzt und die Gültigkeit negiert.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Typ | Beschreibung | Mit Variablen |
|----------|-----|--------------|---------------|
| **INIT** | EInit | Initialisierungsanforderung | SCALE, OFFSET |
| **REQ**  | Event | Normale Ausführungsanforderung | IN |

### **Ereignis-Ausgänge**

| Ereignis | Typ | Beschreibung | Mit Variablen |
|----------|-----|--------------|---------------|
| **INITO** | EInit | Bestätigung der Initialisierung | – |
| **CNF**   | Event | Bestätigung der Ausführung | OUT, VALID |

### **Daten-Eingänge**

| Variable | Typ | Initialwert | Beschreibung |
|----------|-----|-------------|--------------|
| **IN** | ULINT | `LWORD_TO_ULINT(NOT_AVAILABLE_LWM)` | Rohwert vom Feldbus |
| **SCALE** | LREAL | `1.0` | Skalierungsfaktor |
| **OFFSET** | DINT | `0` | Offset, der nach der Skalierung addiert wird |

### **Daten-Ausgänge**

| Variable | Typ | Initialwert | Beschreibung |
|----------|-----|-------------|--------------|
| **OUT** | LREAL | `0.0` | Skalierter Ausgangswert (nur gültig, wenn VALID = TRUE) |
| **VALID** | BOOL | `FALSE` | Gültigkeitssignal: TRUE, wenn IN ≤ `VALID_SIGNAL_LW`, sonst FALSE |

### **Adapter**

Keine Adapter vorhanden.

## Funktionsweise

Der Funktionsblock besitzt zwei Betriebszustände, die durch die Ereignisse **INIT** und **REQ** aktiviert werden:

1. **INIT‑Zustand**  
   Beim Eintreffen des INIT-Ereignisses wird der Algorithmus `INIT` ausgeführt (derzeit leer). Anschließend wird das Ereignis **INITO** gesendet.  
   Über die mit INIT verbundenen Eingänge können die Parameter **SCALE** und **OFFSET** gesetzt werden.

2. **REQ‑Zustand**  
   Bei einem REQ-Ereignis wird der Algorithmus `REQ` ausgeführt:
   - Prüfung: `IN ≤ LWORD_TO_ULINT(VALID_SIGNAL_LW)`  
     - **Gültig** (Bedingung erfüllt):  
       `OUT := ULINT_TO_LREAL(IN) * SCALE + DINT_TO_LREAL(OFFSET)`  
       `VALID := TRUE`  
     - **Ungültig** (Bedingung nicht erfüllt):  
       `OUT := 0.0`  
       `VALID := FALSE`  
   - Anschließend wird das Ereignis **CNF** mit den neuen Werten von **OUT** und **VALID** ausgegeben.

Die Konstanten `NOT_AVAILABLE_LWM` und `VALID_SIGNAL_LW` stammen aus dem importierten Paket `eclipse4diac::signalprocessing::FIELDBUS_SIGNAL` und legen den Schwellwert für die Gültigkeitserkennung fest.

## Technische Besonderheiten

- Der Baustein ist als **SimpleFB** mit zwei Zuständen implementiert, wodurch er deterministisch und ohne komplexe Zustandsautomaten arbeitet.
- Die Gültigkeitsprüfung erfolgt durch einen Vergleich mit dem importierten `VALID_SIGNAL_LW`. Dies ermöglicht eine anwendungsspezifische Konfiguration des gültigen Wertebereichs.
- Bei ungültigem Signal wird der Ausgang **OUT** auf 0,0 zurückgesetzt – eine definierte Fehlerbehandlung.
- Skalierung und Offset werden als LREAL bzw. DINT übergeben, der Offset wird intern in LREAL konvertiert, sodass auch negative Werte möglich sind.
- Der Initialwert von **IN** (`NOT_AVAILABLE_LWM`) ist so gewählt, dass er beim ersten Durchlauf als ungültig erkannt wird, falls kein gültiger Feldbuswert vorliegt.

## Zustandsübersicht

| Zustand | Beschreibung | Auslöser | Ausgabeereignis |
|---------|--------------|----------|-----------------|
| **INIT** | Initialisierung (keine Aktion) | INIT | INITO |
| **REQ**  | Verarbeitung des Eingangssignals (Skalierung oder Fehlerfall) | REQ | CNF |

## Anwendungsszenarien

- **Feldbus‑Sensorik**: Ein 64‑Bit‑ULINT‑Wert von einem Drucksensor wird mit einem Faktor (z. B. 0,001) in bar umgerechnet und ein Nullpunkt‑Offset addiert. Die Gültigkeitsprüfung verhindert die Verarbeitung von Kommunikationsfehlern.
- **Fehlerbehandlung**: Bei Überschreitung des `VALID_SIGNAL_LW` (z. B. bei Sensorausfall) wird **VALID** auf FALSE gesetzt, sodass die übergeordnete Steuerung den Wert nicht übernimmt.
- **Initialisierung**: Beim Anlagenstart können über INIT die Skalierung und der Offset aus einem Parametersatz geladen werden.

## Vergleich mit ähnlichen Bausteinen

- **FIELDBUS_SINT_TO_SIGNAL_SCALED** – gleiche Logik, jedoch für vorzeichenbehaftete 8‑Bit‑Werte (SINT). Der vorliegende Block verarbeitet 64‑Bit‑Unsigned‑Werte.
- **FIELDBUS_ULINT_TO_SIGNAL (ohne Skalierung)** – einfache Typkonvertierung ohne Skalierung und ohne integrierte Gültigkeitsprüfung.
- **GENERIC_SCALER** – allgemeiner Skalierungsbaustein, bei dem die Gültigkeitsprüfung extern realisiert werden muss.

## Fazit

Der Funktionsblock **FIELDBUS_ULINT_TO_SIGNAL_SCALED** bietet eine kompakte, parametrierbare Lösung zur sicheren Umwandlung von Feldbus‑Rohdaten in physikalische Werte. Durch die Kombination von Gültigkeitsprüfung, Skalierung und Offset eignet er sich ideal für industrielle Automatisierungsaufgaben, bei denen Datenintegrität und einfache Kalibrierung gefordert sind.