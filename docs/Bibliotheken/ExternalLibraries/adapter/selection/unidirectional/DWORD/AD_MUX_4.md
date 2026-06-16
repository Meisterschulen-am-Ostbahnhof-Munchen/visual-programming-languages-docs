# AD_MUX_4


![AD_MUX_4](./AD_MUX_4.svg)

* * * * * * * * * *

## Einleitung

Der **AD_MUX_4** ist ein generischer, ereignisgesteuerter Adapter-Multiplexer für unidirektionale analoge/Daten-Signale. Über den Index *K* wird aus vier Eingangsadaptern (IN1 … IN4) ein Kanal ausgewählt und an den Ausgangsadapter (OUT) durchgeschaltet. Der Baustein eignet sich für flexible Signalroutingaufgaben in Automatisierungs- und Steuerungssystemen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Beschreibung |
|----------|--------------|
| **REQ**   | Anforderung, den Index *K* auszuwerten und die entsprechende Verbindung herzustellen. |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung |
|----------|--------------|
| **CNF**   | Bestätigung der erfolgreichen Schaltoperation. |

### **Daten-Eingänge**

| Variablenname | Typ  | Beschreibung |
|---------------|------|--------------|
| **K**         | UINT | Index für die Auswahl des Eingangskanals (Wertebereich 0–3). |

### **Daten-Ausgänge**
Der Baustein besitzt keine direkten Datenausgänge; die Ausgabe erfolgt über den Adapter **OUT**.

### **Adapter**

| Typ | Name | Richtung | Beschreibung |
|-----|------|----------|--------------|
| `adapter::types::unidirectional::AD` | **OUT** | Plug | Ausgangsadapter, der den Wert des gewählten Eingangs liefert. |
| `adapter::types::unidirectional::AD` | **IN1** | Socket | Erster Eingangskanal (Index *K* = 0). |
| `adapter::types::unidirectional::AD` | **IN2** | Socket | Zweiter Eingangskanal (Index *K* = 1). |
| `adapter::types::unidirectional::AD` | **IN3** | Socket | Dritter Eingangskanal (Index *K* = 2). |
| `adapter::types::unidirectional::AD` | **IN4** | Socket | Vierter Eingangskanal (Index *K* = 3). |

## Funktionsweise

1. Der Baustein wartet im Ruhezustand auf ein Ereignis am Eingang **REQ**.
2. Bei Eintreffen von **REQ** wird der aktuelle Wert des Daten-Eingangs **K** gelesen.
3. Je nach Wert von *K* (0, 1, 2 oder 3) wird der entsprechende Socket-Adapter (**IN1** bis **IN4**) mit dem Plug-Adapter **OUT** verbunden.
4. Sobald die Verbindung hergestellt ist, wird ein Bestätigungsereignis am Ausgang **CNF** ausgegeben.
5. Der ausgewählte Eingangswert steht daraufhin am **OUT**-Adapter zur Verfügung.

Hinweis: Im Fehlerfall (z. B. *K* > 3) wird die Verbindung nicht hergestellt; das Verhalten ist abhängig von der konkreten Implementierung – typischerweise bleibt der letzte gültige Wert oder eine 0 erhalten.

## Technische Besonderheiten

- **Adapterbasierte Schnittstelle**: Der Baustein nutzt das Adapterkonzept der 4diac-IDE für unidirektionale Verbindungen. Dadurch können komplexe Signaltypen zwischen Bausteinen typensicher und flexibel ausgetauscht werden.
- **Generischer Typ**: Die XML-Attribute deklarieren den FB als generischen Baustein (`GEN_AD_MUX`), was eine Wiederverwendung mit verschiedenen Adaptertypen oder Datenstrukturen ermöglicht.
- **Keine innere Zustandsmaschine**: Der FB ist rein ereignisgesteuert und besitzt keinen expliziten ECC (Event-Control-Chart). Die Auswahl erfolgt sofort bei **REQ**; es gibt keine wartenden Zustände.
- **Einfaches Index-Schema**: Der Index *K* wird als 16‑Bit‑Ganzzahl (UINT) interpretiert, sodass auch Werte über 3 technisch möglich sind, aber nur die ersten vier Kanäle adressiert werden.

## Zustandsübersicht

Da der Baustein ohne ECC arbeitet, kann er als ein Zustand betrachtet werden:

| Zustand | Beschreibung |
|---------|--------------|
| **Idle** | Warten auf **REQ**. Keine aktive Verbindung oder die Verbindung des letzten gültigen Schaltvorgangs bleibt bestehen. |

Bei Eintreffen von **REQ** wird die Verbindung aktualisiert, und es erfolgt sofort der Übergang zurück in den Idle-Zustand nach Ausgabe von **CNF**.

## Anwendungsszenarien

- **Sensorauswahl**: In einer Maschinensteuerung werden vier analoge Sensoren (z. B. Drucksensoren) über einen AD-Wandler ausgelesen. Der AD_MUX_4 kann je nach Betriebsmodus den passenden Sensor auf den nachfolgenden Verarbeitungsbaustein schalten.
- **Pfadumschaltung**: In einer Kommunikationsleitung mit mehreren Datenquellen kann der Baustein als einfacher 4:1‑Adapter-Multiplexer eingesetzt werden.
- **Test- und Diagnosefunktionen**: Zur Fehlersuche können nacheinander verschiedene Signalquellen auf einen gemeinsamen Analyse-Pfad gelegt werden.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Kanäle | Schnittstelle | Besonderheiten |
|----------|--------|---------------|----------------|
| **AD_MUX_4** (dieser FB) | 4 | Adapter (unidirektional) | Generisch, kein ECC, einfaches Index-Event-Handling |
| **AD_MUX_2** | 2 | Adapter | Entsprechend für zwei Kanäle, identische Funktionsweise |
| **MUX** (Standard) | variabel | Dateneingänge (ANY) | Eignet sich für Werte vom Typ ANY, nicht auf Adapter beschränkt; arbeitet meist mit boolescher Auswahl |
| **SELECT** | 2 | Daten- und Event-Schnittstelle | Oftmals mit zwei Daten-Eingängen und einem Schaltsignal, eher für Einzelwerte geeignet |

Der AD_MUX_4 zeichnet sich durch seine Adapter-basierte, unidirektionale Signalweiterleitung aus, die in modularen IEC‑61499‑Anwendungen eine saubere Kapselung erlaubt.

## Fazit

Der **AD_MUX_4** ist ein kompakter und flexibler Adapter-Multiplexer, der vier Eingangskanäle über einen numerischen Index auf einen Ausgangs-Pfad schaltet. Seine ereignisgesteuerte Arbeitsweise und die Adapter‑Schnittstellen machen ihn ideal für modulare Automatisierungssysteme, die eine dynamische Signalauswahl erfordern. Durch die einfache Struktur lässt er sich leicht in übergeordnete Steuerungslogiken integrieren.