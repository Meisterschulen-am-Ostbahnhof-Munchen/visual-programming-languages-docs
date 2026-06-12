# ALI_TO_ALR


![ALI_TO_ALR](./ALI_TO_ALR.svg)

*(Bild nicht verfügbar)*

* * * * * * * * * *

## Einleitung

Der Funktionsblock **ALI_TO_ALR** ist ein Composite-Baustein, der die Konvertierung eines **ALI-Adapters** (LINT-Datentyp) in einen **ALR-Adapter** (LREAL-Datentyp) realisiert. Er dient als Brücke zwischen unterschiedlichen Adapter-Schnittstellen und ermöglicht eine nahtlose Datenüberführung von 64‑Bit‑Ganzzahlen in 64‑Bit‑Gleitkommazahlen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Der FB besitzt keine separaten Ereignis-Eingänge. Die ereignisgesteuerte Verarbeitung erfolgt über den **Socket** `ALI_IN`, dessen Ereignis `E1` die Konvertierung auslöst.

### **Ereignis-Ausgänge**

Es sind keine eigenständigen Ereignis-Ausgänge vorhanden. Das Ergebnisereignis wird über den **Plug** `ALR_OUT` auf dessen Ereignis `E1` ausgegeben.

### **Daten-Eingänge**

Der FB verfügt über keine direkten Daten-Eingänge. Die zu konvertierenden LINT-Daten werden über den **Socket** `ALI_IN` (Datenpunkt `D1`) bereitgestellt.

### **Daten-Ausgänge**

Analog gibt es keine separaten Daten-Ausgänge. Der konvertierte LREAL-Wert wird über den **Plug** `ALR_OUT` (Datenpunkt `D1`) ausgegeben.

### **Adapter**

| Typ | Name | Richtung | Beschreibung |
|-----|------|----------|--------------|
| **Socket** | `ALI_IN` | Eingang | Adapter vom Typ `adapter::types::unidirectional::ALI` (LINT) |
| **Plug**  | `ALR_OUT` | Ausgang | Adapter vom Typ `adapter::types::unidirectional::ALR` (LREAL) |

## Funktionsweise

Der FB arbeitet als reine Weiterleitung und Konvertierung:

1. Ein Ereignis am **Socket** `ALI_IN.E1` triggert den internen Funktionsblock `Convert` (Typ `F_LINT_TO_LREAL`).
2. Gleichzeitig wird der LINT-Wert von `ALI_IN.D1` an den Eingang `Convert.IN` übergeben.
3. Der Konvertierungsblock `Convert` wandelt den Wert gemäß IEC 61131-Konvertierungslogik in einen LREAL-Wert um.
4. Nach Abschluss der Konvertierung erzeugt `Convert` das Ereignis `CNF`, das an den **Plug** `ALR_OUT.E1` weitergeleitet wird.
5. Zeitgleich wird der konvertierte LREAL-Wert von `Convert.OUT` an `ALR_OUT.D1` übergeben.

Die gesamte Verarbeitung erfolgt ereignisgesteuert und ohne eigene Zustandslogik.

## Technische Besonderheiten

- **Composite-Baustein**: Die Logik wird ausschließlich durch die Verschaltung des standardisierten Konvertierungsbausteins `F_LINT_TO_LREAL` realisiert – kein eigener Algorithmus.
- **Adapter-orientierte Schnittstelle**: Der FB kapselt die Konvertierung vollständig in die Adapter-Schnittstellen, sodass er in Umgebungen mit einheitlichen Adapter-Typen (unidirektional) eingesetzt werden kann.
- **Kein Zustandsautomat**: Aufgrund der reinen Datenfluss-Struktur gibt es keinen internen Zustandsautomaten.

## Zustandsübersicht

Der FB besitzt keinen eigenen Zustandsautomaten. Die Abarbeitung folgt ausschließlich der Ereigniskette des inneren Netzwerks:

- Idle → Ereignis an `ALI_IN.E1` → Konvertierung läuft → Ergebnisereignis an `ALR_OUT.E1` → zurück in Idle.

## Anwendungsszenarien

- Integration von Komponenten, die LINT-Werte liefern (z. B. Zähler, Positionsgeber), in Systeme, die LREAL erwarten (z. B. Regelungsalgorithmen mit Gleitkommaberechnung).
- Umstellung von Integer-basierten auf Fließkomma-basierte Adapter-Schnittstellen ohne Änderung der übergeordneten Architektur.
- Zwischenschicht in modularen Steuerungsprojekten, in denen unterschiedliche Datentypen miteinander verbunden werden müssen.

## Vergleich mit ähnlichen Bausteinen

In der Bibliothek existieren analoge Konverter für andere Datentypen (z. B. `LINT_TO_REAL`, `DINT_TO_REAL`). `ALI_TO_ALR` ist die Adapter‑spezifische Variante, die die Konvertierung in die standardisierten unidirektionalen Adapter `ALI` und `ALR` einbettet. Sie erlaubt einen einfachen Austausch zwischen verschiedenen Adapter-Typen, ohne dass die aufrufende Umgebung die Details der Konvertierung kennen muss.

## Fazit

Der FB `ALI_TO_ALR` bietet eine saubere, wartbare und standardkonforme Lösung zur Umwandlung eines LINT-Adapters in einen LREAL-Adapter. Durch die Nutzung eines bewährten IEC 61131‑Konvertierungsbausteins bleibt die Implementierung zuverlässig und effizient. Er eignet sich besonders für modulare Steuerungsarchitekturen, in denen Datentyp‑ und Adapter‑Kompatibilität gefordert ist.