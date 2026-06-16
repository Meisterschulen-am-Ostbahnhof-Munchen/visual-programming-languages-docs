# ALI_TO_AR


![ALI_TO_AR](./ALI_TO_AR.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **ALI_TO_AR** ist ein zusammengesetzter Baustein (Composite FB), der einen LINT‑Adapter (ALI) in einen REAL‑Adapter (AR) umwandelt. Er dient als universelle Konvertierungsschnittstelle, um ganzzahlige 64‑Bit‑Werte aus der IEC‑61131‑Welt in Gleitkommawerte für die weitere Verarbeitung in Steuerungsanwendungen bereitzustellen. Der Baustein ist unter der Eclipse Public License 2.0 lizenziert und wird von der HR Agrartechnik GmbH bereitgestellt.

## Schnittstellenstruktur
Der Baustein besitzt keine direkten Ereignis‑ oder Datenports. Die gesamte Kommunikation erfolgt über zwei vordefinierte unidirektionale Adapter:

### **Ereignis-Eingänge**
– Keine (die Ereignisschnittstelle wird über den Adapter **ALI_IN** bereitgestellt)

### **Ereignis-Ausgänge**
– Keine (die Ereignisschnittstelle wird über den Adapter **AR_OUT** bereitgestellt)

### **Daten-Eingänge**
– Keine (die Datenschnittstelle wird über den Adapter **ALI_IN** bereitgestellt)

### **Daten-Ausgänge**
– Keine (die Datenschnittstelle wird über den Adapter **AR_OUT** bereitgestellt)

### **Adapter**

| Richtung | Name   | Typ                                      | Beschreibung                     |
|----------|--------|------------------------------------------|----------------------------------|
| Socket   | ALI_IN | `adapter::types::unidirectional::ALI`    | LINT‑Eingabeadapter (64‑Bit Integer) |
| Plug     | AR_OUT | `adapter::types::unidirectional::AR`     | REAL‑Ausgabeadapter (Gleitkomma) |

Die Adapter enthalten jeweils einen Ereigniskanal (E1) und einen Datenkanal (D1), die über die interne Vernetzung des Bausteins verbunden sind.

## Funktionsweise
Der Baustein realisiert eine einfache datengetriebene Konvertierung:

1. Über den Socket **ALI_IN** trifft ein Ereignis am Ereignis‑Eingang **E1** ein – gleichzeitig wird der zugehörige LINT‑Wert am Daten‑Eingang **D1** bereitgestellt.
2. Dieses Ereignis wird an den internen Baustein `iec61131::conversion::F_LINT_TO_REAL` weitergeleitet (Ereignis **REQ**).
3. Der interne Baustein wandelt den LINT‑Wert in einen REAL‑Wert um und signalisiert die Fertigstellung über den Ereignis‑Ausgang **CNF**.
4. Der konvertierte REAL‑Wert wird über die Datenverbindung an den Daten‑Eingang des Plug‑Adapters **AR_OUT** (D1) übergeben.
5. Gleichzeitig wird das Ereignis **E1** des Adapters **AR_OUT** ausgelöst, sodass die angeschlossene Logik den neuen REAL‑Wert verarbeiten kann.

Die gesamte Umwandlung erfolgt ohne Zustandsspeicherung – jede Anforderung wird sofort bearbeitet.

## Technische Besonderheiten
- **Composite‑Baustein**: Der ALI_TO_AR ist ein zusammengesetzter Funktionsblock, der ausschließlich aus dem internen Standardbaustein `F_LINT_TO_REAL` besteht.
- **Bibliothekseinbindung**: Die Konvertierung nutzt die IEC‑61131‑Bibliothek `iec61131::conversion::F_LINT_TO_REAL`, die als Import deklariert ist.
- **Paketstruktur**: Der Baustein ist im Paket `adapter::conversion::unidirectional` organisiert.
- **Lizenz**: Der Quellcode steht unter der Eclipse Public License 2.0 (EPL‑2.0).

## Zustandsübersicht
Der Baustein besitzt keine eigenen Zustände. Er arbeitet rein ereignisgesteuert und datenflussorientiert. Es gibt keine initialisierungs‑ oder fehlerbezogenen Zustände – jede ankommende Anfrage wird direkt verarbeitet.

## Anwendungsszenarien
- **Zählerauswertung**: Ein LINT‑Zähler (z. B. Impulszähler) liefert eine große Ganzzahl, die für eine Regelung in einen REAL‑Wert umgerechnet werden muss.
- **Datenvorverarbeitung**: In einer SPS‑Applikation liegen Messwerte als LINT vor (z. B. aus einem Encoder), die für weitere Berechnungen oder Visualisierung in REAL konvertiert werden.
- **Adapter‑Brücke**: Der Baustein dient als standardisierter Konverter zwischen zwei unterschiedlichen Adaptertypen in einer geräteübergreifenden Kommunikationsinfrastruktur.

## Vergleich mit ähnlichen Bausteinen
- **ALI_TO_ARI**: Wandelt LINT in ein ARRAY‑von‑REAL um – für Mehrfachwerte oder Puffer.
- **LREAL_TO_AR**: Konvertiert LREAL (80‑Bit‑Gleitkomma) in REAL – für Verluste durch geringere Genauigkeit.
- **Direkte Typkonvertierung** in IEC‑61131‑Funktionen (z. B. `LINT_TO_REAL`) – ohne Adapter‑Kapselung, erfordert manuelle Verdrahtung von Ereignissen.

Der ALI_TO_AR bietet gegenüber reinen Funktionsaufrufen den Vorteil der standardisierten Adapter‑Schnittstelle, die in modularen Systemen mit plug‑&‑play‑Fähigkeit verwendet werden kann.

## Fazit
Der **ALI_TO_AR** ist ein kompakter, wiederverwendbarer Funktionsblock zur Konvertierung von LINT‑ in REAL‑Werte über eine Adapter‑Schnittstelle. Seine einfache interne Struktur und die klare Ereignis‑Daten‑Kopplung machen ihn zu einem unverzichtbaren Baustein für jede Applikation, die ganzzahlige Sensordaten in Gleitkommawerte für Regelungen oder Visualisierungen umsetzen muss. Die Lizenzierung unter EPL‑2.0 ermöglicht eine uneingeschränkte Nutzung in offenen und kommerziellen Projekten.