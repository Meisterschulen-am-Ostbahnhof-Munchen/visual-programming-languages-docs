# FIELDBUS_USINT_TO_SIGNAL_SCALED


![FIELDBUS_USINT_TO_SIGNAL_SCALED](./FIELDBUS_USINT_TO_SIGNAL_SCALED.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **FIELDBUS_USINT_TO_SIGNAL_SCALED** dient der Umwandlung eines eingehenden USINT-Signals in einen skalierten REAL-Wert unter Berücksichtigung einer Gültigkeitsprüfung. Er wird typischerweise in der Feldbus-Signalverarbeitung eingesetzt, um Rohwerte aus dem Feldbus (z. B. Sensordaten) mit einem Skalierungsfaktor und einem Offset zu versehen und parallel die Gültigkeit des Eingangssignals zu bewerten. Der Baustein ist nach dem Standard IEC 61499-1 aufgebaut.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Typ | Beschreibung |
| :--- | :--- | :--- |
| `INIT` | EInit | Initialisierungsanfrage; mit den Parametern `SCALE` und `OFFSET` verknüpft. |
| `REQ` | Event | Normale Ausführungsanfrage; mit dem Daten-Eingang `IN` verknüpft. |

### **Ereignis-Ausgänge**

| Ereignis | Typ | Beschreibung |
| :--- | :--- | :--- |
| `INITO` | EInit | Bestätigung der Initialisierung. |
| `CNF` | Event | Bestätigung der Ausführung; mit den Ausgängen `OUT` und `VALID` verknüpft. |

### **Daten-Eingänge**

| Name | Datentyp | Initialwert | Beschreibung |
| :--- | :--- | :--- | :--- |
| `IN` | USINT | `BYTE_TO_USINT(NOT_AVAILABLE_B)` | Eingangssignal als vorzeichenloser 8‑Bit‑Wert. Der Initialwert entspricht dem Signal „nicht verfügbar“. |
| `SCALE` | REAL | `REAL#1.0` | Skalierungsfaktor (Multiplikation). |
| `OFFSET` | DINT | `DINT#0` | Offset, der nach der Skalierung addiert wird. |

### **Daten-Ausgänge**

| Name | Datentyp | Initialwert | Beschreibung |
| :--- | :--- | :--- | :--- |
| `OUT` | REAL | `REAL#0.0` | Skalierter Ausgangswert. |
| `VALID` | BOOL | `FALSE` | Gültigkeitsflag: `TRUE`, wenn das Eingangssignal gültig ist. |

### **Adapter**

Keine vorhanden.

## Funktionsweise

Der Baustein arbeitet mit zwei Zuständen: `INIT` und `REQ`.

- Bei einem `INIT`-Ereignis werden die Parameter `SCALE` und `OFFSET` übernommen (der Algorithmus ist leer, die Werte werden jedoch durch das `With`-Binding eingelesen). Anschließend wird `INITO` ausgegeben.
- Bei einem `REQ`-Ereignis wird der Algorithmus `REQ` ausgeführt:  
  Falls der Eingangswert `IN` kleiner oder gleich dem vordefinierten Grenzwert `BYTE_TO_USINT(VALID_SIGNAL_B)` ist, gilt das Signal als gültig. In diesem Fall wird der Wert wie folgt skaliert:
  ```
  OUT := USINT_TO_REAL(IN) * SCALE + DINT_TO_REAL(OFFSET)
  ```
  und `VALID` wird auf `TRUE` gesetzt.  
  Überschreitet `IN` den Grenzwert (d. h. das Signal ist ungültig), werden `OUT` auf `0.0` und `VALID` auf `FALSE` gesetzt.

Das Verhalten spiegelt den Eingang 1:1 auf den Ausgang wider, sofern das Signal gültig ist – mit zusätzlicher Skalierung und Offset.

## Technische Besonderheiten

- Die Konstanten `NOT_AVAILABLE_B` und `VALID_SIGNAL_B` stammen aus dem externen Paket `eclipse4diac::signalprocessing::FIELDBUS_SIGNAL`. Sie definieren die Grenzen zwischen gültigen und ungültigen USINT-Werten. `BYTE_TO_USINT(NOT_AVAILABLE_B)` ist der initiale Zustand des Eingangs und kennzeichnet ein „nicht verfügbares“ Signal.
- Der `INIT`-Algorithmus enthält keinen ST-Code – die Initialisierung beschränkt sich auf das Bereitstellen der Parameter über die Ereignisbindung. Der Baustein erwartet vor dem ersten `REQ` einen `INIT`-Aufruf, um Skalierung und Offset zu setzen.
- Die Skalierung erfolgt grundsätzlich als REAL‑Arithmetik; der Offset wird deshalb von DINT nach REAL konvertiert.

## Zustandsübersicht

Der Funktionsblock besitzt zwei elementare Zustände als einfacher FB:

| Zustand | Aktion | Ausgangsereignis |
| :--- | :--- | :--- |
| `INIT` | Führe Algorithmus `INIT` aus (leer) | `INITO` |
| `REQ` | Führe Algorithmus `REQ` aus | `CNF` |

Es existieren keine weiteren Wartezustände – jeder eingehende Event führt sofort zur Bearbeitung des zugehörigen Algorithmus und zur Ausgabe des zugehörigen Ausgangsereignisses.

## Anwendungsszenarien

- **Feldbus-Sensorauswertung**: Ein Sensor liefert einen USINT-Rohwert (z. B. 0…200). Über `SCALE` und `OFFSET` wird daraus die physikalische Größe (z. B. Druck in bar) berechnet. Der Grenzwert `VALID_SIGNAL_B` trennt gültige Messwerte von Fehler- oder Initialisierungswerten.
- **Aktualisierung von Prozessvariablen**: In SPS- oder Steuerungsapplikationen wird der Baustein zyklisch mit `REQ` getriggert, um die neuesten Feldbusdaten zu verarbeiten und in den Steuerungskontext zu übernehmen.

## Vergleich mit ähnlichen Bausteinen

- **`FIELDBUS_USINT_TO_SIGNAL`**: Ein einfacherer Baustein ohne Skalierung und Offset; er gibt den USINT-Wert direkt als REAL oder als anderen Datentyp aus.
- **`FIELDBUS_WORD_TO_SIGNAL_SCALED`**: Analoger Baustein für WORD-Eingänge – bietet eine höhere Auflösung, benötigt aber einen anderen Datentyp.
- **`FIELDBUS_USINT_TO_SIGNAL_SCALED`** zeichnet sich durch die Kombination aus Gültigkeitsprüfung (basierend auf der Konstante `VALID_SIGNAL_B`) und einfacher linearer Skalierung (Multiplikation + Addition) aus.

## Fazit

Der Funktionsblock `FIELDBUS_USINT_TO_SIGNAL_SCALED` ist ein kompakter, aber leistungsfähiger Baustein zur Verarbeitung von 8‑Bit‑Feldbussignalen. Er vereint Gültigkeitserkennung, Skalierung und Offset in einer logischen Einheit und eignet sich besonders für Anwendungen, bei denen Rohwerte in physikalische Größen umgerechnet und gleichzeitig auf ihre Plausibilität geprüft werden müssen. Die einfache Zustandsmaschine und die klar definierten Schnittstellen machen ihn robust und einfach einsetzbar.