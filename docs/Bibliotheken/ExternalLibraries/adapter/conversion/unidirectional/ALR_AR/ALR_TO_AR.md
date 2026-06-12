# ALR_TO_AR


![ALR_TO_AR](./ALR_TO_AR.svg)

*Kein Bild verfügbar*

* * * * * * * * * *

## Einleitung  
Der Funktionsblock **ALR_TO_AR** ist ein Composite-Baustein, der einen LREAL-Adapter (ALR) in einen REAL-Adapter (AR) umwandelt. Er dient als Bindeglied zwischen Steuerungskomponenten, die mit unterschiedlichen Gleitkomma-Genauigkeiten arbeiten, und ermöglicht eine saubere, ereignisgesteuerte Datenkonvertierung innerhalb eines IEC 61499-Netzwerks.

## Schnittstellenstruktur  
### **Ereignis-Eingänge**  
- **E1** (über Socket `ALR_IN`): Startet die Konvertierung des anliegenden LREAL-Wertes.  

### **Ereignis-Ausgänge**  
- **E1** (über Plug `AR_OUT`): Signalisiert, dass der konvertierte REAL-Wert am Ausgang gültig ist.  

### **Daten-Eingänge**  
- **D1** (über Socket `ALR_IN`): LREAL-Eingangswert (64‑Bit Gleitkomma).  

### **Daten-Ausgänge**  
- **D1** (über Plug `AR_OUT`): REAL-Ausgangswert (32‑Bit Gleitkomma).  

### **Adapter**  
- **ALR_IN** (Socket): Adapter vom Typ `adapter::types::unidirectional::ALR` – nimmt LREAL-Daten entgegen.  
- **AR_OUT** (Plug): Adapter vom Typ `adapter::types::unidirectional::AR` – stellt REAL-Daten bereit.  

## Funktionsweise  
1. Ein Ereignis am Eingang **E1** (des ALR_IN‑Sockets) triggert den internen Baustein `F_LREAL_TO_REAL`.  
2. Gleichzeitig wird der LREAL-Wert von **D1** (ALR_IN) direkt an den Konvertierungsbaustein übergeben.  
3. Der Konvertierungsbaustein wandelt den 64‑Bit‑Wert in einen 32‑Bit‑REAL‑Wert um.  
4. Nach Abschluss der Konvertierung wird ein Ereignis am Ausgang **E1** (AR_OUT) erzeugt und der REAL-Wert an **D1** (AR_OUT) weitergegeben.  

Die Übertragung erfolgt streng sequenziell: erst Ereignis, dann Datenfluss – die interne Verbindung gewährleistet eine zuverlässige Synchronisation.

## Technische Besonderheiten  
- **Composite-Baustein**: Der ALR_TO_AR kapselt die Konvertierungslogik und vereinfacht die Wiederverwendung in verschiedenen Projekten.  
- **IEC 61131‑Funktion**: Die eigentliche Typumwandlung basiert auf der standardisierten Bibliotheksfunktion `F_LREAL_TO_REAL`.  
- **Adapter‑Typen**: Beide Adapter sind unidirektional ausgelegt und erlauben eine klare Trennung von Ein‑ und Ausgabeseite.  
- **Keine Zustandsmaschine**: Der Baustein arbeitet rein ereignisgesteuert ohne internen Zustandsspeicher.  

## Zustandsübersicht  
Da es sich um einen Composite‑Baustein ohne eigene Zustandsautomaten handelt, gibt es keine expliziten Zustände. Der interne Ablauf ist deterministisch:  
- **Bereit / Idle** – wartet auf ein Eingangsereignis.  
- **Konvertierung aktiv** – nach Ereigniseingang bis zum Erzeugen des Ausgangsereignisses (dauert i. d. R. einen Zyklus).  

Die Latenz ist minimal und durch die Ausführungsreihenfolge des zugrunde liegenden IEC‑61499‑Laufzeitsystems bestimmt.

## Anwendungsszenarien  
- **Sensor‑Integration**: Ein Feldgerät liefert LREAL‑Messwerte, nachgeschaltete Logik erwartet jedoch REAL‑Werte (z. B. SPS‑Kommunikation).  
- **Adapter‑Kopplung**: Verbindung zweier Module, die unterschiedliche Adapter‑Schnittstellen verwenden, ohne dass der Entwickler die Konvertierung manuell programmieren muss.  
- **Datenkonsistenz**: Erzwingt eine saubere Trennung von 64‑Bit‑ und 32‑Bit‑Datenpfaden und vermeidet implizite Typumwandlungen.  

## Vergleich mit ähnlichen Bausteinen  
- **F_LREAL_TO_REAL** (direkt): Bietet die gleiche Konvertierung, erfordert jedoch separate Ereignis‑ und Datenverbindungen. ALR_TO_AR kapselt diese Verbindungen und stellt eine einheitliche Adapter‑Schnittstelle bereit.  
- **LINT_TO_INT** (Adapter‑Variante): Analoge Logik für ganzzahlige Typen mit unterschiedlichen Bitbreiten. Der prinzipielle Aufbau ist identisch, jedoch auf andere Datentypen zugeschnitten.  
- **Eigene Composite‑Konverter**: ALR_TO_AR reduziert den Aufwand für wiederkehrende Adapter‑Konvertierungen und erhöht die Lesbarkeit des Netzwerks.  

## Fazit  
Der **ALR_TO_AR** ist ein einfacher, aber effektiver Composite‑Baustein, der die Lücke zwischen LREAL‑ und REAL‑Adapter‑Schnittstellen schließt. Er bietet eine saubere, ereignisgesteuerte Konvertierung ohne zusätzlichen Ballast und lässt sich leicht in existierende 4diac‑Projekte einbinden. Dank der Verwendung von Standard‑Bibliotheksfunktionen bleibt die Umwandlung performant und zuverlässig.