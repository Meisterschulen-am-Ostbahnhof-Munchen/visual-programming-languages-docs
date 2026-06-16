# AD_TO_ALI


![AD_TO_ALI](./AD_TO_ALI.svg)

* * * * * * * * * *
## Einleitung
Der **AD_TO_ALI** ist ein Composite-Funktionsbaustein zur unidirektionalen Umwandlung eines DWORD-Werts (über einen AD-Adapter) in einen LINT-Wert (über einen ALI-Adapter). Die Konvertierung erfolgt mittels des integrierten Standard-FBs `F_DWORD_TO_LINT`. Der Baustein ermöglicht eine einfache und standardisierte Anbindung von Komponenten, die unterschiedliche Datentypen über Adapterschnittstellen austauschen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine separaten Ereignis-Eingänge vorhanden. Die Ereignissteuerung erfolgt über den Adapter **AD_IN** (Ereignis *E1*).

### **Ereignis-Ausgänge**
Keine separaten Ereignis-Ausgänge vorhanden. Ausgangsereignisse werden über den Adapter **ALI_OUT** (Ereignis *E1*) bereitgestellt.

### **Daten-Eingänge**
Keine separaten Daten-Eingänge vorhanden. Die Eingangsdaten (DWORD) werden über den Adapter **AD_IN** (Data *D1*) bezogen.

### **Daten-Ausgänge**
Keine separaten Daten-Ausgänge vorhanden. Die Ausgangsdaten (LINT) werden über den Adapter **ALI_OUT** (Data *D1*) ausgegeben.

### **Adapter**

| Adapter | Typ | Richtung | Beschreibung |
|---------|-----|----------|--------------|
| **AD_IN** | `adapter::types::unidirectional::AD` | Socket | Empfängt einen DWORD-Wert (*D1*) sowie ein Eingangsereignis (*E1*). |
| **ALI_OUT** | `adapter::types::unidirectional::ALI` | Plug | Sendet den konvertierten LINT-Wert (*D1*) sowie ein Ausgangsereignis (*E1*). |

## Funktionsweise
Der Baustein wartet auf ein Ereignis am **AD_IN**-Adapter (Ereignis *E1*). Sobald dieses eintrifft, wird der aktuell anliegende DWORD-Wert (Data *D1*) aus dem Adapter gelesen und an den internen Baustein **Convert** (Typ `F_DWORD_TO_LINT`) übergeben. Dieser führt die Datentypkonvertierung durch. Nach erfolgreicher Konvertierung wird der resultierende LINT-Wert an den **ALI_OUT**-Adapter (Data *D1*) übergeben und ein Ereignis (*E1*) zur Bestätigung ausgelöst.

## Technische Besonderheiten
- **Reine Composite-Logik**: Der FB enthält keine eigene Zustandsmaschine, sondern realisiert die Konvertierung ausschließlich über die Verschaltung des eingebetteten FBs `F_DWORD_TO_LINT`.
- **Standardkonformität**: Die verwendete Konvertierungsfunktion entspricht der IEC 61131-3 (Typkonvertierung `DWORD_TO_LINT`).
- **Synchronität**: Ereignis und Daten werden innerhalb eines einzigen Ausführungszyklus vom Eingang zum Ausgang weitergeleitet (E1 → REQ → CNF → E1).

## Zustandsübersicht
Als Composite-Baustein besitzt **AD_TO_ALI** keine eigene Zustandsmaschine. Das Verhalten wird allein durch die innere Verschaltung und die Zustände des FBs `F_DWORD_TO_LINT` bestimmt. Eine grafische Zustandsübersicht entfällt.

## Anwendungsszenarien
- **Industrielle Automatisierung**: Umwandlung von DWORD-basierten Sensordaten (z. B. Zählerstände) in LINT-Werte zur Weiterverarbeitung in Systemen mit 64‑Bit-Integern.
- **Speicheradressierung**: Konvertierung von 32‑Bit-Adressen (DWORD) in 64‑Bit-Adressen (LINT) für große Speicherbereiche.
- **Datenintegration**: Anbindung von Komponenten, die unterschiedliche Adapterprotokolle nutzen, über eine standardisierte Konvertierungsschnittstelle.

## Vergleich mit ähnlichen Bausteinen
Es existieren analoge Konvertierungsbausteine wie `AD_TO_ALI` für andere Datentypen (z. B. `AD_TO_ALI` für DWORD→LINT, `AI_TO_ALI` für INT→LINT). Der vorliegende FB deckt spezifisch die Umwandlung von **DWORD** nach **LINT** ab und ist auf diese Kombination optimiert. Er ersetzt nicht die allgemeine `F_DWORD_TO_LINT`-Funktion, sondern kapselt sie in einer adapterbasierten Schnittstelle.

## Fazit
Der **AD_TO_ALI** bietet eine saubere, wiederverwendbare Lösung zur Konvertierung von DWORD-Adaptern auf LINT-Adapter. Durch die Composite-Struktur bleibt die Logik transparent und leicht in bestehende 4diac‑Projekte integrierbar. Er eignet sich besonders für Szenarien, in denen eine einheitliche Adapterschnittstelle gefordert ist, aber unterschiedliche Datentypen zusammengeführt werden müssen.