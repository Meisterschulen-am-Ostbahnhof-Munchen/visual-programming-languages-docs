# F_RAW_TO_PHYS


![F_RAW_TO_PHYS](./F_RAW_TO_PHYS.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein **F_RAW_TO_PHYS** konvertiert einen ISOBUS‑Rohwert vom Typ `UDINT` in einen physikalischen `REAL`-Wert. Die Umrechnung erfolgt nach der standardisierten ISOBUS‑Formel:  

`display = (raw + offset) * scale`

Er wird typischerweise in landwirtschaftlichen Steuerungen eingesetzt, um Sensordaten oder Stellgliedwerte zwischen der CAN‑basierten ISOBUS‑Signalebene und der Applikation umzurechnen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ   | Beschreibung |
|------|-------|--------------|
| REQ  | Event | Startet die Umrechnung eines Rohwerts (mit `u32Raw` und `stObj`). |

### **Ereignis-Ausgänge**

| Name | Typ   | Beschreibung |
|------|-------|--------------|
| CNF  | Event | Bestätigt, dass die Berechnung abgeschlossen und der Ausgangswert gültig ist. |

### **Daten-Eingänge**

| Name   | Typ   | Beschreibung |
|--------|-------|--------------|
| u32Raw | UDINT | Der rohe Integerwert (z. B. aus einem ISOBUS‑Message‑Objekt). |
| stObj  | `NumericObjectPool_S` | Struktur, die den Offset (`i32Offset : DINT`) und den Skalierungsfaktor (`r32Scale : REAL`) enthält. |

### **Daten-Ausgänge**

| Name | Typ  | Beschreibung |
|------|------|--------------|
| (kein expliziter Name) | REAL | Der berechnete physikalische Wert, ausgegeben als Gleitkommazahl. |

### **Adapter**
Keine.

## Funktionsweise

Der Baustein führt bei einem Ereignis am **REQ**‑Eingang folgende Berechnung durch:

1. Der Rohwert `u32Raw` wird von `UDINT` in `LINT` konvertiert (64‑Bit, um Überläufe bei der Addition zu vermeiden).
2. Der Offset `stObj.i32Offset` wird ebenfalls in `LINT` erweitert.
3. Beide Werte werden addiert: `(u32Raw + stObj.i32Offset)`.
4. Das Zwischenergebnis wird nach `REAL` konvertiert und mit dem Skalierungsfaktor `stObj.r32Scale` multipliziert.

Ergebnis: `REAL := (LINT(UDINT(u32Raw)) + LINT(stObj.i32Offset)) * stObj.r32Scale`

**Beispiel (aus der Quelltext‐Dokumentation):**  
- Rohwert = 50000  
- Skalierung = 0,01  
- Offset = -100000  
- Rechnung: `(50000 + (-100000)) * 0,01 = (-50000) * 0,01 = -500,0`  

Das Ergebnis steht nach dem Ereignis **CNF** am Datenausgang zur Verfügung.

## Technische Besonderheiten

- Der Baustein verwendet **`LINT`** (64‑Bit Integer) als Zwischentyp, um einen Überlauf bei der Addition von `UDINT` und `DINT` (z. B. große positive mit großen negativen Werten) sicher zu vermeiden.
- Die Ausgangsvariable hat keinen eigenen Namen – in der 4diac‑IDE wird sie automatisch als `OUT` dargestellt oder kann über die Schnittstelle referenziert werden.
- Die Konfiguration von Offset und Skalierung erfolgt über eine externe Struktur (`NumericObjectPool_S`), die typischerweise aus einem Pool‑Objekt stammt, das alle Parameter eines ISOBUS‑Objekts bündelt.

## Zustandsübersicht

Der Funktionsbaustein besitzt **keine** internen Zustände oder Speicher. Jeder Aufruf verarbeitet die aktuellen Eingabedaten und erzeugt zeitgleich den Ausgangswert. Er ist somit ein reiner **Funktionsbaustein ohne Gedächtnis** (combinatorial logic).

## Anwendungsszenarien

- **ISOBUS‑Steuergeräte** (Tractors, Implement) – Wandlung von CAN‑Rohdaten in physikalische Einheiten (z. B. Druck, Position, Drehzahl).
- **Landwirtschaftliche Applikationen** – Umrechnung von Sensorwerten aus dem ISOBUS‑Protokoll in anzeigbare Größen.
- **Test‑ und Simulationsumgebungen** – Nachbildung der ISOBUS‑Konvertierung für Entwicklungs‑ und Verifikationszwecke.

## Vergleich mit ähnlichen Bausteinen

- **F_RAW_TO_PHYS** ist speziell auf die ISOBUS‑Formel `(raw + offset) * scale` ausgelegt und verwendet die dort üblichen Datentypen (`UDINT`, `DINT`).  
- Allgemeine Konverter‑Bausteine (z. B. `LREAL_TO_REAL`) bieten keine Offset‑Skalierungslogik und müssen daher manuell um diese Berechnung ergänzt werden.  
- Andere ISOBUS‑spezifische Bausteine wie `F_PHYS_TO_RAW` kehren die Operation um (Rückrechnung von physikalischem Wert auf Rohwert).

## Fazit

Der **F_RAW_TO_PHYS** Baustein ist eine nützliche und sauber implementierte Komponente für die ISOBUS‑Datenkonvertierung. Durch die Verwendung von 64‑Bit Zwischenwerten wird Überlauf vermieden, und die Kapselung der Parameter in eine Struktur erleichtert die Wiederverwendung in Projekten, die mit dem `NumericObjectPool`‑Konzept arbeiten. Er eignet sich sowohl für den produktiven Einsatz als auch für die schnelle Prototypenerstellung im Bereich landwirtschaftlicher Steuerungen.