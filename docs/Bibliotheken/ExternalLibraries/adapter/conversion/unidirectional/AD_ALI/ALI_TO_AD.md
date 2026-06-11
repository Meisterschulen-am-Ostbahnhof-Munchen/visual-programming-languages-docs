# ALI_TO_AD


![ALI_TO_AD](./ALI_TO_AD.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `ALI_TO_AD` ist ein Composite-Baustein zur Konvertierung einer LINT–Adapter-Schnittstelle (ALI) in eine DWORD–Adapter-Schnittstelle (AD). Er dient als unidirektionaler Übersetzer zwischen zwei unterschiedlichen Datentypen innerhalb einer adapterbasierten Kommunikationsstruktur.

## Schnittstellenstruktur

Der Baustein besitzt keine eigenständigen Ereignis- oder Dateneingänge/-ausgänge. Die gesamte Kommunikation erfolgt ausschließlich über vordefinierte Adapter.

### **Ereignis-Eingänge**

Keine. Die Ereignissteuerung erfolgt über den eingehenden Socket‑Adapter `ALI_IN`.

### **Ereignis-Ausgänge**

Keine. Die Ergebnisereignisse werden über den ausgehenden Plug‑Adapter `AD_OUT` bereitgestellt.

### **Daten-Eingänge**

Keine. Die Eingangsdaten werden über den Socket‑Adapter `ALI_IN` übertragen.

### **Daten-Ausgänge**

Keine. Die Ausgangsdaten werden über den Plug‑Adapter `AD_OUT` übertragen.

### **Adapter**

| Richtung | Name    | Typ                                  | Beschreibung                           |
|----------|---------|--------------------------------------|----------------------------------------|
| Socket   | ALI_IN  | `adapter::types::unidirectional::ALI` | Eingangsadapter vom Typ LINT           |
| Plug     | AD_OUT  | `adapter::types::unidirectional::AD`  | Ausgangsadapter vom Typ DWORD          |

## Funktionsweise

Im Inneren des Bausteins wird eine einzelne Instanz des Funktionsblocks `iec61131::conversion::F_LINT_TO_DWORD` verwendet. Die Ereignis- und Datenverbindungen sind wie folgt verschaltet:

1. Ein Ereignis vom Socket `ALI_IN.E1` triggert den Eingang `REQ` des Konverters.
2. Der Konverter liest den LINT‑Wert vom Eingang `ALI_IN.D1` ein und wandelt ihn in einen DWORD‑Wert um.
3. Nach erfolgreicher Konvertierung erzeugt der Konverter das Bestätigungsereignis `CNF`, das auf den Plug `AD_OUT.E1` weitergeleitet wird.
4. Gleichzeitig wird der konvertierte DWORD‑Wert vom Ausgang `Convert.OUT` auf den Datenausgang `AD_OUT.D1` übertragen.

Die gesamte Übersetzung erfolgt ereignisgesteuert: Ein eingehendes Ereignis löst die Konvertierung aus und das Ergebnis wird mit einem Ausgangsereignis quittiert.

## Technische Besonderheiten

- Der Baustein ist vollständig als Composite realisiert und benötigt keine eigene Laufzeitlogik.
- Der interne Konverter `F_LINT_TO_DWORD` ist ein IEC‑61131‑3-Baustein, der eine bitgenaue Konvertierung eines 64‑Bit‑Ganzzahlwerts (LINT) in einen 32‑Bit‑Doppelwortwert (DWORD) vornimmt.
- Die Adapter sind als unidirektional definiert, d. h. die Daten fließen ausschließlich vom Eingangs‑ zum Ausgangsadapter.
- Der Baustein ist für den Einsatz in Automatisierungssystemen konzipiert, die Adapter‑Schnittstellen nach der Norm IEC 61499 nutzen.

## Zustandsübersicht

Der Funktionsblock besitzt keinen eigenen expliziten Zustandsautomaten. Sein Verhalten wird vollständig durch die Ereignisweitergabe und die interne Logik des Konverterbausteins bestimmt. Aus Sicht des Anwenders verhält er sich wie eine transparente Datenwandlung, die bei jedem eingehenden Ereignis einmal ausgeführt wird.

## Anwendungsszenarien

- **Integration heterogener Feldgeräte** – Wenn ein Gerät oder ein Teilnetzwerk Daten im LINT‑Format (z. B. als Zählerwert oder Zeitstempel) bereitstellt, das Zielsystem aber DWORD‑Werte erwartet.
- **Adapter‑Brücke zwischen Subsystemen** – In einer verteilten Steuerung nach IEC 61499 kann `ALI_TO_AD` eingesetzt werden, um zwei Subsysteme mit unterschiedlichen Adapterdefinitionen zu verbinden.
- **Datenformat‑Anpassung in Migrationsprojekten** – Bei der Modernisierung von Anlagen, bei denen alte Komponenten noch LINT‑Adapter liefern, neue Komponenten jedoch DWORD‑Adapter benötigen.

## Vergleich mit ähnlichen Bausteinen

- **`INT_TO_DWORD`** – Wandelt einen Integer‑Wert (16 Bit) in DWORD um, wird aber nicht auf Adapter‑Ebene angeboten.
- **`DWORD_TO_LINT`** – Kehrt die hier beschriebene Konvertierung um und wandelt DWORD zurück nach LINT.
- **Eigene Kombinationsbausteine** – Statt eines fest verdrahteten Adapter‑Converters könnte die Konvertierung auch manuell mit einem `F_LINT_TO_DWORD` und separaten Adaptern realisiert werden. Der Composite‑Baustein bietet hier eine kompakte und wiederverwendbare Kapselung.

## Fazit

`ALI_TO_AD` ist ein einfacher, aber nützlicher Composite‑Baustein, der die unidirektionale Konvertierung eines LINT‑Adapters in einen DWORD‑Adapter ermöglicht. Er erlaubt eine saubere Trennung der Datentypen auf der Adapterebene und vereinfacht die Integration unterschiedlicher Systeme in einer IEC‑61499‑Umgebung. Die Verwendung eines standardisierten IEC‑61131‑Konverters gewährleistet eine definierte und reproduzierbare Datenwandlung.