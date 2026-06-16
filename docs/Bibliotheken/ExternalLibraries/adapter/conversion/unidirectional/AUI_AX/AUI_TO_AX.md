# AUI_TO_AX


![AUI_TO_AX](./AUI_TO_AX.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AUI_TO_AX** ist ein Composite-Baustein, der einen AUI-Adapter (Typ *AUI* mit einem UINT-Wert) in einen AX-Adapter (Typ *AX* mit einem BOOL-Wert) umwandelt. Er dient als bidirektionale Konvertierungsschnittstelle zwischen zwei unterschiedlichen Adaptertypen und wird typischerweise eingesetzt, um digitale Vergleichsergebnisse für die Weiterverarbeitung in BOOL-basierten Adaptern bereitzustellen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Keine direkten Ereignis-Eingänge. Die Ereignissteuerung erfolgt ausschließlich über den Socket-Adapter **AUI_IN**.

### **Ereignis-Ausgänge**
Keine direkten Ereignis-Ausgänge. Das Ergebnis-Event wird über den Plug-Adapter **AX_OUT** weitergegeben.

### **Daten-Eingänge**
Keine direkten Daten-Eingänge. Der zu verarbeitende UINT-Wert wird über den Socket-Adapter **AUI_IN** bereitgestellt.

### **Daten-Ausgänge**
Keine direkten Daten-Ausgänge. Das BOOL-Ergebnis wird über den Plug-Adapter **AX_OUT** ausgegeben.

### **Adapter**
- **AUX_IN (Socket)** – Typ: *adapter::types::unidirectional::AUI*  
  - Ereignis: E1 (auslösendes Ereignis für den Vergleich)  
  - Daten: D1 (UINT-Wert, der mit 0 verglichen wird)  
- **AX_OUT (Plug)** – Typ: *adapter::types::unidirectional::AX*  
  - Ereignis: E1 (Bestätigungsereignis nach erfolgtem Vergleich)  
  - Daten: D1 (BOOL-Ergebnis: TRUE wenn D1 ≠ 0, sonst FALSE)

## Funktionsweise
Der Baustein enthält intern eine Instanz des Vergleichsbausteins *iec61131::comparison::F_NE* (Ungleichheit). Der Ablauf ist:

1. Ein Ereignis am Socket **AUI_IN.E1** triggert den Eingang **REQ** des F_NE-Bausteins.
2. Der vom Socket über **AUI_IN.D1** gelieferte UINT-Wert wird mit der Konstanten *UINT#0* verglichen.
3. Das Vergleichsergebnis (BOOL) wird am Ausgang **F_NE.OUT** bereitgestellt.
4. Das Ergebnis-Event **F_NE.CNF** wird an den Plug **AX_OUT.E1** weitergeleitet.
5. Das BOOL-Ergebnis wird gleichzeitig über die Datenverbindung an **AX_OUT.D1** übergeben.

Somit gilt:  
- AUI_IN.D1 = 0 → AX_OUT.D1 = FALSE  
- AUI_IN.D1 ≠ 0 → AX_OUT.D1 = TRUE

## Technische Besonderheiten
- **Lizenz:** Eclipse Public License 2.0 (EPL-2.0)  
- **Autor:** Franz Höpfinger, HR Agrartechnik GmbH  
- **Paket:** `adapter::conversion::unidirectional`  
- **Interner Baustein:** `iec61131::comparison::F_NE` mit Parameter `IN2 = UINT#0`  
- Der Baustein ist ein reines Composite, enthält keine eigene Zustandsmaschine. Die gesamte Logik wird durch den eingebetteten F_NE realisiert.

## Zustandsübersicht
Da es sich um einen Composite-Baustein ohne eigene ECC (Execution Control Chart) handelt, existiert keine explizite Zustandsmaschine. Das Verhalten wird vollständig durch den internen F_NE-Baustein bestimmt, der einen einfachen Vergleich ohne Zwischenspeicherung durchführt. Der Baustein ist somit zustandslos.

## Anwendungsszenarien
- **Schwellwertdetektion:** Überführung eines analogen (UINT-)Sensorwerts in ein digitales Signal (BOOL), z. B. „Wert ungleich Null“ als Alarm- oder Steuersignal.  
- **Adapter-Konvertierung:** Einsatz in Systemen, die unterschiedliche Adapterstandards (AUI ↔ AX) verwenden, um Kompatibilität zwischen Komponenten herzustellen.  
- **Einfache Logikverkettung:** Verwendung als binäre Entscheidungsstufe in größeren Composite-Funktionsblöcken.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Eingabetyp | Ausgabetyp | Funktion |
|----------|------------|------------|----------|
| **AUI_TO_AX** | AUI (UINT) | AX (BOOL) | Ungleichheit mit Null |
| *AUI_TO_AX_INV* (hypothetisch) | AUI (UINT) | AX (BOOL) | Gleichheit mit Null (invertiert) |
| *CONV_UINT_TO_BOOL* (direkt) | UINT (Data) | BOOL (Data) | Direkter Datenwandler, kein Adapter |

Der Baustein hebt sich durch die vollständige Adapterkonformität und die integrierte Ereignissteuerung von einfachen Datenkonvertern ab.

## Fazit
**AUI_TO_AX** ist ein kompakter, zweckorientierter Composite-FB zur Umwandlung eines UINT-basierten AUI-Adapters in einen BOOL-basierten AX-Adapter. Dank der Nutzung des standardisierten F_NE-Vergleichs ist die Funktion zuverlässig und leicht nachvollziehbar. Der Baustein eignet sich besonders für die Integration in Adapter-basierte Automatisierungsarchitekturen, bei denen ein einfacher Null-Vergleich auf die Signalebene gehoben werden muss.