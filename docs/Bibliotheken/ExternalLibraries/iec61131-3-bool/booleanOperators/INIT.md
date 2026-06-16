# INIT


![INIT](./INIT.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **INIT** dient als direkte Durchleitung von Ereignissen. Er ist als Gegenstück zu einem `E_TRIG`-Baustein konzipiert und wird typischerweise in der Initialisierungsphase eines Systems eingesetzt. Der FB verfügt über zwei Ereigniseingänge und zwei korrespondierende Ereignisausgänge; Daten werden nicht verarbeitet.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Name  | Typ    | Kommentar                     |
|-------|--------|-------------------------------|
| INIT  | EInit  | Initialisierungsanforderung   |
| REQ   | Event  | Dienstanforderung             |

### **Ereignis-Ausgänge**

| Name  | Typ    | Kommentar                     |
|-------|--------|-------------------------------|
| INITO | EInit  | Initialisierungsbestätigung   |
| CNF   | Event  | Bestätigung der Anforderung   |

### **Daten-Eingänge**
Keine.

### **Daten-Ausgänge**
Keine.

### **Adapter**
Keine.

## Funktionsweise
Der Baustein arbeitet ereignisgesteuert und führt keine eigene Logik oder Zustandsänderung durch. Jedes ankommende Ereignis wird unverzögert und ohne Verarbeitung an den entsprechenden Ausgang weitergeleitet:
- Ein Ereignis am Eingang `INIT` erzeugt sofort ein Ereignis am Ausgang `INITO`.
- Ein Ereignis am Eingang `REQ` erzeugt sofort ein Ereignis am Ausgang `CNF`.

Dieses Verhalten wird durch eine schlichte Verbindung der Ereignispfade im inneren FBNetzwerk realisiert. Es findet keine Wertänderung oder Zustandsspeicherung statt.

## Technische Besonderheiten
- **Direkte Durchleitung**: Der FB ist extrem schlank und benötigt keine internen Variablen oder zeitlichen Verzögerungen.
- **Ereignistypen**: Die Eingangs- und Ausgangsereignisse `INIT`/`INITO` sind als `EInit` typisiert, während `REQ`/`CNF` als Standard `Event` deklariert sind. Dies erlaubt eine klare semantische Trennung zwischen Initialisierungs- und Betriebsereignissen.
- **Lizenz**: Der Baustein steht unter der Eclipse Public License 2.0 (EPL-2.0).

## Zustandsübersicht
Der Funktionsblock besitzt **keine internen Zustände**. Er ist ein reiner Durchleitungsbaustein, der zu jedem Zeitpunkt auf eingehende Ereignisse reagiert, ohne einen Zustand zu wechseln. Daher ist eine Zustandsmaschine nicht erforderlich.

## Anwendungsszenarien
- **Platzhalter in Entwurfsphasen**: Wenn ein `E_TRIG`-Baustein später durch eine komplexere Logik ersetzt werden soll, kann `INIT` vorübergehend als einfache Durchleitung dienen.
- **Initialisierungskaskaden**: In Architekturen, die mehrere Initialisierungsschritte durchführen, können `INIT`-Bausteine verwendet werden, um Ereignisse ohne Verarbeitung an nachfolgende Blöcke weiterzugeben.
- **Prototyping und Tests**: Zum Überbrücken von nicht benötigten Initialisierungslogiken oder zum Debuggen von Ereignisflüssen.

## Vergleich mit ähnlichen Bausteinen
- **E_TRIG (Eingangstrigger)**: `E_TRIG` erzeugt ein Ausgangsereignis nur bei einer steigenden oder fallenden Flanke eines angeschlossenen booleschen Eingangs. `INIT` hingegen reagiert direkt auf ein Ereignis und benötigt keinen Datenwert.
- **E_PERMIT (Freigabe)**: `E_PERMIT` lässt Ereignisse nur passieren, wenn ein boolescher Freigabeeingang gesetzt ist. `INIT` besitzt keine solche Bedingung.
- **E_DELAY (Verzögerung)**: `E_DELAY` hält Ereignisse für eine bestimmte Zeit zurück. `INIT` arbeitet ohne Verzögerung.

## Fazit
Der `INIT`-Funktionsblock ist ein minimalistischer, aber nützlicher Baustein zur direkten Ereignisdurchleitung. Aufgrund seiner Einfachheit eignet er sich besonders für Entwurfsphasen, Initialisierungsabläufe und als temporärer Platzhalter. Er erfüllt die grundlegende Anforderung, Initialisierungs- und Serviceereignisse unverändert weiterzugeben, und kann bei Bedarf durch funktional reichere Bausteine ersetzt werden.