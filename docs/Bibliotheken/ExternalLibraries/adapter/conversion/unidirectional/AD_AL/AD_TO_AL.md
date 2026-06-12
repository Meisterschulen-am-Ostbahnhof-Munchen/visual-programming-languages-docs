# AD_TO_AL


![AD_TO_AL](./AD_TO_AL.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AD_TO_AL** ist ein Composite-Baustein, der eine unidirektionale Konvertierung eines AD-Adapters (DWORD) in einen AL-Adapter (LWORD) realisiert. Er dient als Brücke zwischen Subsystemen, die unterschiedliche Adaptertypen verwenden, jedoch dieselbe logische Verbindung benötigen. Der Baustein reicht Ereignis- und Datensignale eins zu eins durch und ermöglicht so die nahtlose Integration heterogener Komponenten.

## Schnittstellenstruktur

Der Baustein besitzt ausschließlich Adapter-Schnittstellen; separate Ereignis- oder Daten-Ein-/Ausgänge sind nicht vorhanden.

### **Ereignis-Eingänge**

Keine.

### **Ereignis-Ausgänge**

Keine.

### **Daten-Eingänge**

Keine.

### **Daten-Ausgänge**

Keine.

### **Adapter**

| Typ | Richtung | Name | Kommentar |
|-----|----------|------|-----------|
| Socket (Eingang) | Input | `AD_IN` | DWORD-Adapter-Eingang vom Typ `adapter::types::unidirectional::AD` |
| Plug (Ausgang) | Output | `AL_OUT` | LWORD-Adapter-Ausgang vom Typ `adapter::types::unidirectional::AL` |

## Funktionsweise

Der Baustein ist ein reiner Weiterleitungsbaustein. Innerhalb des Composite-FBs werden die Adapter-Kanäle direkt verbunden:

- **Ereignisverbindung:** `AD_IN.E1` → `AL_OUT.E1`  
  Jedes eingehende Ereignis am AD-Adapter wird unverändert an den AL-Adapter weitergegeben.
- **Datenverbindung:** `AD_IN.D1` → `AL_OUT.D1`  
  Der eingehende Datenwert (DWORD) wird ohne Transformation als LWORD an den Ausgang übergeben.

Die Typumwandlung erfolgt implizit durch die Kopplung der Adapter; eine explizite Datentyp-Konvertierung findet nicht statt. Die Laufzeitumgebung sorgt dafür, dass die Werte entsprechend der Adapterdefinition behandelt werden.

## Technische Besonderheiten

- **Composite-Baustein:** Der FB enthält keine eigene Logik (keine Zustandsmaschine, keine Algorithmen) und besteht ausschließlich aus internen Verbindungen.
- **Unidirektionalität:** Die Adapter sind unidirektional ausgelegt (nur eine Daten- und eine Ereignisrichtung).
- **Paketstruktur:** Der FB ist im Paket `adapter::conversion::unidirectional` abgelegt.
- **Typkonvertierung:** AD (DWORD) und AL (LWORD) sind als eigenständige Adaptertypen definiert; der FB ermöglicht deren Zusammenschaltung ohne manuelle Codierung.
- **Metadaten:** Der Baustein stammt von *HR Agrartechnik GmbH*, Version 1.0, erstellt am 17.02.2026.

## Zustandsübersicht

Der Baustein besitzt keinen internen Zustandsautomaten. Der Zustand ist identisch mit dem Zustand der angeschlossenen Adapter. Das Durchreichen erfolgt ohne Verzögerung oder Logik.

## Anwendungsszenarien

- **Systemintegration:** Verbindung von Komponenten, die unterschiedliche Adapterprotokolle nutzen (z. B. eine Steuerung mit DWORD-Schnittstelle und ein Buskoppler mit LWORD-Schnittstelle).
- **Testumgebungen:** Einfaches Einschleusen von Testdaten durch Austausch von Adaptern.
- **Modularisierung:** Trennung von Schnittstellendefinition und Datenflusslogik in großen IEC 61499-Projekten.

## Vergleich mit ähnlichen Bausteinen

- `AL_TO_AD`: Führt die umgekehrte Konvertierung (LWORD → DWORD) durch.
- Direkte Adapter-Konvertierungsbausteine (z. B. `BYTE_TO_WORD`) ersetzen in der Regel keine Adapter, sondern wandeln elementare Datentypen um.
- Andere „Composite“-Bausteine im Paket `adapter::conversion` bieten ähnliche Weiterleitungen für andere Adaptertypen (z. B. `AI_TO_AO`, `DI_TO_DO`).

Im Gegensatz zu Bausteinen mit eigener Logik beschränkt sich `AD_TO_AL` auf das reine Durchreichen, was maximale Transparenz und niedrigste Latenz gewährleistet.

## Fazit

Der Funktionsblock `AD_TO_AL` ist ein schlanker, aber wertvoller Helfer zur Adapter-Konvertierung in der 4diac-IDE. Er reduziert manuellen Verdrahtungsaufwand und erhöht die Wiederverwendbarkeit von Komponenten, die auf unterschiedliche Adapterstandards setzen. Dank seiner einfachen Struktur ist er robust, performant und leicht verständlich – ideal für die typische Arbeit mit unidirektionalen Adapterflüssen.