# AB_TO_AUDI


![AB_TO_AUDI](./AB_TO_AUDI.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsblock **AB_TO_AUDI** ist ein zusammengesetzter Baustein (Composite FB), der die Konvertierung eines AB-Adapters (Datentyp BYTE) in einen AUDI-Adapter (Datentyp UDINT) durchführt. Er dient als Schnittstelle zwischen unterschiedlichen Datenformaten in einer IEC 61499-basierten Automatisierungsumgebung.

## Schnittstellenstruktur
Der Baustein besitzt keine direkten Ereignis- oder Datenein-/ausgänge auf der obersten Ebene. Die Kommunikation erfolgt ausschließlich über zwei Adapter:

### **Ereignis-Eingänge**
- Keine (die Ereignisse werden über den Socket-Adapter `AB_IN` bereitgestellt)

### **Ereignis-Ausgänge**
- Keine (die Ereignisse werden über den Plug-Adapter `AUDI_OUT` ausgegeben)

### **Daten-Eingänge**
- Keine (die Daten werden über den Socket-Adapter `AB_IN` bereitgestellt)

### **Daten-Ausgänge**
- Keine (die Daten werden über den Plug-Adapter `AUDI_OUT` ausgegeben)

### **Adapter**
- **`AB_IN`** (Socket) – Typ: `adapter::types::unidirectional::AB`  
  Nimmt ein BYTE-Signal entgegen. Der Adapter stellt ein Ereignis `E1` und einen Datenwert `D1` (BYTE) bereit.
- **`AUDI_OUT`** (Plug) – Typ: `adapter::types::unidirectional::AUDI`  
  Gibt das konvertierte UDINT-Signal aus. Der Adapter erwartet ein Ereignis `E1` und einen Datenwert `D1` (UDINT).

## Funktionsweise
Der Baustein nutzt intern einen vordefinierten Konvertierungsbaustein `F_BYTE_TO_UDINT` aus der IEC 61131-Bibliothek. Der Ablauf:

1. Über den Socket `AB_IN` wird ein Ereignis `E1` empfangen, das den Start der Konvertierung auslöst.
2. Gleichzeitig wird der zugehörige BYTE-Datenwert aus `AB_IN.D1` an den Konverter `F_BYTE_TO_UDINT.IN` weitergeleitet.
3. Der Konverter berechnet den UDINT-Wert und gibt ihn an seinem Ausgang `OUT` aus.
4. Das Bestätigungsereignis `CNF` des Konverters wird an den Plug `AUDI_OUT.E1` gesendet.
5. Der konvertierte UDINT-Wert wird über `AUDI_OUT.D1` an den angeschlossenen Baustein weitergegeben.

Somit wird eine unidirektionale BYTE-zu-UDINT-Wandlung mit Ereignissteuerung realisiert.

## Technische Besonderheiten
- **Unidirektionale Adapter**: Sowohl der Eingangs- als auch der Ausgangsadapter sind unidirektional ausgelegt – Daten fließen nur in eine Richtung (BYTE → UDINT).
- **Synchroner Betrieb**: Die Konvertierung erfolgt streng ereignisgesteuert: Jedes eingehende Ereignis `E1` löst genau eine Umwandlung und ein ausgehendes Ereignis aus.
- **Standardkonvertierung**: Der interne Baustein `F_BYTE_TO_UDINT` ist ein etablierter IEC 61131-Baustein, sodass die Konvertierung normkonform und portabel ist.

## Zustandsübersicht
Da es sich um einen rein zusammengesetzten Baustein ohne eigenen Zustandsautomaten handelt, ergibt sich die Zustandslogik aus dem Zusammenspiel der internen Verbindungen:
- **Bereit**: nach Initialisierung, warten auf Ereignis `AB_IN.E1`.
- **Konvertierung aktiv**: nach Empfang von `AB_IN.E1`, während der interne Konverter arbeitet.
- **Ausgabe bereit**: nach Bestätigung durch `Convert.CNF`, bis das Ereignis `AUDI_OUT.E1` und der zugehörige Datenwert übergeben werden.

## Anwendungsszenarien
- **Protokollanpassung**: Wenn ein Sensor oder Aktor mit BYTE-Schnittstelle an einen Steuerungsteil angeschlossen werden soll, der UDINT erwartet (z.B. für Zählwerte, Frequenzen oder Zeitwerte).
- **Datenaufbereitung in Automatisierungsnetzwerken**: Einsatz in SPS- oder verteilten Systemen, um unterschiedliche Datenbreiten zu harmonisieren.
- **Adapterbrücke**: Als Zwischenglied zwischen vordefinierten Adaptertypen in einer IEC 61499-Applikation.

## Vergleich mit ähnlichen Bausteinen
- **AB_TO_DINT**: Konvertiert BYTE nach DINT (vorzeichenbehaftet) – hier wird nach UDINT (vorzeichenlos) umgewandelt.
- **Direkte Konverter** wie `F_BYTE_TO_UDINT`: Diese sind einfache Funktionsbausteine ohne Adapter-Schnittstelle. `AB_TO_AUDI` kapselt diesen Baustein in eine Adapterstruktur und integriert die Ereignissteuerung.

## Fazit
Der Funktionsblock `AB_TO_AUDI` stellt eine kompakte und wiederverwendbare Lösung zur Umwandlung von BYTE-Daten über einen AB-Adapter in UDINT-Daten über einen AUDI-Adapter dar. Durch die Verwendung standardisierter Konvertierung und Adapter wird eine hohe Kompatibilität und klare Schnittstellen in IEC 61499-Systemen erreicht.