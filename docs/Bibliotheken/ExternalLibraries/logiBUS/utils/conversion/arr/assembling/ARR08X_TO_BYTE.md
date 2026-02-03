# ARR08X_TO_BYTE

```{index} single: ARR08X_TO_BYTE
```

<img width="1176" height="217" alt="image" src="https://github.com/user-attachments/assets/7e2d9580-9a80-4dea-ad4f-4100a7186544" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `ARR08X_TO_BYTE` dient der Konvertierung eines Arrays von acht booleschen Werten (`BOOL`) in einen einzigen Byte-Wert (`BYTE`). Jedes Bit im resultierenden Byte entspricht dabei einem Element des Eingabe-Arrays. Diese Operation ist nützlich, um mehrere binäre Signale (z. B. Schalterzustände oder Fehlerflags) platzsparend zu bündeln und für die weitere Verarbeitung oder Kommunikation vorzubereiten.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
*   `REQ` (Request): Löst die Konvertierungsoperation aus. Bei einem ankommenden Ereignis an diesem Eingang wird der aktuelle Wert des Eingangsarrays `IN` gelesen und in ein Byte umgewandelt.

### **Ereignis-Ausgänge**
*   `CNF` (Confirm): Wird ausgelöst, sobald die Konvertierung abgeschlossen ist. Dieses Ereignis signalisiert, dass der Ausgangswert (das Byte) gültig und aktuell ist.

### **Daten-Eingänge**
*   `IN` (Array[0..7] of BOOL): Das Eingabe-Array, das die acht zu konvertierenden booleschen Werte enthält. Der Index `0` entspricht dem niederwertigsten Bit (LSB, Bit 0) des resultierenden Bytes, der Index `7` dem höchstwertigen Bit (MSB, Bit 7).

### **Daten-Ausgänge**
*   `OUT` (BYTE): Der Ausgangswert, der aus den acht booleschen Eingängen zusammengesetzt ist. Der Datenausgang ist nicht explizit benannt (leerer Name in der Schnittstelle), wird aber durch den Ereignisausgang `CNF` begleitet.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Bei Empfang eines `REQ`-Ereignisses führt der Block eine bitweise Zuweisung durch. Jedes Bit des internen Ergebnisbytes (`ARR08X_TO_BYTE`) wird direkt dem entsprechenden Element des Eingabe-Arrays `IN` zugewiesen. Nach Abschluss dieser Zuweisungen wird das `CNF`-Ereignis generiert, und der berechnete Byte-Wert steht am Ausgang zur Verfügung.

Die zugrunde liegende ST-Code-Logik ist:
```
ARR08X_TO_BYTE.0 := IN[0];
ARR08X_TO_BYTE.1 := IN[1];
...
ARR08X_TO_BYTE.7 := IN[7];
```

## Technische Besonderheiten
*   **Fest verdrahtete Größe:** Der Block ist spezifisch für die Konvertierung von genau 8 booleschen Werten. Für andere Array-Größen sind andere Blöcke erforderlich.
*   **Direkte Bit-Zuordnung:** Die Abbildung ist deterministisch und erfolgt ohne jegliche arithmetische Operationen, was eine sehr schnelle und ressourcenschonende Ausführung ermöglicht.
*   **Index-Bit-Mapping:** Es ist kritisch, die Zuordnung von Array-Index zu Bit-Position im Byte zu beachten: `IN[0]` → Bit 0 (LSB), `IN[7]` → Bit 7 (MSB).

## Zustandsübersicht
Der Funktionsblock ist zustandslos (stateless). Er besitzt keinen internen Speicher zwischen den Aufrufen. Seine Ausgabe ist zu jedem Zeitpunkt ausschließlich eine direkte Funktion der aktuellen Eingangswerte beim Eintreffen des `REQ`-Ereignisses.

## Anwendungsszenarien
*   **Kommunikationsprotokolle:** Bündeln mehrerer binärer Gerätestatusse in ein einzelnes Datenbyte für die Übertragung über serielle Schnittstellen oder Feldbusse (z. B. PROFIBUS, CANopen).
*   **Speicheroptimierung:** Kompaktere Speicherung von bis zu 8 Schaltzuständen oder Alarmbedingungen in einer einzigen Byte-Variablen.
*   **SPS-interne Datenhandhabung:** Vorbereitung von Daten für Blöcke oder Funktionen, die Byte- oder Wort-Datentypen erwarten, anstatt einzelner Booles.

## ⚖️ Vergleich mit ähnlichen Bausteinen
*   **`BOOL_TO_BYTE`-Blöcke:** Viele Bibliotheken bieten Blöcke an, die acht einzelne `BOOL`-Eingänge (z. B. `IN0`...`IN7`) zu einem `BYTE` kombinieren. `ARR08X_TO_BYTE` verwendet hingegen ein Array als Eingabe, was die Verdrahtung bei vielen Signalen aus einer gemeinsamen Quelle (z. B. einem vorherigen Array-Ausgang) oft übersichtlicher gestaltet.
*   **`MERGE`/`PACK`-Blöcke:** Allgemeinere Blöcke können verschiedene Datentypen zusammenführen. `ARR08X_TO_BYTE` ist spezialisierter, einfacher und für seinen spezifischen Zweck effizienter.
*   **Bitweises Schieben (`SHL`, `OR`):** Die gleiche Funktion könnte mit einer Schleife und bitweisen Operationen in ST realisiert werden. Dieser vorgefertigte Block bietet eine standardisierte, sofort einsatzbereite und fehlerunanfälligere Lösung.

## Fazit
Der `ARR08X_TO_BYTE`-Funktionsblock ist ein einfaches, aber äußerst nützliches Werkzeug für die Signalverarbeitung in IEC 61499-Systemen. Er bietet eine elegante und performante Methode, um acht boolesche Werte aus einem Array in ein kompaktes Byte zu konvertieren. Seine klare Schnittstelle und deterministische Funktionsweise machen ihn zu einer zuverlässigen Komponente für Anwendungen in der Automatisierungstechnik, insbesondere dort, wo Daten für die Kommunikation oder platzoptimierte Speicherung aufbereitet werden müssen.