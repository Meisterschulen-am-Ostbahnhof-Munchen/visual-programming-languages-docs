# AIS


![AIS](./AIS.svg)

**Unidirektionaler Adapter für 1 Ereignis und 1 Zeichenkette**

* * * * * * * * * *
## Einleitung
Der Adapter **AIS** (Adapter Interface String) stellt eine unidirektionale Schnittstelle zur Verfügung, über die genau ein Ereignis (E1) zusammen mit einer zugehörigen Zeichenkette (D1) von einer Plug‑Instanz an eine Socket‑Instanz übertragen werden kann. Er wird verwendet, um einfache, gerichtete Datenflüsse zu realisieren, bei denen keinerlei Rückmeldung oder zusätzliche Steuerung erforderlich ist.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine.

### **Ereignis-Ausgänge**
| Name | Typ   | Kommentar |
|------|-------|-----------|
| E1   | Event | Indikation (oder Request) – das Ereignis wird beim Senden der Daten ausgelöst. |

### **Daten-Eingänge**
Keine.

### **Daten-Ausgänge**
| Name | Typ    | Kommentar |
|------|--------|-----------|
| D1   | STRING | Die zum Ereignis gehörenden Daten (Zeichenkette). |

### **Adapter**
Dieser Baustein ist selbst ein Adapter. Er besitzt keine weiteren internen Adapter.

## Funktionsweise
Der Adapter arbeitet nach dem Prinzip einer unidirektionalen „Plug‑&nbsp;Socket“‑Verbindung.  
- Die **Plug**-Instanz sendet ein Ereignis an E1 und legt gleichzeitig die Daten auf D1 ab.  
- Die **Socket**-Instanz empfängt dieses Ereignis und kann den Wert von D1 auslesen.  
Eine Kommunikation in die Gegenrichtung ist nicht vorgesehen.

## Technische Besonderheiten
- **Minimaler Ressourcenverbrauch**: Der Adapter benötigt nur ein Ereignis und eine Zeichenkette – ideal für ressourcenbeschränkte Steuerungen.  
- **Typsicherheit**: Der Datentyp ist auf STRING festgelegt; der Adapter kann direkt in Applikationen verwendet werden, die genau diese Signatur benötigen.  
- **Einfache Wiederverwendung**: Durch die strikte Trennung in Plug und Socket lassen sich Module leicht kapseln und austauschen.

## Zustandsübersicht
Der Adapter besitzt keinen internen Zustandsautomaten. Er verhält sich **zustandslos**: Jedes eingehende Ereignis an der Plug‑Seite wird unverzögert als Ausgangsereignis an der Socket‑Seite weitergeleitet. Der Datenwert D1 wird dabei zum Zeitpunkt des Ereignisses übernommen.

## Anwendungsszenarien
- **Sensor‑Anbindung**: Übergabe eines einzelnen Messwerts (z.&nbsp;B. Lauftext eines RFID‑Lesers) an eine Verarbeitungseinheit.  
- **Monitor‑Schnittstelle**: Ausgabe eines Status‑Strings aus einer Steuerung an ein Anzeigeelement.  
- **Debugging**: Einfaches Herausführen von Diagnoseinformationen aus einem Funktionsblock.

## Vergleich mit ähnlichen Bausteinen
- **Komplexere Adapter** wie z.&nbsp;B. Adapter mit mehreren Ereignissen und gemischten Datentypen bieten mehr Flexibilität, benötigen aber auch mehr Konfigurationsaufwand.  
- **Bidirektionale Adapter** (z.&nbsp;B. mit je einem Ereignis pro Richtung) erlauben eine Rückmeldung; der AIS‑Adapter verzichtet bewusst darauf, um die Schnittstelle so einfach wie möglich zu halten.  
- Der AIS ist speziell auf **genau ein Ereignis + eine Zeichenkette** optimiert – andere Adapter mit gleicher Signatur, aber anderem Namen, könnten funktional identisch sein.

## Fazit
Der Adapter **AIS** ist ein schlanker, zustandsloser Baustein für die unidirektionale Übertragung eines Ereignisses zusammen mit einem String. Er eignet sich hervorragend für alle Fälle, in denen eine einfache, klare Signalweiterleitung ohne zusätzliche Logik oder Rückkanal benötigt wird. Durch die minimale Schnittstelle bleibt die Applikation übersichtlich und leicht verständlich.