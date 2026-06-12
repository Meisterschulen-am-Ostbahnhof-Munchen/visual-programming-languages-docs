# AS_SPLIT_9


![AS_SPLIT_9](./AS_SPLIT_9.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AS_SPLIT_9** dient dazu, einen eingehenden **AS‑Adapter** (unidirektional) auf neun separate Ausgangsadapter aufzuteilen. Er wird als generischer Baustein ausgeführt und verteilt das am Socket `IN` anliegende AS‑Signal identisch an alle neun Plug‑Ausgänge (`OUT1` … `OUT9`). Damit eignet er sich ideal, um ein einziges AS‑Signal mehrfach an verschiedene nachgeschaltete Komponenten weiterzuleiten.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- Keine

### **Ereignis-Ausgänge**
- Keine

### **Daten-Eingänge**
- Keine

### **Daten-Ausgänge**
- Keine

### **Adapter**

| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| **Socket** | `IN` | `adapter::types::unidirectional::AS` | Eingangsadapter (AS‑Schnittstelle) |
| **Plug**  | `OUT1` | `adapter::types::unidirectional::AS` | Erster Ausgangsadapter |
| **Plug**  | `OUT2` | `adapter::types::unidirectional::AS` | Zweiter Ausgangsadapter |
| **Plug**  | `OUT3` | `adapter::types::unidirectional::AS` | Dritter Ausgangsadapter |
| **Plug**  | `OUT4` | `adapter::types::unidirectional::AS` | Vierter Ausgangsadapter |
| **Plug**  | `OUT5` | `adapter::types::unidirectional::AS` | Fünfter Ausgangsadapter |
| **Plug**  | `OUT6` | `adapter::types::unidirectional::AS` | Sechster Ausgangsadapter |
| **Plug**  | `OUT7` | `adapter::types::unidirectional::AS` | Siebter Ausgangsadapter |
| **Plug**  | `OUT8` | `adapter::types::unidirectional::AS` | Achter Ausgangsadapter |
| **Plug**  | `OUT9` | `adapter::types::unidirectional::AS` | Neunter Ausgangsadapter |

## Funktionsweise

Der Baustein empfängt über den Socket `IN` eine AS‑Verbindung. Interne Logik leitet dieses eingehende Signal ohne Veränderung an alle neun Plug‑Ausgänge (`OUT1` … `OUT9`) weiter. Dadurch stehen an allen Ausgängen stets die gleichen AS‑Daten und/oder Ereignisse zur Verfügung. Eine separate Zustandsmaschine oder interne Verarbeitung existiert nicht – die Verteilung erfolgt direkt und ohne zeitliche Verzögerung.

## Technische Besonderheiten

- **Generischer Baustein** – Der FB wird als **GEN_AS_SPLIT** klassifiziert und kann bei Bedarf parametrisiert werden (z. B. für eine variable Anzahl von Ausgängen).  
- **Unidirektionale Adapter** – Sowohl Ein‑ als auch Ausgänge nutzen den Typ `adapter::types::unidirectional::AS`. Dies stellt sicher, dass die Daten‑/Ereignisrichtung von IN zu OUT strikt eingehalten wird.  
- Keine eigenen Ereignis‑ oder Dateneingänge erforderlich – die gesamte Schnittstelle besteht ausschließlich aus Adaptern.

## Zustandsübersicht

Der FB besitzt keine explizite Zustandsmaschine (ECC). Die Verteilung erfolgt rein kombinatorisch, sobald der Eingangsadapter gültige Daten oder Ereignisse liefert.

## Anwendungsszenarien

- **Signalverteilung** – Ein AS‑Sensor oder eine Steuerung muss mehrere Aktoren oder überwachte Komponenten gleichzeitig versorgen.  
- **Parallelbetrieb** – An ein AS‑Netzwerk sollen mehrere Teilnehmer angeschlossen werden, ohne dass eine aktive Replikation erforderlich ist.  
- **Test- und Simulationsumgebungen** – Ein ausgehendes AS‑Signal wird auf mehrere Prüfmodule oder Analysewerkzeuge aufgeteilt.

## Vergleich mit ähnlichen Bausteinen

- **AS_SPLIT_2**, **AS_SPLIT_4** u. Ä. – Diese Bausteine bieten eine geringere Anzahl von Ausgängen (2, 4 usw.) und sind für kleinere Verteilungen optimiert.  
- **AS_MUX** – Ein Multiplexer, der mehrere Eingänge auf einen Ausgang legt; das Gegenteil des Splitters.  
- **AS_COPY** – Kopiert ein Signal auf einen zweiten Ausgang; entspricht einem 1:2‑Split.  
- **AS_SPLIT_9** stellt mit neun Ausgängen die größte Standardvariante dar und deckt umfangreiche Verteilungsanforderungen ab.

## Fazit

Der **AS_SPLIT_9** ist ein unkomplizierter, zuverlässiger Funktionsblock zur Vervielfältigung eines AS‑Signals. Durch die reine Adapter‑Schnittstelle und das Fehlen interner Logik eignet er sich besonders für Anwendungen, in denen ein Ausgangssignal auf viele Empfänger verteilt werden muss. Seine generische Natur erlaubt zudem eine einfache Anpassung an spezifische Projektanforderungen.