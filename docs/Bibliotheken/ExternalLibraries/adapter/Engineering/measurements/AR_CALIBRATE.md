# AR_CALIBRATE


![AR_CALIBRATE](./AR_CALIBRATE.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `AR_CALIBRATE` dient der Offset- und Skalenkalibrierung eines analogen Eingangssignals, das über einen Adapter bereitgestellt wird. Er ermöglicht eine zweistufige Kalibrierung: Zunächst wird der Offset durch Vergleich mit einem Referenzwert bei aktiver Kalibrierung (CO) ermittelt, anschließend die Skalierung über eine zweite Referenz (CS). Das kalibrierte Ausgangssignal wird kontinuierlich berechnet.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Typ | Mit | Beschreibung |
|----------|-----|-----|--------------|
| `SET` | `EInit` | `Y_Offset`, `Y_Scale` | Setzt die Referenzwerte für Offset- und Skalenkalibrierung |

### **Ereignis-Ausgänge**

Der Funktionsblock besitzt keine eigenen Ereignis-Ausgänge. Ereignisse werden jedoch über die angeschlossenen Adapter gesendet (z. B. `Y.E1`, `OFFSET.EO1`, `SCALE.EO1`).

### **Daten-Eingänge**

| Name | Typ | Beschreibung |
|------|-----|--------------|
| `Y_Offset` | `REAL` | Referenzwert für die Offset-Kalibrierung |
| `Y_Scale`  | `REAL` | Referenzwert für die Skalen-Kalibrierung |

### **Daten-Ausgänge**

Der FB hat keine direkten Daten-Ausgänge. Die berechneten Werte werden über die Adapter `Y`, `OFFSET` und `SCALE` zur Verfügung gestellt.

### **Adapter**

**Plugs (bereitstellende Schnittstellen):**

| Adapter | Typ | Beschreibung |
|---------|-----|--------------|
| `Y` | `adapter::types::unidirectional::AR` | Kalibrierter Ausgang (Daten + Ereignis) |
| `OFFSET` | `adapter::types::bidirectional::AR2` | Liefert den berechneten Offsetwert (bidirektional) |
| `SCALE` | `adapter::types::bidirectional::AR2` | Liefert den berechneten Skalenfaktor (bidirektional) |

**Sockets (nutzende Schnittstellen):**

| Adapter | Typ | Beschreibung |
|---------|-----|--------------|
| `X` | `adapter::types::unidirectional::AR` | Analoger Eingangswert (unidirektional) |
| `CO` | `adapter::types::unidirectional::AX` | Trigger für Offset-Kalibrierung (Ereignis + Daten) |
| `CS` | `adapter::types::unidirectional::AX` | Trigger für Skalen-Kalibrierung (Ereignis + Daten) |

## Funktionsweise

Der FB arbeitet mit drei Basisalgorithmen, die in den Zuständen `REQ`, `CO` und `CS` ausgeführt werden:

* **REQ** (Normalbetrieb):  
  `Y.D1 := (X.D1 + OFFSET.DI1) * SCALE.DI1`  
  Der Ausgangswert wird aus dem Eingang, dem aktuellen Offset und dem Skalenfaktor berechnet.

* **CO** (Offset-Kalibrierung):  
  `OFFSET.DO1 := Y_Offset - X.D1`  
  Der Offset wird als Differenz zwischen dem Referenzwert `Y_Offset` und dem aktuellen Eingangswert ermittelt.

* **CS** (Skalen-Kalibrierung):  
  `SCALE.DO1 := Y_Scale / (X.D1 + OFFSET.DI1)`  
  Der Skalenfaktor ergibt sich aus dem Referenzwert `Y_Scale` geteilt durch den um den Offset korrigierten Eingangswert.

**Ablauf der Kalibrierung:**  
1. Im Zustand `REQ` wird der FB durch ein Ereignis auf dem Adapter `CO` (mit Daten) in den Zustand `CO` überführt. Dort wird der Offset berechnet und über den Adapter `OFFSET` ausgegeben. Anschließend kehrt der FB sofort nach `REQ` zurück.  
2. Analog erfolgt die Skalenkalibrierung über den Adapter `CS` und den Zustand `CS`.  
3. Das Ereignis `SET` aktualisiert die Referenzwerte `Y_Offset` und `Y_Scale`, ohne den Kalibrierungszustand zu verlassen.  
4. Wiederholte Messungen (über `X.E1`) aktualisieren den Ausgang `Y` mit den aktuellen Kalibrierparametern.

Die Übergänge zwischen den Zuständen sind wie folgt definiert:

- `REQ` → `REQ`: bei `X.E1`, `SET`, `OFFSET.EI1` oder `SCALE.EI1`  
- `REQ` → `CO`: wenn `CO.E1` eintritt und das assoziierte Datum (`CO.D1`) gültig ist  
- `REQ` → `CS`: wenn `CS.E1` eintritt und das assoziierte Datum (`CS.D1`) gültig ist  
- `CO` → `REQ`: immer (Bedingung `1`)  
- `CS` → `REQ`: immer (Bedingung `1`)

## Technische Besonderheiten

* **Adapterbasierte Kommunikation**: Sämtliche Ein- und Ausgänge (außer den Referenzwerten) werden über Adapter realisiert. Dies ermöglicht eine flexible Kopplung mit unterschiedlichen analogen Eingangsbausteinen.  
* **Bidirektionale Kalibrieradapter**: Die Adapter `OFFSET` und `SCALE` sind bidirektional ausgelegt, sodass sie sowohl vom Kalibrier-FB beschrieben als auch von externen Bausteinen gelesen werden können.  
* **Zweistufige Kalibrierung**: Offset und Skalierung werden nacheinander kalibriert. Der Skalenfaktor verwendet bereits den ermittelten Offset, um eine korrekte lineare Korrektur zu gewährleisten.  
* **Keine eigene Ereignisausgabe**: Der FB erzeugt keine eigenen Ereignisse, sondern löst über die Adapter-Ereignisse aus (z. B. `Y.E1` nach jeder Berechnung).

## Zustandsübersicht

| Zustand | Beschreibung | Aktion |
|---------|--------------|--------|
| **REQ** | Normalbetrieb – Berechnung des kalibrierten Ausgangs | Führt Algorithmus `REQ` aus, sendet Ereignis auf `Y.E1` |
| **CO** | Offset-Kalibrierung | Führt Algorithmus `CO` aus, sendet Ereignis auf `OFFSET.EO1` |
| **CS** | Skalen-Kalibrierung | Führt Algorithmus `CS` aus, sendet Ereignis auf `SCALE.EO1` |

## Anwendungsszenarien

* **Industrielle Messwertverarbeitung**: Kalibrierung von Drucksensoren, Temperaturfühlern oder anderen analogen Gebern, bei denen Offset und Verstärkung nachjustiert werden müssen.  
* **Einmessung von Messketten**: Nach dem Anschluss eines Sensors kann durch Anlegen eines bekannten Nullpunkts (Offset) und eines bekannten Messwerts (Skalierung) die gesamte Kette linearisiert werden.  
* **Automatische Nachkalibrierung**: Durch zyklisches Auslösen der Kalibrierungsadapter können Drift-Effekte kompensiert werden.

## Vergleich mit ähnlichen Bausteinen

Einfache Skalierungsbausteine (z. B. `SCALE`) bieten nur eine feste Multiplikation und Addition, ohne automatische Kalibrierung. Der `AR_CALIBRATE` hingegen integriert die gesamte Kalibrierlogik – inklusive Referenzvorgabe und ereignisgesteuerter Aktivierung – und eignet sich daher für dynamische Umgebungen, in denen Parameter während des Betriebs angepasst werden müssen.

## Fazit

Der Funktionsblock `AR_CALIBRATE` stellt eine robuste Lösung zur Offset- und Skalenkalibrierung analoger Signale dar. Dank der Adapter-basierten Schnittstellen und der klaren Zustandsmaschine lässt er sich leicht in bestehende Automatisierungslösungen integrieren und ermöglicht eine präzise, wiederholbare Messwertkorrektur.