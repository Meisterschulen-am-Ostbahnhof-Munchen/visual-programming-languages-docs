# AS_TO_AI


![AS_TO_AI](./AS_TO_AI.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsblock `AS_TO_AI` ist ein Composite-Funktionsblock, der einen AS-Adapter (Datentyp SINT) in einen AI-Adapter (Datentyp INT) umwandelt. Er dient als einfacher Konverter, um Komponenten mit unterschiedlichen Adapter-Typen innerhalb der 4diac-IDE zu verbinden.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- Keine

### **Ereignis-Ausgänge**
- Keine

### **Daten-Eingänge**
- Keine

### **Daten-Ausgänge**
- Keine

### **Adapter**
- **AS_IN** (Socket, Typ: `adapter::types::unidirectional::AS`)  
  Erwartet einen SINT-Wert und ein zugehöriges Ereignis E1.
- **AI_OUT** (Plug, Typ: `adapter::types::unidirectional::AI`)  
  Stellt einen INT-Wert und ein Ereignis E1 bereit.

## Funktionsweise
Der FB leitet das Ereignis E1 vom AS_IN-Socket direkt zum AI_OUT-Plug weiter. Parallel dazu wird der Datenwert D1 vom AS_IN-Socket auf den AI_OUT-Plug übertragen. Dabei erfolgt eine implizite Typkonvertierung von SINT (8‑Bit vorzeichenbehaftet) nach INT (16‑Bit vorzeichenbehaftet). Es findet keine weitere Verarbeitung oder Zustandslogik statt.

## Technische Besonderheiten
- Die Typkonvertierung von SINT zu INT wird automatisch von der 4diac‑Laufzeitumgebung durchgeführt, ohne dass zusätzliche Code‑Blöcke erforderlich sind.
- Der Baustein ist als **Composite FB** realisiert und enthält kein eigenes ECC (Execution Control Chart).
- Er ist im Paket `adapter::conversion::unidirectional` abgelegt, was auf unidirektionale Adapter-Konvertierung hinweist.

## Zustandsübersicht
Da es sich um einen Composite-Funktionsblock handelt, besitzt `AS_TO_AI` keine eigenen Zustände. Das Verhalten ergibt sich ausschließlich aus der Verdrahtung der internen Verbindungen.

## Anwendungsszenarien
- Ein Sensor liefert Daten über einen AS-Adapter (SINT), aber die angeschlossene Verarbeitungskomponente erwartet einen AI-Adapter (INT).  
- Migration von 8‑Bit‑ zu 16‑Bit‑Datenpfaden, ohne die Quell‑ oder Zielkomponente zu ändern.  
- Prototyping und Systemintegration, wenn unterschiedliche Adapterversionen aufeinandertreffen.

## Vergleich mit ähnlichen Bausteinen
- **AI_TO_AS**: Führt die umgekehrte Konvertierung (INT → SINT) durch.  
- **AI_TO_AD** o. Ä.: Konvertiert zwischen anderen ganzzahligen Datentypen (z. B. INT nach DINT).  
- Im Gegensatz zu diesen Bausteinen arbeitet `AS_TO_AI` verlustfrei, da der Zieltyp (INT) den Quelltyp (SINT) vollständig abbilden kann.

## Fazit
Der `AS_TO_AI`-Funktionsblock ist ein einfaches, aber effektives Werkzeug zur Sicherstellung der Adapter-Kompatibilität in 4diac‑Anwendungen. Er übernimmt die automatische Typkonvertierung von SINT nach INT und erleichtert so die Integration heterogener Komponenten ohne manuelle Anpassung des Datenpfades.