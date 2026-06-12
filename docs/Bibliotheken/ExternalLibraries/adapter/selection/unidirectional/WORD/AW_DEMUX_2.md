# AW_DEMUX_2


![AW_DEMUX_2](./AW_DEMUX_2.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsblock AW_DEMUX_2 realisiert einen generischen AW-Demultiplexer. Er leitet einen eingehenden AW-Wert (über den Socket `IN`) wahlweise an einen der beiden Ausgangsadapter (`OUT1` oder `OUT2`) weiter. Die Auswahl des Zielausgangs erfolgt ereignisgesteuert über den Daten-Eingang `K`.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Kommentar | Mit |
|----------|-----------|-----|
| `REQ`    | Set Index K | `K` |

### **Ereignis-Ausgänge**

| Ereignis | Kommentar |
|----------|-----------|
| `CNF`    | Bestätigung der Indexsetzung |

### **Daten-Eingänge**

| Name | Typ   | Kommentar |
|------|-------|-----------|
| `K`  | UINT  | index     |

### **Daten-Ausgänge**

*Keine*

### **Adapter**

**Eingangsadapter (Socket)**

| Adapter | Typ                               | Kommentar                          |
|---------|-----------------------------------|------------------------------------|
| `IN`    | `adapter::types::unidirectional::AW` | Input Value to demultiplex          |

**Ausgangsadapter (Plugs)**

| Adapter | Typ                               | Kommentar |
|---------|-----------------------------------|-----------|
| `OUT1`  | `adapter::types::unidirectional::AW` |           |
| `OUT2`  | `adapter::types::unidirectional::AW` |           |

## Funktionsweise
Der Funktionsblock wartet auf ein Ereignis an `REQ`. Bei dessen Eintreten wird der aktuell am Daten-Eingang `K` anliegende Index ausgewertet.  
- Ist `K = 0`, wird der über `IN` eingehende AW-Wert an den Adapter `OUT1` weitergeleitet.  
- Ist `K = 1`, erfolgt die Weiterleitung an `OUT2`.  
- Für Werte von `K` größer als 1 ist das Verhalten nicht definiert (implemenationsabhängig).  
Nach erfolgreicher Umschaltung wird das Bestätigungsereignis `CNF` ausgegeben.

## Technische Besonderheiten
- **Generischer Baustein:** Der FB ist durch das Attribut `GenericClassName` als generisch gekennzeichnet (`'GEN_AW_DEMUX'`). Er kann je nach Anpassung des Adapter-Typs für verschiedene uni-direktionale AW-Schnittstellen eingesetzt werden.  
- **Adapterbasierte Kommunikation:** Die Datenweitergabe erfolgt über Adapterverbindungen, die eine lose Kopplung der Komponenten ermöglichen und typsicher sind.  
- **Ereignisgesteuerte Auswahl:** Die Demultiplex-Funktion wird ausschließlich durch das Ereignis `REQ` angestoßen. Ohne ein Ereignis bleibt die aktuelle Verbindung bestehen.

## Zustandsübersicht
Der FB besitzt keine explizite Zustandsmaschine (ECC). Sein Verhalten lässt sich wie folgt beschreiben:

| Zustand (implizit) | Beschreibung |
|--------------------|--------------|
| **Idle**           | Warten auf ein `REQ`-Ereignis. Der zuletzt gesetzte Index bleibt aktiv. |
| **Processing**     | Nach Empfang von `REQ` wird der Index `K` ausgewertet und der Eingangswert auf den entsprechenden Ausgang umgeleitet. |
| **Confirm**        | Nach Abschluss der Umschaltung wird `CNF` gesendet und der FB kehrt in den Idle-Zustand zurück. |

## Anwendungsszenarien
- **Steuerung paralleler Prozesse:** Ein eingehender Datenstrom (z. B. Messwerte oder Steuerbefehle) soll wahlweise auf zwei verschiedene Verarbeitungseinheiten verteilt werden.  
- **Umschaltung von Signalquellen:** In einer Maschinensteuerung wird ein Sensorwert abwechselnd an zwei unterschiedliche Auswertealgorithmen gesendet.  
- **Test und Simulation:** In Testumgebungen kann derselbe Datenwert gezielt an verschiedene Simulationspfade geleitet werden.

## Vergleich mit ähnlichen Bausteinen
- **Standard DEMUX:** Ein klassischer Demultiplexer für elementare Datentypen (z. B. INT, BOOL) arbeitet ohne Adapter und benötigt mehrere Datenausgänge. Der AW_DEMUX_2 hingegen verwendet Adapter, was eine höhere Abstraktion und Wiederverwendbarkeit ermöglicht.  
- **AW_SWITCH:** Ein FB mit ähnlicher Funktion, der jedoch den Eingangswert nicht dupliziert, sondern zwischen verschiedenen Quellen umschaltet (Multiplexer).  
- **Vorteile des AW_DEMUX_2:** Klare Trennung von Steuerlogik und Datenübergabe, einfache Erweiterbarkeit auf weitere Ausgänge (z. B. AW_DEMUX_4).

## Fazit
Der AW_DEMUX_2 ist ein kompakter, generischer Funktionsblock zur Adapter-basierten Demultiplexierung von AW-Werten. Seine ereignisgesteuerte Auswahl und die klare Schnittstellenstruktur machen ihn zu einem flexiblen Baustein für modulare Automatisierungslösungen. Dank der generischen Auslegung kann er leicht an unterschiedliche AW-Typen angepasst werden, ohne die grundlegende Funktionalität zu verändern.