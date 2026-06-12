# AUI_TO_AW


![AUI_TO_AW](./AUI_TO_AW.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `AUI_TO_AW` ist ein zusammengesetzter (Composite) Baustein, der einen AUI-Adapter (Datentyp UINT) in einen AW-Adapter (Datentyp WORD) umwandelt. Er kapselt die Typkonvertierung und stellt sie als einheitliche Adapterschnittstelle zur Verfügung, sodass Systemkomponenten mit unterschiedlichen Datentypen nahtlos miteinander verbunden werden können.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| `AUI_IN.E1` | Ereignis (über Adapter) | Trigger zur Konvertierung des eingehenden UINT-Wertes |

### **Ereignis-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| `AW_OUT.E1` | Ereignis (über Adapter) | Bestätigung, dass der konvertierte WORD-Wert bereitgestellt wurde |

### **Daten-Eingänge**

| Name | Datentyp | Kommentar |
|------|----------|-----------|
| `AUI_IN.D1` | UINT (über Adapter) | Der zu konvertierende Eingangswert |

### **Daten-Ausgänge**

| Name | Datentyp | Kommentar |
|------|----------|-----------|
| `AW_OUT.D1` | WORD (über Adapter) | Der konvertierte Ausgangswert |

### **Adapter**

| Richtung | Name | Typ | Kommentar |
|----------|------|-----|-----------|
| Socket (Eingang) | `AUI_IN` | `adapter::types::unidirectional::AUI` | UINT‑Adapter als Quelle |
| Plug (Ausgang) | `AW_OUT` | `adapter::types::unidirectional::AW` | WORD‑Adapter als Senke |

## Funktionsweise

Der Baustein reagiert auf ein Ereignis am Socket `AUI_IN.E1`. Daraufhin wird der aktuelle Wert von `AUI_IN.D1` (Datentyp UINT) an den internen Konvertierungsbaustein `F_UINT_TO_WORD` weitergeleitet. Dieser wandelt den Wert nach IEC 61131 in den Datentyp WORD um. Sobald die Konvertierung abgeschlossen ist, wird der Ergebniswert an den Plug `AW_OUT.D1` übergeben und ein Bestätigungsereignis auf `AW_OUT.E1` ausgelöst.

Das Zusammenspiel von Ereignis- und Datenfluss sorgt für eine sichere und deterministische Datenweitergabe.

## Technische Besonderheiten

- **Composite‑Aufbau:** Der Baustein kapselt die komplette Umwandlungslogik in einem einzigen Funktionsblock, sodass in der Anwendung keine weiteren Konvertierungsschritte nötig sind.
- **Typkonvertierung:** Die Konvertierung erfolgt mittels des standardisierten IEC‑61131‑Bausteins `F_UINT_TO_WORD`. UINT und WORD sind bitkompatibel, sodass keine Datenverluste auftreten.
- **Adapter‑Schnittstelle:** Durch die Nutzung von Adaptern wird eine lose Kopplung der Komponenten erreicht. Der Baustein kann direkt in Adapter‑basierte Netzwerke eingefügt werden.
- **Keine Zustände:** Der Baustein besitzt kein eigenes Zustandsverhalten (ECC). Er arbeitet rein ereignisgesteuert und führt bei jedem Trigger eine sofortige Umwandlung durch.

## Zustandsübersicht

Der Baustein enthält keinen eigenen Zustandsautomaten (ECC). Die Ablaufsteuerung erfolgt allein durch die Ereignisverbindungen im Composite‑Netzwerk. Nach dem Start ist der Baustein sofort bereit, eingehende Ereignisse zu verarbeiten und die Konvertierung durchzuführen.

## Anwendungsszenarien

- **Adapter‑Brücke:** Wenn ein Systemteil nur über einen AUI‑Adapter (UINT) kommuniziert, ein anderer Teil jedoch einen AW‑Adapter (WORD) erwartet, kann `AUI_TO_AW` als Vermittler eingesetzt werden.
- **Daten‑Typanpassung:** In Industrie 4.0‑ oder IIoT‑Umgebungen, in denen Geräte unterschiedliche Datentypen verwenden, dient der Baustein zur Harmonisierung der Schnittstellen.
- **Modulare Verkettung:** Der Baustein lässt sich einfach in eine Kette von Adaptern einfügen, um die Kompatibilität zwischen Komponenten herzustellen.

## Vergleich mit ähnlichen Bausteinen

- **Direkte Nutzung von `F_UINT_TO_WORD`:** Statt des Composite‑Bausteins könnte man direkt `F_UINT_TO_WORD` verwenden und die Adapter separat miteinander verbinden. Der Composite‑Block vereinfacht die Verkabelung und erhöht die Wiederverwendbarkeit.
- **Analoge Konverter (z. B. `AWORD_TO_AUINT`):** Es existieren entsprechende Bausteine für die umgekehrte Richtung. `AUI_TO_AW` fokussiert auf die spezifische Umwandlung von UINT zu WORD und bietet eine klar benannte, zielgerichtete Lösung.

## Fazit

Der Funktionsblock `AUI_TO_AW` stellt eine kompakte und robuste Lösung zur Umwandlung eines UINT‑Adapter‑Signals in ein WORD‑Adapter‑Signal dar. Durch die Kapselung der Standardkonvertierung und die Adapter‑Schnittstelle wird die Integration in bestehende Systeme erleichtert und die Lesbarkeit des Netzwerks verbessert. Der Baustein ist ideal geeignet, um Datentypunterschiede zwischen Komponenten auszugleichen, ohne die Übersichtlichkeit der Anwendung zu beeinträchtigen.