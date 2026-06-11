# AL_TO_AULI


![AL_TO_AULI](./AL_TO_AULI.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AL_TO_AULI** ist ein zusammengesetzter Baustein (Composite FB), der eine Datentypkonvertierung von einem **AL-Adapter** (Typ `LWORD`) in einen **AULI-Adapter** (Typ `ULINT`) vornimmt.  
Er dient als Brücke zwischen Komponenten, die mit unterschiedlichen Datentypen arbeiten, und ermöglicht eine nahtlose Integration in IEC 61499‑basierten Systemen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Über den Socket **AL_IN** (Adapter `AL`) wird das Ereignis **E1** empfangen. Dieses Ereignis triggert die Konvertierung des anliegenden LWORD-Werts.

### **Ereignis-Ausgänge**

Über den Plug **AULI_OUT** (Adapter `AULI`) wird das Ereignis **E1** gesendet, sobald die Konvertierung abgeschlossen ist und der ULINT-Wert am Ausgang bereitsteht.

### **Daten-Eingänge**

| Name   | Adapter-Port | Datentyp | Beschreibung                     |
|--------|--------------|----------|----------------------------------|
| AL_IN  | D1           | LWORD    | Eingangswert im LWORD-Format     |

### **Daten-Ausgänge**

| Name    | Adapter-Port | Datentyp | Beschreibung                      |
|---------|--------------|----------|-----------------------------------|
| AULI_OUT| D1           | ULINT    | Konvertierter Wert im ULINT-Format|

### **Adapter**

| Typ         | Richtung | Name      | Beschreibung                         |
|-------------|----------|-----------|--------------------------------------|
| `AL`        | Socket   | AL_IN     | Eingangsadapter mit LWORD-Daten      |
| `AULI`      | Plug     | AULI_OUT  | Ausgangsadapter mit ULINT-Daten      |

## Funktionsweise

Der FB realisiert die Konvertierung durch einen internen Baustein `F_LWORD_TO_ULINT` aus der Bibliothek `iec61131::conversion`.  
- Sobald am Eingangsadapter **AL_IN** ein Ereignis **E1** eintrifft, wird dieses an den Eingang **REQ** des internen Konvertierungsbausteins weitergeleitet.  
- Gleichzeitig wird der Datenwert **D1** (LWORD) an den Eingang **IN** des Konverters übergeben.  
- Nach erfolgreicher Konvertierung signalisiert der interne Baustein dies über seinen Ausgang **CNF**, welcher das Ereignis **E1** des Ausgangsadapters **AULI_OUT** auslöst.  
- Der konvertierte ULINT‑Wert steht dann am Datenausgang **D1** des Ausgangsadapters zur Verfügung.

## Technische Besonderheiten

- **Lizenz:** Der Baustein wird unter der **Eclipse Public License 2.0** bereitgestellt.  
- **Version:** 1.0 (Stand 2026-02-17)  
- **Abhängigkeiten:** Er benötigt die Funktion `F_LWORD_TO_ULINT` aus der Bibliothek `iec61132::conversion`.  
- **Portabilität:** Als Composite FB ist er plattformunabhängig und kann in jeder 4diac‑IDE‑Umgebung eingesetzt werden.  
- **Typ-Hash:** Der Baustein besitzt ein Attribut `eclipse4diac::core::TypeHash` zur eindeutigen Identifikation (Wert leer).

## Zustandsübersicht

Der FB **AL_TO_AULI** besitzt keine eigene Zustandsmaschine – er delegiert die gesamte Konvertierungslogik an den internen Baustein `F_LWORD_TO_ULINT`. Dadurch verhält er sich wie eine transparente Umwandlungsschicht, die nur bei einem eingehenden Ereignis aktiv wird und nach der Konvertierung wieder in den Ruhezustand zurückkehrt.

## Anwendungsszenarien

- **Datentypanpassung** in SPS‑ oder Automatisierungssystemen, wenn ein LWORD‑Signal (z. B. aus einem Kommunikationsmodul) in einen ULINT‑Wert für eine nachfolgende Verarbeitung (z. B. Zähler oder Arithmetik) umgewandelt werden muss.  
- **Adapter‑Brücke** zwischen Funktionsblöcken, die ausschließlich mit dem AULI‑Adapter arbeiten, und solchen, die den AL‑Adapter verwenden.  
- **Migration** von bestehenden LWORD‑basierten Komponenten auf ULINT‑basierte Systeme ohne Änderung der Signalkette.

## Vergleich mit ähnlichen Bausteinen

- **F_LWORD_TO_ULINT (direkter Konverter):** Dieser reine Funktionsbaustein führt dieselbe Konvertierung durch, jedoch ohne Adapter‑Schnittstellen. Er eignet sich für einfache Datenfluss‑Modelle, während **AL_TO_AULI** speziell für den Einsatz in Adapter‑basierten Architekturen optimiert ist.  
- **Andere Adapter‑Konverter (z. B. AL_TO_UDINT, AL_TO_DWORD):** Ähnliche Bausteine existieren für andere Zieltypen (UDINT, DWORD). Sie unterscheiden sich nur im Ausgabedatentyp, folgen aber dem gleichen Entwurfsmuster.

## Fazit

Der **AL_TO_AULI**‑Funktionsblock bietet eine einfache und robuste Möglichkeit, LWORD‑Daten über Adapter in ULINT‑Daten umzuwandeln. Durch die Kapselung der Konvertierungslogik in einem Composite FB bleibt die Schnittstelle klar und wiederverwendbar. Er eignet sich besonders für modulare IEC‑61499‑Projekte, in denen Adapter als standardisierte Kommunikationsschnittstellen eingesetzt werden.