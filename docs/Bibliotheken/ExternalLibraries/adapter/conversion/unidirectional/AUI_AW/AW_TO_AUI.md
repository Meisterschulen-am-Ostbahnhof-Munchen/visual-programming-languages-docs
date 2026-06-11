# AW_TO_AUI


![AW_TO_AUI](./AW_TO_AUI.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AW_TO_AUI** ist ein zusammengesetzter Baustein (Composite FB), der einen **AW (WORD)**-Adapter in einen **AUI (UINT)**-Adapter umwandelt. Er ermöglicht die nahtlose Anbindung von Komponenten, die unterschiedliche Datentypen über unidirektionale Adapter nutzen. Intern verwendet er den Standard-Konvertierungsbaustein `F_WORD_TO_UINT` zur Typumwandlung.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Der FB besitzt keine eigenständigen Ereignis-Eingänge. Das Ereignis `E1` wird über den **Socket (Eingangsadapter) `AW_IN`** bereitgestellt und löst die Datenkonvertierung aus.

### **Ereignis-Ausgänge**

Der FB besitzt keine eigenständigen Ereignis-Ausgänge. Das Ereignis `E1` wird über den **Plug (Ausgangsadapter) `AUI_OUT`** nach erfolgreicher Konvertierung ausgegeben.

### **Daten-Eingänge**

Der FB besitzt keine eigenständigen Daten-Eingänge. Das Datum `D1` vom Typ `WORD` wird über den **Socket `AW_IN`** bereitgestellt.

### **Daten-Ausgänge**

Der FB besitzt keine eigenständigen Daten-Ausgänge. Das Datum `D1` vom Typ `UINT` wird über den **Plug `AUI_OUT`** ausgegeben.

### **Adapter**

| Name     | Richtung | Typ                                     | Beschreibung                     |
|----------|----------|-----------------------------------------|----------------------------------|
| `AW_IN`  | Eingang  | `adapter::types::unidirectional::AW`   | WORD-Adapter-Eingang (Socket)    |
| `AUI_OUT`| Ausgang  | `adapter::types::unidirectional::AUI`  | UINT-Adapter-Ausgang (Plug)      |

## Funktionsweise

Der Funktionsblock fungiert als reine Konvertierungsschicht zwischen zwei unterschiedlichen Adaptertypen. Intern ist ein einziger Funktionsbaustein `F_WORD_TO_UINT` eingebettet:

1. **Ereignissteuerung**:  
   - Ein eingehendes Ereignis am Socket `AW_IN.E1` triggert den Konvertierungsvorgang (`Convert.REQ`).  
   - Nach Abschluss der Konvertierung erzeugt der interne Baustein ein Bestätigungsereignis (`Convert.CNF`), das an den Plug `AUI_OUT.E1` weitergeleitet wird.

2. **Datenfluss**:  
   - Der vom Socket `AW_IN.D1` bereitgestellte `WORD`-Wert wird an den Eingang `Convert.IN` übergeben.  
   - Der Ausgang `Convert.OUT` liefert den konvertierten `UINT`-Wert, der an den Plug `AUI_OUT.D1` weitergegeben wird.

Die Umwandlung erfolgt nach der IEC 61131-3 Standardkonvertierung `WORD_TO_UINT`.

## Technische Besonderheiten

- **Reine Composite-Struktur**: Der FB besitzt keine eigene Zustandsmaschine oder Logik, sondern delegiert die gesamte Funktionalität an den eingebetteten Standardbaustein.
- **Unidirektionale Adapter**: Sowohl der Eingangs- als auch der Ausgangsadapter sind als unidirektionale Typen ausgelegt, was eine einfache und gerichtete Datenweitergabe ermöglicht.
- **Wiederverwendbarkeit**: Der Baustein kann in Projekten eingesetzt werden, in denen eine Schnittstellenanpassung zwischen WORD- und UINT-basierten Komponenten erforderlich ist.

## Zustandsübersicht

Da es sich um einen zusammengesetzten Baustein ohne eigene Zustandsmaschine handelt, gibt es keine internen Zustände. Der FB verhält sich strikt ereignisgesteuert: Auf jedes Ereignis am Eingang folgt – nach abgeschlossener Konvertierung – ein Ereignis am Ausgang.

## Anwendungsszenarien

- **Systemintegration**: Verbindung einer Komponente, die Daten als `WORD` über einen AW-Adapter bereitstellt, mit einer anderen Komponente, die `UINT` über einen AUI-Adapter erwartet.
- **Protokollanpassung**: Einsatz in Middleware- oder Gateway-Funktionen, um unterschiedliche Datenformate innerhalb einer Steuerungsarchitektur zu harmonisieren.
- **Modulare Erweiterung**: Einfaches Einfügen in bestehende 4diac-Netzwerke, ohne dass Änderungen an den angrenzenden Bausteinen erforderlich sind.

## Vergleich mit ähnlichen Bausteinen

Andere Konvertierungsbausteine (z. B. `F_WORD_TO_DWORD` oder `F_INT_TO_UINT`) arbeiten direkt auf Datenports. Der `AW_TO_AUI` hingegen ist speziell für die Adapter-basierte Kommunikation ausgelegt und kapselt sowohl die Typumwandlung als auch die Adapterlogik in einer Einheit. Dadurch wird die Handhabung von Adapter-Schnittstellen vereinfacht, und der Netzwerkentwurf bleibt übersichtlich.

## Fazit

Der Funktionsblock `AW_TO_AUI` bietet eine kompakte und zuverlässige Lösung zur Adapterkonvertierung von `WORD` nach `UINT`. Durch die Verwendung eines standardisierten IEC‑61131‑Konvertierungsbausteins und der klaren Ereignissteuerung ist er leicht verständlich und wartbar. Er eignet sich besonders für Projekte, die eine saubere Trennung zwischen unterschiedlichen Datentypen auf Adapterebene erfordern.