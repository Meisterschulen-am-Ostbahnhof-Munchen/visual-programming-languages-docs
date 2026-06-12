# ALR_MUX_4


![ALR_MUX_4](./ALR_MUX_4.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `ALR_MUX_4` realisiert einen 4‑Kanal‑Multiplexer für Daten des Typs `ALR`. Er wählt aus vier Adapter‑Eingängen (`IN1` … `IN4`) einen aus und leitet dessen Signal an den Adapter‑Ausgang `OUT` weiter. Die Auswahl erfolgt über den ganzzahligen Index `K` (0‑basiert). Der Baustein ist als generischer FB (`GEN_ALR_MUX`) implementiert und über Adapter‑Schnittstellen mit der Umgebung verbunden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Beschreibung |
|------|-----|--------------|
| `REQ` | Event | Setzt den Index `K` und löst die Weiterleitung des entsprechenden Eingangs aus. |

### **Ereignis-Ausgänge**

| Name | Typ | Beschreibung |
|------|-----|--------------|
| `CNF` | Event | Bestätigung, dass die Auswahl gemäß `K` erfolgt ist. |

### **Daten-Eingänge**

| Name | Datentyp | Beschreibung |
|------|----------|--------------|
| `K` | UINT | Index des zu multiplexenden Eingangs (0 … 3). |

### **Daten-Ausgänge**

Der Baustein besitzt keine eigenständigen Datenausgänge – die Ausgangsdaten werden über den Adapter‑Plug `OUT` bereitgestellt.

### **Adapter**

| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| Plug (Ausgang) | `OUT` | `adapter::types::unidirectional::ALR` | Adapter, der die Daten des ausgewählten Eingangs liefert. |
| Socket (Eingang) | `IN1` | `adapter::types::unidirectional::ALR` | Erster Daten‑Adapter (Index 0). |
| Socket (Eingang) | `IN2` | `adapter::types::unidirectional::ALR` | Zweiter Daten‑Adapter (Index 1). |
| Socket (Eingang) | `IN3` | `adapter::types::unidirectional::ALR` | Dritter Daten‑Adapter (Index 2). |
| Socket (Eingang) | `IN4` | `adapter::types::unidirectional::ALR` | Vierter Daten‑Adapter (Index 3). |

## Funktionsweise

Sobald am Ereigniseingang `REQ` ein Signal anliegt, liest der Baustein den aktuellen Wert von `K` aus. Dieser ganzzahlige Wert (0 … 3) bestimmt, welcher der vier Adapter‑Eingänge (`IN1` für K=0, `IN2` für K=1, `IN3` für K=2, `IN4` für K=3) zum Ausgang `OUT` durchgeschaltet wird. Unmittelbar nach dem Durchschalten wird der Ereignisausgang `CNF` gesetzt, um den erfolgreichen Abschluss der Operation zu signalisieren.

Die Datenübertragung erfolgt vollständig über die Adapter‑Schnittstellen; der Baustein selbst besitzt keine direkten Datenfelder für die zu multiplexenden Werte.

## Technische Besonderheiten

- **Adapterbasierte Ein-/Ausgabe:** Der FB arbeitet ausschließlich mit Adaptern des Typs `ALR`. Dies ermöglicht eine lose Kopplung zwischen den Kommunikationspartnern und eine einfache Wiederverwendung der Multiplexer‑Funktion.
- **Generische Implementierung:** Durch die Zuordnung der generischen Klasse `GEN_ALR_MUX` kann der FB für verschiedene Adapter‑Typen oder Kanalzahlen angepasst werden, sofern die Schnittstellen kompatibel sind.
- **Keine Zustandsmaschine:** Die Logik ist rein kombinatorisch (Ereignis‑getriggert) und benötigt keinen internen Zustand.

## Zustandsübersicht

Der Baustein besitzt keine explizite Zustandsmaschine (ECC). Die Verarbeitung erfolgt ereignisgesteuert: Ein Impuls an `REQ` führt direkt zur Auswahl und zur Ausgabe von `CNF`.

## Anwendungsszenarien

- **Umschaltung von Sensordaten** in einer landwirtschaftlichen Steuerung, bei der je nach Betriebsmodus unterschiedliche ALR‑Datenquellen (z. B. Füllstand, Temperatur) an eine zentrale Auswertung weitergeleitet werden.
- **Test‑ und Simulationsumgebungen,** in denen verschiedene ALR‑Signale gezielt auf einen gemeinsamen Bus geschaltet werden müssen.
- **Redundante Systeme,** bei denen bei Ausfall einer Quelle automatisch auf eine Reserve umgeschaltet wird (durch Änderung des Index `K`).

## Vergleich mit ähnlichen Bausteinen

- Einfache **2‑Kanal‑Multiplexer** besitzen nur zwei Eingänge und benötigen z. B. einen booleschen Selektor.
- Im Gegensatz zu **schaltbaren Verbindungsbausteinen** (z. B. `MUX` mit `ANY`‑Typen) arbeitet `ALR_MUX_4` ausschließlich mit einem festen Adapter‑Protokoll und ist daher für standardisierte ALR‑Daten optimiert.
- Verglichen mit einem **16‑Kanal‑Multiplexer** bietet dieser Baustein eine kleinere, auf vier Kanäle beschränkte Auswahl, was die Komplexität reduziert und die Wartbarkeit erhöht.

## Fazit

Der `ALR_MUX_4` ist ein kompakter, ereignisgesteuerter Multiplexer für vier ALR‑Adapter‑Eingänge. Seine adapterbasierte Schnittstelle und die parametrisierbare Indexauswahl machen ihn zu einem flexiblen Werkzeug für die Signalkanal‑Umschaltung in industriellen Steuerungssystemen. Die einfache Handhabung (ein Ereignis, ein Index) erlaubt eine schnelle Integration in bestehende Automatisierungslösungen.