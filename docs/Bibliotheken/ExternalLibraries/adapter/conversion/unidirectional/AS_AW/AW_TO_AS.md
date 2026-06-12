# AW_TO_AS


![AW_TO_AS](./AW_TO_AS.svg)

* * * * * * * * * *
## Einleitung  
Der Funktionsblock `AW_TO_AS` ist ein Composite-Baustein, der einen WORD-basierten Adapter (AW) in einen SINT-basierten Adapter (AS) umwandelt. Er kapselt die notwendige Typkonvertierung und ermöglicht so die einfache Integration unterschiedlicher Adapter-Schnittstellen in der Automatisierungstechnik.

## Schnittstellenstruktur  

### **Ereignis-Eingänge**  
- `AW_IN.E1` – Startet die Konvertierung des anliegenden Datenwerts.

### **Ereignis-Ausgänge**  
- `AS_OUT.E1` – Signalisiert, dass der konvertierte Wert am Datenausgang bereitsteht.

### **Daten-Eingänge**  
- `AW_IN.D1` (WORD) – Der 16-Bit-Wert, der in einen SINT-Wert umgewandelt werden soll.

### **Daten-Ausgänge**  
- `AS_OUT.D1` (SINT) – Der konvertierte 8-Bit-Wert (vorzeichenbehaftet, Wertebereich -128 … 127).

### **Adapter**  
- **Socket (Eingang)**: `AW_IN` vom Typ `adapter::types::unidirectional::AW`  
- **Plug (Ausgang)**: `AS_OUT` vom Typ `adapter::types::unidirectional::AS`

## Funktionsweise  
Der Baustein ist als Composite realisiert und verwendet intern den IEC‑61131‑Funktionsbaustein `F_WORD_TO_SINT`. Ein eingehendes Ereignis an `AW_IN.E1` triggert die Wandlung: Der Datenwert von `AW_IN.D1` wird an den Eingang `IN` des internen Konverters übergeben. Nach erfolgreicher Umwandlung erzeugt dieser ein Bestätigungsereignis an `CNF`, das an den Ausgangsadapter `AS_OUT.E1` weitergeleitet wird. Gleichzeitig wird der konvertierte SINT‑Wert an `AS_OUT.D1` ausgegeben.

## Technische Besonderheiten  
- Die Konvertierung folgt der IEC‑61131‑Funktion `WORD_TO_SINT`. Ein Überlauf tritt auf, wenn der eingehende WORD-Wert außerhalb des gültigen SINT-Bereichs (-128 … 127) liegt – dies muss in der Anwendung berücksichtigt werden.  
- Der Baustein arbeitet rein ereignisgesteuert: Eine Wandlung erfolgt nur bei einem Ereignis am Eingang.  
- Die Adapter sind unidirektional ausgelegt; eine Rückwandlung von SINT nach WORD ist nicht vorgesehen.

## Zustandsübersicht  
Da es sich um einen einfachen Composite‑FB ohne eigenen Zustandsautomaten handelt, existiert keine explizite Zustandsmaschine. Der FB wartet auf ein Ereignis, führt die Konvertierung aus und gibt das Ergebnis synchron aus. Eine Zustandstabelle ist nicht erforderlich.

## Anwendungsszenarien  
- Anpassung von Sensordaten, die als WORD (z. B. über einen analogen Eingang) geliefert werden, an ein System, das SINT‑Werte verarbeitet.  
- Umwandlung von Feldbus‑Datenformaten bei der Kopplung unterschiedlicher Automatisierungskomponenten.  
- Einsatz in heterogenen Steuerungsumgebungen, in denen Adapter unterschiedliche Datentypen verwenden.

## Vergleich mit ähnlichen Bausteinen  
Analog aufgebaute Konverter wie `AW_TO_BY` (WORD → BYTE) oder `AINT_TO_AUDINT` (INT → UDINT) folgen demselben Prinzip. Der `AW_TO_AS`-Baustein hebt sich durch die spezifische Adapter‑Kombination hervor, die eine direkte Einbindung in Adapter-basierte Architekturen ermöglicht. Im Gegensatz zu einfachen Typkonvertierungen auf Datenebene wird hier die ereignisgesteuerte Adapter‑Schnittstelle genutzt, was die Wiederverwendbarkeit und Austauschbarkeit erhöht.

## Fazit  
Der Composite FB `AW_TO_AS` bietet eine kompakte und klare Lösung zur Konvertierung eines WORD-Adapters in einen SINT-Adapter. Die Kapselung der Konvertierung in einem eigenen Baustein verbessert die Lesbarkeit und Wartbarkeit der Applikation. Der FB eignet sich besonders für Umgebungen, in denen mit unterschiedlichen Datentypen auf Adapterebene gearbeitet wird.