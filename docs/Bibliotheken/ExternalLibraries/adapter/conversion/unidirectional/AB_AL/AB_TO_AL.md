# AB_TO_AL


![AB_TO_AL](./AB_TO_AL.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `AB_TO_AL` ist ein Composite-Baustein zur Konvertierung eines unidirektionalen BYTE-Adapters (Typ `AB`) in einen unidirektionalen LWORD-Adapters (Typ `AL`). Er wird eingesetzt, um Daten von einem 8‑Bit‑Datenformat in ein 64‑Bit‑Datenformat zu überführen und dabei die Ereignissteuerung des Quelladapters auf den Zieladapter zu übertragen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Der Baustein besitzt keine direkten Ereigniseingänge. Der eingehende Ereignisfluss erfolgt indirekt über den Socket-Adapter `AB_IN`. Der Adapter `AB` stellt intern einen Ereigniseingang (`E1`) bereit, der mit dem Ereignisausgang des Zieladapters verbunden wird.

### **Ereignis-Ausgänge**

Der Baustein besitzt keine direkten Ereignisausgänge. Der ausgehende Ereignisfluss erfolgt indirekt über den Plug-Adapter `AL_OUT`. Der Adapter `AL` stellt intern einen Ereignisausgang (`E1`) bereit, der durch die interne Verbindung aktiviert wird.

### **Daten-Eingänge**

| Name | Datentyp | Beschreibung |
|------|----------|--------------|
| `AB_IN.D1` | BYTE | 8‑Bit‑Eingangswert (über den Socket-Adapter) |

### **Daten-Ausgänge**

| Name | Datentyp | Beschreibung |
|------|----------|--------------|
| `AL_OUT.D1` | LWORD | 64‑Bit‑Ausgangswert (über den Plug-Adapter) |

### **Adapter**

| Name | Richtung | Adapter-Typ | Beschreibung |
|------|----------|-------------|--------------|
| `AB_IN` | Socket | `adapter::types::unidirectional::AB` | Eingangsadapter, liefert BYTE-Daten und ein Ereignis |
| `AL_OUT` | Plug | `adapter::types::unidirectional::AL` | Ausgangsadapter, erwartet LWORD-Daten und gibt ein Ereignis weiter |

## Funktionsweise

Der Baustein ist als reine Verdrahtung (Composite) realisiert. Intern werden folgende Verbindungen hergestellt:

- Ereignis: `AB_IN.E1` → `AL_OUT.E1`  
- Daten: `AB_IN.D1` → `AL_OUT.D1`

Sobald am Socket-Adapter `AB_IN` ein Ereignis eintrifft, wird der zugehörige BYTE-Wert (`D1`) an den Datenausgang `AL_OUT.D1` weitergegeben und gleichzeitig das Ereignis an `AL_OUT.E1` weitergeleitet. Dabei findet eine implizite Typkonvertierung von BYTE (8 Bit) nach LWORD (64 Bit) statt – die oberen 56 Bit werden mit Nullen aufgefüllt. Der Baustein besitzt keine eigene Zustandslogik oder Verzögerung.

## Technische Besonderheiten

- **Reiner Kompositbaustein**: Kein Algorithmus, keine Zustandsmaschine – die Funktionalität ergibt sich ausschließlich aus der internen Verdrahtung.
- **Unidirektionale Adapter**: Der Datenfluss ist nur von `AB_IN` zu `AL_OUT` möglich; eine Rückrichtung existiert nicht.
- **Automatische Typkonvertierung**: Die 4diac-IDE führt die Umwandlung von BYTE nach LWORD implizit durch (Big-Endian-Erweiterung mit Nullen).
- **Keine Parameter oder Konfiguration**: Der Baustein benötigt keine zusätzlichen Einstellungen.

## Zustandsübersicht

Als Composite-Baustein ohne eigene Zustandsmaschine existiert kein definierter Zustand. Das Verhalten wird vollständig durch die eingehenden Ereignisse und Daten des Socket-Adapters bestimmt.

## Anwendungsszenarien

- **Schnittstellenanpassung**: Ein Sensor liefert BYTE-Daten über einen AB-Adapter, das nachfolgende System erwartet jedoch LWORD-Daten über einen AL-Adapter.
- **Datenaufbereitung**: Vereinfachte Integration von 8‑Bit‑Geräten in 64‑Bit‑Steuerungsarchitekturen.
- **Protokollumsetzung**: Wenn Ereignisse und Daten über Adapter gekapselt werden, kann `AB_TO_AL` als universelle Konvertierungsstufe dienen.

## Vergleich mit ähnlichen Bausteinen

Es existieren weitere Adapter-Konvertierungsbausteine wie `WORD_TO_DWORD`, `ARRAY_TO_STRUCT` oder spezifische Typwandler. `AB_TO_AL` zeichnet sich jedoch durch die vollständige Kapselung in Adapter aus – sowohl Ereignis als auch Daten werden gemeinsam konvertiert. Dies vereinfacht den Austausch kompletter Schnittstellen, ohne dass separate Data- und Event-Connections modelliert werden müssen.

## Fazit

`AB_TO_AL` ist ein einfacher, aber nützlicher Composite-Baustein zur Umwandlung eines BYTE-Adapters in einen LWORD‑Adapter. Er reduziert den Modellierungsaufwand bei Typkonvertierungen in Adapter-basierten Netzwerken und stellt sicher, dass Ereignisse synchron zu den Daten weitergegeben werden. Aufgrund seiner klar definierten Schnittstelle eignet er sich besonders für modulare und wiederverwendbare Automatisierungslösungen.