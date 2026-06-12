# AULI_FB_CTD


![AULI_FB_CTD](./AULI_FB_CTD.svg)


* * * * * * * * * *

## Einleitung

Der Funktionsblock **AULI_FB_CTD** realisiert einen **Abwärtszähler (Down Counter)** auf Basis des Datentyps `ULINT` (unsigned long integer). Er ist als **Adapter-Version** ausgeführt und kapselt den Standardbaustein `FB_CTD_ULINT` aus der IEC 61131-3-Bibliothek. Der Baustein ermöglicht eine modulare Anbindung über die Adapter-Schnittstellen CD (Count Down), LD (Load) und PV (Preset Value) sowie die Ausgabe des aktuellen Zählwerts (CV) und eines binären Signals (Q) über entsprechende Plug-Adapter.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Der Baustein besitzt **keine direkten Ereignis-Eingänge**. Die Triggerung erfolgt ausschließlich über die **Event-Kanäle der Socket-Adapter**:

| Adapter   | Event-Port | Beschreibung                        |
|-----------|------------|-------------------------------------|
| **CD**    | CD.E1      | Zählimpuls (Count Down)             |
| **LD**    | LD.E1      | Ladeimpuls (Load des Preset-Werts)  |
| **PV**    | PV.E1      | Aktualisierung des Preset-Werts     |

> **Hinweis:** Jedes dieser Ereignisse löst eine Verarbeitung des internen Zählers aus. Der Zähler wird dabei immer neu berechnet – unabhängig davon, ob sich der Wert tatsächlich ändert.

### **Ereignis-Ausgänge**

| Name | Beschreibung                                       |
|------|----------------------------------------------------|
| CNF  | Bestätigung (Confirmation) nach jeder Verarbeitung |

Zusätzlich werden über die Plug-Adapter **zwei Ereignis-Ausgänge** bereitgestellt:

| Adapter | Event-Port | Beschreibung                                     |
|---------|------------|--------------------------------------------------|
| **Q**   | Q.E1       | Wird bei jeder Verarbeitung ausgegeben           |
| **CV**  | CV.E1      | Wird bei jeder Verarbeitung ausgegeben           |

> **Anmerkung:** Da die Ereignisse bei jedem Update (CD, LD, PV) feuern, wird empfohlen, bei Bedarf eine Änderungsflanke mit einem `AX_D_FF` zu filtern (siehe Technische Besonderheiten).

### **Daten-Eingänge**

Daten werden ebenfalls über die **Socket-Adapter** bereitgestellt:

| Adapter | Daten-Port | Datentyp | Beschreibung                              |
|---------|------------|----------|-------------------------------------------|
| **CD**  | CD.D1      | `BOOL`   | Zählimpuls (steigende Flanke)             |
| **LD**  | LD.D1      | `BOOL`   | Ladebefehl (steigende Flanke)             |
| **PV**  | PV.D1      | `ULINT`  | Preset-Wert (bei LD oder PV-Update geladen) |

### **Daten-Ausgänge**

Daten werden über die **Plug-Adapter** ausgegeben:

| Adapter | Daten-Port | Datentyp | Beschreibung                              |
|---------|------------|----------|-------------------------------------------|
| **Q**   | Q.D1       | `BOOL`   | Zählerstand = 0 (Ausgangssignal)          |
| **CV**  | CV.D1      | `ULINT`  | Aktueller Zählerstand                     |

### **Adapter**

| Richtung | Adapter-Typ           | Kurzbeschreibung                     |
|----------|-----------------------|--------------------------------------|
| Socket   | `AX` (bidirektional)  | Count-Down-Steuerung (Event + BOOL)  |
| Socket   | `AX` (bidirektional)  | Load-Steuerung (Event + BOOL)        |
| Socket   | `AULI` (bidirektional)| Preset-Wert (Event + ULINT)          |
| Plug     | `AX` (bidirektional)  | Ausgang Q (Event + BOOL)             |
| Plug     | `AULI` (bidirektional)| Ausgang Zählerstand (Event + ULINT)  |

## Funktionsweise

Der Baustein kapselt die IEC 61131-3-Funktion `FB_CTD_ULINT`. Die interne Logik wird durch die Ereignisse der drei Socket-Adapter getriggert:

1. **CD-Ereignis (Count Down):**  
   Bei einer steigenden Flanke von `CD.D1` und einem gleichzeitigen Event auf `CD.E1` wird der Zählerstand um 1 dekrementiert (sofern er > 0 ist). Der neue Wert wird am Plug `CV` ausgegeben.

2. **LD-Ereignis (Load):**  
   Bei einer steigenden Flanke von `LD.D1` und einem Event auf `LD.E1` wird der aktuelle Preset-Wert (`PV.D1`) in den Zähler geladen. Der Zählerstand wird auf den Preset-Wert gesetzt.

3. **PV-Ereignis (Preset Value Update):**  
   Ein Event auf `PV.E1` aktualisiert den intern gespeicherten Preset-Wert (ohne den Zählerstand zu verändern). Dies ist nützlich, um den Preset dynamisch während des Betriebs zu ändern.

Nach jeder Verarbeitung wird das Bestätigungsereignis `CNF` sowie die Ereignisse auf den Plug-Adaptern `Q.E1` und `CV.E1` gesendet. Die Daten `Q.D1` und `CV.D1` werden entsprechend aktualisiert.

## Technische Besonderheiten

- **Datentyp ULINT:**  
  Der Baustein arbeitet mit vorzeichenlosen 64‑Bit-Ganzzahlen (ULINT), wodurch Zählbereiche von 0 bis 2⁶⁴‑1 möglich sind – geeignet für sehr große Zählaufgaben.

- **Adapter-basierte Anbindung:**  
  Alle Ein- und Ausgänge erfolgen über Adapter (`AX` für binäre Signale, `AULI` für ULINT-Werte). Dies ermöglicht eine saubere Kapselung und modulare Verdrahtung in der 4diac-IDE.

- **Ereignisausgabe bei jedem Update:**  
  Der Baustein feuert die Ausgangsereignisse bei jedem eingehenden Ereignis (CD, LD, PV) – auch wenn sich der Zählerstand oder Ausgangswert nicht ändert. Dadurch entsteht ein **permanentes Triggern** des nachgeschalteten Netzwerks.  
  → **Empfehlung:** Verwenden Sie einen `AX_D_FF` (Differentiator/Filter) an den Ausgängen, wenn nur bei Wertänderung reagiert werden soll.

- **Kein interner Zustandsautomat:**  
  Der Baustein selbst besitzt keinen eigenen Zustandsautomaten; die Zustandslogik (z. B. Erkennung der steigenden Flanke) wird vom internen `FB_CTD_ULINT` übernommen.

## Zustandsübersicht

Der Baustein verwaltet intern lediglich den **Zählerstand** (CV) und den **aktuellen Preset-Wert** (PV). Eine explizite Zustandsmaschine liegt nicht vor. Die möglichen Aktionen sind:

| Zustand / Aktion | Auslöser                  | Ergebnis                                                |
|------------------|---------------------------|---------------------------------------------------------|
| Count Down       | CD-Ereignis & CD.D1=TRUE  | CV := CV - 1 (falls CV>0)                               |
| Load             | LD-Ereignis & LD.D1=TRUE  | CV := PV (aktueller Preset)                             |
| Preset Update    | PV-Ereignis               | PV wird überschrieben (CV bleibt unverändert)           |

Der Ausgang `Q` wird auf `TRUE` gesetzt, sobald `CV = 0` ist; andernfalls ist er `FALSE`.

## Anwendungsszenarien

- **Stückzähler mit großem Bereich:**  
  Erfassung von Produktionsmengen mit Wertebereich > 32 Bit (z. B. 10 Mrd. Teile).

- **Vorwahl- oder Ablaufsteuerung:**  
  Einsatz als Abwärtszähler in einer Ablaufkette, bei der nach Erreichen des Werts 0 ein Signal ausgelöst wird (z. B. Chargenende).

- **Dynamische Preset-Werte:**  
  Änderung des Zähl-Endwerts während des Betriebs über das PV-Ereignis, ohne den aktuellen Zählerstand zu beeinflussen.

- **Modulare Systeme:**  
  Integration in größere Steuerungsarchitekturen, die durchgängig auf Adapter-Kommunikation setzen (z. B. über den Eclipse 4diac-Adapter-Mechanismus).

## Vergleich mit ähnlichen Bausteinen

| Baustein             | Datentyp | Schnittstelle         | Besonderheit                                   |
|----------------------|----------|-----------------------|------------------------------------------------|
| `FB_CTD_ULINT`       | ULINT    | Standard-EA           | Basis-Abwärtszähler ohne Adapter               |
| **AULI_FB_CTD**      | ULINT    | Adapter (AX, AULI)    | Adapter-gekapselt, alle Events führen zu Update|
| `FB_CTD` (Standard)  | INT/UINT | Standard-EA           | Meist 16‑Bit oder 32‑Bit, feste Ereignislogik  |

Der **AULI_FB_CTD** bietet durch die Adapter-Kopplung eine flexiblere Einbindung in komplexe Netzwerke, hat aber den „NebenEffekt", dass Ausgangsereignisse auch bei unveränderten Werten gesendet werden. Für Anwendungen, die nur bei Wertänderung feuern sollen, ist der Basisbaustein `FB_CTD_ULINT` oder eine Kombination mit einem Flankendetektor (`AX_D_FF`) zu bevorzugen.

## Fazit

Der **AULI_FB_CTD** ist ein leistungsfähiger Abwärtszähler für 64‑Bit-Werte, der über Adapter-Schnittstellen in 4diac-Projekte integriert wird. Er eignet sich besonders für große Zählbereiche und modulare Steuerungstopologien. Die ständige Ereignisausgabe erfordert eine sorgfältige Handhabung des nachfolgenden Netzwerks, kann aber durch geeignete Filterbausteine (z. B. `AX_D_FF`) gezähmt werden. Dank der Kapselung des bewährten `FB_CTD_ULINT` ist die Funktionsweise robust und standardkonform.