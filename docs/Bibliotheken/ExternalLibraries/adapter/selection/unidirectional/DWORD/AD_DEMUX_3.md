# AD_DEMUX_3


![AD_DEMUX_3](./AD_DEMUX_3.svg)

* * * * * * * * * *
## Einleitung
Der AD_DEMUX_3 ist ein generischer Demultiplexer-Funktionsblock, der einen über einen Adapter (Typ `unidirectional::AD`) bereitgestellten Eingangswert auf einen von drei Ausgangsadaptern umleitet. Die Auswahl des Zielausgangs erfolgt über einen numerischen Index. Der Baustein wird vor allem in der Steuerungs- und Automatisierungstechnik eingesetzt, um Signale gezielt an verschiedene Komponenten weiterzugeben.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| REQ  | Event | Set Index K (mit Datenausgang K) |

### **Ereignis-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| CNF  | Event | Confirmation of Set Index K |

### **Daten-Eingänge**

| Name | Typ  | Kommentar |
|------|------|-----------|
| K    | UINT | Index zur Auswahl des Ausgangs (gültige Werte 0, 1, 2) |

### **Daten-Ausgänge**
Keine Datenausgänge vorhanden.

### **Adapter**

| Rolle       | Name | Typ                                  | Kommentar |
|-------------|------|--------------------------------------|-----------|
| Socket (IN) | IN   | adapter::types::unidirectional::AD   | Eingangswert, der demultiplext wird |
| Plug (OUT1) | OUT1 | adapter::types::unidirectional::AD   | Erster Ausgang |
| Plug (OUT2) | OUT2 | adapter::types::unidirectional::AD   | Zweiter Ausgang |
| Plug (OUT3) | OUT3 | adapter::types::unidirectional::AD   | Dritter Ausgang |

## Funktionsweise
Sobald ein Ereignis am **REQ**-Eingang eintrifft, wird der aktuelle Wert des Index `K` gelesen. Anschließend wird der am **IN**-Socket anliegende Adapter (und damit die übergebene Information) auf den durch `K` bestimmten Ausgangsadapter (OUT1, OUT2 oder OUT3) weitergeleitet. Nach erfolgreichem Umschalten wird ein Ereignis am **CNF**-Ausgang gesendet, um die Durchführung zu bestätigen. Bei einem ungültigen Indexwert (z. B. größer als 2) bleibt der Baustein ohne Wirkung oder kann – je nach Implementierung – einen Fehler auslösen.

## Technische Besonderheiten
- **Generischer Typ:** Der FB ist als generischer Funktionsblock deklariert (`GenericClassName = 'GEN_AD_DEMUX'`) und kann für verschiedene Adaptertypen instantiiert werden, solange der grundlegende `unidirectional::AD`-Adapter verwendet wird.
- **Unidirektionale Kommunikation:** Die Adapter erlauben nur eine Datenflussrichtung vom Eingang zum Ausgang. Rückmeldungen sind nicht vorgesehen.
- **Einfache Ereignissteuerung:** Es gibt keine Zustandsmaschine – der FB arbeitet streng ereignisgesteuert und führt bei jedem REQ die Umschaltung sofort aus.

## Zustandsübersicht
Der FB besitzt keine explizite Zustandsmaschine im XML-Modell. Das Verhalten ist rein sequenziell:
1. Warten auf REQ-Ereignis.
2. Lesen von K und Weiterleiten des IN-Adapters an den ausgewählten OUT-Adapter.
3. Senden von CNF.
Danach ist der FB wieder bereit für das nächste REQ.

## Anwendungsszenarien
- **Signalverteilung:** Ein einzelnes Messsignal (z. B. Temperatur oder Druck) wird je nach Index an verschiedene Regler oder Anzeigen weitergeleitet.
- **Aktorumschaltung:** Ein Steuersignal wird wahlweise an einen von drei Aktoren (z. B. Ventile oder Motoren) gesendet.
- **Test- und Diagnoseaufgaben:** In der Inbetriebnahme kann ein Prüfsignal dynamisch auf verschiedene Pfade geschaltet werden, ohne die Verdrahtung zu ändern.

## Vergleich mit ähnlichen Bausteinen
- **AD_DEMUX_2 / AD_DEMUX_N:** Analoge Bausteine mit zwei oder einer flexiblen Anzahl von Ausgängen. AD_DEMUX_3 ist auf drei Ausgänge festgelegt.
- **Multiplexer (z. B. AD_MUX):** Ein Multiplexer schaltet mehrere Eingänge auf einen Ausgang – genau die umgekehrte Funktionalität.
- **Einfacher Schalter:** AD_DEMUX_3 arbeitet ohne Zwischenspeicherung und eignet sich daher besonders für zeitkritische Weiterleitungen im laufenden Betrieb.

## Fazit
Der AD_DEMUX_3 ist ein kompakter, generischer Demultiplexer für Adapter-basierte Schnittstellen. Durch die klare Ereignissteuerung und die einfache Indexauswahl eignet er sich ideal zur dynamischen Signalverteilung in verteilten Automatisierungssystemen. Die feste Anzahl von drei Ausgängen deckt viele typische Anwendungsfälle ab und ermöglicht eine schnelle Implementierung ohne überflüssige Konfiguration.