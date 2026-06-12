# AUI_CTD


![AUI_CTD](./AUI_CTD.svg)

* * * * * * * * * *

## Einleitung

Der **AUI_CTD** ist ein ereignisgesteuerter Abwärtszähler (Down Counter) mit Adapter-Schnittstellen. Er verfügt über eine **On-Change-Auslösung**: Das Ausgangssignal **Q** wird nur dann aktualisiert, wenn sich sein logischer Zustand tatsächlich ändert. Dadurch werden unnötige Ereignisse vermieden und die Effizienz in ereignisbasierten Systemen gesteigert.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Beschreibung                                  |
|----------|----------------------------------------------|
| **CD**   | Count Down – reduziert den Zählerwert um 1.  |
| **LD**   | Load – lädt den Zählerwert **CV** mit dem Preset-Wert **PV**. |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung                                              |
|----------|----------------------------------------------------------|
| **CDO**  | Count Down Output – wird nach jedem CD-Schritt ausgegeben. |
| **LDO**  | Load Output – wird nach einem erfolgreichen Laden ausgegeben. |

### **Daten-Eingänge**

Der FB besitzt keine direkten Daten-Eingänge. Stattdessen werden Werte über die Adapter-Schnittstelle **PV** bereitgestellt.

### **Daten-Ausgänge**

Der FB besitzt keine direkten Daten-Ausgänge. Die aktuellen Werte von **CV** und **Q** werden über die jeweiligen Adapter-Ports ausgegeben.

### **Adapter**

| Port  | Typ                                            | Richtung | Beschreibung                                         |
|-------|------------------------------------------------|----------|------------------------------------------------------|
| **Q** | `adapter::types::unidirectional::AX` (BOOL)   | Plug     | Statusausgang: `TRUE`, wenn **CV ≤ 0**.            |
| **CV**| `adapter::types::unidirectional::AUI` (INT)   | Plug     | Aktueller Zählerwert.                                |
| **PV**| `adapter::types::unidirectional::AUI` (INT)   | Socket   | Preset-Wert, der beim LD-Ereignis in **CV** geladen wird. |

## Funktionsweise

1. **Count Down (CD)**  
   Jedes **CD**-Ereignis dekrementiert **CV** um 1 und setzt **Q** auf `TRUE`, falls **CV ≤ 0** ist. Anschließend wird **CDO** ausgegeben.

2. **Load (LD)**  
   Ein **LD**-Ereignis kopiert den Wert von **PV** nach **CV**. **Q** wird entsprechend aktualisiert (TRUE bei **CV ≤ 0**). Danach wird **LDO** ausgegeben.

3. **On-Change-Triggering**  
   Der FB vergleicht den aktuellen **Q**-Wert mit dem gespeicherten Vorgängerwert **Q_OLD**. Nur wenn sich **Q** geändert hat, wird das Adapter-Ereignis **Q.E1** ausgelöst. Andernfalls kehrt der FB direkt zum Startzustand zurück. Dies verhindert wiederholte identische Meldungen.

4. **PV-Änderungen**  
   Wenn sich der **PV**-Adapter meldet (Ereignis **PV.E1**), wird **Q** neu berechnet (**UPDATE**-Algorithmus). Auch hier erfolgt die Ausgabe von **Q** nur bei einer Zustandsänderung.

## Technische Besonderheiten

- **On-Change-Triggering** – Reduziert Ereignislast, indem der **Q**-Ausgang nur bei tatsächlichen Änderungen aktiviert wird.  
- **Adapter-Schnittstelle** – Ermöglicht lose Kopplung und Wiederverwendung in komplexen Steuerungsstrukturen.  
- **Initialwert** – **Q_OLD** wird mit `FALSE` initialisiert, sodass beim ersten Durchlauf eine Änderung erkannt wird, falls **CV** bereits ≤ 0 ist.

## Zustandsübersicht

Der Ablauf wird durch folgende ECC-Zustände gesteuert:

| Zustand       | Beschreibung                                                  | Aktionen                         |
|---------------|--------------------------------------------------------------|----------------------------------|
| **START**     | Wartet auf eingehende Ereignisse (CD, LD, PV.E1).            | –                                |
| **CD**        | Führt den Count-Down-Algorithmus aus.                        | `CD (CV--, Q aktualisieren)`, `CV.E1`, `CDO` |
| **LD**        | Lädt **PV** in **CV**.                                       | `LOAD (CV:=PV; Q aktualisieren)`, `CV.E1`, `LDO` |
| **UPDATE_PV** | Neuberechnung von **Q** bei Änderung von **PV**.              | `UPDATE (Q aus CV berechnen)`    |
| **EMIT_Q**    | Speichert den aktuellen **Q**-Wert und löst **Q.E1** aus.    | `SAVE_Q (Q_OLD:=Q)`, `Q.E1`      |

**Transitionen**:  
- Nach **CD**, **LD** oder **UPDATE_PV** wird nur dann zu **EMIT_Q** gewechselt, wenn `Q.D1 ≠ Q_OLD`.  
- Bei Gleichheit (`Q.D1 = Q_OLD`) erfolgt sofort die Rückkehr zu **START**, ohne **Q.E1** auszulösen.  
- Von **EMIT_Q** wird stets zurück zu **START** gewechselt.

## Anwendungsszenarien

- **Materialzähler** in Förderanlagen: Bei jedem Teil, das die Station verlässt, wird **CD** getriggert. Sobald **CV ≤ 0**, wird eine Nachschub-Anforderung gesendet.  
- **Zyklussteuerung** für wiederholte Abläufe: Der Zähler läuft von einem Startwert (geladen über **LD**) bis Null und löst dann eine Aktion aus.  
- **Ereignisoptimierte Systeme** mit vielen parallelen Zählern: Dank On-Change-Triggering werden nur relevante Statusänderungen weitergemeldet.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Besonderheit                     | Unterschied zu AUI_CTD                             |
|----------|----------------------------------|-----------------------------------------------------|
| **E_CTD**| Standard-Abwärtszähler ohne Adapter | Verwendet direkte Daten-Ein-/Ausgänge und keine Adapter. Kein On-Change-Triggering. |
| **E_CTUD** | Aufwärts-/Abwärtszähler          | Bietet beide Zählrichtungen, jedoch ohne Adapter und ohne On-Change. |
| **AUI_CTU**| Aufwärtszähler mit Adapter       | Zählt aufwärts, analoge Adapter-Struktur, ebenfalls On-Change. |

Der **AUI_CTD** füllt die Lücke eines spezialisierten Abwärtszählers mit moderneren Adapter-Konzepten und reduziertem Ereignisaufkommen.

## Fazit

Der **AUI_CTD** ist ein leistungsfähiger Abwärtszähler für IEC 61499-konforme Steuerungen. Durch die Kombination von Adapter-Schnittstellen und On-Change-Triggerung eignet er sich besonders für modulare, ressourcenschonende Automatisierungslösungen. Sein Verhalten ist deterministisch und kann über die ECC einfach nachvollzogen werden. Damit ist er eine optimale Wahl für Applikationen, die eine zuverlässige und effiziente Zählerfunktion mit minimierter Ereigniskommunikation erfordern.