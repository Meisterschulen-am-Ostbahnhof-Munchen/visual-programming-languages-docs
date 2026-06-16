# ADI_TO_ALR


![ADI_TO_ALR](./ADI_TO_ALR.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **ADI_TO_ALR** ist ein zusammengesetzter Baustein (Composite FB), der einen ADI‑Adapter (Datentyp DINT) in einen ALR‑Adapter (Datentyp LREAL) umwandelt. Er dient als unidirektionaler Konverter zwischen zwei standardisierten Adapter‑Schnittstellen und ermöglicht die nahtlose Integration von ganzzahligen Werten in Systeme, die Gleitkommazahlen benötigen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- Keine dedizierten Ereignis-Eingänge vorhanden.  
  Die Ereignisweiterleitung erfolgt über den Adapter **ADI_IN** (siehe Adapter‑Abschnitt).

### **Ereignis-Ausgänge**
- Keine dedizierten Ereignis-Ausgänge vorhanden.  
  Das Ereignis wird über den Adapter **ALR_OUT** ausgegeben (siehe Adapter‑Abschnitt).

### **Daten-Eingänge**
- Keine dedizierten Daten-Eingänge vorhanden.  
  Der zu konvertierende Wert wird über den Adapter **ADI_IN** bereitgestellt (siehe Adapter‑Abschnitt).

### **Daten-Ausgänge**
- Keine dedizierten Daten-Ausgänge vorhanden.  
  Der konvertierte Wert wird über den Adapter **ALR_OUT** ausgegeben (siehe Adapter‑Abschnitt).

### **Adapter**

| Name        | Typ                                        | Richtung | Beschreibung                       |
|-------------|--------------------------------------------|----------|------------------------------------|
| **ADI_IN**  | `adapter::types::unidirectional::ADI`      | Socket   | Eingang: DINT‑Wert und Ereignis    |
| **ALR_OUT** | `adapter::types::unidirectional::ALR`      | Plug     | Ausgang: LREAL‑Wert und Ereignis   |

*Hinweis:* Die Adapter implizieren jeweils ein Ereignis‑ und ein Datensignal (`E1` und `D1`).

## Funktionsweise
Der Baustein führt intern eine direkte Durchleitung durch:
- **Ereignis:** Das eingehende Ereignis `ADI_IN.E1` wird unverzögert auf den Ausgang `ALR_OUT.E1` übertragen.
- **Daten:** Der ganzzahlige Wert `ADI_IN.D1` (Datentyp DINT) wird ohne Skalierung oder Umrechnung in den Datentyp LREAL konvertiert und als `ALR_OUT.D1` ausgegeben. Die Typumwandlung erfolgt implizit durch die Laufzeitumgebung des IEC 61499‑Systems.

Es findet keine weitere Verarbeitung (Filterung, Begrenzung, Verzögerung) statt.

## Technische Besonderheiten
- **Composite‑Baustein:** Die Konvertierung wird durch einen einfachen „Wire‑Through“ im FBNetzwerk realisiert – keine Zustandsmaschine, keine eigenen Algorithmen.
- **Implizite Typumwandlung:** DINT → LREAL ist eine verlustfreie Umwandlung (LREAL bietet 64‑Bit Genauigkeit).
- **Unidirektional:** Der Datenfluss erfolgt ausschließlich vom Socket zum Plug.
- **Wiederverwendbarkeit:** Durch die Kapselung als Adapter‑Konverter kann der Baustein in beliebigen Systemen eingesetzt werden, die auf die entsprechenden Adapter‑Schnittstellen angewiesen sind.

## Zustandsübersicht
Der Baustein besitzt **keine Zustandsmaschine**. Er ist rein kombinatorisch (ereignisgesteuert) und führt bei jedem eingehenden Ereignis sofort die Durchleitung aus.

## Anwendungsszenarien
- **Zählerwerte als Gleitkommazahlen:** Ein ganzzahliger Zähler (z.B. Stückzahlen, Impulse) soll in einer Steuerung als LREAL‑Wert weiterverarbeitet werden.
- **Schnittstellenanpassung:** Systemkomponenten, die bereits mit ADI‑Adaptern arbeiten, können nahtlos an Komponenten angebunden werden, die ALR‑Adapter erwarten.
- **Prototypische Entwicklung:** Einfache Umwandlung ohne zusätzliche Logik, um schnell verschiedene Adapterprotokolle zu verknüpfen.

## Vergleich mit ähnlichen Bausteinen

| Baustein               | Typumwandlung        | Ereignisverhalten                                   |
|------------------------|----------------------|-----------------------------------------------------|
| **ADI_TO_ALR**         | DINT → LREAL         | Direkte Durchleitung ohne Verzögerung               |
| `INT_TO_REAL` (4diac)  | INT → REAL           | Eigenständiger FB mit eigenem Ereignis‑Interface    |
| individuelle Konverter | beliebig             | oft mit Zustandsmaschinen oder Parametrierung       |

Der vorliegende Baustein zeichnet sich durch seine **einfache Adapter‑orientierte Struktur** aus, die eine direkte Kopplung in Adapter‑Netzwerken ermöglicht, ohne separate Daten‑ und Ereignis‑Kanäle definieren zu müssen.

## Fazit
**ADI_TO_ALR** ist ein minimaler, aber nützlicher Konverter für die unidirektionale Übertragung von DINT‑Werten in das LREAL‑Format. Er ist robust, schnell und erfordert keinerlei Konfiguration. Dank seiner Composite‑Struktur lässt er sich leicht in bestehende Applikationen integrieren, die auf Adapter‑Schnittstellen basieren.