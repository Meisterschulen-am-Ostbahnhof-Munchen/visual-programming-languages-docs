# AUI_TO_AR


![AUI_TO_AR](./AUI_TO_AR.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AUI_TO_AR** ist ein Composite-Baustein, der einen AUI-Adapter (UINT) in einen AR-Adapter (REAL) umwandelt. Er ermöglicht die nahtlose Integration eines unsigned Integer-Signals in Systeme, die einen REAL-Wert erwarten, indem er das Ereignis und den Datenwert 1:1 durchschleift.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Der Baustein besitzt keinen direkten Ereignis-Eingang, da die Ereignisse ausschließlich über den Input-Adapter **AUI_IN** bereitgestellt werden:

- **E1** (vom AUI_IN Adapter): Ereignis, das die Datenübertragung auslöst.

### **Ereignis-Ausgänge**

Auch die Ereignis-Ausgänge werden über den Output-Adapter **AR_OUT** realisiert:

- **E1** (vom AR_OUT Adapter): Ereignis, das nach erfolgter Konvertierung ausgegeben wird.

### **Daten-Eingänge**

Daten-Eingänge sind nur indirekt über den **AUI_IN**-Adapter vorhanden:

- **D1** (vom AUI_IN Adapter): zu konvertierender Wert als **UINT**.

### **Daten-Ausgänge**

Daten-Ausgänge werden über den **AR_OUT**-Adapter zur Verfügung gestellt:

- **D1** (vom AR_OUT Adapter): konvertierter Wert als **REAL**.

### **Adapter**

| Bezeichnung | Typ | Richtung | Beschreibung |
|-------------|-----|----------|--------------|
| **AUI_IN** | `adapter::types::unidirectional::AUI` | Input (Socket) | Liefert ein UINT-Signal und ein zugehöriges Ereignis. |
| **AR_OUT** | `adapter::types::unidirectional::AR` | Output (Plug) | Gibt das konvertierte REAL-Signal und ein Ereignis aus. |

## Funktionsweise

Der Baustein **AUI_TO_AR** fungiert als reine Durchschleif-Komponente. Er verbindet 1:1:

- **AUI_IN.E1** → **AR_OUT.E1**  
- **AUI_IN.D1** → **AR_OUT.D1**

Das bedeutet: Sobald ein Ereignis am AUI_IN-Eingang eintrifft, wird das zugehörige **UINT**-Datum ohne zusätzliche Verarbeitung oder Typumwandlung zum **AR_OUT**-Ausgang weitergeleitet. Die eigentliche Konvertierung von **UINT** nach **REAL** muss entweder durch den sendenden Adapter oder durch einen nachgeschalteten Baustein erfolgen – der **AUI_TO_AR** selbst führt keine arithmetische Wandlung durch. Er stellt lediglich sicher, dass die Ereignis- und Datenpfade zwischen den beiden unterschiedlichen Adapter-Typen kompatibel sind.

## Technische Besonderheiten

- **Composite-Baustein:** Die Implementierung erfolgt rein über das Netzwerk aus Adapterverbindungen, ohne eigene Logik oder Zustandsautomaten.
- **Keine Typumwandlung:** Der **AUI_TO_AR** führt keine explizite Konvertierung des Datentyps durch. Er setzt voraus, dass der **AUI_IN**-Adapter bereits REAL-konforme Daten liefert oder dass die Typumwandlung extern erfolgt.
- **Unidirektionaler Adapter-Typ:** Beide Adapter sind unidirektional ausgelegt, d.h. sie übertragen Daten und Ereignisse nur in eine Richtung (von AUI_IN nach AR_OUT).

## Zustandsübersicht

Da der Baustein als reines Verbindungsnetzwerk ohne eigenen Zustandsautomaten realisiert ist, existiert keine Zustandsmaschine. Die Funktionalität beschränkt sich auf die sofortige Weiterleitung eingehender Ereignisse und Daten.

## Anwendungsszenarien

- **Systemintegration:** Einbindung von Sensoren oder Steuerungen, die ihre Messwerte als UINT über einen AUI-Adapter bereitstellen, in ein System, das REAL-Werte über AR-Adapter erwartet.
- **Protokollanpassung:** Wenn zwei Subsysteme unterschiedliche Adapter-Typen für die gleiche physikalische Größe verwenden, kann **AUI_TO_AR** als Adapter-Übersetzer dienen (vorausgesetzt, der UINT-Wert repräsentiert numerisch bereits den gewünschten REAL-Wert).
- **Erweiterung von Bibliotheken:** Als wiederverwendbares Baustein in einem Bibliotheksprojekt, um Adapter-Konvertierungen übersichtlich zu gestalten.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Funktion | Unterschied |
|----------|----------|-------------|
| **AUI_TO_AR** | Adapter-Umschaltung UINT → REAL | Nur Durchschleif; keine Typumwandlung, erwartet kompatible Daten. |
| **AR_TO_AUI** | Adapter-Umschaltung REAL → UINT | Umgekehrte Richtung, ebenfalls reine Durchschleif. |
| **CONV_UINT_TO_REAL** | Typumwandlung von UINT nach REAL | Führt tatsächliche Konvertierung durch, benötigt aber direkte Daten-Ein-/Ausgänge statt Adapter. |

## Fazit

Der **AUI_TO_AR** ist ein einfacher, aber nützlicher Composite-Baustein, der die Adapter-Typen **AUI** und **AR** miteinander verbindet, ohne die Daten zu verändern. Er eignet sich besonders für Systeme, in denen die Typkompatibilität bereits auf Adapter-Ebene gegeben ist oder eine nachgelagerte Konvertierung erfolgt. Seine schlanke Struktur macht ihn zu einem zuverlässigen Hilfsmittel für die Integration unterschiedlicher Adapter-Protokolle.