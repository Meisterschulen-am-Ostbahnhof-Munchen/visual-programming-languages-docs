# AB_DEMUX_2


![AB_DEMUX_2](./AB_DEMUX_2.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AB_DEMUX_2** ist ein generischer Demultiplexer (Abzweiger) für einen unidirektionalen AB-Adapter. Er ermöglicht es, einen ankommenden Datenstrom (über den Socket **IN**) wahlweise auf einen von zwei Ausgangsadaptern (**OUT1** oder **OUT2**) weiterzuleiten. Die Auswahl des Zielausgangs erfolgt über den Parameter **K** bei jedem REQ-Ereignis. Der Baustein ist speziell für Steuerungsanwendungen konzipiert, in denen eine Signalverteilung auf verschiedene Pfade erforderlich ist.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name  | Typ    | Kommentar                |
|-------|--------|--------------------------|
| REQ   | Event  | Anforderung einer Umschaltung; benötigt den Parameter K. |

### **Ereignis-Ausgänge**

| Name  | Typ    | Kommentar                          |
|-------|--------|------------------------------------|
| CNF   | Event  | Bestätigung der erfolgten Umschaltung. |

### **Daten-Eingänge**

| Name | Typ   | Kommentar               |
|------|-------|-------------------------|
| K    | UINT  | Index (0 oder 1), der bestimmt, welcher Ausgang aktiviert wird. |

### **Daten-Ausgänge**

Keine direkten Datenausgänge – die Ausgabe erfolgt ausschließlich über die Adapter-Schnittstellen.

### **Adapter**

| Bezeichnung | Typ                                  | Richtung | Kommentar                                |
|-------------|--------------------------------------|----------|------------------------------------------|
| IN          | adapter::types::unidirectional::AB   | Socket   | Empfängt die zu verteilenden Daten.      |
| OUT1        | adapter::types::unidirectional::AB   | Plug     | Erster Ausgang für den demultiplexten Datenstrom. |
| OUT2        | adapter::types::unidirectional::AB   | Plug     | Zweiter Ausgang für den demultiplexten Datenstrom. |

## Funktionsweise

Der Baustein arbeitet nach dem Prinzip eines 1‑zu‑2‑Demultiplexers:

1. Ein ankommendes **REQ**-Ereignis triggert die Verarbeitung.
2. Der Wert des Daten-Eingangs **K** wird ausgelesen. Er muss den Wert **0** oder **1** annehmen.
3. Bei **K = 0** wird der Datenstrom vom **IN**-Adapter auf den Adapter **OUT1** umgeleitet.  
   Bei **K = 1** erfolgt die Weiterleitung auf **OUT2**.
4. Nach erfolgreicher Umschaltung wird das **CNF**-Ereignis gesendet.

Während der Verarbeitung werden die Daten des **IN**-Adapters vollständig auf den ausgewählten Ausgangsadapter übertragen. Die nicht ausgewählte Ausgangsschnittstelle bleibt inaktiv (keine Datenweitergabe).

## Technische Besonderheiten

- **Generischer Charakter**: Der FB ist als generischer Funktionsblock (`GEN_AB_DEMUX`) deklariert, d.h. er kann prinzipiell mit verschiedenen Adaptertypen instantiiert werden. In dieser Ausprägung wird der Adapter `adapter::types::unidirectional::AB` verwendet.
- **Keine Pufferung**: Der Demultiplexer arbeitet strikt ereignisgesteuert und puffert keine Daten. Eine erneute Anforderung überschreibt vorherige Umschaltungen sofort.
- **Einfache Erweiterbarkeit**: Die Architektur erlaubt eine einfache Anpassung auf mehrere Ausgänge, wenngleich die vorliegende Version genau zwei Ausgänge besitzt.

## Zustandsübersicht

Der Funktionsblock besitzt keine expliziten Zustände im Sinne eines Zustandsautomaten – er reagiert unmittelbar auf jedes **REQ**-Ereignis. Das Verhalten lässt sich wie folgt beschreiben:

- **Ruhezustand**: Kein REQ aktiv. Ausgänge sind inaktiv (keine Daten auf **OUT1** oder **OUT2**).
- **Umschaltvorgang**: Bei Eintreffen von **REQ** wird **K** ausgewertet, die Datenverbindung auf den entsprechenden Ausgang gelegt und unverzüglich **CNF** zurückgegeben. Danach kehrt der Baustein in den Ruhezustand zurück.

## Anwendungsszenarien

- **Routing von Sensorwerten**: Ein Sensor liefert kontinuierlich Daten (z.B. über einen AB-Adapter). Je nach Betriebsmodus (K = 0 oder K = 1) werden die Daten an verschiedene Steuereinheiten weitergeleitet.
- **Umschaltung zwischen zwei Aktor-Pfaden**: In einer redundanten Ansteuerung kann der Datenstrom wahlweise auf einen primären oder einen sekundären Aktor geschaltet werden.
- **Test-/Normalbetrieb**: Im Testmodus (K=1) werden die Daten auf ein Analysegerät umgeleitet, während im Normalbetrieb (K=0) die Produktionssteuerung versorgt wird.

## Vergleich mit ähnlichen Bausteinen

| Baustein                | Eigenschaften                                                                 |
|-------------------------|-------------------------------------------------------------------------------|
| **AB_DEMUX_2**          | Speziell für unidirektionale AB-Adapter; zwei Ausgänge; indexgesteuert.      |
| **AB_DEMUX_4**          | Analoger Demultiplexer mit vier Ausgängen, erwartet einen größeren Indexbereich. |
| **AB_SWITCH**           | Bidirektionale Umschaltung (Weiche) zwischen zwei Pfaden, meist für Datenadapter. |
| **E_DEMUX** (Ereignis)  | Demultiplext Ereignisse, keine Datenadapter – reine Ereignissteuerung.       |

Der **AB_DEMUX_2** zeichnet sich durch seine einfache Handhabung mit nur zwei Ausgängen und die direkte Adapterkopplung aus. Im Vergleich zu einem Ereignis-Demultiplexer werden hier vollständige Adaptersignale (inkl. aller enthaltenen Daten) weitergeleitet.

## Fazit

Der **AB_DEMUX_2** ist ein kompakter, ereignisgesteuerter Demultiplexer für unidirektionale AB-Adapter. Durch die klare Trennung von Ereignissteuerung und Datenweiterleitung eignet er sich ideal für modulare Automatisierungslösungen, bei denen ein Datenstrom zwischen zwei Zielen umgeschaltet werden muss. Seine generische Auslegung ermöglicht den Einsatz in verschiedenen Kontexten, während die einfache Schnittstelle eine zuverlässige Integration in bestehende 4diac-Projekte gewährleistet.