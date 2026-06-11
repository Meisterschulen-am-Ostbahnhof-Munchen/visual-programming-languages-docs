# ADI_TO_ALI


![ADI_TO_ALI](./ADI_TO_ALI.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **ADI_TO_ALI** ist ein Composite-Baustein, der einen unidirektionalen ADI-Adapter (Datentyp DINT) in einen unidirektionalen ALI-Adapter (Datentyp LINT) umwandelt. Er dient der Anpassung der Datenbreite von 32‑Bit auf 64‑Bit und ermöglicht so die nahtlose Integration von Komponenten unterschiedlicher Integer-Typen in Automatisierungssystemen nach IEC 61499‑2. Der Baustein ist unter der Eclipse Public License 2.0 verfügbar.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine

### **Ereignis-Ausgänge**
Keine

### **Daten-Eingänge**
Keine

### **Daten-Ausgänge**
Keine

### **Adapter**
- **ADI_IN** (Socket) – Typ: `adapter::types::unidirectional::ADI`  
  Nimmt einen DINT-Wert (32‑Bit) sowie ein zugehöriges Ereignis entgegen.
- **ALI_OUT** (Plug) – Typ: `adapter::types::unidirectional::ALI`  
  Gibt den konvertierten LINT-Wert (64‑Bit) sowie das weitergeleitete Ereignis aus.

## Funktionsweise
Der Baustein realisiert eine direkte Durchschleifung:  
- Das Ereignis `E1` vom ADI_IN-Socket wird ohne Verzögerung an den ALI_OUT-Plug weitergegeben.  
- Gleichzeitig wird der Datenwert `D1` (DINT) übertragen; dabei erfolgt eine implizite Typumwandlung von 32‑Bit Integer (DINT) auf 64‑Bit Integer (LINT).  
- Es findet keine Zwischenspeicherung oder Verarbeitungslogik statt – jede ankommende Ereignis‑Daten‑Kombination wird sofort an die Ausgabeseite weitergeleitet.

## Technische Besonderheiten
- **Kein interner Zustand** – Der Baustein ist vollständig kombinatorisch und besitzt kein Gedächtnis.  
- **Automatische Typkonvertierung** durch die Datenverbindung; der Wertebereich von DINT wird von LINT vollständig abgedeckt, sodass keine Informationsverluste auftreten.  
- **Adapterbasierte Kommunikation** gemäß IEC 61499‑2 ermöglicht lose Kopplung und Wiederverwendbarkeit.  
- Der Baustein ist als Composite ausgeführt, d. h. sein Verhalten wird allein durch das interne FBNetzwerk (eine Ereignis‑ und eine Datenverbindung) definiert.

## Zustandsübersicht
Der Baustein besitzt keinen Zustandsautomaten. Die Funktionalität beschränkt sich auf die direkte Weiterleitung der Adapter‑Signale.

## Anwendungsszenarien
- **Systemmigration** von 32‑Bit auf 64‑Bit Datenverarbeitung, z. B. bei der Modernisierung von Steuerungen.  
- **Integration älterer Komponenten**, die DINT‑Werte liefern, in neue Module, die LINT‑Schnittstellen voraussetzen.  
- **Adapter‑Brücke** in heterogenen Netzwerken, um unterschiedliche Integer‑Typen zwischen Funktionsblöcken anzupassen.

## Vergleich mit ähnlichen Bausteinen
Einfache Typkonverter (z. B. `DINT_TO_LINT`) arbeiten meist auf Datenebene ohne Ereignisweitergabe. Der `ADI_TO_ALI`‑Baustein hingegen kapselt Ereignis und Daten in einer Adapter‑Schnittstelle und eignet sich daher besonders für modulare, ereignisgesteuerte Architekturen. Gegenüber einer manuellen Konvertierung im Netzwerk reduziert er die Komplexität und erhöht die Lesbarkeit des Systems.

## Fazit
`ADI_TO_ALI` ist ein minimaler, aber effektiver Baustein zur Anpassung der Datenbreite zwischen DINT‑ und LINT‑Adaptern. Seine einfache Durchschleifungslogik und die automatische Typumwandlung machen ihn zu einem nützlichen Werkzeug für die Überbrückung von Integer‑Typen in IEC‑61499‑Systemen. Die Einhaltung des Standards und die Lizenz unter EPL 2.0 gewährleisten offene Verwendbarkeit und Interoperabilität.