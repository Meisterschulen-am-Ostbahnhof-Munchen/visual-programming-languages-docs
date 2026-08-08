# BYTE_AB_AX_SEL_AB


![BYTE_AB_AX_SEL_AB](./BYTE_AB_AX_SEL_AB.svg)

*(Kein Bild verfügbar)*

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `BYTE_AB_AX_SEL_AB` ist ein zusammengesetzter Funktionsbaustein (Composite Function Block) für IEC 61499-Systeme. Er dient der binären Auswahl (Multiplexing) von Daten des Typs `BYTE`. Der Baustein ermöglicht es, zwischen einem lokalen Eingangswert und einem über einen Adapter eingespeisten Eingangswert zu wählen. Die Steuerung der Auswahl erfolgt über einen separaten Adapter-Eingang (Selektor). Das Ergebnis wird ebenfalls über einen Adapter ausgegeben. 

Durch die Verwendung von Adaptern wird die Verdrahtung innerhalb der 4diac-IDE erheblich vereinfacht und die Kapselung von Signal- und Event-Flüssen verbessert.

---

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Beschreibung | Zugeordnete Daten |
| :--- | :--- | :--- |
| `EI0` | Setzt/aktualisiert den lokalen Eingangswert `IN0`. | `IN0` |

### **Ereignis-Ausgänge**

*Keine direkten Ereignis-Ausgänge vorhanden. Die Ereignisausgabe erfolgt ausschließlich gekapselt über den Ausgangs-Adapter `OUT`.*

### **Daten-Eingänge**

| Variable | Datentyp | Beschreibung |
| :--- | :--- | :--- |
| `IN0` | `BYTE` | Auszuwählender lokaler Eingangswert (Eingang 0). |

### **Daten-Ausgänge**

*Keine direkten Daten-Ausgänge vorhanden. Die Datenausgabe erfolgt ausschließlich gekapselt über den Ausgangs-Adapter `OUT`.*

### **Adapter**

| Adaptername | Typ | Richtung | Beschreibung |
| :--- | :--- | :--- | :--- |
| `OUT` | `adapter::types::unidirectional::AB` | Plug (Stecker) | Der ausgewählte Ausgangswert (enthält Ereignis `E1` und Daten `D1` vom Typ `BYTE`). |
| `IN1` | `adapter::types::unidirectional::AB` | Socket (Buchse) | Auszuwählender Eingangswert 1 (enthält Ereignis `E1` und Daten `D1` vom Typ `BYTE`). |
| `G` | `adapter::types::unidirectional::AX` | Socket (Buchse) | Selektor-Eingang (enthält Auswahlsignal `D1` und Trigger-Ereignis `E1`). |

---

## Funktionsweise

Der Baustein basiert intern auf einem Netzwerk aus Standard-Funktionsbausteinen, die die Event- und Datensynchronisation sicherstellen:

1. **Speicherung & Triggerung:** 
   * Ein Event an `EI0` speichert den Wert `IN0` im D-Flip-Flop `E_D_FF_ANY_IN0` und triggert den internen Transfer (`F_MOVE_IN0`).
   * Ein Event am Adapter `IN1` (`IN1.E1`) speichert den Wert `IN1.D1` im D-Flip-Flop `E_D_FF_ANY_IN1` und triggert den Transfer (`F_MOVE_IN1`).
   * Ein Event am Adapter `G` (`G.E1`) speichert den Selektorzustand `G.D1` im Flip-Flop `E_D_FF_G` und triggert die Auswertung.

2. **Auswahl-Logik (Selection):**
   * Der Baustein `F_SEL` (IEC 61131-3 Selection) führt die eigentliche Auswahl aus.
   * Ist der Zustand von `G` (über `E_D_FF_G.Q`) **FALSE**, wird der Wert von `IN0` an den Ausgang weitergegeben.
   * Ist der Zustand von `G` **TRUE**, wird der Wert von `IN1` an den Ausgang weitergegeben.

3. **Ausgabe:**
   * Nach der Auswahl wird der Wert über den Konvertierungsbaustein `F_MOVE_OUT` an das Ausgangs-Flip-Flop `E_D_FF_ANY_OUT` übergeben.
   * Dieses generiert das Ausgangsereignis `OUT.E1` und legt das ausgewählte Byte auf den Datenkanal `OUT.D1` des Ausgangs-Adapters.

---

## Technische Besonderheiten

* **Adapter-Kopplung:** Durch die Nutzung von unidirektionalen Adaptern (`AB` und `AX`) ist der Baustein optimal für modularisierte Softwarearchitekturen geeignet, da Daten und Ereignisse in strukturierten Kanälen gebündelt werden.
* **Flanken- und Ereignisgesteuert:** Jede Änderung an einem der Eingänge (`IN0`, `IN1` oder `G`) triggert sofort eine Neuberechnung und stellt sicher, dass der Ausgang `OUT` stets konsistente und aktuelle Daten liefert.
* **Sicherheit durch Daten-Flip-Flops:** Die Verwendung von `E_D_FF`-Bausteinen im internen Netzwerk verhindert Daten-Race-Conditions, indem Datenwerte synchron mit ihren zugehörigen Ereignissen zwischengespeichert werden.

---

## Zustandsübersicht

| Zustand Selektor (`G.D1`) | Aktualisierter Eingang | Verhalten am Ausgang (`OUT`) |
| :---: | :---: | :--- |
| `FALSE` | `IN0` / `EI0` | `OUT.D1` übernimmt den Wert von `IN0`. Event `OUT.E1` wird ausgelöst. |
| `FALSE` | `IN1` / `IN1.E1` | Keine direkte Änderung am Ausgang (Wert `IN1` ist inaktiv). |
| `TRUE` | `IN1` / `IN1.E1` | `OUT.D1` übernimmt den Wert von `IN1.D1`. Event `OUT.E1` wird ausgelöst. |
| `TRUE` | `IN0` / `EI0` | Keine direkte Änderung am Ausgang (Wert `IN0` ist inaktiv). |
| Beliebig | Wechsel von `G.D1` | Der Ausgang wechselt sofort auf den nun aktiven Eingang und löst `OUT.E1` aus. |

---

## Anwendungsszenarien

* **Umschaltung von Betriebsmodi:** Dynamisches Umschalten zwischen einem lokal definierten Standard-Betriebsmodus (über `IN0` als Byte-Konstante) und einem remote empfangenen Betriebsmodus (über Adapter `IN1`).
* **Signal-Routing in Feldbussystemen:** Routing von Status- oder Diagnose-Bytes in dezentralen Steuerungssystemen in Abhängigkeit von Systemzuständen (gesteuert über `G`).
* **Redundante Sensorik:** Auswahl zwischen zwei redundanten Byte-codierten Sensorwerten basierend auf einem übergeordneten Fehlererkennungs-Flag.

---

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zum Standard-Auswahlbaustein `F_SEL` aus der IEC 61131-3 Bibliothek bietet `BYTE_AB_AX_SEL_AB` folgende Vorteile:
* Keine manuelle Verdrahtung von Event- und Datenleitungen für den Selektor und den zweiten Eingang erforderlich, da diese über standardisierte Adapter-Schnittstellen laufen.
* Integrierte Zwischenspeicherung der Datenströme, was die Robustheit in verteilten IEC 61499 Anwendungen erhöht.

---

## Fazit

Der `BYTE_AB_AX_SEL_AB` ist ein spezialisierter und hochgradig gekapselter Baustein zur byte-basierten Signalumschaltung. Durch die konsequente Nutzung von Adaptern fügt er sich nahtlos in moderne, ereignisgesteuerte Steuerungsarchitekturen ein und minimiert den Implementierungs- und Testaufwand bei komplexen Routing-Aufgaben in der 4diac-IDE.