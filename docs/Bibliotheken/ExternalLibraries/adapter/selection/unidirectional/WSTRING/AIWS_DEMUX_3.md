# AIWS_DEMUX_3


![AIWS_DEMUX_3](./AIWS_DEMUX_3.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AIWS_DEMUX_3** ist ein generischer Demultiplexer für Daten des Typs **AIWS** (Agricultural Information and Workflow System). Er verteilt einen eingehenden AIWS-Wert auf einen von drei Ausgängen, abhängig von einem übergebenen Index. Entwickelt für den Einsatz in der Agrartechnik, ermöglicht er die gezielte Weiterleitung von Informationen innerhalb eines Steuerungssystems.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Kommentar | mit Variable |
|----------|-----------|--------------|
| REQ      | Set Index K | K            |

### **Ereignis-Ausgänge**

| Ereignis | Kommentar                       |
|----------|---------------------------------|
| CNF      | Bestätigung des Set Index K     |

### **Daten-Eingänge**

| Name | Typ   | Kommentar |
|------|-------|-----------|
| K    | UINT  | Index     |

### **Daten-Ausgänge**

Keine (Weitergabe erfolgt über Adapterausgänge).

### **Adapter**

| Typ               | Name  | Richtung |
|-------------------|-------|----------|
| AIWS (unidirektional) | IN    | Socket   |
| AIWS (unidirektional) | OUT1  | Plug     |
| AIWS (unidirektional) | OUT2  | Plug     |
| AIWS (unidirektional) | OUT3  | Plug     |

## Funktionsweise

Der Baustein arbeitet als **1-zu-3 Demultiplexer**. Sobald ein **REQ**-Ereignis eintrifft, wird der aktuelle Wert des Daten-Eingangs **K** (Index) ausgelesen. Abhängig von **K** (Wertebereich 1, 2 oder 3 – andere Werte werden ignoriert oder führen zu keinem Ausgang) wird der am Socket **IN** anliegende AIWS-Wert auf den entsprechenden Plug **OUT1**, **OUT2** oder **OUT3** weitergeleitet. Nach erfolgreicher Übertragung wird das Ereignis **CNF** ausgegeben, um den Abschluss der Operation zu bestätigen.

## Technische Besonderheiten

- **Generischer Aufbau**: Der FB ist mit dem Attribut `GenericClassName` als `'GEN_AIWS_DEMUX'` markiert und kann daher in generischen Instanzen verwendet werden.
- **Unidirektionale Adapter**: Alle AIWS-Adapter sind unidirektional ausgelegt, was eine klare Datenflussrichtung vorgibt.
- **Herstellerspezifisch**: Entwickelt von der HR Agrartechnik GmbH, optimiert für landwirtschaftliche Automatisierungslösungen.
- **Paketstruktur**: Der Baustein gehört zum Paket `adapter::selection::unidirectional` und verwendet eine Type-Hash-Prüfung aus `eclipse4diac::core`.

## Zustandsübersicht

Der Baustein besitzt keine explizit modellierte Zustandsmaschine. Sein Verhalten lässt sich jedoch auf zwei grundlegende Zustände reduzieren:

1. **Idle** – Warten auf ein REQ-Ereignis.
2. **Weiterleitung aktiv** – Nach Eintreffen von REQ erfolgt die Umschaltung und Datenübergabe an den ausgewählten Ausgang. Danach wird sofort CNF gesendet und der Baustein kehrt in den Idle-Zustand zurück.

## Anwendungsszenarien

- **Verteilung von Sensordaten**: Ein einzelner AIWS-Sensor liefert Daten, die je nach Index an verschiedene Aktoren (z. B. Ventile, Antriebe) weitergeleitet werden.
- **Routing in landwirtschaftlichen Steuerungen**: In einer Feldspritze können unterschiedliche Arbeitsbreiten oder Segmente über die drei Ausgänge angesteuert werden.
- **Umschaltung zwischen mehreren Dosiereinheiten**: Je nach gewähltem Programm (Index) wird der Dosierbefehl an die entsprechende Einheit geleitet.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Funktion | Unterschied |
|----------|----------|-------------|
| **AIWS_DEMUX_3** | 1-zu-3 Demultiplexer für AIWS-Daten | Speziell für den AIWS-Datentyp, drei Ausgänge |
| **Generic DEMUX** (z. B. IEC 61499 Standard) | Demultiplexer für beliebige Datentypen | Nicht auf AIWS beschränkt, oft mehrere Ausgänge frei konfigurierbar |
| **AIWS_SELECT** | 1-aus-n Selektor (Multiplexer) | Arbeitet umgekehrt: wählt einen von mehreren Eingängen aus |

Der **AIWS_DEMUX_3** bietet eine auf die Agrartechnik zugeschnittene, sofort einsetzbare Lösung ohne zusätzliche Konfiguration.

## Fazit

Der **AIWS_DEMUX_3** ist ein einfacher, aber wichtiger Funktionsblock für die gezielte Verteilung von AIWS-Informationen auf drei Ausgänge. Dank seiner klaren Schnittstelle und der generischen Auslegung lässt er sich nahtlos in landwirtschaftliche Automatisierungsprojekte integrieren. Er reduziert den Programmieraufwand und erhöht die Übersichtlichkeit von Datenflussdiagrammen.