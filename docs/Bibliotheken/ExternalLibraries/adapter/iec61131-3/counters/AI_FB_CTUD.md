# AI_FB_CTUD


![AI_FB_CTUD](./AI_FB_CTUD.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AI_FB_CTUD** realisiert einen Aufwärts-/Abwärtszähler (Up-Down-Counter) vom Datentyp **INT** in einer Adapter-basierten Variante. Er kapselt den IEC 61131‑3 Standardbaustein `FB_CTUD` und stellt dessen Funktionalität über die Adapter-Schnittstellen (`AX` und `AI`) der 4diac‑IDE zur Verfügung. Der Baustein eignet sich besonders für den Einsatz in industriellen Steuerungssystemen, die auf ereignisgesteuerte Kommunikation setzen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Der Baustein besitzt keine separaten Ereignis-Eingänge im klassischen Sinne. Stattdessen werden Ereignisse über die **Sockets** (Adapter) empfangen:
- **CU** (AX) – Zählereignis aufwärts (Count Up)
- **CD** (AX) – Zählereignis abwärts (Count Down)
- **R** (AX) – Rücksetzen (Reset)
- **LD** (AX) – Laden des Presetwertes (Load)
- **PV** (AI) – Übergabe des Presetwertes (Preset Value)

Jedes eingehende Ereignis löst eine Aktualisierung des internen Zählers aus.

### **Ereignis-Ausgänge**
- **CNF** – Bestätigung der Ausführung (Execution Confirmation), wird bei jeder Aktualisierung ausgegeben.
- **QU** (AX) – Ausgangsereignis für den Aufwärtszähler (Up Output)
- **QD** (AX) – Ausgangsereignis für den Abwärtszähler (Down Output)
- **CV** (AI) – Ausgangsereignis für den aktuellen Zählwert (Count Value)

### **Daten-Eingänge**
Alle Daten werden über die **Sockets** bereitgestellt:
- **CU.D** (BOOL) – Zählimpuls aufwärts
- **CD.D** (BOOL) – Zählimpuls abwärts
- **R.D** (BOOL) – Rücksetzsignal
- **LD.D** (BOOL) – Freigabe zum Laden des Presetwerts
- **PV.D** (INT) – Vorgabewert (Preset Value)

### **Daten-Ausgänge**
- **QU.D** (BOOL) – Aufwärtszähl-Flag (TRUE, wenn Zähler den PV-Wert erreicht hat)
- **QD.D** (BOOL) – Abwärtszähl-Flag (TRUE, wenn Zähler den Wert 0 erreicht hat)
- **CV.D** (INT) – Aktueller Zählerstand

### **Adapter**
- **Sockets (Eingänge):**
  - `CU` (Typ `adapter::types::unidirectional::AX`)
  - `CD` (Typ `adapter::types::unidirectional::AX`)
  - `R` (Typ `adapter::types::unidirectional::AX`)
  - `LD` (Typ `adapter::types::unidirectional::AX`)
  - `PV` (Typ `adapter::types::unidirectional::AI`)
- **Plugs (Ausgänge):**
  - `QU` (Typ `adapter::types::unidirectional::AX`)
  - `QD` (Typ `adapter::types::unidirectional::AX`)
  - `CV` (Typ `adapter::types::unidirectional::AI`)

## Funktionsweise
Der Baustein arbeitet als reiner **Adapter-Wrapper** für den internen IEC 61131‑3 FB `FB_CTUD`. Die eingehenden Adapter-Ereignisse (über die Sockets) werden auf den Ereignis-Eingang `FB_CTUD.REQ` zusammengeführt, während die zugehörigen Datenwerte (z. B. `CU.D`, `PV.D`) an die entsprechenden Eingänge des internen Zählers weitergeleitet werden. Bei jeder Ausführung des internen FBs werden dessen Ausgänge (`CV`, `QU`, `QD`) gelesen und über die Adapter-Plugs ausgegeben. Gleichzeitig wird das Ereignis `CNF` erzeugt.

Der interne Zähler verhält sich wie ein klassischer IEC‑61131‑3 Up-Down-Counter:
- Ein positiver Flanke an `CU` erhöht den Zählwert um 1.
- Ein positiver Flanke an `CD` verringert den Zählwert um 1.
- Ein positiver Flanke an `R` setzt den Zählwert auf 0 zurück.
- Die Kombination `LD = TRUE` und ein Ereignis an `PV` lädt den aktuellen Zählwert auf den Wert von `PV`.
- `QU` wird TRUE, wenn der Zählwert den Presetwert erreicht oder überschreitet.
- `QD` wird TRUE, wenn der Zählwert den Wert 0 erreicht oder unterschreitet.

## Technische Besonderheiten
- **Keine Änderungsdetektion:** Der Baustein gibt **bei jedem empfangenen Ereignis** (unabhängig von einer tatsächlichen Wertänderung) die Ausgänge `CNF`, `QU`, `QD` und `CV` aus. Falls ein Verhalten gewünscht ist, bei dem die Ausgänge nur bei einer Änderung feuern, sollte ein vorgeschalteter **AX_D_FF** (Differentiator/Filter) verwendet werden. Dies wird auch im Quellcode des Bausteins ausdrücklich empfohlen.
- **Adapter-Nutzung:** Sämtliche Kommunikation erfolgt über unidirektionale Adapter (`AX` für boolesche Ereignisse, `AI` für analoge Werte). Dies ermöglicht eine lose Kopplung und Wiederverwendbarkeit in verschiedenen Systemtopologien.
- **Einheitliche Triggerung:** Alle fünf Ereignisquellen (CU, CD, R, LD, PV) führen zur Ausführung des internen Zählers über den gemeinsamen `REQ`-Eingang – es gibt keine separate Abarbeitungslogik pro Ereignis.

## Zustandsübersicht
Der Baustein selbst besitzt keinen expliziten Zustandsautomaten, sondern spiegelt den Zustand des internen `FB_CTUD` wider:
- **Zählerstand (INT):** Initial 0, verändert sich durch CU, CD, R oder LD.
- **Flags:** `QU` und `QD` werden basierend auf dem Vergleich von Zählerstand und Presetwert (bzw. 0) gesetzt.
- **Presetwert:** Wird über den `PV`-Adapter gespeichert und bei jedem `LD`-Ereignis geladen.

Eine detaillierte Zustandsmaschine des IEC‑61131‑3 Counters kann der entsprechenden Norm entnommen werden.

## Anwendungsszenarien
- **Ereigniszählung in beide Richtungen:** Z. B. Erfassung von Werkstücken auf einem Förderband, wobei Sensoren für Einlauf (CU) und Auslauf (CD) verwendet werden.
- **Lagerbestandsverwaltung:** Auf- und Abbuchung von Materialien in einem Puffer.
- **Positionierung mit Preset:** Ein System kann auf eine vorgegebene Position (PV) gesetzt und dann mittels CU/CD nachgeführt werden.
- **Resets nach Zyklusende:** Rücksetzen des Zählers nach Erreichen einer bestimmten Stückzahl.

## Vergleich mit ähnlichen Bausteinen
- **FB_CTUD (Standard IEC‑61131‑3):** Der `AI_FB_CTUD` ist eine **Adapter-Version** des gleichen Logikbausteins. Während der Standard-FB klassische Ein-/Ausgangspins verwendet, kommuniziert die Adapter-Version über Ereignis- und Daten-Adapter. Dies vereinfacht die Einbettung in 4diac‑Systeme mit adapterbasierter Kommunikation.
- **AI_FB_CTU / AI_FB_CTD:** Einfache Aufwärts- bzw. Abwärtszähler ohne Gegenrichtung. `AI_FB_CTUD` bietet beide Zählrichtungen in einem Baustein.
- **AX_D_FF:** Ein Differentiator/Filter, der nur bei Änderungen feuert. Kann als Vorschaltbaustein eingesetzt werden, um das Ausgabeverhalten von `AI_FB_CTUD` zu optimieren.

## Fazit
Der `AI_FB_CTUD` ist ein leistungsfähiger, adapterbasierter Aufwärts-/Abwärtszähler, der die etablierte IEC‑61131‑3 Funktionalität in die ereignisgesteuerte Welt von 4diac überführt. Durch die saubere Kapselung und die Verwendung unidirektionaler Adapter ist er flexibel einsetzbar und gut in modulare Automatisierungslösungen integrierbar. Die explizite Empfehlung zur Nutzung eines `AX_D_FF` für änderungsgesteuerte Ausgaben zeigt, dass der Baustein bewusst einfach gehalten wurde – eine Stärke für transparente und vorhersagbare Systeme.