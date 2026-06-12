# ALI_TO_AI


![ALI_TO_AI](./ALI_TO_AI.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **ALI_TO_AI** ist ein zusammengesetzter Baustein (Composite FB), der einen **ALI-Adapter** (Eingang einer LINT‑Wert‑Schnittstelle) in einen **AI-Adapter** (Ausgang einer INT‑Wert‑Schnittstelle) umwandelt. Er dient dazu, Daten eines LINT‑basierten Adapters in den INT‑basierten Adaptertyp zu überführen, ohne dass der Anwender die Konvertierung selbst implementieren muss.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Name     | Datentyp | Beschreibung                                        |
|----------|----------|-----------------------------------------------------|
| ALI_IN   | Ereignis | Steuersignal des ALI‑Adapters, löst die Konvertierung aus |

### **Ereignis-Ausgänge**
| Name     | Datentyp | Beschreibung                                          |
|----------|----------|-------------------------------------------------------|
| AI_OUT   | Ereignis | Bestätigungssignal des AI‑Adapters nach erfolgreicher Konvertierung |

### **Daten-Eingänge**
| Name     | Datentyp | Beschreibung                       |
|----------|----------|------------------------------------|
| ALI_IN.D1| LINT     | Der umzuwandelnde LINT‑Wert        |

### **Daten-Ausgänge**
| Name     | Datentyp | Beschreibung                       |
|----------|----------|------------------------------------|
| AI_OUT.D1| INT      | Der konvertierte INT‑Wert          |

### **Adapter**
| Richtung | Name    | Typ          | Beschreibung                              |
|----------|---------|--------------|-------------------------------------------|
| Socket   | ALI_IN  | ALI (unidirectional) | Liefert LINT‑Werte und Steuereignisse   |
| Plug     | AI_OUT  | AI (unidirectional) | Gibt konvertierte INT‑Werte und Ereignisse aus |

## Funktionsweise
Der Baustein arbeitet als reine Kopplung eines ALI‑Sockets mit einem AI‑Plug. Im Inneren wird der intern verfügbare Konvertierungsbaustein **F_LINT_TO_INT** verwendet.  
1. Ein eingehendes Ereignis am **ALI_IN.E1** triggert den Konvertierungsbaustein.  
2. Gleichzeitig wird der aktuelle Wert von **ALI_IN.D1** an den Eingang des Konverters übergeben.  
3. Nach Abschluss der Konvertierung wird das Ergebnis an **AI_OUT.D1** weitergeleitet.  
4. Ein Bestätigungsereignis wird über **AI_OUT.E1** ausgegeben.  

Der gesamte Ablauf erfolgt atomar innerhalb eines Zyklus – Verzögerungen entstehen nur durch die Laufzeit des Konvertierungsbausteins.

## Technische Besonderheiten
- **Reine Adapterkopplung**: Der Baustein enthält keine eigene Zustandslogik oder Zeitsteuerung.  
- **Verwendung von IEC‑61131‑Konvertierung**: Die eigentliche Typumwandlung erfolgt durch den standardisierten Baustein `F_LINT_TO_INT`.  
- **Einfache Zusammensetzung**: Alle Verbindungen sind direkt und ohne zwischengeschaltete Logik.  
- **Typ‑ und ereignisgetrieben**: Die Konvertierung wird nur bei einem Ereignis am ALI‑Eingang ausgeführt.

## Zustandsübersicht
Als zusammengesetzter Baustein ohne eigenes Zustandsdiagramm hat **ALI_TO_AI** keinen eigenen Zustandsautomaten. Der interne Konvertierungsbaustein `F_LINT_TO_INT` arbeitet nach dem einfachen Muster:  
- **IDLE**: Warten auf ein Ereignis.  
- **CONVERT**: Ausführen der Konvertierung und Ausgabe des Ergebnisses.  

## Anwendungsszenarien
- **Systemkopplung**: Wenn ein Sensormodul LINT‑Werte über einen ALI‑Adapter liefert, das Steuerungssystem jedoch INT‑Werte über einen AI‑Adapter erwartet.  
- **Protokoll‑ oder Schnittstellenanpassung**: Integration von Komponenten unterschiedlicher Hersteller, die verschiedene Adaptertypen verwenden.  
- **Bereinigung von Datenpfaden**: Vereinfachung des Signalflusses durch definierte Konvertierung an einer zentralen Stelle.

## Vergleich mit ähnlichen Bausteinen
| Baustein        | Funktion                                  | Unterschied                                                      |
|-----------------|-------------------------------------------|------------------------------------------------------------------|
| ALI_TO_AI       | LINT → INT über Adapter                   | Speziell für unidirektionale ALI‑/AI‑Schnittstellen              |
| LINT_TO_INT     | Direkte Konvertierung LINT → INT          | Keine Adapterintegration – reine Datenkonvertierung               |
| AI_TO_ALI       | INT → LINT (umgekehrte Richtung)          | Gleiche Struktur, aber entgegengesetzte Datenrichtung             |

## Fazit
**ALI_TO_AI** ist ein kleiner, aber nützlicher zusammengesetzter Baustein, der die Lücke zwischen zwei gebräuchlichen IEC‑61499‑Adaptertypen schließt. Durch die Kapselung der Konvertierungslogik wird die Wiederverwendung vereinfacht und die Systemintegration beschleunigt. Der Baustein ist robust, da er auf einen standardisierten IEC‑61131‑Konverter zurückgreift, und benötigt keinerlei Konfiguration.