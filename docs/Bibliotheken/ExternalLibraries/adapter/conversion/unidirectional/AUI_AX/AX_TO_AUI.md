# AX_TO_AUI


![AX_TO_AUI](./AX_TO_AUI.svg)

* * * * * * * * * *
## Einleitung
Der AX_TO_AUI ist ein Composite Funktionsblock (FB), der einen BOOL-Wert aus einem AX-Adapter in einen UINT-Wert für einen AUI-Adapter umwandelt. Er kapselt die Konvertierungslogik und ermöglicht eine nahtlose Integration zwischen unidirektionalen Adaptern unterschiedlicher Datentypen. Die Umwandlung erfolgt ereignisgesteuert über einen internen IEC 61131 Konvertierungsbaustein.

## Schnittstellenstruktur
Der Baustein besitzt keine direkten Ereignis- oder Datenschnittstellen, sondern ausschließlich Adapter-Schnittstellen. Die nachfolgende Aufstellung beschreibt die über die Adapter bereitgestellten bzw. benötigten Signale.

### **Ereignis-Eingänge**
- **AX_IN.E1** (Ereignis vom angeschlossenen AX-Adapter): Löst die Konvertierung des bereitgestellten BOOL-Werts aus.

### **Ereignis-Ausgänge**
- **AUI_OUT.E1** (Ereignis zum angeschlossenen AUI-Adapter): Signalisiert, dass der umgewandelte UINT-Wert anliegt.

### **Daten-Eingänge**
- **AX_IN.D1** (BOOL): Boolescher Eingangswert (z. B. 0 oder 1), der in einen UINT-Wert konvertiert werden soll.

### **Daten-Ausgänge**
- **AUI_OUT.D1** (UINT): Ganzzahliger Ausgangswert (0 oder 1), der dem konvertierten BOOL-Eingang entspricht.

### **Adapter**
- **AX_IN** (Socket) – Typ: `adapter::types::unidirectional::AX` (BOOL)
- **AUI_OUT** (Plug) – Typ: `adapter::types::unidirectional::AUI` (UINT)

## Funktionsweise
Der FB arbeitet als einfache Pipeline: Ein eingehendes Ereignis am Socket AX_IN.E1 triggert den internen Funktionsblock `F_BOOL_TO_UINT`. Dieser liest den aktuellen Wert von AX_IN.D1, wandelt ihn in einen UINT-Wert um (BOOL FALSE → 0, BOOL TRUE → 1) und legt das Ergebnis an AUI_OUT.D1 an. Nach Abschluss wird ein Ereignis über AUI_OUT.E1 ausgegeben. Der gesamte Vorgang ist atomar und ereignisgesteuert, es existiert kein interner Zustand.

## Technische Besonderheiten
- Der Baustein ist als Composite FB realisiert, d. h. er besteht aus einem Netzwerk untergeordneter FB-Instanzen (hier nur `F_BOOL_TO_UINT`).
- Die Umwandlung folgt der IEC 61131-3 Konvertierungsregel: BOOL FALSE = 0, BOOL TRUE = 1.
- Die Verwendung von Adaptern ermöglicht eine lose Kopplung zwischen Komponenten unterschiedlicher Domänen (BOOL-Steuerung und UINT-Kommunikation).
- Der FB besitzt keine eigene Zustandsmaschine; die Abarbeitung ist rein ereignisgesteuert.

## Zustandsübersicht
Da es sich um einen Composite FB ohne eigenes ECC (Execution Control Chart) handelt, gibt es keine expliziten Zustände. Die Funktionalität reduziert sich auf die ereignisgesteuerte Ausführung des internen FBs.

## Anwendungsszenarien
- **Steuerungsschnittstelle**: Ein BOOL-Signal (z. B. Schalter Ein/Aus) wird in einen numerischen Wert gewandelt, um es über einen AUI-Adapter an eine übergeordnete Steuerung zu senden.
- **Protokollanpassung**: Anbindung einer BOOL-basierten Sensorik an ein System, das UINT-Werte erwartet (z. B. zur Weiterverarbeitung in arithmetischen Blöcken).
- **Vereinheitlichung von Adapterschnittstellen**: Der FB dient als Adapter zwischen zwei unterschiedlichen unidirektionalen Adaptertypen und vermeidet Doppelentwicklungen.

## Vergleich mit ähnlichen Bausteinen
- **AX_TO_AUI** wandelt BOOL → UINT um.
- **AX_TO_ASI** würde BOOL → SINT konvertieren, **AX_TO_ADI** BOOL → DINT – alle folgen demselben Muster, jedoch mit unterschiedlichen Zieltypen.
- Im Gegensatz zu einem generischen `F_BOOL_TO_UINT` bietet dieser FB eine gekapselte Adapterschnittstelle und ist direkt in Adapter-basierte Architekturen integrierbar.

## Fazit
Der AX_TO_AUI ist ein kleiner, spezialisierter Baustein zur Konvertierung von BOOL- in UINT-Daten über Adapterschnittstellen. Er erfüllt eine typische Integrationsaufgabe in IEC 61499-basierten Systemen, bei der unterschiedliche Datentypen über unidirektionale Adapter verbunden werden müssen. Seine Composite-Struktur macht die Implementierung transparent und erweiterbar.