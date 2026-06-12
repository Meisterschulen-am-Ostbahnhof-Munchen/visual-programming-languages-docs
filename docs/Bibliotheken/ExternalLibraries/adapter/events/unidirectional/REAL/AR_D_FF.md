# AR_D_FF


![AR_D_FF](./AR_D_FF.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsbaustein **AR_D_FF** realisiert ein daten-gesteuertes Flipflop (D-Latch) gemäß der Spezifikation IEC 61499-1 Annex A. Er dient als Kapselung des Standardbausteins `iec61499::events::E_D_FF_ANY` und stellt dessen Funktionalität über zwei unidirektionale Adapter zur Verfügung. Der Baustein übernimmt bei einer positiven Flanke des Taktsignals einen Datenwert und hält diesen bis zur nächsten Flanke.

## Schnittstellenstruktur
Der AR_D_FF besitzt keine direkten Ereignis- oder Datenein-/ausgänge; die gesamte Kommunikation erfolgt über seine zwei Adapter.

### **Ereignis-Eingänge**
- **Keine direkten.**  
  Das Taktereignis wird über den Eingangsadapter **I** bereitgestellt (siehe Adapter‑Abschnitt).

### **Ereignis-Ausgänge**
- **Keine direkten.**  
  Das Bestätigungsereignis wird über den Ausgangsadapter **Q** bereitgestellt (siehe Adapter‑Abschnitt).

### **Daten-Eingänge**
- **Keine direkten.**  
  Der zu latchnde Datenwert wird über den Eingangsadapter **I** bereitgestellt (siehe Adapter‑Abschnitt).

### **Daten-Ausgänge**
- **Keine direkten.**  
  Der gelatchte Datenwert wird über den Ausgangsadapter **Q** bereitgestellt (siehe Adapter‑Abschnitt).

### **Adapter**
| Adapter | Richtung / Typ | Beschreibung | Enthaltene Elemente |
|---------|----------------|--------------|---------------------|
| **I**   | Socket (`adapter::types::unidirectional::AR`) | Wert, der gelatcht werden soll. | **E1** (Ereigniseingang) – Taktsignal (CLK)<br>**D1** (Dateneingang) – Datenwert |
| **Q**  | Plug (`adapter::types::unidirectional::AR`) | Gelatchter Wert. | **E1** (Ereignisausgang) – Bestätigung nach erfolgreichem Latch<br>**D1** (Datenausgang) – gelatchter Datenwert |

## Funktionsweise
Der Baustein arbeitet nach dem Prinzip eines flankengesteuerten D‑Flipflops:
1. Ein Ereignis am Takteingang **I.E1** aktiviert die Übernahme.
2. Zum Zeitpunkt der positiven Flanke wird der aktuelle Datenwert **I.D1** intern gespeichert.
3. Der gespeicherte Wert wird sofort an **Q.D1** ausgegeben.
4. Gleichzeitig wird ein Ereignis auf **Q.E1** ausgelöst, um die Verarbeitung zu bestätigen.

Der interne Zustand bleibt zwischen zwei Taktflanken unverändert (Speicherverhalten).

## Technische Besonderheiten
- **Adapter‑basierte Kapselung:** Der AR_D_FF nutzt ausschließlich unidirektionale Adapter (Typ `AR`) für Ein‑ und Ausgabe. Dies ermöglicht eine modulare, standardisierte Einbindung in größere Adapter‑Netzwerke.
- **Verwendung des Standardbausteins `E_D_FF_ANY`:** Die eigentliche Flipflop‑Logik wird durch den IEC‑61499‑Standardbaustein realisiert. Änderungen an der internen Implementierung wirken sich nicht auf die nach außen sichtbare Schnittstelle aus.
- **Kein Reset‑Eingang:** Im Gegensatz zu anderen Flipflop‑Varianten verfügt dieser Baustein über keine Rücksetzfunktion. Der Zustand kann nur durch einen neuen Datenwert und einen Taktimpuls geändert werden.

## Zustandsübersicht
Der Baustein besitzt einen einzigen internen Speicher (den gelatchten Datenwert). Zustandsübergänge erfolgen ausschließlich bei einer positiven Flanke am Takteingang **I.E1**:

| Alter Zustand | Eingang D1 (aktuell) | Neuer Zustand | Ausgang D1 | Ereignis Q.E1 |
|---------------|----------------------|---------------|------------|---------------|
| *beliebig*    | *beliebig*           | Wert von D1   | Wert von D1 | wird ausgelöst |

Es gibt keine weiteren internen Zustände oder Verzweigungen.

## Anwendungsszenarien
- **Datensynchronisation:** Übernahme eines Datenwortes zu einem definierten Zeitpunkt, z. B. in einem zyklischen Steuerungssystem.
- **Pufferung:** Zwischenspeicherung eines Wertes zwischen zwei Berechnungsschritten.
- **Ereignisgesteuerte Signalweitergabe:** Anwendungen, in denen ein Wert nur dann aktualisiert werden darf, wenn ein bestimmtes Ereignis eintritt.

## Vergleich mit ähnlichen Bausteinen
| Baustein | Eigenschaft | Unterschied zu AR_D_FF |
|----------|-------------|------------------------|
| **AR_SR_FF** | Set‑Reset‑Flipflop | Latcht keinen Datenwert, sondern wird über Set/Reset gesetzt/rückgesetzt. Besitzt zwei Ereigniseingänge. |
| **E_D_FF_ANY** | Standard‑D‑Flipflop ohne Adapter | Gleiche Kernlogik, aber direkte Ereignis‑/Datenanschlüsse; keine Adapter‑Kapselung. |
| **AR_T_FF** | Toggle‑Flipflop | Schaltet bei jedem Taktimpuls den Ausgang um; kein Dateneingang. |

## Fazit
Der **AR_D_FF** ist ein einfaches, zuverlässiges D‑Flipflop, das durch die Adapter‑Schnittstelle besonders für modulare und wiederverwendbare IEC‑61499‑Anwendungen geeignet ist. Die Kapselung des Standardbausteins erhöht die Robustheit und erleichtert die Integration in größere Systeme. Für Anwendungen, die einen Reset oder eine andere Logik erfordern, stehen spezialisierte Flipflop‑Varianten zur Verfügung.