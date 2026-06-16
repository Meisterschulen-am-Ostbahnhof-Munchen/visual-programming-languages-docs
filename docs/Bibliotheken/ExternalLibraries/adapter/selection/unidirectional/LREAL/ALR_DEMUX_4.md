# ALR_DEMUX_4


![ALR_DEMUX_4](./ALR_DEMUX_4.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **ALR_DEMUX_4** fungiert als ein Demultiplexer für datenstromorientierte ALR-Signale (Agricultural Logic Router). Er verteilt einen eingehenden ALR-Datenstrom wahlweise auf einen von vier gleichartigen Ausgängen. Die Auswahl des Zielausgangs erfolgt dynamisch über den Index K, der bei einem Ereignis am Eingang REQ ausgewertet wird. Die Ausgabe wird über den Ereignisausgang CNF quittiert. Der Baustein ist generisch ausgelegt und kann für verschiedene ALR-Typen parametrisiert werden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Beschreibung |
|----------|--------------|
| **REQ** | Auslöser für die Umschaltung des Datenpfads. Der zugehörige Daten-Eingang K wird dabei ausgewertet. |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung |
|----------|--------------|
| **CNF** | Bestätigung, dass der Datenpfad entsprechend K gesetzt wurde. |

### **Daten-Eingänge**

| Name | Typ    | Beschreibung |
|------|--------|--------------|
| **K** | UINT   | Index des gewünschten Ausgangs (Wertebereich 1..4). |

### **Daten-Ausgänge**
Keine direkten Daten-Ausgänge vorhanden. Die Datenweitergabe erfolgt ausschließlich über die Adapter-Schnittstellen.

### **Adapter**

| Typ | Name | Richtung | Beschreibung |
|-----|------|----------|--------------|
| Socket (Input) | **IN** | unidirektional | ALR-Eingang, der verteilt werden soll. |
| Plug (Output) | **OUT1** | unidirektional | Erster Zielausgang (Adresse 1). |
| Plug (Output) | **OUT2** | unidirektional | Zweiter Zielausgang (Adresse 2). |
| Plug (Output) | **OUT3** | unidirektional | Dritter Zielausgang (Adresse 3). |
| Plug (Output) | **OUT4** | unidirektional | Vierter Zielausgang (Adresse 4). |

## Funktionsweise
1. Im Ruhezustand ist kein Datenpfad aktiv.
2. Wird ein **REQ**-Ereignis empfangen, liest der Baustein den aktuellen Wert von **K**.
3. Abhängig von **K** (1–4) wird der ALR-Datenstrom vom Socket **IN** an den entsprechenden Plug **OUTx** durchverbunden. Alle anderen Ausgänge bleiben inaktiv.
4. Nach erfolgreicher Umschaltung wird das Ereignis **CNF** gesendet.
5. Sollte **K** außerhalb des gültigen Bereichs liegen, wird keine Verbindung hergestellt; dennoch wird **CNF** gesendet (die Aktion bleibt wirkungslos).

## Technische Besonderheiten
- **Generischer Typ**: Der Baustein kann über das Attribut `GenericClassName` auf einen beliebigen ALR-Untertyp spezialisiert werden, z. B. für unterschiedliche Datenformate oder Protokolle.
- **Unidirektionale Adapter**: Die ALR-Schnittstellen sind unidirektional, d. h. der Datenfluss erfolgt nur vom Socket zu den Plugs.
- **Keine Zustandsmaschine**: Der FB arbeitet ereignisgesteuert ohne internen Zustand. Die Umschaltung erfolgt rein kombinatorisch bei REQ.
- **Lizenz**: Der Baustein ist unter der EPL 2.0 lizenziert (Eclipse Public License).

## Zustandsübersicht
Der Funktionsblock besitzt keine explizite Zustandsmaschine. Sein Verhalten kann als unmittelbare Reaktion auf das REQ-Ereignis beschrieben werden:
- **Vor REQ**: Kein Datenpfad aktiv.
- **Nach REQ mit gültigem K**: Der ausgewählte OUT-Pfad ist aktiv (solange, bis ein neuer REQ eintrifft).

## Anwendungsszenarien
- **Verteilung von Steuerbefehlen** in der Landtechnik: Ein zentraler ALR-Datenstrom wird je nach Maschinensituation auf verschiedene Aktoren (z. B. Ventile, Leisten) verteilt.
- **Routing von Messwerten** in Feldbussystemen: Ein Sensor liefert Daten, die über den Demultiplexer wechselweise an mehrere Auswertungseinheiten gesendet werden.
- **Test- und Simulationsumgebungen**: Gezielte Einschleusung von Testdaten in einen von mehreren nachgelagerten Blöcken.

## Vergleich mit ähnlichen Bausteinen
- **ALR_MUX_4**: Der Multiplexer sammelt Daten von vier Eingängen und gibt sie an einen Ausgang weiter – die Umkehrfunktion des Demultiplexers.
- **ALR_DEMUX_2**: Ein Demultiplexer mit nur zwei Ausgängen, geeignet für kleinere Konfigurationen.
- **Generische DEMUX-Bausteine**: Andere Implementierungen verwenden oft direkte Daten-Ein-/Ausgänge, während ALR_DEMUX_4 auf Adaptern basiert, was eine flexiblere Typanpassung ermöglicht.

## Fazit
**ALR_DEMUX_4** ist ein kompakter, ereignisgesteuerter Demultiplexer für ALR-Datenströme. Die Adapter-basierte Schnittstelle und der generische Aufbau machen ihn vielseitig einsetzbar in automatisierten landwirtschaftlichen Systemen. Er erlaubt eine einfache, indexgesteuerte Verteilung von Signalen ohne zusätzliche Logik und ist besonders in Szenarien mit mehreren gleichartigen Aktoren oder Sensoren nützlich.