# AW_DEMUX_5


![AW_DEMUX_5](./AW_DEMUX_5.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein **AW_DEMUX_5** ist ein generischer Demultiplexer für unidirektionale AW-Adapter. Er verteilt das an einem Eingangsadapter anliegende Signal auf einen von fünf Ausgangsadaptern, abhängig von einem numerischen Index. Der Baustein wird verwendet, wenn Daten aus einer Quelle wahlweise an mehrere Senken weitergeleitet werden sollen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| REQ  | Event | Set Index K |

Der Ereigniseingang **REQ** triggert die Demultiplex-Operation und verwendet den aktuellen Wert des Daten-Eingangs `K`.

### **Ereignis-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| CNF  | Event | Confirmation of Set Index K |

Nach erfolgreicher Umschaltung wird das Ereignis **CNF** ausgegeben.

### **Daten-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| K    | UINT | Index (erwartet Werte 1..5) |

Der Eingang `K` legt fest, welcher der fünf Ausgangsadapter aktiviert wird.

### **Daten-Ausgänge**

Keine.

### **Adapter**

**Plugs (Ausgänge):**

| Name | Typ | Kommentar |
|------|-----|-----------|
| OUT1 | adapter::types::unidirectional::AW | Ausgang 1 |
| OUT2 | adapter::types::unidirectional::AW | Ausgang 2 |
| OUT3 | adapter::types::unidirectional::AW | Ausgang 3 |
| OUT4 | adapter::types::unidirectional::AW | Ausgang 4 |
| OUT5 | adapter::types::unidirectional::AW | Ausgang 5 |

**Sockets (Eingang):**

| Name | Typ | Kommentar |
|------|-----|-----------|
| IN   | adapter::types::unidirectional::AW | Eingangssignal zum Demultiplexen |

## Funktionsweise

Der Baustein arbeitet nach dem Demultiplex-Prinzip:
1. Der Socket **IN** empfängt kontinuierlich Daten eines unidirektionalen AW-Adapters.
2. Bei einem **REQ**-Ereignis wird der Wert von **K** ausgewertet.
3. Abhängig vom Index (1..5) wird die Verbindung vom **IN**-Socket auf den entsprechenden **OUT**_n_-Plug geschaltet.
4. Nach dem Schalten wird **CNF** ausgegeben.

Die Datenverbindung bleibt bestehen, bis ein neuer REQ mit einem anderen Index eintrifft. Für ungültige Indizes wird keine Aktion ausgeführt oder es erfolgt ein undefinierter Zustand (abhängig von der Implementierung).

## Technische Besonderheiten

- **Generischer Typ**: Der Baustein ist als generisches FB (`GEN_AW_DEMUX`) deklariert, sodass er für unterschiedliche AW-Adapterkonfigurationen wiederverwendet werden kann.
- **Unidirektionaler Adapter**: Die verwendeten Adapter (AW) sind unidirektional, d.h. die Daten fließen nur in eine Richtung (Socket → Plug).
- **Indexgrenzen**: Der Index `K` ist vom Typ `UINT`, sinnvoll sind Werte von 1 bis 5. Werte außerhalb dieses Bereichs führen zu keinem definierten Verhalten.
- **Keine Datenausgänge**: Der Baustein gibt keine eigenen Daten aus, sondern leitet lediglich die Adapterverbindungen weiter.

## Zustandsübersicht

Der FB besitzt keine explizit modellierte Zustandsmaschine. Sein internes Verhalten lässt sich durch folgenden impliziten Zustandsautomaten beschreiben:

- **IDLE**: Warten auf ein **REQ**-Ereignis.
- **SELECT**: Bei **REQ** wird der Index `K` ausgewertet und die entsprechende Verbindung hergestellt.
- **DONE**: Nach erfolgreichem Umschalten wird **CNF** gesendet, und der FB kehrt in den IDLE-Zustand zurück.

## Anwendungsszenarien

- **Signalverteilung**: Ein Sensorsignal (z.B. Adapter für einen analogen Wert) soll wahlweise an verschiedene Steuerungseinheiten gesendet werden.
- **Routing**: In einer vernetzten Automatisierungsumgebung kann ein Datenstrom gezielt an fünf verschiedene nachgelagerte Bausteine weitergeleitet werden.
- **Testumgebungen**: Umschaltung zwischen verschiedenen Testpfaden, ohne die Verdrahtung zu ändern.

## Vergleich mit ähnlichen Bausteinen

- **Standard-Demultiplexer**: Herkömmliche Demultiplexer arbeiten meist mit Datenleitungen und haben separate Ausgangsereignisse. Dieser FB nutzt Adapter, was die Kapselung komplexer Datenstrukturen ermöglicht.
- **AW_SELECT**: Ein analoger Multiplexer, der mehrere Eingänge auf einen Ausgang schaltet. AW_DEMUX_5 ist die Umkehrfunktion.
- **MUX/DEMUX mit Ereignissteuerung**: Viele Demultiplexer besitzen separate Enable-Eingänge; hier erfolgt die Aktivierung über das **REQ**-Ereignis, was eine synchrone Verarbeitung ermöglicht.

## Fazit

Der **AW_DEMUX_5** ist ein spezialisierter Demultiplexer für unidirektionale AW-Adapter in der 4diac-IDE. Durch die Verwendung von Adaptern eignet er sich besonders für modulare Automatisierungslösungen, bei denen Datenströme flexibel zwischen Komponenten umgeschaltet werden müssen. Seine einfache Schnittstelle (ein Ereignis, ein Index, fünf Ausgänge) macht ihn leicht einsetzbar, während die generische Natur eine breite Wiederverwendung erlaubt.