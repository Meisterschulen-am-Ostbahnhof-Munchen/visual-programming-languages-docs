# E_D_FF_ANY_HYS


![E_D_FF_ANY_HYS](./E_D_FF_ANY_HYS.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **E_D_FF_ANY_HYS** realisiert ein Daten-Latch-Flipflop mit einer einstellbaren Hysterese. Er übernimmt einen numerischen Eingangswert `D` auf den Ausgang `Q`, jedoch nur dann, wenn die Differenz zwischen dem aktuellen Ausgang `Q` und dem neuen Eingang `D` einen vorgegebenen Schwellwert (`HYSTERESIS`) überschreitet. Dadurch werden kleine, unerwünschte Schwankungen (z. B. Rauschen) wirksam unterdrückt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Beschreibung |
|------|-----|-------------|
| `CLK` | Event | Taktsignal; bei einer steigenden Flanke wird der Latch-Vorgang ausgelöst. |

### **Ereignis-Ausgänge**

| Name | Typ | Beschreibung |
|------|-----|-------------|
| `EO` | Event | Wird nach erfolgreicher Übernahme von `D` nach `Q` (d. h. wenn die Hysterese-Bedingung erfüllt ist) ausgegeben. |

### **Daten-Eingänge**

| Name | Typ | Beschreibung |
|------|-----|-------------|
| `D` | ANY\_NUM | Der zu latchende Wert. |
| `HYSTERESIS` | ANY\_NUM | Hysterese-Band; die minimale absolute Änderung zwischen `Q` und `D`, die eine Übernahme auslöst. |

### **Daten-Ausgänge**

| Name | Typ | Beschreibung |
|------|-----|-------------|
| `Q` | ANY\_NUM | Der aktuell latched Wert. |

### **Adapter**

Keine Adapter.

## Funktionsweise

Der Baustein besitzt einen internen Zustandsautomaten mit den Zuständen `START` und `SET`. Nach dem Start befindet er sich im Zustand `START`. Beim ersten `CLK`-Ereignis wird in den Zustand `SET` gewechselt und der Algorithmus `LATCH` ausgeführt, unabhängig von der Hysterese. Dabei wird `Q := D` gesetzt und das Ereignis `EO` ausgelöst.

In jedem weiteren Aufruf von `CLK` im Zustand `SET` wird geprüft, ob die absolute Differenz zwischen dem aktuellen `Q` und dem neuen `D` größer oder gleich `HYSTERESIS` ist. Die Bedingung lautet:

`GE(SUB(MAX(D, Q), MIN(D, Q)), HYSTERESIS)`

*   `MAX(D, Q)` und `MIN(D, Q)` liefern die größere bzw. kleinere der beiden Zahlen.
*   `SUB(...)` berechnet die positive Differenz (Betrag).
*   `GE(...)` prüft, ob diese Differenz ≥ `HYSTERESIS` ist.

Nur wenn diese Bedingung **wahr** ist, wird der Algorithmus `LATCH` erneut ausgeführt (Q := D) und `EO` gesendet. Ist die Bedingung falsch, bleibt `Q` unverändert und es wird kein Ereignis ausgegeben. Der Zustand bleibt in beiden Fällen `SET`.

## Technische Besonderheiten

*   **Generischer Datentyp:** Die Ein- und Ausgänge `D`, `HYSTERESIS` und `Q` sind als `ANY_NUM` deklariert. Der Baustein kann daher mit beliebigen numerischen IEC-61499-Typen (z. B. `INT`, `REAL`, `LREAL`) verwendet werden, solange alle drei Größen den gleichen konkreten Typ besitzen.
*   **Hysterese-Funktion:** Die Hysterese wird als Betrag der Differenz zwischen altem und neuem Wert realisiert. Dadurch ist die Schaltrichtung egal – ein Überschreiten des Schwellwerts in beide Richtungen löst eine Übernahme aus.
*   **Initialverhalten:** Beim ersten `CLK` nach dem Start wird der Wert immer übernommen (keine Hysterese-Prüfung). Dies entspricht einer Initialisierung des Ausgangs.

## Zustandsübersicht

Der Funktionsblock enthält einen sehr einfachen Automaten mit zwei Zuständen:

| Zustand | Beschreibung |
|---------|--------------|
| `START` | Initialer Zustand nach dem Start des Bausteins. Wartet auf das erste `CLK`-Ereignis. |
| `SET` | Arbeitszustand. Bei jedem `CLK` wird die Hysterese-Bedingung ausgewertet. |

**Transitionen:**

*   `START` → `SET` : bei jedem `CLK` (ohne Bedingung).
*   `SET` → `SET` : bei `CLK` **und** erfüllter Hysterese-Bedingung (d. h. `GE(SUB(MAX(D,Q), MIN(D,Q)), HYSTERESIS) == true`). Dann wird `LATCH` ausgeführt und `EO` ausgegeben.
*   `SET` → `SET` : bei `CLK` **ohne** erfüllte Bedingung: Es findet kein Algorithmus statt, kein Ereignis.

Es gibt keinen Übergang zurück nach `START` – der Automat bleibt nach dem ersten `CLK` dauerhaft in `SET`.

## Anwendungsszenarien

*   **Stabilisierung von Sensorsignalen:** Wenn ein analoger Sensor (z. B. Temperatur, Druck, Füllstand) durch Rauschen oder kleine Schwankungen unruhige Werte liefert, kann der Baustein die Ausgabe glätten. Beispiel: Füllstandsmessung mit einem Abstandssensor, bei dem kleinere Wellen auf der Flüssigkeitsoberfläche ignoriert werden sollen.
*   **Schalthysterese in Regelungen:** In Zweipunktreglern oder Vergleichern kann dieser Baustein genutzt werden, um ein ständiges Ein-/Ausschalten (Flattern) zu verhindern. Der `HYSTERESIS`-Wert definiert die tote Zone.
*   **Wertübernahme mit Totband:** In der MES-/SCADA-Ebene können überwachte Prozesswerte nur dann aktualisiert werden, wenn sich der Wert signifikant ändert – das reduziert Datenverkehr und Alarmflut.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Funktion | Unterschied |
|----------|----------|-------------|
| `E_D_FF` | Standard-D-Flipflop (nur boolesche Werte) | Übernimmt jeden Takt sofort, keine Hysterese, nur `BOOL`-Typ. |
| `E_D_FF_ANY` | D-Flipflop für beliebige Datentypen (ohne Hysterese) | Gleiche Funktion wie `E_D_FF`, aber generisch. Übernimmt jeden Takt sofort. |
| `E_D_FF_ANY_HYS` (dieser Baustein) | D-Flipflop mit Hysterese für beliebige numerische Typen | Übernimmt nur bei ausreichender Abweichung. |

Der wesentliche Vorteil von `E_D_FF_ANY_HYS` ist die Kombination aus generischem Datentyp (`ANY_NUM`) und einer konfigurierbaren Hysterese, die eine flexible und robuste Signalverarbeitung ermöglicht.

## Fazit

Der Funktionsblock **E_D_FF_ANY_HYS** erweitert das klassische D-Flipflop um eine Hysterese-Funktion für numerische Werte. Er eignet sich ideal für Anwendungen, bei denen kleine Änderungen unterdrückt werden sollen, ohne auf einen speziellen booleschen Schwellwertschalter angewiesen zu sein. Dank des generischen Typs kann er in unterschiedlichsten Steuerungs- und Automatisierungsszenarien eingesetzt werden. Die einfache Zustandslogik und die klare Schnittstelle machen ihn effizient und leicht verständlich.