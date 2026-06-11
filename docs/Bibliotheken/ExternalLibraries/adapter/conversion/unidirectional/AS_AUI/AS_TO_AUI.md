# AS_TO_AUI


![AS_TO_AUI](./AS_TO_AUI.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `AS_TO_AUI` ist ein zusammengesetzter Baustein (Composite FB), der die Konvertierung eines SINT-Adapter-Inputs (`AS`) in einen UINT-Adapter-Output (`AUI`) realisiert. Er kapselt die Typumwandlung und ermöglicht eine saubere, adapterbasierte Schnittstelle zwischen Komponenten, die unterschiedliche Datentypen verwenden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Bezeichnung | Datentyp | Beschreibung |
|-------------|----------|--------------|
| `E1` (über `AS_IN`) | EVENT | Startet die Konvertierung des anliegenden SINT-Werts. |

### **Ereignis-Ausgänge**

| Bezeichnung | Datentyp | Beschreibung |
|-------------|----------|--------------|
| `E1` (über `AUI_OUT`) | EVENT | Bestätigt die abgeschlossene Konvertierung und Ausgabe des UINT-Werts. |

### **Daten-Eingänge**

| Bezeichnung | Datentyp | Beschreibung |
|-------------|----------|--------------|
| `D1` (über `AS_IN`) | SINT | Der zu konvertierende vorzeichenbehaftete 8‑Bit‑Wert. |

### **Daten-Ausgänge**

| Bezeichnung | Datentyp | Beschreibung |
|-------------|----------|--------------|
| `D1` (über `AUI_OUT`) | UINT | Der konvertierte vorzeichenlose 16‑Bit‑Wert. |

### **Adapter**

| Bezeichnung | Typ | Richtung | Beschreibung |
|-------------|-----|----------|--------------|
| `AS_IN` | `adapter::types::unidirectional::AS` | Socket (Eingang) | Stellt den SINT-Wert und das auslösende Ereignis bereit. |
| `AUI_OUT` | `adapter::types::unidirectional::AUI` | Plug (Ausgang) | Gibt den konvertierten UINT-Wert und das Bestätigungsereignis aus. |

## Funktionsweise

Der Baustein arbeitet ereignisgesteuert:

1. Wenn am `AS_IN`-Adapter das Ereignis `E1` eintrifft, wird der anliegende SINT-Datenwert (`D1`) an den internen Konvertierungsbaustein `F_SINT_TO_UINT` weitergeleitet.
2. Der `F_SINT_TO_UINT`-Baustein führt die Datentypkonvertierung gemäß IEC 61131 durch (SINT → UINT).
3. Sobald die Konvertierung abgeschlossen ist, wird der resultierende UINT-Wert an den `AUI_OUT`-Adapter übergeben und das Ereignis `E1` auf `AUI_OUT` ausgelöst.

Der gesamte Ablauf ist innerhalb eines Ereigniszyklus atomar: Ereignis rein, Daten wandeln, Ereignis raus.

## Technische Besonderheiten

- Der Baustein verwendet intern die IEC‑61131‑Konvertierungsfunktion `F_SINT_TO_UINT`, die aus der Bibliothek `iec61131::conversion` stammt.
- Die Adapter sind als **unidirektionale** Typen ausgelegt (AS für Eingang, AUI für Ausgang), was die Datenflussrichtung klar definiert und Missverständnisse vermeidet.
- Es gibt keine internen Zustände oder Zeitverhalten – die Konvertierung erfolgt rein kombinatorisch, gesteuert durch das Ereignis.
- Der Baustein ist unter der Eclipse Public License 2.0 lizenziert.

## Zustandsübersicht

Da es sich um einen zusammengesetzten Baustein ohne eigene Zustandsmaschine handelt, existiert kein interner Zustandsautomat. Der Baustein ist vollständig ereignisgetrieben und führt bei jedem Auslösen die Konvertierung sofort aus.

## Anwendungsszenarien

- **Anbindung unterschiedlicher Bussysteme**: Wenn ein Sensor (z. B. AS‑Interface) SINT‑Werte liefert, die Steuerung aber UINT‑Werte erwartet, kann dieser Baustein die Übersetzung übernehmen.
- **Protokoll‑ oder Adapter‑Kompatibilität**: Einsatz in heterogenen Automatisierungssystemen, in denen verschiedene Feldbusse oder Komponenten mit unterschiedlichen Datentypen arbeiten.
- **Datenaufbereitung**: Vorbereitung von SINT‑Daten für eine weitere Verarbeitung, die ausschließlich UINT unterstützt.

## Vergleich mit ähnlichen Bausteinen

- **Direkte Konvertierungs‑FBs** (z. B. `F_SINT_TO_UINT`): Diese arbeiten auf Ebene einzelner Signale ohne Adapter‑Kapselung. `AS_TO_AUI` integriert die Adapter‑Schnittstelle und ist daher leichter in adapterbasierte Architekturen einbindbar.
- **Bidirektionale Adapter‑Konverter**: Falls eine Umwandlung in beide Richtungen nötig ist, müsste ein separater Baustein (z. B. `AUI_TO_AS`) verwendet werden. `AS_TO_AUI` ist strikt unidirektional.

## Fazit

Der `AS_TO_AUI`‑Baustein bietet eine einfache, zuverlässige und standardisierte Methode, um SINT‑Adapter‑Daten in ein UINT‑Adapter‑Format zu konvertieren. Dank der Verwendung von IEC‑61131‑Bausteinen und unidirektionalen Adaptern ist er robust, leicht verständlich und gut in bestehende 4diac‑Projekte integrierbar.