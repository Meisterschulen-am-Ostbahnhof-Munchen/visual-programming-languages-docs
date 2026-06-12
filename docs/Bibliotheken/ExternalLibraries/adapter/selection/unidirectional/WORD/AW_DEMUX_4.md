# AW_DEMUX_4


![AW_DEMUX_4](./AW_DEMUX_4.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AW_DEMUX_4** ist ein generischer Demultiplexer für Adapter des Typs `adapter::types::unidirectional::AW`. Er verteilt ein eingehendes Adapter-Signal (über den Socket `IN`) auf einen von vier Ausgangs-Adaptern (`OUT1` bis `OUT4`). Die Auswahl des Zielausgangs erfolgt über den ganzzahligen Index `K`, der über den Ereigniseingang `REQ` gesetzt wird. Der Baustein eignet sich für die dynamische Weiterleitung von Datenströmen in Automatisierungsanwendungen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Name | Typ   | Kommentar                    |
|------|-------|------------------------------|
| REQ  | Event | Setzt den Index `K`          |

Der Ereigniseingang `REQ` löst die Verarbeitung aus: Der aktuelle Wert von `K` wird übernommen und das Eingangssignal an den entsprechenden Ausgang weitergeleitet.

### **Ereignis-Ausgänge**
| Name | Typ   | Kommentar                               |
|------|-------|-----------------------------------------|
| CNF  | Event | Bestätigung der Übernahme von `K`       |

Nach erfolgreicher Umschaltung wird das Ereignis `CNF` gesendet.

### **Daten-Eingänge**
| Name | Typ   | Kommentar        |
|------|-------|------------------|
| K    | UINT  | Index (1‑basierend typischerweise) |

Der Wert von `K` bestimmt, welcher Ausgangsadapter aktiviert wird. Gültige Werte sind typischerweise 1 bis 4.

### **Daten-Ausgänge**
Keine.

### **Adapter**
| Richtung | Name  | Typ                                     | Kommentar                       |
|----------|-------|-----------------------------------------|---------------------------------|
| Socket   | IN    | `adapter::types::unidirectional::AW`   | Eingangssignal (Quelle)         |
| Plug     | OUT1  | `adapter::types::unidirectional::AW`   | Ausgang 1                       |
| Plug     | OUT2  | `adapter::types::unidirectional::AW`   | Ausgang 2                       |
| Plug     | OUT3  | `adapter::types::unidirectional::AW`   | Ausgang 3                       |
| Plug     | OUT4  | `adapter::types::unidirectional::AW`   | Ausgang 4                       |

Die Adapter sind unidirektional und vom Typ `AW` (z. B. für Analog‑ oder Werte‑Weiterleitung).

## Funktionsweise
1. Der Baustein wartet auf ein Ereignis am Eingang `REQ`.
2. Beim Eintreffen von `REQ` wird der aktuelle Wert des Daten‑Eingangs `K` erfasst.
3. Abhängig von `K` wird das an `IN` anliegende Adapter‑Signal auf den entsprechenden Ausgangsadapter (`OUT1` … `OUT4`) durchgeschaltet.
4. Nach erfolgter Umschaltung wird das Ereignis `CNF` ausgegeben.

Der Baustein arbeitet ereignisgesteuert und verändert die Signalweiterleitung nur bei einem neuen `REQ`.

## Technische Besonderheiten
- **Generischer Baustein:** Der Funktionsblock wird als generisches Template (`GEN_AW_DEMUX`) bereitgestellt und kann bei Bedarf für andere Adaptertypen spezialisiert werden.
- **Indexbereich:** Der Index `K` ist als `UINT` deklariert. Wird ein Wert außerhalb von 1…4 übergeben, bleibt die Umschaltung undefiniert oder der Baustein ignoriert den Wert (je nach Implementierung).
- **EPL 2.0 Lizenz:** Der Baustein steht unter der Eclipse Public License 2.0 und darf in eigenen Projekten genutzt und modifiziert werden.

## Zustandsübersicht
Da es sich um einen grundlegenden Demultiplexer handelt, besitzt der Baustein nur einen impliziten Zustand:

- **IDLE:** Warten auf `REQ`.
- **PROCESSING:** Bei `REQ` wird `K` ausgewertet und die Umschaltung ausgeführt. Anschließend wird `CNF` gesendet und der Baustein kehrt in den IDLE‑Zustand zurück.

Eine explizite Zustandsmaschine ist im XML nicht definiert, aber das beschriebene Verhalten ist üblich für solche Funktionsblöcke.

## Anwendungsszenarien
- **Signalverteilung:** In einer Steuerung soll ein analoger Messwert wahlweise an verschiedene Verbraucher gesendet werden (z. B. Anzeige, Protokollierung, Regelung).
- **Umschaltung von Kommunikationswegen:** Ein Datenstrom aus einer Quelle wird je nach Betriebsmodus an unterschiedliche nachgelagerte Bausteine weitergeleitet.
- **Test‑ und Simulationsumgebungen:** Ein Signalgenerator kann über den Index `K` flexibel an mehrere Testobjekte angeschlossen werden.

## Vergleich mit ähnlichen Bausteinen
| Baustein       | Funktion                                   | Ausgänge |
|----------------|--------------------------------------------|----------|
| **AW_DEMUX_4** | Demultiplexer für AW‑Adapter (1→4)         | 4        |
| AW_MUX_4       | Multiplexer für AW‑Adapter (4→1)           | 1        |
| AW_DEMUX_2     | Demultiplexer mit zwei Ausgängen           | 2        |

Der AW_DEMUX_4 ist die Erweiterung auf vier Ausgänge. Er bietet eine höhere Anzahl von Zielen, benötigt aber eine klare Festlegung des Index.

## Fazit
Der **AW_DEMUX_4** ist ein einfacher, aber nützlicher generischer Demultiplexer für unidirektionale Adapter. Er ermöglicht die flexible Weiterleitung eines Eingangssignals an einen von vier Ausgängen, gesteuert über einen Index. Dank seiner generischen Struktur und der Lizenz unter EPL 2.0 ist er gut in IEC 61499‑basierte Automatisierungssysteme integrierbar.