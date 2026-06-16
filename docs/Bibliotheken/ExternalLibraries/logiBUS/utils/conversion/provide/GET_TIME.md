# GET_TIME


![GET_TIME](./GET_TIME.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein **GET_TIME** ermöglicht das Auslesen eines TIME-Werts aus einer InOut-Variable und stellt diesen als gepufferten Ausgangswert zur Verfügung. Er dient als einfache Schnittstelle, um einen externen Zeitwert in die Bausteinstruktur zu übernehmen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Name | Typ | Kommentar | Mit Variablen |
|------|-----|-----------|---------------|
| REQ | Event | Normaler Ausführungsanforderung | IN |

### **Ereignis-Ausgänge**

| Name | Typ | Kommentar | Mit Variablen |
|------|-----|-----------|---------------|
| CNF | Event | Bestätigung der Ausführung | OUT, IN |

### **Daten-Eingänge**
Keine dedizierten Daten-Eingänge vorhanden.

### **Daten-Ausgänge**

| Name | Typ | Kommentar | Initialwert |
|------|-----|-----------|-------------|
| OUT | TIME | Gepufferter Ausgangswert | T#0s |

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
**GET_TIME** implementiert einen einfachen, ereignisgesteuerten Ablauf. Ein Ereignis am Eingang **REQ** löst die Ausführung des Algorithmus aus. Dabei wird der aktuelle Wert der InOut-Variable **IN** in den Datenausgang **OUT** kopiert und zwischengespeichert. Anschließend wird ein Ereignis am Ausgang **CNF** erzeugt, das die erfolgreiche Übernahme quittiert. Die InOut-Variable **IN** dient dabei ausschließlich als lesbare Quelle und behält ihren Wert bei.

## Technische Besonderheiten
- Die Variable **IN** ist als **InOut** deklariert. Sie kann von außen mit einer anderen Variablen oder einem anderen Ausgang verbunden werden, ohne dass der Baustein Schreibzugriff darauf nimmt. Dies erlaubt eine flexible Anbindung an externe Zeitgeber oder Signale.
- Der Ausgang **OUT** puffert den gelesenen Wert. Nach einem **REQ**-Ereignis steht der aktuelle **IN**-Wert bis zur nächsten Anforderung am Ausgang zur Verfügung.
- Der Baustein besitzt keinen eigenen Zeitgeber oder Puffer für Verzögerungen.

## Zustandsübersicht

| Zustand | Beschreibung | Ausgeführte Aktion |
|---------|--------------|-------------------|
| REQ | Wartet auf ein Ereignis am Eingang **REQ**. Nach Eintritt wird der Algorithmus ausgeführt und ein **CNF**-Ereignis gesendet. | `OUT := IN;` |

## Anwendungsszenarien
- **Zeitmessung**: Übernahme einer aktuellen Systemzeit (z. B. `TIME()` oder eines Taktgebers) in einen Ausgang für weitere Verarbeitung.
- **Signalweiterleitung**: Gepuffertes Weiterleiten eines externen TIME-Signals, um asynchrone Änderungen der Quelle vom restlichen Ablauf zu entkoppeln.
- **Initialisierung**: Setzen eines Startzeitwerts in einer Steuerungslogik.

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einem reinen **MOVE**-Baustein für TIME-Daten verwendet **GET_TIME** ein **InOut**-Interface, das eine direkte Verbindung zur Quelle auch ohne zusätzlichen Daten-Eingang ermöglicht. Es ist speziell auf TIME-Werte zugeschnitten und bietet keine allgemeine Datenkopierfunktion. Andere Zeitbausteine wie **E_TIME** oder **TIME_IN** arbeiten oft mit eigenem Zeitgeber oder Ereigniszählung, während **GET_TIME** passiv einen externen Wert abruft.

## Fazit
**GET_TIME** ist ein schlanker, übersichtlicher Funktionsbaustein zum Auslesen und Puffern eines TIME-Werts. Seine einfache Ereignissteuerung und die Verwendung einer InOut-Variable machen ihn besonders geeignet für Szenarien, in denen ein externer Zeitwert punktuell in eine Steuerungslogik übernommen werden soll.