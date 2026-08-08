# Hysteresis_AR_AX


![Hysteresis_AR_AX](./Hysteresis_AR_AX.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock `Hysteresis_AR_AX` ist ein Basic-Funktionsblock (BFB) für die ereignisgesteuerte Signalverarbeitung in der IEC 61499. Er dient der Analog-Digital-Wandlung eines analogen Eingangssignals unter Berücksichtigung einer einstellbaren Hysterese. Dadurch wird verhindert, dass kleine Signalschwankungen oder Rauschen um einen Schwellenwert herum zu einem schnellen, unerwünschten Hin- und Herschalten des digitalen Ausgangs (Oszillation) führen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*   **INIT**: Initialisierungsanforderung (`EInit`). Aktiviert oder deaktiviert den Baustein in Kopplung mit dem Eingang `QI`.

### **Ereignis-Ausgänge**

*   **INITO**: Initialisierungsbestätigung (`EInit`). Signalisiert den Abschluss der Initialisierung oder Deinitialisierung in Kopplung mit `QO`.

### **Daten-Eingänge**

*   **QI** (BOOL): Input Event Qualifier. Bestimmt, ob der Baustein aktiv sein soll (`TRUE`) oder deinitialisiert werden soll (`FALSE`).

### **Daten-Ausgänge**

*   **QO** (BOOL): Output Event Qualifier. Zeigt den aktuellen Status der Funktionsblock-Aktivierung an.

### **Adapter**

Der Baustein nutzt standardisierte, unidirektionale Adapter für eine saubere, modulare Kopplung von Daten und Ereignissen.

*   **Sockets (Eingangs-Adapter):**
    *   **INPUT** (`adapter::types::unidirectional::AR`): Der zu überwachende analoge Eingangswert. Der Wert liegt an `INPUT.D1` an; die Auswertung wird durch das Ereignis `INPUT.E1` getriggert.
    *   **THRESHOLD** (`adapter::types::unidirectional::AR`): Der Mittelpunkt des Hysteresebandes (`THRESHOLD.D1`).
    *   **HYSTERESIS** (`adapter::types::unidirectional::AR`): Die Gesamtbreite des Hysteresebandes (`HYSTERESIS.D1`).

*   **Plugs (Ausgangs-Adapter):**
    *   **OUTPUT** (`adapter::types::unidirectional::AX`): Das digitale Ausgangssignal. Gibt das Schaltergebnis am Datenpunkt `OUTPUT.D1` (BOOL) aus und triggert den Ausgang über das Ereignis `OUTPUT.E1`.

## Funktionsweise

Die Hysterese ist symmetrisch um den Schwellenwert (`THRESHOLD`) definiert. Die Gesamtbreite des Hysteresebandes wird durch den Parameter `HYSTERESIS` vorgegeben.

### Berechnungsformeln

Um Fehlkonfigurationen zu vermeiden, wird intern stets der Absolutwert der Hysteresebreite (`ABS(HYSTERESIS.D1)`) verwendet.

1.  **Einschaltbedingung (Switch-on):**
    Der Ausgang schaltet ein (`OUTPUT.D1 := TRUE`), wenn der Eingangswert die obere Grenze des Hysteresebandes erreicht oder überschreitet:
    $$\text{INPUT.D1} \ge \text{THRESHOLD.D1} + \frac{|\text{HYSTERESIS.D1}|}{2.0}$$

2.  **Ausschaltbedingung (Switch-off):**
    Der Ausgang schaltet aus (`OUTPUT.D1 := FALSE`), wenn der Eingangswert die untere Grenze des Hysteresebandes streng unterschreitet:
    $$\text{INPUT.D1} < \text{THRESHOLD.D1} - \frac{|\text{HYSTERESIS.D1}|}{2.0}$$

## Technische Besonderheiten

*   **Verhinderung von Oszillationen:** Durch die Verwendung einer strikten Ungleichung ($<$) beim Ausschalten und einer weichen Ungleichung ($\ge$) beim Einschalten wird ein stabiles Verhalten an den exakten Grenzen des Hysteresebandes garantiert.
*   **Absoluthysterese:** Durch die Verwendung der `ABS`-Funktion im Execution Control Chart (ECC) arbeitet der Baustein auch dann korrekt, wenn für die Hysteresebreite fälschlicherweise ein negativer Wert übergeben wird.
*   **Adapterbasierte Architektur:** Die Verwendung von unidirektionalen Adaptern (`AR` / `AX`) bündelt Daten- und Ereignisleitungen. Dies erhöht die Übersichtlichkeit im Applikationsdiagramm signifikant.

## Zustandsübersicht

Das Verhalten wird über die folgenden Zustände im Execution Control Chart (ECC) gesteuert:

1.  **START**: Ruhezustand vor der Initialisierung.
2.  **Init**: Setzt den Ausgang `OUTPUT.D1` zurück und setzt `QO := QI`.
3.  **sOFF**: Zustand des ausgeschalteten Ausgangs. Der Algorithmus `alOff` stellt sicher, dass `OUTPUT.D1` auf `FALSE` gesetzt ist. Ein Übergang nach `sON` erfolgt, sobald die Einschaltbedingung erfüllt ist.
4.  **sON**: Zustand des eingeschalteten Ausgangs. Der Algorithmus `alOn` setzt `OUTPUT.D1` auf `TRUE` (sofern `QI` aktiv ist). Ein Übergang zurück nach `sOFF` erfolgt, sobald die Ausschaltbedingung erfüllt ist.
5.  **DeInit**: Deinitialisierungszustand. Setzt die Ausgänge kontrolliert zurück.

## Anwendungsszenarien

*   **Zwei-Punkt-Temperaturregelung:** Steuerung einer Heizung. Die Heizung schaltet ein, wenn die Temperatur unter den Sollwert minus der halben Hysterese fällt, und schaltet erst wieder aus, wenn die Temperatur den Sollwert plus der halben Hysterese überschreitet.
*   **Füllstandskontrolle:** Ein- und Ausschalten von Pumpen in Tanks. Verhindert ein permanentes Schalten der Pumpen bei unruhigen Flüssigkeitsoberflächen (Wellenbewegungen).
*   **Grenzüberwachung im Prozessbereich:** Umwandlung verrauschter analoger Sensorwerte (z.B. Druck, Durchfluss) in stabile digitale Alarmsignale.

## Vergleich mit ähnlichen Bausteinen

Im Gegensatz zu klassischen Komparator-Bausteinen (wie `GT` oder `LT`), die sofort bei jeder minimalen Schwellenwertüberschreitung reagieren, puffert `Hysteresis_AR_AX` das Signal durch das definierte Band ab. 

Gegenüber Standard-Hysteresegliedern, die oft mit separaten Pins für Daten und Trigger-Events arbeiten, vereinfacht dieser Baustein durch das standardisierte Adapter-Konzept (`AR`/`AX`) das Signalrouting in komplexeren 4diac-Anwendungen erheblich.

## Fazit

Der `Hysteresis_AR_AX` ist ein hocheffizienter und robuster Baustein für die Signalvorverarbeitung. Dank der integrierten Absolutwertbildung der Hysterese und den asymmetrischen Schaltbedingungen bietet er eine hohe Ausfallsicherheit im praktischen Betrieb. Durch das konsequente Nutzen von Adaptern fügt er sich ideal in moderne, serviceorientierte Steuerungsarchitekturen ein.