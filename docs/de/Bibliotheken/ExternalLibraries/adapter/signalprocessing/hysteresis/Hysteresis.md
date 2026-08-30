# Hysteresis


![Hysteresis](./Hysteresis.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `Hysteresis` dient als analog-digitaler Umsetzer mit integrierter Hysteresekurve. Er wandelt ein analoges Eingangssignal (`INPUT`) in ein binäres Ausgangssignal (`OUTPUT`) um. Durch die Definition eines Schwellenwerts (`THRESHOLD`) und einer Hysteresebreite (`HYSTERESIS`) wird ein unerwünschtes Prellen oder schnelles Oszillieren des Ausgangs bei verrauschten Eingangssignalen effektiv verhindert.

* * * * * * * * * *
## Schnittstellenstruktur

### **Ereignis-Eingänge**

-   **INIT**: Initialisiert den Funktionsbaustein. Aktualisiert den Ausgangs-Qualifier `QO` basierend auf `QI`.
-   **REQ**: Löst eine Berechnung des Hysteresezustands basierend auf den aktuellen Eingangswerten aus.

### **Ereignis-Ausgänge**

-   **INITO**: Bestätigt den Abschluss der Initialisierung oder Deinitialisierung.
-   **CNF**: Bestätigt die Ausführung der Berechnung und signalisiert, dass ein aktualisierter Ausgangswert vorliegt.

### **Daten-Eingänge**

-   **QI** (BOOL): Eingangs-Event-Qualifier. Steuert die Gültigkeit der Eingangsdaten und die Aktivierung des Bausteins.
-   **INPUT** (REAL): Das zu überwachende, analoge Eingangssignal.
-   **THRESHOLD** (REAL, Standardwert: `0.0`): Der Mittelpunkt des Hysteresebands (Sollwert).
-   **HYSTERESIS** (REAL, Standardwert: `0.1`): Die Gesamtbreite des Hysteresebands.

### **Daten-Ausgänge**

-   **QO** (BOOL): Ausgangs-Event-Qualifier (gibt an, ob der Baustein aktiv und betriebsbereit ist).
-   **OUTPUT** (BOOL): Das digitale Ausgangssignal des Hystereseglieds.

### **Adapter**

*Dieser Funktionsbaustein verwendet keine Adapter.*

* * * * * * * * * *
## Funktionsweise

Der Funktionsbaustein arbeitet mit einem symmetrischen Hystereseband um den definierten Mittelpunkt (`THRESHOLD`). Um auch bei negativen Hysteresewerten ein konsistentes Verhalten zu gewährleisten, wird intern der Absolutwert (`ABS`) der Hysterese verwendet.

Die Schwellenwerte für das Schalten berechnen sich wie folgt:
-   **Einschaltpunkt (Switch-on):** $THRESHOLD + \frac{|HYSTERESIS|}{2.0}$
-   **Ausschaltpunkt (Switch-off):** $THRESHOLD - \frac{|HYSTERESIS|}{2.0}$

### Schaltlogik:

1.  Befindet sich der Baustein im Zustand **sOFF** (Ausgang ist `FALSE`), schaltet der Ausgang auf `TRUE` (**sON**), sobald das Eingangssignal den oberen Grenzwert erreicht oder überschreitet:
    $$\text{INPUT} \ge \text{THRESHOLD} + \frac{|\text{HYSTERESIS}|}{2.0}$$
2.  Befindet sich der Baustein im Zustand **sON** (Ausgang ist `TRUE`), schaltet der Ausgang erst dann wieder auf `FALSE` (**sOFF**), wenn das Eingangssignal den unteren Grenzwert streng unterschreitet:
    $$\text{INPUT} < \text{THRESHOLD} - \frac{|\text{HYSTERESIS}|}{2.0}$$

* * * * * * * * * *
## Technische Besonderheiten

-   **Schwingungsschutz:** Die Ausschaltbedingung verwendet eine strikte Ungleichung ($<$), während die Einschaltbedingung inklusiv ist ($\ge$). Dies verhindert Oszillationen exakt an den Grenzen des Hysteresebands.
-   **Sicherheitsverriegelung über QI:** Der Ausgang `OUTPUT` kann nur dann den Zustand `TRUE` annehmen, wenn der Eingangs-Qualifier `QI` auf `TRUE` gesetzt ist. Ist `QI` im Zustand `FALSE`, bleibt der Ausgang gesperrt (`FALSE`).
-   **Robustheit:** Durch die Verwendung von `ABS(HYSTERESIS)` im Algorithmus führt die Eingabe einer negativen Hysterese nicht zu einem Fehlverhalten des Bausteins.

* * * * * * * * * *
## Zustandsübersicht

Der Funktionsbaustein ist als Basic-FB mit einer Execution Control Chart (ECC) realisiert:

1.  **START**: Der Standard-Ruhezustand nach dem Systemstart.
2.  **Init**: Wird durch das Ereignis `INIT` bei gesetztem `QI = TRUE` aufgerufen. Initialisiert den Baustein und setzt den Ausgang `OUTPUT` auf `FALSE`.
3.  **sOFF**: Der Zustand, in dem die Ausschaltbedingung erfüllt ist (`OUTPUT = FALSE`).
4.  **sON**: Der Zustand, in dem die Einschaltbedingung erfüllt ist (`OUTPUT = TRUE` sofern `QI = TRUE`).
5.  **DeInit**: Wird durch `INIT` bei `QI = FALSE` aufgerufen. Setzt `QO` und `OUTPUT` zurück auf `FALSE`.

* * * * * * * * * *
## Anwendungsszenarien

-   **Zweipunktregler:** Temperaturregelung (z. B. Heizung ein bei $< 19^\circ\text{C}$, aus bei $> 21^\circ\text{C}$ mit einem Threshold von $20^\circ\text{C}$ und einer Hysterese von $2^\circ\text{C}$).
-   **Füllstandsüberwachung:** Aktivierung einer Pumpe beim Erreichen eines maximalen Füllstands und Deaktivierung beim Unterschreiten des Minimalwerts.
-   **Rauschunterdrückung:** Digitalisierung von verrauschten analogen Sensorsignalen (z. B. Druck- oder Helligkeitssensoren), um unruhige Signalwechsel am Ausgang zu eliminieren.

* * * * * * * * * *
## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu einem einfachen Komparator (z. B. `GT` oder `GE`-Bausteine), die sofort bei jedem minimalen Über- oder Unterschreiten eines Wertes schalten, bietet der `Hysteresis`-Baustein durch die zwei Schaltschwellen eine inhärente Signalstabilisierung. Er vereint die Logik von zwei Komparatoren und einem RS-Flip-Flop in einem einzigen, übersichtlichen Baustein.

* * * * * * * * * *
## Fazit

Der `Hysteresis`-Baustein ist ein essenzielles Werkzeug in der Signalverarbeitung und Regelungstechnik innerhalb der IEC 61499. Er bietet eine robuste, einfach zu konfigurierende Lösung zur Erzeugung stabiler binärer Steuersignale aus kontinuierlichen analogen Eingangswerten.
