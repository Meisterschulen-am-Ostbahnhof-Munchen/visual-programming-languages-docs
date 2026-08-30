# AR_CALIBRATE_SQ


![AR_CALIBRATE_SQ](./AR_CALIBRATE_SQ.svg)

*(Kein Bild vorhanden)*

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `AR_CALIBRATE_SQ` ist ein adapterbasierter, sequenzieller Baustein zur Zwei-Punkt-Kalibrierung (Offset- und anschließende Skalierungs-Kalibrierung). Er stellt sicher, dass die Kalibrierungsschritte in einer fest definierten mathematischen und logischen Reihenfolge ablaufen. Über den internen Zustandsautomaten (ECC) wird erzwungen, dass die Offset-Kalibrierung (CO) zwingend vor der Skalierungs-Kalibrierung (CS) durchgeführt werden muss.

Die Berechnung des kalibrierten Ausgangs erfolgt nach der Formel:
$$Y = (X + \text{OFFSET}) \cdot \text{SCALE}$$

## Schnittstellenstruktur

### **Ereignis-Eingänge**

-   **SET** (Typ: `EInit`): Setzt die Referenzwerte `Y_Offset` und `Y_Scale` im Baustein.

### **Ereignis-Ausgänge**

-   *Keine direkten Ereignis-Ausgänge auf Bausteinebene.* (Die Ereignissteuerung erfolgt vollständig gekoppelt über die Adapter-Schnittstellen).

### **Daten-Eingänge**

-   **Y_Offset** (Typ: `REAL`): Gewünschter Ziel-Ausgangswert $Y$ am niedrigen Kalibrierungspunkt (Offset).
-   **Y_Scale** (Typ: `REAL`): Gewünschter Ziel-Ausgangswert $Y$ am hohen Kalibrierungspunkt (Skalierung).

### **Daten-Ausgänge**

-   *Keine direkten Daten-Ausgänge auf Bausteinebene.* (Die Datenübergabe erfolgt über die Adapter-Schnittstellen).

### **Adapter**

#### **Plugs (Ausgangsseitig / Speicherverbindungen)**

-   **Y** (Typ: `adapter::types::unidirectional::AR`): Der kalibrierte Ausgangswert.
-   **OFFSET** (Typ: `adapter::types::bidirectional::AR2`): Verbindung zum Speicher des Offset-Werts (Standard-Anfangswert: 0.0).
-   **SCALE** (Typ: `adapter::types::bidirectional::AR2`): Verbindung zum Speicher des Skalierungswerts (Standard-Anfangswert: 1.0).

#### **Sockets (Eingangsseitig / Sensorverbindungen)**

-   **X** (Typ: `adapter::types::unidirectional::AR`): Der unkalibrierte Rohwerteingang des Sensors.
-   **CO** (Typ: `adapter::types::unidirectional::AX`): Befehl zur Durchführung der Offset-Kalibrierung ("Calibrate Offset").
-   **CS** (Typ: `adapter::types::unidirectional::AX`): Befehl zur Durchführung der Skalierungs-Kalibrierung ("Calibrate Scale").

## Funktionsweise

Die Kalibrierung verläuft in zwei sequenziellen Hauptschritten, die mathematisch entkoppelt sind:

### 1. Offset-Kalibrierung (CO)

1. Der Sensor wird mit der niedrigen Referenzgröße beaufschlagt.
2. Der gewünschte Zielwert wird an `Y_Offset` angelegt.
3. Der Trigger `CO.E1` (mit `CO.D1` = TRUE) wird ausgelöst.
4. Berechnung des Offsets:
   $$\text{OFFSET} := \frac{Y\_Offset}{\text{SCALE}} - X$$
   *Hinweis:* Nach diesem Schritt entspricht der Ausgang $Y$ unabhängig vom aktuellen Skalierungswert exakt dem Wert `Y_Offset`.

### 2. Skalierungs-Kalibrierung (CS)

1. Der Sensor wird mit der hohen Referenzgröße beaufschlagt.
2. Der gewünschte Zielwert wird an `Y_Scale` angelegt.
3. Der Trigger `CS.E1` (mit `CS.D1` = TRUE) wird ausgelöst.
4. Berechnung von Skalierung und Offset (basierend auf beiden Referenzpunkten):
   $$\text{SCALE} := \frac{Y\_Scale - Y\_LOW\_INT}{X - X\_LOW\_INT}$$
   $$\text{OFFSET} := \frac{Y\_LOW\_INT}{\text{SCALE}} - X\_LOW\_INT$$
   *Hinweis:* Nach diesem Schritt verläuft die Kennlinie exakt durch beide Kalibrierungspunkte.

## Technische Besonderheiten

-   **ECC-erzwungene Reihenfolge:** Der Zustand zur Skalierungs-Kalibrierung (`CS`) kann im Zustandsautomaten erst erreicht werden, wenn zuvor eine Offset-Kalibrierung im Zustand `CO` stattgefunden hat. Ein direktes Auslösen von `CS` aus dem Ruhezustand ist nicht möglich.
-   **Flexibilität beim Offset:** Die Offset-Kalibrierung (`CO`) kann im Zustand `WAIT_CS` jederzeit wiederholt werden, falls Korrekturen am Nullpunkt notwendig sind.
-   **Kontinuierliche Berechnung:** Die reguläre Berechnung des Ausgangswertes $Y$ über den Rohwerteingang `X.E1` wird in jedem Zustand des Bausteins ausgeführt.
-   **Interne Variablen:**
    -   `X_LOW_INT` (REAL): Speichert den unkalibrierten Rohwert während des CO-Schritts zwischen.
    -   `Y_LOW_INT` (REAL): Speichert den gewünschten Zielwert (`Y_Offset`) während des CO-Schritts.

## Zustandsübersicht

-   **IDLE:** Ruhezustand. Wartet auf Rohdaten oder den Start der Kalibrierung.
-   **REQ:** Berechnet den kalibrierten Ausgangswert $Y$ im Normalbetrieb.
-   **CO:** Führt die Offset-Kalibrierung aus und speichert die Zwischenwerte.
-   **WAIT_CS:** Zustand nach der Offset-Kalibrierung. Berechnungen laufen normal weiter; das System wartet auf die Skalierungs-Kalibrierung.
-   **REQ_WAIT:** Berechnet den kalibrierten Ausgangswert $Y$ während der Wartezeit auf die Skalierungs-Kalibrierung.
-   **CS:** Führt die finale Skalierungs-Kalibrierung durch und berechnet die Parameter neu. Kehrt anschließend in den Zustand `IDLE` zurück.

## Anwendungsszenarien

-   **Präzise Sensor-Kalibrierung:** Ideal für industrielle Messwertaufnehmer (z. B. Waagen, Drucksensoren oder Temperatursensoren), die zyklisch manuell oder automatisiert kalibriert werden müssen.
-   **Fehlerminimierung bei der Inbetriebnahme:** Durch die fest vorgegebene Sequenz (erst Nullpunkt/Offset, dann Steigung/Skalierung) werden Fehlkalibrierungen durch Bediener wirksam verhindert.

## Vergleich mit ähnlichen Bausteinen

| Merkmal | AR_CALIBRATE | AR_CALIBRATE_SQ |
| :--- | :--- | :--- |
| **CO-Berechnungsformel** | $\text{OFFSET} := Y\_Offset - X$ | $\text{OFFSET} := \frac{Y\_Offset}{\text{SCALE}} - X$ |
| **Ausgang Y nach CO** | $Y = Y\_Offset \cdot \text{SCALE}$ (nur korrekt für $\text{SCALE} = 1$) | $Y = Y\_Offset$ (immer mathematisch korrekt) |
| **Ablaufsteuerung** | Keine Einschränkung (CO und CS beliebig triggerbar) | ECC-erzwungen (CO muss zwingend vor CS erfolgen) |

## Fazit

Der `AR_CALIBRATE_SQ` ist eine mathematisch optimierte und ablaufsichere Weiterentwicklung klassischer Kalibrierungsbausteine. Durch die Kopplung der Offset-Berechnung an den aktuellen Skalierungsfaktor und die softwareseitige Absicherung der Kalibrierungsreihenfolge bietet er eine hervorragende Plattform für fehlerfreie und hochpräzise Zwei-Punkt-Messwertkorrekturen in IEC 61499-Anwendungen.
