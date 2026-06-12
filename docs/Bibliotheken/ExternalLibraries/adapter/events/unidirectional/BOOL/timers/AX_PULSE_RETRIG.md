# AX_PULSE_RETRIG


![AX_PULSE_RETRIG](./AX_PULSE_RETRIG.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AX_PULSE_RETRIG** ist ein nachtriggerbarer (retriggerbarer) Impulsformer mit AX-Adapter-Schnittstelle. Er erzeugt an seinem Ausgang einen Impuls mit einer vorgegebenen Dauer PT. Ein erneuter Startbefehl innerhalb der Impulsdauer setzt die Timer-Zeit zurück und verlängert den Impuls. Der Block wird typischerweise eingesetzt, um zeitlich exakte, verlängerbare Ausgangssignale in Automatisierungssystemen zu generieren.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Beschreibung |
|------|-----|--------------|
| **REQ** | EVENT | Service-Anforderung zum Starten oder Neustarten des Timers (mit PT verbunden) |
| **R**   | EVENT | Zurücksetzen des Timers (Impuls sofort beenden) |

### **Ereignis-Ausgänge**

Der Baustein besitzt keine direkten Ereignis-Ausgänge. Ausgangssignale werden über den Adapter Q bereitgestellt.

### **Daten-Eingänge**

| Name | Typ | Beschreibung |
|------|-----|--------------|
| **PT** | TIME | Impulsdauer (Pulszeit) |

### **Daten-Ausgänge**

Der Baustein besitzt keine direkten Daten-Ausgänge. Ausgangsdaten werden über den Adapter Q bereitgestellt.

### **Adapter**

| Name | Typ | Beschreibung |
|------|-----|--------------|
| **Q** | `adapter::types::unidirectional::AX` | Adapter-Schnittstelle, die den Impulsstatus (Ereignis und Daten) nach außen führt |

## Funktionsweise

- Der Funktionsblock kapselt intern den Standardbaustein `E_PULSE_RETRIG` (gemäß IEC 61499).  
- Ein **REQ**-Ereignis startet den Timer: Der Ausgang Q (über Adapter) wird aktiv und der Impuls beginnt.  
- Falls während der Impulsdauer erneut **REQ** eintrifft, wird der Timer zurückgesetzt und die Impulsdauer beginnt von Neuem (Retrigger-Funktion).  
- Ein **R**-Ereignis unterbricht den Impuls sofort – der Ausgang Q wird inaktiv.  
- Der Adapter Q gibt den aktuellen Impulszustand als Ereignis (über `Q.E1`) und als Datenwert (über `Q.D1`) weiter.

## Technische Besonderheiten

- Nutzung des standardisierten `E_PULSE_RETRIG`-Bausteins als interne Implementierung.  
- Die Ausgabe erfolgt ausschließlich über einen AX-Adapter, der sowohl ein Ereignissignal (bei Zustandsänderung) als auch den binären Impulszustand (Typ BOOL) bereitstellt.  
- Ein erneuter Trigger führt zu einem Neustart der Zeitmessung – ideal für Taster mit Nachlauf oder pulsbreitenmodulierte Signale.  
- Die Impulsdauer PT kann während der Laufzeit geändert werden, wirkt sich aber erst beim nächsten REQ aus.

## Zustandsübersicht

Der Baustein bildet die Zustände des internen `E_PULSE_RETRIG` ab:

| Zustand | Beschreibung |
|---------|--------------|
| **IDLE** | Kein Impuls aktiv; Ausgang Q = FALSE |
| **PULSE** | Impuls läuft; Ausgang Q = TRUE; Timer läuft. Ein REQ-Ereignis führt zurück in PULSE mit neuem Timerstart. |

- Übergang IDLE → PULSE durch REQ.  
- Übergang PULSE → IDLE durch Ablauf der PT-Zeit oder durch Reset R.

## Anwendungsszenarien

- **Verlängerbare Einschaltimpulse**: Wenn ein Sensor mehrfach innerhalb der Impulsdauer auslöst, soll der Ausgang dauerhaft aktiv bleiben (z. B. bei Füllstandsüberwachung).  
- **Taktgeber mit nachtriggerbarer Pulsbreite**: Steuerung von Ventilen oder Lampen, die bei wiederholter Anforderung erneut für eine feste Zeit eingeschaltet werden.  
- **Sicherheitsfunktionen**: Überwachung von Maschinen, bei denen ein erneuter Startbefehl die Stillstandszeit zurücksetzt.  

## Vergleich mit ähnlichen Bausteinen

| Baustein | Eigenschaft |
|----------|-------------|
| **E_PULSE** | Einfacher Impuls ohne Retrigger – einmaliger Timerstart, kein Neustart bei erneutem REQ. |
| **AX_PULSE_RETRIG** | Retriggerbare Version mit AX-Adapter (Ereignis + Daten). |
| **TON / TOF** | Verzögerungsbausteine (Einschaltverzögerung / Ausschaltverzögerung) – kein Impulsformer. |

Der AX_PULSE_RETRIG bietet damit die Flexibilität eines nachtriggerbaren Impulses bei gleichzeitig standardisierter Adapter-Schnittstelle für die einfache Einbindung in größere Funktionsbaustein-Netzwerke.

## Fazit

Der **AX_PULSE_RETRIG** ist ein kompakter, leistungsfähiger Funktionsblock zur Erzeugung von nachtriggerbaren Impulsen. Dank der AX-Adapter-Schnittstelle lässt er sich nahtlos mit anderen Bausteinen verbinden und eignet sich besonders für Anwendungen, bei denen ein Ausgangssignal bei wiederholten Anforderungen verlängert werden muss. Die Verwendung des etablierten `E_PULSE_RETRIG`-Bausteins gewährleistet standardkonformes und zuverlässiges Zeitverhalten.