# ALR_TO_AX


![ALR_TO_AX](./ALR_TO_AX.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **ALR_TO_AX** ist ein Composite-Baustein zur Umwandlung eines LREAL-Werts (über den unidirektionalen ALR-Adapter) in einen BOOL-Wert (über den unidirektionalen AX-Adapter). Er wird typischerweise eingesetzt, um ein analoges Eingangssignal in ein digitales Ausgangssignal zu konvertieren – beispielsweise zur Erkennung einer Schwellwertüberschreitung. Der Baustein basiert auf einem einfachen Null-Vergleich und löst das Ausgangsereignis aus, sobald ein gültiger Wert am Eingang anliegt.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **ALR_IN.E1** – Ereignis vom ALR-Adapter; zeigt an, dass ein neuer LREAL-Wert bereitsteht.

### **Ereignis-Ausgänge**
- **AX_OUT.E1** – Ereignis zum AX-Adapter; signalisiert, dass der konvertierte BOOL-Wert gültig ist.

### **Daten-Eingänge**
- **ALR_IN.D1** – LREAL-Eingangswert (über den ALR-Adapter).

### **Daten-Ausgänge**
- **AX_OUT.D1** – BOOL-Ausgangswert (über den AX-Adapter); ergibt sich aus dem Vergleich des Eingangswerts mit 0.0.

### **Adapter**
- **ALR_IN** – Socket (Typ: *adapter::types::unidirectional::ALR*): unidirektionaler LREAL-Eingangsadapter.
- **AX_OUT** – Plug (Typ: *adapter::types::unidirectional::AX*): unidirektionaler BOOL-Ausgangsadapter.

## Funktionsweise
Bei einem ankommenden Ereignis über **ALR_IN.E1** wird der Datenwert **ALR_IN.D1** (LREAL) an den internen IEC-61131-Baustein **F_NE** übergeben. Dieser vergleicht den Wert mit der Konstanten `LREAL#0.0` und erzeugt **TRUE**, falls der Eingang ungleich null ist, andernfalls **FALSE**. Das Ergebnis wird direkt an **AX_OUT.D1** weitergeleitet, und ein Bestätigungsereignis über **AX_OUT.E1** wird ausgelöst.

Der gesamte Ablauf erfolgt innerhalb eines einzigen Zyklus, da es sich um einen Composite-Block ohne eigenen Zustandsautomaten handelt.

## Technische Besonderheiten
- **Lizenz & Herkunft**: Der Baustein ist unter der Eclipse Public License 2.0 lizenziert und wurde mit der Versionsinformation 1.0 bereitgestellt.  
- **Verwendete Bibliotheken**: Der Vergleichsbaustein *F_NE* stammt aus der IEC‑61131-Bibliothek (*iec61131::comparison*).  
- **Paketname**: Der FB gehört zum Paket *adapter::conversion::unidirectional*.  
- **Kompatibilität**: Er setzt die Adapter-Spezifikation des 4diac‑Frameworks voraus und ist für unidirektionale Adaptertypen ausgelegt.

## Zustandsübersicht
Der Baustein besitzt keinen expliziten Zustandsautomaten. Seine Logik ist rein kombinatorisch und ereignisgesteuert:  
1. Warten auf Ereignis an **ALR_IN.E1**.  
2. Datenverarbeitung (Vergleich mit 0.0).  
3. Ausgabe des BOOL-Ergebnisses an **AX_OUT.D1** und Senden des Bestätigungsereignisses an **AX_OUT.E1**.

## Anwendungsszenarien
- **Analog-Digital-Umwandlung**: Erkennung, ob ein analoger Messwert (z. B. Drucksensor, Temperatur) von null verschieden ist.  
- **Schwellwert-Erkennung**: Durch einfache Modifikation (Austausch von *F_NE* gegen *F_GT* oder *F_LT*) kann eine beliebige Schwellwertlogik realisiert werden.  
- **Adapter-Kopplung**: Einbinden von ALR‑basierten Sensoren in eine AX‑basierte Steuerungslogik, ohne dass komplexe Typkonvertierungen auf übergeordneter Ebene nötig sind.

## Vergleich mit ähnlichen Bausteinen
- **LREAL_TO_BOOL**: Während ein dedizierter LREAL‑to‑BOOL‑Baustein oft einen Schwellwert und Hysterese unterstützt, realisiert *ALR_TO_AX* die einfachste Form – null ≠ null → TRUE.  
- **Vergleichsbausteine (F_NE, F_EQ usw.)**: Diese arbeiten direkt auf Daten, während *ALR_TO_AX* die vollständige Adapter-Integration und Ereignissteuerung übernimmt.  
- **Adapter‑Converter‑Bausteine**: Im selben Paket finden sich weitere uni‑/bidirektionale Konverter, die ähnliche Aufgaben für andere Typen (z. B. BOOL_TO_ALR) erfüllen.

## Fazit
Der **ALR_TO_AX**‑Funktionsblock bietet eine schlanke, zuverlässige Möglichkeit, einen LREAL‑Adapterausgang in einen BOOL‑Adaptereingang umzusetzen. Dank seiner einfachen Struktur eignet er sich hervorragend für grundlegende Digitalisierungsaufgaben in IEC‑61499‑basierten Steuerungssystemen. Er ist leicht verständlich, gut erweiterbar und folgt den gängigen Entwurfsmustern für unidirektionale Adapterkonvertierung.